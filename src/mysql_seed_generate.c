#include "mysql_seed_generate.h"

/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
print_no_database_flag(void);

extern inline int
print_invalid_database_flag(char *const restrict flag);


/* dispatch generate mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
process_db_specs(char *restrict *const restrict db_spec,
		 char *const restrict *const restrict until_ptr)
extern inline int
generate_dispatch(char *const restrict *const restrict arg_ptr,
		  char *const restrict *const restrict until_ptr);
