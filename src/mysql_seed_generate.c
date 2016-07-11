#include "mysql_seed_generate.h"

/* GenerateCounter operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
generate_counter_reset(struct GenerateCounter *const restrict count);

/* GenerateScanState operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
generate_scan_state_reset(struct GenerateScanState *const restrict expecting);

/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
inline void
print_no_db_spec(void)

extern inline void
print_invalid_db_spec(char *restrict *const restrict from,
		      char *restrict *const restrict until,
		      const char *const restrict reason,
		      const size_t length_reason);


/* dispatch generate mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
generate_scan_specs(struct GenerateCounter *const restrict total_count,
		    char *restrict *const restrict from,
		    const char *const restrict *const restrict until);
extern inline int
generate_dispatch(char *const restrict *const restrict from,
		  char *const restrict *const restrict until);
