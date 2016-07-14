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
print_generate_failure_malloc(void);
extern inline void
print_generate_failure_no_valid_db_spec(void);

/* parsing errors (recoverable) */
extern inline void
print_expected_db_flag(char *const restrict invalid);
extern inline void
print_invalid_db_name_empty(char *const restrict *restrict db_spec_start,
			    char *const restrict *restrict invalid);
extern inline void
print_invalid_db_name_invalid(char *const restrict *restrict db_spec_start,
			      char *const restrict *restrict invalid);
extern inline void
print_invalid_db_name_long(char *const restrict *restrict db_spec_start,
			   char *const restrict *restrict invalid);
extern inline void
print_expected_tbl_flag(char *const restrict *restrict db_spec_start,
			char *const restrict *restrict invalid);
extern inline void
print_invalid_tbl_name_empty(char *const restrict *restrict db_spec_start,
			     char *const restrict *restrict invalid);
extern inline void
print_invalid_tbl_name_invalid(char *const restrict *restrict db_spec_start,
			       char *const restrict *restrict invalid);
extern inline void
print_invalid_tbl_name_long(char *const restrict *restrict db_spec_start,
			    char *const restrict *restrict invalid);
extern inline void
print_expected_col_flag(char *const restrict *restrict db_spec_start,
			char *const restrict *restrict invalid);
extern inline void
print_invalid_col_name_empty(char *const restrict *restrict db_spec_start,
			     char *const restrict *restrict invalid);
extern inline void
print_invalid_col_name_invalid(char *const restrict *restrict db_spec_start,
			       char *const restrict *restrict invalid);
extern inline void
print_invalid_col_name_long(char *const restrict *restrict db_spec_start,
			    char *const restrict *restrict invalid);
extern inline void
print_invalid_row_count_invalid(char *const restrict *restrict db_spec_start,
				char *const restrict *restrict invalid);
extern inline void
print_invalid_row_count_zero(char *const restrict *restrict db_spec_start,
			     char *const restrict *restrict invalid);
extern inline void
print_invalid_row_count_large(char *const restrict *restrict db_spec_start,
			      char *const restrict *restrict invalid);

/* parse UTF-8 identifiers from input
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
parse_db_name(struct String *const restrict db_name,
	      char *const restrict *const restrict db_spec_start,
	      char *const restrict *const restrict input);

extern inline bool
parse_tbl_name(struct String *const restrict tbl_name,
	       char *const restrict *const restrict db_spec_start,
	       char *const restrict *const restrict input);
extern inline bool
parse_col_name(struct String *const restrict col_name,
	       char *const restrict *const restrict db_spec_start,
	       char *const restrict *const restrict input);

extern inline bool
parse_row_count(size_t *const restrict row_count,
		char *const restrict *const restrict db_spec_start,
		char *const restrict *const restrict input);


extern inline void
generate_scan_specs(struct GeneratorCounter *const restrict generator_count,
		    struct DbSpec *restrict db_spec,
		    int *const restrict exit_status,
		    char *const restrict *restrict from,
		    char *const restrict *const restrict until);

/* dispatch generate mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
generate_dispatch(char *restrict *const restrict arg,
		  const int rem_argc);
