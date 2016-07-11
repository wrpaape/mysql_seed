#include "mysql_seed_generate.h"

/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
print_no_database_flag(void);

extern inline int
print_invalid_database_flag(char *const restrict flag);


/* dispatch generate mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
generate_scan_specs(struct GenerateCounter *const restrict count,
		    char *restrict *const restrict from,
		    const char *const restrict *const restrict until);
extern inline int
generate_dispatch(char *const restrict *const restrict from,
		  char *const restrict *const restrict until);
