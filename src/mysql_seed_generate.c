#include "mysql_seed_generate.h"

/* Generator/DatbaseCounter operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
database_counter_reset(struct DatabaseCounter *const restrict database);
extern inline void
generator_counter_increment(struct GeneratorCounter *const restrict generator,
			    struct DatabaseCounter *const restrict database);


/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
/* irrecoverable failures */
extern inline void
no_db_spec(void);
extern inline void
generate_failure_malloc(void);
extern inline void
generate_failure_no_valid_db_spec(void);

/* parsing errors (recoverable) */
/* DB_SPEC */
extern inline void
short_db_spec(const struct GenerateArgvState *const restrict argv);
extern inline void
expected_db_flag(char *const restrict invalid);
extern inline void
invalid_db_name_empty(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_db_name_invalid(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_db_name_long(const struct GenerateArgvState *const restrict argv);

/* TBL_SPEC */
extern inline void
expected_tbl_flag(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_tbl_name_empty(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_tbl_name_invalid(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_tbl_name_long(const struct GenerateArgvState *const restrict argv);


/* COL_SPEC */
extern inline void
expected_col_flag(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_col_name_empty(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_col_name_invalid(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_col_name_long(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_row_count_invalid(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_row_count_zero(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_row_count_large(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_col_type_invalid(const struct GenerateArgvState *const restrict argv);

/* confirm flag match
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
db_flag_match(struct GenerateArgvState *const restrict argv);

extern inline bool
tbl_flag_match(struct GenerateArgvState *const restrict argv);

extern inline bool
col_flag_match(struct GenerateArgvState *const restrict argv);


/* parse UTF-8 identifiers from input
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
parse_db_name(struct String *const restrict db_name,
	      struct GenerateArgvState *const restrict argv);

extern inline bool
parse_tbl_name(struct String *const restrict tbl_name,
	       struct GenerateArgvState *const restrict argv);

extern inline bool
parse_col_name(struct String *const restrict col_name,
	       struct GenerateArgvState *const restrict argv);


extern inline bool
parse_row_count(size_t *const restrict row_count,
		struct GenerateArgvState *const restrict argv);

/* recover from parse error
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
generate_parse_error(struct GenerateParseState *const restrict state);

/* finished parsing
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
parse_generate_complete(struct GenerateParseState *const restrict state);

/* parse spec groups
 *─────────────────────────────────────────────────────────────────────────── */
/* COL_SPEC */
extern inline void
parse_string_qualifiers(struct GenerateParseState *const restrict state);
extern inline void
parse_col_type(struct GenerateParseState *const restrict state);
extern inline void
parse_first_col_spec(struct GenerateParseState *const restrict state);
extern inline void
parse_rem_col_specs(struct GenerateParseState *const restrict state);
/* TBL_SPEC */
extern inline void
parse_rem_tbl_specs(struct GenerateParseState *const restrict state);
extern inline void
parse_first_tbl_spec(struct GenerateParseState *const restrict state);
/* DB_SPEC */
extern inline void
parse_next_db_spec(struct GenerateParseState *const restrict state);
extern inline void
parse_db_specs(struct GenerateParseState *const restrict state);


/* dispatch generate mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
generate_dispatch(char *restrict *const restrict arg,
		  const int rem_argc);
