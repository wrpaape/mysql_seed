#include "mysql_seed_execute.h"

/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
execute_failure_no_exec_spec(void);

extern inline void
execute_failure_short_exec_spec(void);

/* dispatch load mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
execute_dispatch(char *const restrict *const restrict arg_ptr,
		 const unsigned int rem_argc);
