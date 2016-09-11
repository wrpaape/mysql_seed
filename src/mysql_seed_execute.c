#include "mysql_seed_execute.h"

/* global constants
 *─────────────────────────────────────────────────────────────────────────── */
ExecuteDispatchNode *const
EXECUTE_DISPATCH_MAP[EXECUTE_DISPATH_MAP_LENGTH] = {
	[0u] = &execute_failure_no_exec_spec,
	[1u] = &execute_failure_short_exec_spec,
	[2u] = &execute_dispatch2,
	[3u] = &execute_dispatch3,
	[4u] = &execute_dispatch4,
	[5u] = &execute_dispatch5,
	[6u] = &execute_dispatch6
};



extern inline int
execute_dispatch_large(char *const restrict *restrict arg,
		       char *const restrict *const restrict until);

/* ExecuteDispatchNodes
 *─────────────────────────────────────────────────────────────────────────── */
int
execute_dispatch6(char *const restrict *restrict arg)
{
	return EXIT_FAILURE;
}

int
execute_dispatch5(char *const restrict *restrict arg)
{
	return EXIT_FAILURE;
}

int
execute_dispatch4(char *const restrict *restrict arg)
{
	return EXIT_FAILURE;
}

int
execute_dispatch3(char *const restrict *restrict arg)
{
	return EXIT_FAILURE;
}

int
execute_dispatch2(char *const restrict *restrict arg)
{

	++arg;
	puts(*arg);
	return EXIT_FAILURE;
}

/* irrecoverable failures */
int
execute_failure_short_exec_spec(char *const restrict *restrict arg)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_EXEC_SPEC_SHORT,
		     sizeof(FAILURE_EXEC_SPEC_SHORT) - 1lu);

	return EXIT_FAILURE;
}

int
execute_failure_no_exec_spec(char *const restrict *restrict arg)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_NO_EXEC_SPEC,
		     sizeof(FAILURE_NO_EXEC_SPEC) - 1lu);

	return EXIT_FAILURE;
}

/* dispatch load mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
execute_dispatch(char *const restrict *restrict arg,
		 const unsigned int rem_argc);
