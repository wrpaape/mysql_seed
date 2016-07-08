#include "mysql_seed_help.h"

extern inline void
exit_help_usage(void);

extern inline void
exit_help_generate(void);

extern inline void
exit_help_load(void);

/* print help message, return success status
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
print_help_usage(void);

extern inline int
print_help_generate(void);

extern inline int
print_help_load(void);


/* dispatch help mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
help_dispatch(char *const restrict *const restrict arg_ptr,
	      char *const restrict *const restrict until_ptr);
