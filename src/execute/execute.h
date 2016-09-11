#ifndef MYSQL_SEED_EXECUTE_EXECUTE
#define MYSQL_SEED_EXECUTE_EXECUTE

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "execute/executor.h"	/* mysql API, ExecSpec, Executor */


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define EXECUTE_FAILURE(REASON)						\
"\n" FAILURE_HEADER_WRAP("execute", " - " REASON)

#define EXECUTE_FAILURE_MALLOC						\
EXECUTE_FAILURE(MALLOC_FAILURE_REASON)



inline int
mysql_seed_execute(const struct ExecSpec *const restrict exec_spec)
{

	return EXIT_FAILURE;
}

/* worker entry point */
void
load_database(void *arg);

#endif /* ifndef MYSQL_SEED_EXECUTE_EXECUTE */
