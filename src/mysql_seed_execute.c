#include "mysql_seed_execute.h"


/* dispatch load mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
execute_dispatch(char *const restrict *const restrict arg_ptr,
		 const int rem_argc);
