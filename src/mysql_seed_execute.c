#include "mysql_seed_execute.h"

/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
generate_failure_no_exec_spec(void);

/* dispatch load mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
execute_dispatch(char *const restrict *const restrict arg_ptr,
		 const int rem_argc);
