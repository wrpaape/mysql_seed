#include "mysql_seed_help.h"

extern inline int
print_help_usage(void);

extern inline int
print_help_generate(void);

extern inline int
print_help_load(void);

extern inline void
exit_help_usage(void);

extern inline void
exit_help_generate(void);

extern inline void
exit_help_load(void);

extern inline int
help_dispatch(char *const restrict *const restrict arg_ptr,
	      char *const restrict *const restrict until_ptr);
