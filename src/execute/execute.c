#include "execute/execute.h"

/* print error
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
mysql_init_failure(MYSQL *const restrict connection);
extern inline void
mysql_real_connect_failure(MYSQL *const restrict connection);
extern inline void
mysql_real_query_failure(MYSQL *const restrict connection);


/* helper functions
 * ────────────────────────────────────────────────────────────────────────── */
inline void
load_db_path_init(char *restrict load_db_path,
		  const struct String *const restrict db_name);

extern inline int
mysql_seed_execute(const char *const restrict user,
		   const char *const restrict password,
		   const char *const restrict db_name);

extern inline int
mysql_seed_execute_multi(const struct ExecSpec *const restrict exec_spec);

/* worker entry point */
void
load_database(void *arg)
{
}
