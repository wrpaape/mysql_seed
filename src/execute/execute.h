#ifndef MYSQL_SEED_EXECUTE_EXECUTE
#define MYSQL_SEED_EXECUTE_EXECUTE

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "execute/executor.h"	/* mysql API, ExecSpec, Executor */


/* error messages
 * ────────────────────────────────────────────────────────────────────────── */
#define MYSQL_INIT_FAILURE_HEADER					\
FAILURE_HEADER_REASON("mysql_init")

#define MYSQL_REAL_CONNECT_FAILURE_HEADER				\
FAILURE_HEADER_REASON("mysql_real_connect")

#define MYSQL_REAL_QUERY_FAILURE_HEADER					\
FAILURE_HEADER_REASON("mysql_real_query")


/* macro constants
 * ────────────────────────────────────────────────────────────────────────── */
#define MYSQL_ERROR_BUFFER_SIZE 512lu

/* print error
 * ────────────────────────────────────────────────────────────────────────── */
inline void
mysql_init_failure(MYSQL *const restrict connection)
{
	char buffer[MYSQL_ERROR_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  MYSQL_INIT_FAILURE_HEADER,
			  sizeof(MYSQL_INIT_FAILURE_HEADER) - 1lu);

	ptr = put_string(ptr,
			 mysql_error(connection));

	PUT_STRING_WIDTH(ptr,
			 ERROR_CLOSE,
			 ERROR_CLOSE_WIDTH);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
mysql_real_connect_failure(MYSQL *const restrict connection)
{
	char buffer[MYSQL_ERROR_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  MYSQL_REAL_CONNECT_FAILURE_HEADER,
			  sizeof(MYSQL_REAL_CONNECT_FAILURE_HEADER) - 1lu);

	ptr = put_string(ptr,
			 mysql_error(connection));

	PUT_STRING_WIDTH(ptr,
			 ERROR_CLOSE,
			 ERROR_CLOSE_WIDTH);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
mysql_real_query_failure(MYSQL *const restrict connection)
{
	char buffer[MYSQL_ERROR_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  MYSQL_REAL_QUERY_FAILURE_HEADER,
			  sizeof(MYSQL_REAL_QUERY_FAILURE_HEADER) - 1lu);

	ptr = put_string(ptr,
			 mysql_error(connection));

	PUT_STRING_WIDTH(ptr,
			 ERROR_CLOSE,
			 ERROR_CLOSE_WIDTH);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
log_mysql_real_query_failure(struct ThreadLog *const restrict log,
			     MYSQL *const restrict connection)
{
	mutex_lock_try_catch_open(&log->lock);

	mutex_lock_muffle(&log->lock);

	thread_log_append_string_size(log,
				      MYSQL_REAL_QUERY_FAILURE_HEADER,
				      sizeof(MYSQL_REAL_QUERY_FAILURE_HEADER)
				      - 1lu);

	thread_log_append_string(log,
				 mysql_error(connection));

	thread_log_append_string_width(log,
				       ERROR_CLOSE,
				       ERROR_CLOSE_WIDTH);

	mutex_unlock_muffle(&log->lock);

	mutex_lock_try_catch_close();
}


inline void
log_execute_failure(struct ThreadLog *const restrict log,
		    const char *const restrict failure)
{
	mutex_lock_try_catch_open(&log->lock);

	mutex_lock_muffle(&log->lock);

	thread_log_append_string(log,
				 failure);

	mutex_unlock_muffle(&log->lock);

	mutex_lock_try_catch_close();
}

/* query server under lock protection
 * ────────────────────────────────────────────────────────────────────────── */
inline void
executor_do_locked_query(struct Executor *const restrict executor,
			 const struct String *const restrict query)
{
	const char *restrict failure;
	struct MysqlServer *const restrict server = &executor->server;

	mutex_lock_try_catch_open(&server->query_lock);

	if(LIKELY(mutex_lock_report(&server->query_lock,
				    &failure))) {
		if (LIKELY(mysql_real_query(server->connection,
					    query->bytes,
					    query->length) == 0)) {

			if (UNLIKELY(mutex_unlock_report(&server->query_lock,
							 &failure))) {
				log_execute_failure(&executor->log,
						    failure);
				executor->exit_status = EXIT_FAILURE;
			}
		} else {
			mutex_unlock_muffle(&server->query_lock);
			log_mysql_real_query_failure(&executor->log,
						     server->connection);
			executor->exit_status = EXIT_FAILURE;
		}
	} else {
		log_execute_failure(&executor->log,
				    failure);
		executor->exit_status = EXIT_FAILURE;
	}

	mutex_lock_try_catch_close();
}

/* worker entry point */
void
build_database(void *arg);

/* initialize worker tasks for thread pool
 * ────────────────────────────────────────────────────────────────────────── */
inline struct TaskNode *restrict
execute_init_task_nodes(struct TaskNode *restrict next_node,
			struct ExecArg *restrict exec_arg,
			struct Executor *const restrict executor,
			const struct StringInterval *const restrict db_names)
{
	struct TaskNode *restrict prev_node;

	const struct String *restrict db_name		  = db_names->from;
	const struct String *const restrict db_name_until = db_names->until;

	exec_arg->executor = executor;
	exec_arg->db_name  = db_name;

	procedure_closure_init(&next_node->task,
			       &build_database,
			       exec_arg);
	next_node->prev	= NULL;

	++db_name;

	do {
		++exec_arg;
		exec_arg->executor = executor;
		exec_arg->db_name  = db_name;

		prev_node = next_node;
		++next_node;

		procedure_closure_init(&next_node->task,
				       &build_database,
				       exec_arg);
		next_node->prev = prev_node;
		prev_node->next = next_node;

		++db_name;
	} while (db_name < db_name_until);

	next_node->next = NULL;

	return next_node;
}


/* load database(s) into server
 * ────────────────────────────────────────────────────────────────────────── */
/* load a single database into MySQL server */
inline void
execute_single(MYSQL *const restrict connection,
	       const struct String *const restrict db_name,
	       int *const restrict exit_status)
{
	struct String query;
	const char *restrict failure;

	if (query_load_report(&query,
			      db_name,
			      &failure)) {
		if (UNLIKELY(mysql_real_query(connection,
					      query.bytes,
					      query.length) != 0)) {
			mysql_real_query_failure(connection);
			*exit_status = EXIT_FAILURE;
		}

		free(query.bytes);

	} else {
		print_failure(failure);
		*exit_status = EXIT_FAILURE;
	}
}


/* load a multiple databases into MySQL server in parallel */
inline void
execute_multiple(MYSQL *const restrict connection,
		 const struct StringInterval *const restrict db_names,
		 const unsigned int count_db_names,
		 int *const restrict exit_status)
{
	struct Executor executor;

	executor.build_databases.head
	= malloc((  sizeof(struct ExecArg)
		  + sizeof(struct TaskNode)) * count_db_names);

	if (UNLIKELY(executor.build_databases.head == NULL)) {
		execute_failure_malloc();
		*exit_status = EXIT_FAILURE;
		return;
	}

	struct ExecArg *const restrict exec_args
	= (struct ExecArg *const restrict) (  executor.build_databases.head
					    + count_db_names);

	/* intialize thread pool worker tasks */
	executor.build_databases.last
	= execute_init_task_nodes(executor.build_databases.head,
				  exec_args,
				  &executor,
				  db_names);

	/* at most 1 worker for each database */
	const size_t count_workers = (count_db_names > COUNT_EXECUTOR_WORKERS)
				   ? COUNT_EXECUTOR_WORKERS
				   : count_db_names;

	/* initialize thread pool */
	thread_pool_init(&executor.pool,
			 &executor.build_databases,
			 &executor.workers[0],
			 count_workers);

	/* initialize thread log */
	thread_log_init(&executor.log,
			"executor");

	/* initialize the server */
	mutex_init(&executor.server.query_lock);
	executor.server.connection = connection;

	executor.exit_status = EXIT_SUCCESS;



	/* free alloc */
	free(executor.build_databases.head);
}


/* connect to server then dispatch loading
 * ────────────────────────────────────────────────────────────────────────── */
inline void
mysql_seed_execute(const struct MysqlCredentials *const restrict creds,
		   const struct StringInterval *const restrict db_names,
		   const unsigned int count_db_names,
		   int *const restrict exit_status)
{
	MYSQL connection;

	if (UNLIKELY(mysql_init(&connection) == NULL)) {
		mysql_init_failure(&connection);
		*exit_status = EXIT_FAILURE;

	} else {
		if (MYSQL_REAL_CONNECT(&connection,
				       creds->user,
				       creds->password.bytes) == NULL) {
			mysql_real_connect_failure(&connection);
			*exit_status = EXIT_FAILURE;

		} else if (count_db_names == 1u) {
			execute_single(&connection,
				       db_names->from,
				       exit_status);

		} else {
			execute_multiple(&connection,
					 db_names,
					 count_db_names,
					 exit_status);
		}

		mysql_close(&connection);
	}
}

#endif /* ifndef MYSQL_SEED_EXECUTE_EXECUTE */
