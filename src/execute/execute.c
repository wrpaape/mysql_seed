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
mysql_seed_execute(const struct String *const restrict db_name,
		   const char *const restrict user,
		   const char *const restrict password,
		   int *const restrict exit_status);

extern inline int
mysql_seed_execute_multi(const struct ExecSpec *const restrict exec_spec);

/* worker entry point */
void
load_database(void *arg)
{
}
