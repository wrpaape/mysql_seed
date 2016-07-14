#include "mysql_seed_load.h"


/* dispatch load mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
load_dispatch(char *const restrict *const restrict arg_ptr,
	      const int rem_argc);
