#include "execute/execute.h"

/* print error
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
mysql_init_failure(MYSQL *const restrict mysql);
extern inline void
mysql_real_connect_failure(MYSQL *const restrict mysql);
extern inline void
mysql_real_query_failure(MYSQL *const restrict mysql);
extern inline void
log_mysql_real_query_failure(struct ThreadLog *const restrict log,
			     MYSQL *const restrict mysql);

extern inline void
mysql_flush_results_failure(MYSQL *const restrict mysql);
extern inline void
log_mysql_flush_results_failure(struct ThreadLog *const restrict log,
				MYSQL *const restrict mysql);
extern inline void
mysql_next_result_failure(MYSQL *const restrict mysql);
extern inline void
log_mysql_next_result_failure(struct ThreadLog *const restrict log,
			      MYSQL *const restrict mysql);

extern inline void
log_execute_failure(struct ThreadLog *const restrict log,
		    const char *const restrict failure);
extern inline void
execute_failure_constructor(const char *const restrict failure);
extern inline void
execute_failure_destructor(const char *const restrict failure);
extern inline void
execute_failure_thread_pool(const char *const restrict failure);


/* flush results of a query
 * ────────────────────────────────────────────────────────────────────────── */
extern inline bool
mysql_flush_results(MYSQL *const restrict mysql);


/* query server under lock protection
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
executor_locked_query(struct Executor *const restrict executor,
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

		executor_locked_query(executor,
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
init_executor_task_nodes(struct TaskNode *restrict next_node,
			 struct ExecArg *restrict exec_arg,
			 struct Executor *const restrict executor,
			 const struct StringInterval *const restrict db_names);

/* wait for pool to shutdown, report any logged errors
 * ────────────────────────────────────────────────────────────────────────── */
extern inline bool
executor_shutdown(struct Executor *const restrict executor);

/* load database(s) into server
 * ────────────────────────────────────────────────────────────────────────── */
/* load a single database into MySQL server */
extern inline void
execute_single(MYSQL *const restrict mysql,
	       const struct String *const restrict db_name,
	       int *const restrict exit_status);
/* load a multiple databases into MySQL server in parallel */
extern inline void
execute_multiple(MYSQL *const restrict mysql,
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
