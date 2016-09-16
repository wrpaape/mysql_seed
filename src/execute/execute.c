#include "execute/execute.h"

/* print error
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
mysql_init_failure(MYSQL *const restrict connection);
extern inline void
mysql_real_connect_failure(MYSQL *const restrict connection);
extern inline void
mysql_real_query_failure(MYSQL *const restrict connection);
extern inline void
log_mysql_real_query_failure(struct ThreadLog *const restrict log,
			     MYSQL *const restrict connection);
extern inline void
log_execute_failure(struct ThreadLog *const restrict log,
		    const char *const restrict failure);

/* query server under lock protection
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
executor_do_locked_query(struct Executor *const restrict executor,
			 const struct String *const restrict query);

/* worker entry point */
void
build_database(void *arg)
{
	struct String query;
	const char *restrict failure;

	const struct ExecArg *const restrict exec_arg
	= (const struct ExecArg *const restrict) arg;

	struct Executor *const restrict executor
	= exec_arg->executor;

	if (query_load_report(&query,
			      exec_arg->db_name,
			      &failure)) {

		executor_do_locked_query(executor,
					 &query);

		free(query.bytes);

	} else {
		log_execute_failure(&executor->log,
				    failure);
		executor->exit_status = EXIT_FAILURE;
	}
}

/* initialize worker tasks for thread pool
 * ────────────────────────────────────────────────────────────────────────── */
extern inline struct TaskNode *restrict
execute_init_task_nodes(struct TaskNode *restrict next_node,
			struct ExecArg *restrict exec_arg,
			struct Executor *const restrict executor,
			const struct StringInterval *const restrict db_names);

/* load database(s) into server
 * ────────────────────────────────────────────────────────────────────────── */
/* load a single database into MySQL server */
extern inline void
execute_single(MYSQL *const restrict connection,
	       const struct String *const restrict db_name,
	       int *const restrict exit_status);
/* load a multiple databases into MySQL server in parallel */
extern inline void
execute_multiple(MYSQL *const restrict connection,
		 const struct StringInterval *const restrict db_names,
		 const unsigned int count_db_names,
		 int *const restrict exit_status);

/* connect to server then dispatch loading
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
mysql_seed_execute(const struct MysqlCredentials *const restrict creds,
		   const struct StringInterval *const restrict db_names,
		   const unsigned int count_db_names,
		   int *const restrict exit_status);
