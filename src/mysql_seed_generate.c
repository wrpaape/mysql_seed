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
error_no_col_type(struct GenerateParseState *const restrict state);
extern inline void
invalid_col_type(const struct GenerateArgvState *const restrict argv);
extern inline void
error_invalid_col_type(struct GenerateParseState *const restrict state);

/* GRP_SPEC */
extern inline void
invalid_grp_count_invalid(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_grp_count_zero(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_grp_count_large(const struct GenerateArgvState *const restrict argv);

/* parsing COL_TYPE_Q */
extern inline void
invalid_string_type_q(const struct GenerateArgvState *const restrict argv);
extern inline void
error_invalid_string_type_q(struct GenerateParseState *const restrict state);
extern inline void
invalid_timestamp_type_q(const struct GenerateArgvState *const restrict argv);
extern inline void
error_invalid_timestamp_type_q(struct GenerateParseState *const restrict state);
extern inline void
no_base_string(const struct GenerateArgvState *const restrict argv);
extern inline void
error_no_base_string(struct GenerateParseState *const restrict state);
extern inline void
invalid_base_string_invalid(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_base_string_long(const struct GenerateArgvState *const restrict argv);
extern inline void
no_hash_length(const struct GenerateArgvState *const restrict argv);
extern inline void
error_no_hash_length(struct GenerateParseState *const restrict state);
extern inline void
invalid_hash_length_invalid(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_hash_length_zero(const struct GenerateArgvState *const restrict argv);
extern inline void
invalid_hash_length_large(const struct GenerateArgvState *const restrict argv);

/* parsing next SPEC */
extern inline void
expected_col_spec_close(const struct GenerateArgvState *const restrict argv);
extern inline void
error_expected_col_spec_close(struct GenerateParseState *const restrict state);
extern inline void
expected_grp_spec_close(const struct GenerateArgvState *const restrict argv);
extern inline void
error_expected_grp_spec_close(struct GenerateParseState *const restrict state);
extern inline void
grp_spec_for_fixed_data(const struct GenerateArgvState *const restrict argv);
extern inline void
error_grp_spec_for_fixed_data(struct GenerateParseState *const restrict state);

/* incomplete DB_SPEC */
extern inline void
inc_db_spec_col_name(const struct GenerateArgvState *const restrict argv);
extern inline void
error_inc_db_spec_col_name(struct GenerateParseState *const restrict state);
extern inline void
inc_db_spec_tbl_name(const struct GenerateArgvState *const restrict argv);
extern inline void
error_inc_db_spec_tbl_name(struct GenerateParseState *const restrict state);
extern inline void
inc_db_spec_row_count(const struct GenerateArgvState *const restrict argv);
extern inline void
error_inc_db_spec_row_count(struct GenerateParseState *const restrict state);
extern inline void
inc_db_spec_col_flag(const struct GenerateArgvState *const restrict argv);
extern inline void
error_inc_db_spec_col_flag(struct GenerateParseState *const restrict state);

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
extern inline bool
parse_grp_count(size_t *const restrict grp_count,
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
parse_column_complete(struct GenerateParseState *const restrict state,
		      GenerateParseNode *const set_col_spec,
		      GenerateParseNode *const handle_grp_spec);


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

/* parse GRP_SPEC
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
no_grp_count(const struct GenerateArgvState *const restrict argv);
extern inline void
error_no_grp_count(struct GenerateParseState *const restrict state);
extern inline void
multiple_grp_specs(const struct GenerateArgvState *const restrict argv);
extern inline void
error_multiple_grp_specs(struct GenerateParseState *const restrict state);
extern inline void
parse_grp_spec(struct GenerateParseState *const restrict state,
	       GenerateParseNode *const set_col_spec)

/* set COL_SPEC
 *─────────────────────────────────────────────────────────────────────────── */
/* -c COL_NAME -i */
extern inline void
column_integer_default(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -u BASE_STRING */
extern inline void
column_string_unique(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -u BASE_STRING -g GRP_COUNT [PART_TYPE] */
extern inline void
column_string_unique_group(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -f BASE_STRING */
extern inline void
column_string_fixed(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -uu */
extern inline void
column_string_uuid(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -uu -g GRP_COUNT [PART_TYPE] */
extern inline void
column_string_uuid_group(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -h LENGTH_HASH */
extern inline void
column_string_hash(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -h HASH_LENGTH -g GRP_COUNT [PART_TYPE] */
extern inline void
column_string_hash_group(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -n1 */
extern inline void
column_string_names_first(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -n1 -g GRP_COUNT [PART_TYPE] */
extern inline void
column_string_names_first_group(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -nl */
extern inline void
column_string_names_last(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -nl -g GRP_COUNT [PART_TYPE] */
extern inline void
column_string_names_last_group(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -nf */
extern inline void
column_string_names_full(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -nf -g GRP_COUNT [PART_TYPE] */
extern inline void
column_string_names_full_group(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s */
extern inline void
column_string_default(struct GenerateParseState *const restrict state);
/* -c COL_NAME -s -g GRP_COUNT [PART_TYPE] */
extern inline void
column_string_default_group(struct GenerateParseState *const restrict state);

/* -c COL_NAME -ts -u */
extern inline void
column_timestamp_unique(struct GenerateParseState *const restrict state);
/* -c COL_NAME -ts -u -g GRP_COUNT [PART_TYPE] */
extern inline void
column_timestamp_unique_group(struct GenerateParseState *const restrict state);
/* -c COL_NAME -ts -f */
extern inline void
column_timestamp_fixed(struct GenerateParseState *const restrict state):
/* -c COL_NAME -ts */
extern inline void
column_timestamp_default(struct GenerateParseState *const restrict state);
/* -c COL_NAME -ts -g GRP_COUNT [PART_TYPE] */
extern inline void
column_timestamp_default_group(struct GenerateParseState *const restrict state);

/* parse COL_TYPE_Q
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
parse_string_default_group(struct GenerateParseState *const restrict state);
extern inline void
parse_string_default(struct GenerateParseState *const restrict state)
extern inline void
parse_string_unique_group(struct GenerateParseState *const restrict state);
extern inline void
parse_string_unique(struct GenerateParseState *const restrict state);
extern inline void
parse_string_fixed(struct GenerateParseState *const restrict state);
extern inline void
parse_string_uuid_group(struct GenerateParseState *const restrict state);
extern inline void
parse_string_uuid(struct GenerateParseState *const restrict state)
extern inline void
parse_string_hash_group(struct GenerateParseState *const restrict state);
extern inline void
parse_string_hash(struct GenerateParseState *const restrict state);
extern inline void
parse_string_names_first_group(struct GenerateParseState *const restrict state);
extern inline void
parse_string_names_first(struct GenerateParseState *const restrict state);
extern inline void
parse_string_names_last_group(struct GenerateParseState *const restrict state);
extern inline void
parse_string_names_last(struct GenerateParseState *const restrict state);
extern inline void
parse_string_names_full_group(struct GenerateParseState *const restrict state);
extern inline void
parse_string_names_full(struct GenerateParseState *const restrict state);
extern inline void
parse_timestamp_fixed(struct GenerateParseState *const restrict state);
extern inline void
parse_timestamp_unique_group(struct GenerateParseState *const restrict state);
extern inline void
parse_timestamp_unique(struct GenerateParseState *const restrict state);

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
