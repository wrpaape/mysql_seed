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
execute_failure_malloc(void);


extern inline void
mysql_seed_execute(const char *const restrict user,
		   const char *const restrict password,
		   const struct String *const restrict db_name,
		   int *const restrict exit_status);

extern inline int
mysql_seed_execute_multi(const struct ExecSpec *const restrict exec_spec);

/* worker entry point */
void
load_database(void *arg)
{
}
