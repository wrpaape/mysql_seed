#include "mysql_seed_help.h"

extern inline void
exit_help_usage(void);

extern inline void
exit_help_generate(void);

extern inline void
exit_help_execute(void);

/* print help message, return success status
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
help_usage(void);

extern inline int
help_generate(void);

extern inline int
help_execute(void);

/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
invalid_mode(char *const restrict mode);


/* dispatch help mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
help_dispatch(char *const restrict *const restrict arg,
	      const unsigned int rem_argc);
