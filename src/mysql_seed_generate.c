#include "mysql_seed_generate.h"

/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
/* irrecoverable failures */
extern inline void
generate_failure_no_db_spec(void);
extern inline void
generate_failure_short_db_spec(char *const restrict *const restrict from,
			       char *const restrict *const restrict until);
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
no_col_type(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_col_type_notsup(const struct GenerateArgvState *const restrict argv);

/* parsing COL_TYPE_Q */
extern inline void
invalid_col_type_q_notsup(const struct GenerateArgvState *const restrict argv);
extern inline void
no_base_string(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_base_string_invalid(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_base_string_long(const struct GenerateArgvState *const restrict argv);
extern inline void
no_hash_length(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_hash_length_invalid(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_hash_length_zero(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_hash_length_large(const struct GenerateArgvState *const restrict argv);

/* parsing next SPEC */
extern inline void
expected_col_tbl_db_flag(const struct GenerateArgvState *const restrict argv);

/* incomplete DB_SPEC */
extern inline void
incomplete_db_spec_col_name(const struct GenerateArgvState *const restrict argv);
extern inline void
incomplete_db_spec_tbl_name(const struct GenerateArgvState *const restrict argv);
extern inline void
incomplete_db_spec_row_count(const struct GenerateArgvState *const restrict argv);
extern inline void
incomplete_db_spec_col_flag(const struct GenerateArgvState *const restrict argv);

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
parse_base_string(struct String *const restrict base,
		  struct GenerateArgvState *const restrict argv);


/* parse ASCII numbers from input
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
parse_row_count(size_t *const restrict row_count,
		struct GenerateArgvState *const restrict argv);
extern inline bool
parse_hash_length(size_t *const restrict hash_length,
		  struct GenerateArgvState *const restrict argv);


/* recover from parse error
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
generate_parse_error(struct GenerateParseState *const restrict state);


/* finished parsing
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
parse_table_complete(struct GenerateParseState *const restrict state);
extern inline void
parse_valid_complete(struct GenerateParseState *const restrict state);
extern inline void
parse_database_complete(struct GenerateParseState *const restrict state);
extern inline void
generate_parse_complete(struct GenerateParseState *const restrict state);
extern inline void
parse_column_complete(struct GenerateParseState *const restrict state);


/* assign type according to MySQL data types, limits
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
type_set_char(struct Label *const restrict type,
	      const uintmax_t length);
extern inline void
type_set_char_parsed_length(struct Label *const restrict type,
			    const char *restrict length);
extern inline void
type_set_varchar(struct Label *const restrict type,
		 const uintmax_t length);
extern inline void
type_set_timestamp(struct Label *const restrict type);
extern inline void
type_set_tinyint(struct Label *const restrict type);
extern inline void
type_set_smallint(struct Label *const restrict type);
extern inline void
type_set_mediumint(struct Label *const restrict type);
extern inline void
type_set_int(struct Label *const restrict type);
extern inline void
type_set_bigint(struct Label *const restrict type);
extern inline void
type_assign_integer_unsigned(struct Label *const restrict type,
			     const uintmax_t upto);
extern inline void
type_assign_upto(struct Label *const restrict type,
		 const size_t upto);

/* set COL_SPEC
 *─────────────────────────────────────────────────────────────────────────── */
/* -c COL_NAME -i */
extern inline void
column_integer_default(struct ColSpec *const restrict col_spec,
		       const size_t row_count,
		       size_t *const restrict counter_upto);
/* -c COL_NAME -s -u BASE_STRING */
extern inline void
column_string_unique(struct ColSpec *const restrict col_spec,
		     const size_t row_count,
		     size_t *const restrict counter_upto);
/* -c COL_NAME -s -f BASE_STRING */
extern inline void
column_string_fixed(struct ColSpec *const restrict col_spec);
/* -c COL_NAME -s -uu */
extern inline void
column_string_uuid(struct ColSpec *const restrict col_spec,
		   unsigned int *const restrict ctor_flags);
/* -c COL_NAME -s -h LENGTH_HASH */
extern inline void
column_string_hash(struct ColSpec *const restrict col_spec,
		   const char *const restrict length);
/* -c COL_NAME -n1 */
extern inline void
column_string_names_first(struct ColSpec *const restrict col_spec,
			  unsigned int *const restrict ctor_flags);
/* -c COL_NAME -nl */
extern inline void
column_string_names_last(struct ColSpec *const restrict col_spec,
			 unsigned int *const restrict ctor_flags);
/* -c COL_NAME -nf */
extern inline void
column_string_names_full(struct ColSpec *const restrict col_spec,
			 unsigned int *const restrict ctor_flags);
/* -c COL_NAME -s */
extern inline void
column_string_default(struct ColSpec *const restrict col_spec,
		      const size_t row_count,
		      size_t *const restrict counter_upto);
/* -c COL_NAME -t -u */
extern inline void
column_timestamp_unique(struct ColSpec *const restrict col_spec);
/* -c COL_NAME -t -f */
extern inline void
column_timestamp_fixed(struct ColSpec *const restrict col_spec);
/* -c COL_NAME -t */
extern inline void
column_timestamp_default(struct ColSpec *const restrict col_spec);

/* parse spec groups
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
parse_integer_qualifier(struct GenerateParseState *const restrict state);
extern inline void
parse_string_qualifier(struct GenerateParseState *const restrict state);
extern inline void
parse_timestamp_qualifier(struct GenerateParseState *const restrict state);
extern inline void
parse_col_type(struct GenerateParseState *const restrict state);
extern inline void
parse_first_col_spec_safe(struct GenerateParseState *const restrict state);
extern inline void
parse_first_col_spec(struct GenerateParseState *const restrict state);
extern inline void
parse_next_col_spec(struct GenerateParseState *const restrict state);
/* TBL_SPEC */
extern inline void
parse_first_tbl_spec(struct GenerateParseState *const restrict state);
extern inline void
parse_next_tbl_spec(struct GenerateParseState *const restrict state);
/* DB_SPEC */
extern inline void
parse_first_db_spec(struct GenerateParseState *const restrict state);
extern inline void
parse_next_db_spec(struct GenerateParseState *const restrict state);
extern inline void
parse_db_specs(struct GenerateParseState *const restrict state);


/* dispatch generate mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
generate_dispatch(char *const restrict *const restrict arg,
		  const int rem_argc);
