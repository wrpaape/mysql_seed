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
EXECUTE_FAILURE("EXEC_SPEC too short - need at least "			\
		EXEC_SPEC_LENGTH_MIN_STRING " arguments to load a "	\
		"single database into MySQL using default USER with "	\
		"no PASSWORD (" EXEC_SPEC_MINIMAL ")")


/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define EXECUTE_DISPATH_MAP_LENGTH 7u


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
typedef int
ExecuteDispatchNode(char *const restrict *restrict arg);


/* global constants
 *─────────────────────────────────────────────────────────────────────────── */
extern ExecuteDispatchNode *const
EXECUTE_DISPATCH_MAP[EXECUTE_DISPATH_MAP_LENGTH];


inline int
execute_dispatch_large(char *const restrict *restrict arg,
		       char *const restrict *const restrict until)
{
	return EXIT_FAILURE;
}

/* ExecuteDispatchNodes
 *─────────────────────────────────────────────────────────────────────────── */
int
execute_dispatch6(char *const restrict *restrict arg);
int
execute_dispatch5(char *const restrict *restrict arg);
int
execute_dispatch4(char *const restrict *restrict arg);
int
execute_dispatch3(char *const restrict *restrict arg);
int
execute_dispatch2(char *const restrict *restrict arg);
/* irrecoverable failures */
int
execute_failure_short_exec_spec(char *const restrict *restrict arg);
int
execute_failure_no_exec_spec(char *const restrict *restrict arg);



/* dispatch load mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
execute_dispatch(char *const restrict *restrict arg,
		 const unsigned int rem_argc)
{
	return (rem_argc < EXECUTE_DISPATH_MAP_LENGTH)
	     ? (EXECUTE_DISPATCH_MAP[rem_argc])(arg)
	     : execute_dispatch_large(arg,
				      arg + rem_argc);
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_ */
