#include "execute/execute.h"

/* print error
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
mysql_init_failure(MYSQL *const restrict connection);
extern inline void
mysql_real_connect_failure(MYSQL *const restrict connection);
extern inline void
mysql_real_query_failure(MYSQL *const restrict connection);

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

/* worker entry point */
void
load_database(void *arg)
{
}
