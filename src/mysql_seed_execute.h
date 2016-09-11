#ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_
#define MYSQL_SEED_MYSQL_SEED_EXECUTE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "execute/execute.h"	/* execute mode */


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define FAILURE_NO_EXEC_SPEC						\
EXECUTE_FAILURE("no EXEC_SPEC provided") MORE_INFO_MESSAGE

#define FAILURE_EXEC_SPEC_SHORT						\
GENERATE_FAILURE("EXEC_SPEC too short - need at least "			\
		 EXEC_SPEC_LENGTH_MIN_STRING " arguments to load a "	\
		 "single database into MySQL using default USER with "	\
		 "no PASSWORD (" EXEC_SPEC_MINIMAL ")"


/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
/* irrecoverable failures */
inline void
execute_failure_no_exec_spec(void)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_NO_EXEC_SPEC,
		     sizeof(FAILURE_NO_EXEC_SPEC) - 1lu);
}

inline void
execute_failure_short_exec_spec(void)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_EXEC_SPEC_SHORT,
		     sizeof(FAILURE_EXEC_SPEC_SHORT) - 1lu);
}

/* parse argv
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
parse_


/* dispatch load mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
execute_dispatch(char *const restrict *const restrict arg,
		 const unsigned int rem_argc)
{
	struct ExecSpec exec_spec;


	switch (rem_argc) {
	default:

	case 2u:
		break;

	case 1u:
		generate_failure_db_spec_short();
		return EXIT_FAILURE;

	case 0u:
		generate_failure_no_db_spec();
		return EXIT_FAILURE;
	}

	return mysql_seed_execute(&exec_spec);
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_ */
