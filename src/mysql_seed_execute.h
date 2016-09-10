#ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_
#define MYSQL_SEED_MYSQL_SEED_EXECUTE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "execute/execute.h"	/* execute mode */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define FAILURE_NO_EXEC_SPEC						\
EXECUTE_FAILURE("no EXEC_SPEC provided") MORE_INFO_MESSAGE


/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
/* irrecoverable failures */
inline void
generate_failure_no_exec_spec(void);
{
	write_muffle(STDERR_FILENO,
		     FAILURE_NO_EXEC_SPEC,
		     sizeof(FAILURE_NO_EXEC_SPEC) - 1lu);
}

/* dispatch load mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
execute_dispatch(char *const restrict *const restrict arg_ptr,
		 const int rem_argc)
{
	if (rem_argc == 0lu) {
		generate_failure_no_exec_spec();
		return EXIT_FAILURE;
	}
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_ */
