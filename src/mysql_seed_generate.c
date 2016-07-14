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
/* irrecoverable failures */
extern inline void
print_no_db_spec(void);
extern inline void
print_db_spec_short(void);
extern inline void
print_generate_dispatch_malloc_failure(void);
extern inline void
print_generate_dispatch_parse_failure(void);
/* parsing DB_NAME */
extern inline void
print_invalid_db_name_empty(char *const restrict *restrict db_spec_start,
			    char *const restrict *restrict invalid);
extern inline void
print_invalid_db_name_invalid(char *const restrict *restrict db_spec_start,
			      char *const restrict *restrict invalid);
extern inline void
print_invalid_db_name_long(char *const restrict *restrict db_spec_start,
			   char *const restrict *restrict invalid);


/* dispatch generate mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
/* extern inline void */
/* generate_scan_specs(struct GeneratorCounter *const restrict generator_count, */
/* 		    struct DbSpec *restrict *restrict spec_buffer, */
/* 		    int *const restrict exit_status, */
/* 		    char *const restrict *restrict from, */
/* 		    char *const restrict *const restrict until); */
extern inline int
generate_dispatch(char *restrict *const restrict arg,
		  const int rem_argc);
