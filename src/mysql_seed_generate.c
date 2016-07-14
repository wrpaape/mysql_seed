#include "mysql_seed_generate.h"

/* Generator/DatbaseCounter operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
generator_counter_reset(struct GeneratorCounter *const restrict gen_counter);
extern inline void
database_counter_reset(struct DatabaseCounter *const restrict db_counter);
extern inline void
generator_counter_increment(struct GeneratorCounter *const restrict gen_counter,
			    struct DatabaseCounter *const restrict db_counter);


/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
print_no_db_spec(void);
extern inline void
print_invalid_db_spec(char *const restrict *const restrict from,
		      char *restrict *const restrict until,
		      const char *const restrict reason,
		      const size_t length_reason);
extern inline void
print_generate_dispatch_malloc_failure(void);
extern inline void
print_generate_dispatch_parse_failure(void);


/* dispatch generate mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
generate_scan_specs(struct GeneratorCounter *const restrict generator_count,
		    struct DbSpec *restrict *restrict spec_buffer,
		    int *const restrict exit_status,
		    char *const restrict *restrict from,
		    const char *const restrict *const restrict until);
extern inline int
generate_dispatch(char *const restrict *const restrict arg,
		  const int rem_argc)
