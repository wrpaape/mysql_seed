#ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_
#define MYSQL_SEED_MYSQL_SEED_GENERATE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/generate.h"		/* mysql_seed_generate */

/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define TINYINT_SIGNED_MIN		-128ll
#define TINYINT_SIGNED_MIN_STRING	"-128"
#define TINYINT_SIGNED_MAX		127ll
#define TINYINT_SIGNED_MAX_STRING	"127"
#define TINYINT_UNSIGNED_MAX		255llu
#define TINYINT_UNSIGNED_MAX_STRING	"255"

#define SMALLINT_SIGNED_MIN		-32768ll
#define SMALLINT_SIGNED_MIN_STRING	"-32768"
#define SMALLINT_SIGNED_MAX		32767ll
#define SMALLINT_SIGNED_MAX_STRING	"32767"
#define SMALLINT_UNSIGNED_MAX		65535llu
#define SMALLINT_UNSIGNED_MAX_STRING	"65535"

#define MEDIUMINT_SIGNED_MIN		-8388608ll
#define MEDIUMINT_SIGNED_MIN_STRING	"-8388608"
#define MEDIUMINT_SIGNED_MAX		8388607ll
#define MEDIUMINT_SIGNED_MAX_STRING	"8388607"
#define MEDIUMINT_UNSIGNED_MAX		16777215llu
#define MEDIUMINT_UNSIGNED_MAX_STRING	"16777215"

#define INT_SIGNED_MIN			-2147483648ll
#define INT_SIGNED_MIN_STRING		"-2147483648"
#define INT_SIGNED_MAX			2147483647ll
#define INT_SIGNED_MAX_STRING		"2147483647"
#define INT_UNSIGNED_MAX		4294967295llu
#define INT_UNSIGNED_MAX_STRING		"4294967295"

#define BIGINT_SIGNED_MIN		(-9223372036854775807ll - 1ll)
#define BIGINT_SIGNED_MIN_STRING	"-9223372036854775808"
#define BIGINT_SIGNED_MAX		9223372036854775807ll
#define BIGINT_SIGNED_MAX_STRING	"9223372036854775807"
#define BIGINT_UNSIGNED_MAX		18446744073709551615llu
#define BIGINT_UNSIGNED_MAX_STRING	"18446744073709551615"


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define FAILURE_NO_DB_SPEC						\
GENERATE_FAILURE("no DB_SPEC provided") MORE_INFO_MESSAGE

#define FAILURE_DB_SPEC_SHORT						\
GENERATE_FAILURE("DB_SPEC too short - need at least "			\
		 DB_SPEC_LENGTH_MIN_STRING " arguments to describe "	\
		 "a database in generate mode, ignoring DB_SPEC "	\
		 "starting with:")

#define GENERATE_FAILURE_NO_VALID_DB_SPEC				\
GENERATE_FAILURE("no valid DB_SPEC")

#define IGNORING_DB_SPEC						\
"\n" ERROR_WRAP("ignoring DB_SPEC") "\n"

#define IGNORING_DB_SPEC_STARTING_WITH					\
"\n" ERROR_WRAP("ignoring DB_SPEC starting with:") "\n"

/* parsing DB_SPEC */
#define ERROR_DB_SPEC_SHORT						\
PARSE_ERROR_MESSAGE("DB_SPEC too short - need at least "		\
		    DB_SPEC_LENGTH_MIN_STRING " arguments to describe "	\
		    "a database in generate mode, ignoring final "	\
		    "DB_SPEC starting with:")

#define ERROR_EXPECTED_DB_FLAG_HEADER					\
PARSE_ERROR_HEADER("expected DATABASE flag instead of")

#define ERROR_INC_DB_SPEC_HEADER					\
PARSE_ERROR_HEADER("incomplete DB_SPEC")

#define ERROR_INC_DB_SPEC_COL_NAME					\
"\n" ERROR_WRAP("reason: expected COL_NAME to follow COLUMN flag, "	\
		"ignoring above DB_SPEC") "\n"

#define ERROR_INC_DB_SPEC_TBL_NAME					\
"\n" ERROR_WRAP("reason: expected TBL_NAME to follow TABLE flag, "	\
		"ignoring above DB_SPEC") "\n"

#define ERROR_INC_DB_SPEC_ROW_COUNT					\
"\n" ERROR_WRAP("reason: expected ROW_COUNT to follow TBL_NAME, "	\
		"ignoring above DB_SPEC") "\n"

#define ERROR_INC_DB_SPEC_COL_FLAG					\
"\n" ERROR_WRAP("reason: expected COLUMN flag to follow ROW_COUNT, "	\
		"ignoring above DB_SPEC") "\n"

/* parsing DB_NAME */
#define ERROR_INVALID_DB_NAME_HEADER					\
PARSE_ERROR_HEADER("invalid DB_NAME")

#define ERROR_INVALID_DB_NAME_EMPTY					\
PARSE_ERROR_HEADER("invalid DB_NAME (empty), ignoring DB_SPEC starting"	\
		   " with")

#define ERROR_INVALID_DB_NAME_REASON_LONG				\
"\n" ERROR_WRAP("reason: exceeded MySql maximum of "			\
		DB_NAME_LENGTH_MAX_STRING " non-null UTF-8 codepoints,"	\
		" ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_DB_NAME_REASON_INVALID				\
"\n" ERROR_WRAP("reason: includes one or more invalid UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

/* parsing TBL_SPEC */
#define ERROR_EXPECTED_TBL_FLAG_HEADER					\
PARSE_ERROR_HEADER("expected TABLE flag instead of")

/* parsing TBL_NAME */
#define ERROR_INVALID_TBL_NAME_HEADER					\
PARSE_ERROR_HEADER("invalid TBL_NAME")

#define ERROR_INVALID_TBL_NAME_EMPTY					\
PARSE_ERROR_HEADER("invalid TBL_NAME (empty), ignoring DB_SPEC "	\
		   "starting with")

#define ERROR_INVALID_TBL_NAME_REASON_LONG				\
"\n" ERROR_WRAP("reason: exceeded MySql maximum of "			\
		TBL_NAME_LENGTH_MAX_STRING " non-null UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_TBL_NAME_REASON_INVALID				\
"\n" ERROR_WRAP("reason: includes one or more invalid UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

/* parsing COL_SPEC */
#define ERROR_EXPECTED_COL_FLAG_HEADER					\
PARSE_ERROR_HEADER("expected COLUMN flag instead of")

/* parsing COL_NAME */
#define ERROR_INVALID_COL_NAME_HEADER					\
PARSE_ERROR_HEADER("invalid COL_NAME")

#define ERROR_INVALID_COL_NAME_EMPTY					\
PARSE_ERROR_HEADER("invalid COL_NAME (empty), ignoring DB_SPEC "	\
		   "starting with")

#define ERROR_INVALID_COL_NAME_REASON_LONG				\
"\n" ERROR_WRAP("reason: exceeded MySql maximum of "			\
		COL_NAME_LENGTH_MAX_STRING " non-null UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_COL_NAME_REASON_INVALID				\
"\n" ERROR_WRAP("reason: includes one or more invalid UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

/* parsing ROW_COUNT */
#define ERROR_INVALID_ROW_COUNT_HEADER					\
PARSE_ERROR_HEADER("invalid ROW_COUNT")

#define ERROR_INVALID_ROW_COUNT_REASON_INVALID				\
"\n" ERROR_WRAP("reason: not an integer or overflows implementation-"	\
		"defined uintmax_t, ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_ROW_COUNT_REASON_ZERO				\
"\n" ERROR_WRAP("reason: ROW_COUNT must be ≥ 1, ignoring DB_SPEC "	\
		"starting with:") "\n"

#define ERROR_INVALID_ROW_COUNT_REASON_LARGE				\
"\n" ERROR_WRAP("reason: ROW_COUNT exceeds the system-Dependent "	\
		"constant UPTO_MAX (" UPTO_MAX_STRING "), ignoring "	\
		"DB_SPEC starting with:") "\n"

/* parsing COL_TYPE */
#define ERROR_NO_COL_TYPE						\
PARSE_ERROR_HEADER("no COL_TYPE provided, ignoring DB_SPEC starting "	\
		   "with")

#define ERROR_INVALID_COL_TYPE_HEADER					\
PARSE_ERROR_HEADER("invalid COL_TYPE")

#define ERROR_INVALID_COL_TYPE_REASON_NOTSUP				\
"\n" ERROR_WRAP("reason: not supported, ignoring DB_SPEC starting "	\
		"with:") "\n"

/* parsing COL_TYPE_Q */
#define ERROR_INVALID_COL_TYPE_Q_HEADER					\
PARSE_ERROR_HEADER("invalid COL_TYPE_Q")

#define ERROR_INVALID_I_TYPE_Q_REASON_NOTSUP				\
"\n" ERROR_WRAP("reason: not supported for COL_TYPE 'integer', "	\
		"ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_S_TYPE_Q_REASON_NOTSUP				\
"\n" ERROR_WRAP("reason: not supported for COL_TYPE 'string', ignoring"	\
		" DB_SPEC starting with:") "\n"

#define ERROR_INVALID_TS_TYPE_Q_REASON_NOTSUP				\
"\n" ERROR_WRAP("reason: not supported for COL_TYPE 'timestamp', "	\
		"ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_DT_TYPE_Q_REASON_NOTSUP				\
"\n" ERROR_WRAP("reason: not supported for COL_TYPE 'datetime', "	\
		"ignoring DB_SPEC starting with:") "\n"

#define ERROR_NO_FIXED_INTEGER						\
PARSE_ERROR_HEADER("no FIXED_INT provided, ignoring DB_SPEC starting "	\
		   "with")

#define ERROR_INVALID_FIXED_INTEGER_HEADER				\
PARSE_ERROR_HEADER("invalid FIXED_INT")

#define ERROR_INVALID_FIXED_INTEGER_REASON_INVALID			\
"\n" ERROR_WRAP("reason: not an integer or overflows implementation-"	\
		"defined intmax_t, ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_FIXED_INTEGER_REASON_SMALL			\
"\n" ERROR_WRAP("reason: FIXED_INT exceeds MySQL lower limit "		\
		"BIGINT_SIGNED_MIN (" BIGINT_SIGNED_MIN_STRING "), "	\
		"ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_FIXED_INTEGER_REASON_LARGE			\
"\n" ERROR_WRAP("reason: FIXED_INT exceeds MySQL upper limit "		\
		"BIGINT_SIGNED_MAX (" BIGINT_SIGNED_MAX_STRING "), "	\
		"ignoring DB_SPEC starting with:") "\n"

#define ERROR_NO_FIXED_U_INTEGER					\
PARSE_ERROR_HEADER("no FIXED_INT provided, ignoring DB_SPEC starting "	\
		   "with")

#define ERROR_INVALID_FIXED_U_INTEGER_HEADER				\
PARSE_ERROR_HEADER("invalid FIXED_UINT")

#define ERROR_INVALID_FIXED_U_INTEGER_REASON_INVALID			\
"\n" ERROR_WRAP("reason: not an integer or overflows implementation-"	\
		"defined uintmax_t, ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_FIXED_U_INTEGER_REASON_LARGE			\
"\n" ERROR_WRAP("reason: FIXED_UINT exceeds MySQL upper limit "		\
		"BIGINT_UNSIGNED_MAX (" BIGINT_UNSIGNED_MAX_STRING ")"	\
		", ignoring DB_SPEC starting with:") "\n"

#define ERROR_NO_BASE_STRING						\
PARSE_ERROR_HEADER("no column base string provided, ignoring DB_SPEC "	\
		   "starting with")

#define ERROR_INVALID_BASE_STRING_HEADER				\
PARSE_ERROR_HEADER("invalid column base string")

#define ERROR_INVALID_BASE_STRING_REASON_INVALID			\
"\n" ERROR_WRAP("reason: includes one or more invalid UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_BASE_STRING_REASON_LONG				\
"\n" ERROR_WRAP("reason: exceeded maximum of "				\
		BASE_STRING_LENGTH_MAX_STRING " non-null UTF-8 "	\
		"codepoints, ignoring DB_SPEC starting with:") "\n"

#define ERROR_NO_FIXED_STRING						\
PARSE_ERROR_HEADER("no column fixed string provided, ignoring DB_SPEC "	\
		   "starting with")

#define ERROR_INVALID_FIXED_STRING_HEADER				\
PARSE_ERROR_HEADER("invalid column fixed string")

#define ERROR_INVALID_FIXED_STRING_REASON_INVALID			\
"\n" ERROR_WRAP("reason: includes one or more invalid UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_FIXED_STRING_REASON_LONG				\
"\n" ERROR_WRAP("reason: exceeded maximum of "				\
		FIXED_STRING_LENGTH_MAX_STRING " non-null UTF-8 "	\
		"codepoints, ignoring DB_SPEC starting with:") "\n"

#define ERROR_NO_HASH_LENGTH						\
PARSE_ERROR_HEADER("no HASH_LENGTH provided, ignoring DB_SPEC starting"	\
		   " with")

#define ERROR_INVALID_HASH_LENGTH_HEADER				\
PARSE_ERROR_HEADER("invalid HASH_LENGTH")

#define ERROR_INVALID_HASH_LENGTH_REASON_INVALID			\
"\n" ERROR_WRAP("reason: not an integer or overflows implementation-"	\
		"defined uintmax_t, ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_HASH_LENGTH_REASON_ZERO				\
"\n" ERROR_WRAP("reason: HASH_LENGTH must be ≥ 1, ignoring DB_SPEC "	\
		"starting with:") "\n"

#define ERROR_INVALID_HASH_LENGTH_REASON_LARGE				\
"\n" ERROR_WRAP("reason: HASH_LENGTH exceeds upper limit "		\
		"HASH_LENGTH_MAX (" HASH_LENGTH_MAX_STRING "), "	\
		"ignoring DB_SPEC starting with:") "\n"

/* parsing RAND_SPEC */
#define ERROR_INVALID_RAND_SPEC_HEADER					\
PARSE_ERROR_HEADER("invalid RAND_SPEC")

#define ERROR_INVALID_RAND_SPEC_REASON_NOTSUP				\
"\n" ERROR_WRAP("reason: not supported, ignoring DB_SPEC starting "	\
		"with:") "\n"

/* parsing GRP_SPEC */
#define ERROR_INVALID_GRP_COUNT_HEADER					\
PARSE_ERROR_HEADER("invalid GRP_COUNT")

#define ERROR_INVALID_GRP_COUNT_REASON_INVALID				\
"\n" ERROR_WRAP("reason: not an integer or overflows implementation-"	\
		"defined uintmax_t, ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_GRP_COUNT_REASON_ZERO				\
"\n" ERROR_WRAP("reason: GRP_COUNT must be ≥ 1, ignoring DB_SPEC "	\
		"starting with:") "\n"

#define ERROR_INVALID_GRP_COUNT_REASON_LARGE				\
"\n" ERROR_WRAP("reason: GRP_COUNT exceeds table ROW_COUNT, ignoring "	\
		"DB_SPEC starting with:") "\n"

#define ERROR_NO_GRP_COUNT						\
PARSE_ERROR_HEADER("no GRP_COUNT provided, ignoring DB_SPEC starting "	\
		   "with")

#define ERROR_MULTIPLE_GRP_SPECS					\
PARSE_ERROR_HEADER("may have no more than 1 GRP_SPEC per column, "	\
		   "ignoring DB_SPEC starting with")

#define ERROR_GRP_SPEC_FOR_FIXED_DATA					\
PARSE_ERROR_HEADER("cannot have GRP_SPEC for fixed column data, "	\
		   "ignoring DB_SPEC starting with")

/* parsing next SPEC */
#define ERROR_EXPECTED_COL_SPEC_CLOSE_HEADER				\
PARSE_ERROR_HEADER("expected GROUP flag, COLUMN flag, TABLE flag, "	\
		   "DATABASE flag, or end of arguments instead of")

#define ERROR_EXPECTED_GRP_SPEC_CLOSE_HEADER				\
PARSE_ERROR_HEADER("expected PART_TYPE, COLUMN flag, TABLE flag, "	\
		   "DATABASE flag, or end of arguments instead of")


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct ValidDbSpecQueue {
	struct DbSpec **last;
	struct DbSpec *head;
};

struct GenerateSpecState {
	struct DbSpec  *db;
	struct TblSpec *tbl;
	struct ColSpec *col;
};

struct GenerateArgvState {
	struct ArgvInterval arg;
	struct ArgvInterval db_spec;
	const char *restrict cache;
};

struct GenerateParseState {
	struct GenerateArgvState argv;
	struct GenerateSpecState specs;
	struct GeneratorCounter generator;
	struct DatabaseCounter database;
	struct ValidDbSpecQueue valid;
	int exit_status;
};

typedef void
GenerateParseNode(struct GenerateParseState *const restrict state);


/* make compiler happy
 *─────────────────────────────────────────────────────────────────────────── */
inline void
parse_next_col_spec(struct GenerateParseState *const restrict state);
inline void
parse_next_db_spec(struct GenerateParseState *const restrict state);
inline void
parse_next_tbl_spec(struct GenerateParseState *const restrict state);
inline void
generate_parse_error(struct GenerateParseState *const restrict state);


/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
/* irrecoverable failures */
inline void
generate_failure_no_db_spec(void)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_NO_DB_SPEC,
		     sizeof(FAILURE_NO_DB_SPEC) - 1lu);
}

inline void
generate_failure_short_db_spec(char *const restrict *const restrict from,
			       char *const restrict *const restrict until)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  FAILURE_DB_SPEC_SHORT,
			  sizeof(FAILURE_DB_SPEC_SHORT) - 1);


	ptr = put_inspect_args(ptr,
			       from,
			       until - 1l);

	*ptr = '\n';

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr + 1l - &buffer[0]);
}

inline void
generate_failure_no_valid_db_spec(void)
{
	write_muffle(STDERR_FILENO,
		     GENERATE_FAILURE_NO_VALID_DB_SPEC,
		     sizeof(GENERATE_FAILURE_NO_VALID_DB_SPEC) - 1lu);

}

/* parsing errors (recoverable) */
/* DB_SPEC */
inline void
short_db_spec(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_DB_SPEC_SHORT,
			  sizeof(ERROR_DB_SPEC_SHORT) - 1);

	ptr = put_inspect_args(ptr,
			       argv->arg.from,
			       argv->arg.until - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
expected_db_flag(char *const restrict invalid)
{
	char buffer[ARG_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_EXPECTED_DB_FLAG_HEADER,
			  sizeof(ERROR_EXPECTED_DB_FLAG_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 invalid,
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      IGNORING_DB_SPEC,
			      sizeof(IGNORING_DB_SPEC) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_db_name_empty(const struct GenerateArgvState *const restrict argv)

{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_DB_NAME_EMPTY,
			  sizeof(ERROR_INVALID_DB_NAME_EMPTY) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);


	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_db_name_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_DB_NAME_HEADER,
			  sizeof(ERROR_INVALID_DB_NAME_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_DB_NAME_REASON_INVALID,
			      sizeof(ERROR_INVALID_DB_NAME_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_db_name_long(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_DB_NAME_HEADER,
			  sizeof(ERROR_INVALID_DB_NAME_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_DB_NAME_REASON_LONG,
			      sizeof(ERROR_INVALID_DB_NAME_REASON_LONG)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


/* TBL_SPEC */
inline void
expected_tbl_flag(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_EXPECTED_TBL_FLAG_HEADER,
			  sizeof(ERROR_EXPECTED_TBL_FLAG_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      IGNORING_DB_SPEC_STARTING_WITH,
			      sizeof(IGNORING_DB_SPEC_STARTING_WITH) - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_tbl_name_empty(const struct GenerateArgvState *const restrict argv)

{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_TBL_NAME_EMPTY,
			  sizeof(ERROR_INVALID_TBL_NAME_EMPTY) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_tbl_name_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_TBL_NAME_HEADER,
			  sizeof(ERROR_INVALID_TBL_NAME_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_TBL_NAME_REASON_INVALID,
			      sizeof(ERROR_INVALID_TBL_NAME_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_tbl_name_long(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_TBL_NAME_HEADER,
			  sizeof(ERROR_INVALID_TBL_NAME_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_TBL_NAME_REASON_LONG,
			      sizeof(ERROR_INVALID_TBL_NAME_REASON_LONG)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

/* COL_SPEC */
inline void
expected_col_flag(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_EXPECTED_COL_FLAG_HEADER,
			  sizeof(ERROR_EXPECTED_COL_FLAG_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      IGNORING_DB_SPEC_STARTING_WITH,
			      sizeof(IGNORING_DB_SPEC_STARTING_WITH) - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_col_name_empty(const struct GenerateArgvState *const restrict argv)

{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_COL_NAME_EMPTY,
			  sizeof(ERROR_INVALID_COL_NAME_EMPTY) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_col_name_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_COL_NAME_HEADER,
			  sizeof(ERROR_INVALID_COL_NAME_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_COL_NAME_REASON_INVALID,
			      sizeof(ERROR_INVALID_COL_NAME_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_col_name_long(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_COL_NAME_HEADER,
			  sizeof(ERROR_INVALID_COL_NAME_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_COL_NAME_REASON_LONG,
			      sizeof(ERROR_INVALID_COL_NAME_REASON_LONG)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


inline void
invalid_row_count_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_ROW_COUNT_HEADER,
			  sizeof(ERROR_INVALID_ROW_COUNT_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_ROW_COUNT_REASON_INVALID,
			      sizeof(ERROR_INVALID_ROW_COUNT_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


inline void
invalid_row_count_zero(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_ROW_COUNT_HEADER,
			  sizeof(ERROR_INVALID_ROW_COUNT_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_ROW_COUNT_REASON_ZERO,
			      sizeof(ERROR_INVALID_ROW_COUNT_REASON_ZERO)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


inline void
invalid_row_count_large(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_ROW_COUNT_HEADER,
			  sizeof(ERROR_INVALID_ROW_COUNT_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_ROW_COUNT_REASON_LARGE,
			      sizeof(ERROR_INVALID_ROW_COUNT_REASON_LARGE)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


inline void
no_col_type(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_NO_COL_TYPE,
			  sizeof(ERROR_NO_COL_TYPE) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_no_col_type(struct GenerateParseState *const restrict state)
{
	no_col_type(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}

inline void
invalid_col_type(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_COL_TYPE_HEADER,
			  sizeof(ERROR_INVALID_COL_TYPE_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_COL_TYPE_REASON_NOTSUP,
			      sizeof(ERROR_INVALID_COL_TYPE_REASON_NOTSUP)
			      - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_col_type(struct GenerateParseState *const restrict state)
{
	invalid_col_type(&state->argv);
	generate_parse_error(state);
}


/* RAND_SPEC */
inline void
invalid_rand_spec(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_RAND_SPEC_HEADER,
			  sizeof(ERROR_INVALID_RAND_SPEC_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_RAND_SPEC_REASON_NOTSUP,
			      sizeof(ERROR_INVALID_RAND_SPEC_REASON_NOTSUP)
			      - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_rand_spec(struct GenerateParseState *const restrict state)
{
	invalid_rand_spec(&state->argv);
	generate_parse_error(state);
}


/* GRP_SPEC */
inline void
invalid_grp_count_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_GRP_COUNT_HEADER,
			  sizeof(ERROR_INVALID_GRP_COUNT_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_GRP_COUNT_REASON_INVALID,
			      sizeof(ERROR_INVALID_GRP_COUNT_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


inline void
invalid_grp_count_zero(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_GRP_COUNT_HEADER,
			  sizeof(ERROR_INVALID_GRP_COUNT_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_GRP_COUNT_REASON_ZERO,
			      sizeof(ERROR_INVALID_GRP_COUNT_REASON_ZERO)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


inline void
invalid_grp_count_large(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_GRP_COUNT_HEADER,
			  sizeof(ERROR_INVALID_GRP_COUNT_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_GRP_COUNT_REASON_LARGE,
			      sizeof(ERROR_INVALID_GRP_COUNT_REASON_LARGE)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


/* parsing COL_TYPE_Q */
inline void
invalid_integer_type_q(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_COL_TYPE_Q_HEADER,
			  sizeof(ERROR_INVALID_COL_TYPE_Q_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_I_TYPE_Q_REASON_NOTSUP,
			      sizeof(ERROR_INVALID_I_TYPE_Q_REASON_NOTSUP)
			      - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_integer_type_q(struct GenerateParseState *const restrict state)
{
	invalid_integer_type_q(&state->argv);
	generate_parse_error(state);
}

inline void
invalid_string_type_q(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_COL_TYPE_Q_HEADER,
			  sizeof(ERROR_INVALID_COL_TYPE_Q_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_S_TYPE_Q_REASON_NOTSUP,
			      sizeof(ERROR_INVALID_S_TYPE_Q_REASON_NOTSUP)
			      - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_string_type_q(struct GenerateParseState *const restrict state)
{
	invalid_string_type_q(&state->argv);
	generate_parse_error(state);
}

inline void
invalid_timestamp_type_q(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_COL_TYPE_Q_HEADER,
			  sizeof(ERROR_INVALID_COL_TYPE_Q_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_TS_TYPE_Q_REASON_NOTSUP,
			      sizeof(ERROR_INVALID_TS_TYPE_Q_REASON_NOTSUP)
			      - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_timestamp_type_q(struct GenerateParseState *const restrict state)
{
	invalid_timestamp_type_q(&state->argv);
	generate_parse_error(state);
}

inline void
invalid_datetime_type_q(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_COL_TYPE_Q_HEADER,
			  sizeof(ERROR_INVALID_COL_TYPE_Q_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_DT_TYPE_Q_REASON_NOTSUP,
			      sizeof(ERROR_INVALID_DT_TYPE_Q_REASON_NOTSUP)
			      - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_datetime_type_q(struct GenerateParseState *const restrict state)
{
	invalid_datetime_type_q(&state->argv);
	generate_parse_error(state);
}


inline void
no_fixed_integer(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_NO_FIXED_INTEGER,
			  sizeof(ERROR_NO_FIXED_INTEGER) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_no_fixed_integer(struct GenerateParseState *const restrict state)
{
	no_fixed_integer(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}

inline void
invalid_fixed_integer_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_FIXED_INTEGER_HEADER,
			  sizeof(ERROR_INVALID_FIXED_INTEGER_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_FIXED_INTEGER_REASON_INVALID,
			      sizeof(ERROR_INVALID_FIXED_INTEGER_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_fixed_integer_invalid(struct GenerateParseState *const restrict state)
{
	invalid_fixed_integer_invalid(&state->argv);
	generate_parse_error(state);
}

inline void
invalid_fixed_integer_small(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_FIXED_INTEGER_HEADER,
			  sizeof(ERROR_INVALID_FIXED_INTEGER_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_FIXED_INTEGER_REASON_SMALL,
			      sizeof(ERROR_INVALID_FIXED_INTEGER_REASON_SMALL)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_fixed_integer_small(struct GenerateParseState *const restrict state)
{
	invalid_fixed_integer_small(&state->argv);
	generate_parse_error(state);
}

inline void
invalid_fixed_integer_large(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_FIXED_INTEGER_HEADER,
			  sizeof(ERROR_INVALID_FIXED_INTEGER_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_FIXED_INTEGER_REASON_LARGE,
			      sizeof(ERROR_INVALID_FIXED_INTEGER_REASON_LARGE)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_fixed_integer_large(struct GenerateParseState *const restrict state)
{
	invalid_fixed_integer_large(&state->argv);
	generate_parse_error(state);
}

inline void
no_fixed_u_integer(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_NO_FIXED_U_INTEGER,
			  sizeof(ERROR_NO_FIXED_U_INTEGER) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_no_fixed_u_integer(struct GenerateParseState *const restrict state)
{
	no_fixed_u_integer(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}

inline void
invalid_fixed_u_integer_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_FIXED_U_INTEGER_HEADER,
			  sizeof(ERROR_INVALID_FIXED_U_INTEGER_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_FIXED_U_INTEGER_REASON_INVALID,
			      sizeof(ERROR_INVALID_FIXED_U_INTEGER_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_fixed_u_integer_invalid(struct GenerateParseState *const restrict state)
{
	invalid_fixed_u_integer_invalid(&state->argv);
	generate_parse_error(state);
}

inline void
invalid_fixed_u_integer_large(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_FIXED_U_INTEGER_HEADER,
			  sizeof(ERROR_INVALID_FIXED_U_INTEGER_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_FIXED_U_INTEGER_REASON_LARGE,
			      sizeof(ERROR_INVALID_FIXED_U_INTEGER_REASON_LARGE)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_invalid_fixed_u_integer_large(struct GenerateParseState *const restrict state)
{
	invalid_fixed_u_integer_large(&state->argv);
	generate_parse_error(state);
}

inline void
no_base_string(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_NO_BASE_STRING,
			  sizeof(ERROR_NO_BASE_STRING) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_no_base_string(struct GenerateParseState *const restrict state)
{
	no_base_string(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}


inline void
invalid_base_string_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_BASE_STRING_HEADER,
			  sizeof(ERROR_INVALID_BASE_STRING_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_BASE_STRING_REASON_INVALID,
			      sizeof(ERROR_INVALID_BASE_STRING_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_base_string_long(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_BASE_STRING_HEADER,
			  sizeof(ERROR_INVALID_BASE_STRING_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_BASE_STRING_REASON_LONG,
			      sizeof(ERROR_INVALID_BASE_STRING_REASON_LONG)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
no_fixed_string(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_NO_FIXED_STRING,
			  sizeof(ERROR_NO_FIXED_STRING) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_no_fixed_string(struct GenerateParseState *const restrict state)
{
	no_fixed_string(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}

inline void
invalid_fixed_string_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_FIXED_STRING_HEADER,
			  sizeof(ERROR_INVALID_FIXED_STRING_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_FIXED_STRING_REASON_INVALID,
			      sizeof(ERROR_INVALID_FIXED_STRING_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_fixed_string_long(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_FIXED_STRING_HEADER,
			  sizeof(ERROR_INVALID_FIXED_STRING_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_FIXED_STRING_REASON_LONG,
			      sizeof(ERROR_INVALID_FIXED_STRING_REASON_LONG)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
no_hash_length(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_NO_HASH_LENGTH,
			  sizeof(ERROR_NO_HASH_LENGTH) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_no_hash_length(struct GenerateParseState *const restrict state)
{
	no_hash_length(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}

inline void
invalid_hash_length_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_HASH_LENGTH_HEADER,
			  sizeof(ERROR_INVALID_HASH_LENGTH_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_HASH_LENGTH_REASON_INVALID,
			      sizeof(ERROR_INVALID_HASH_LENGTH_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_hash_length_zero(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_HASH_LENGTH_HEADER,
			  sizeof(ERROR_INVALID_HASH_LENGTH_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_HASH_LENGTH_REASON_ZERO,
			      sizeof(ERROR_INVALID_HASH_LENGTH_REASON_ZERO)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_hash_length_large(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INVALID_HASH_LENGTH_HEADER,
			  sizeof(ERROR_INVALID_HASH_LENGTH_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_HASH_LENGTH_REASON_LARGE,
			      sizeof(ERROR_INVALID_HASH_LENGTH_REASON_LARGE)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
expected_col_spec_close(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_EXPECTED_COL_SPEC_CLOSE_HEADER,
			  sizeof(ERROR_EXPECTED_COL_SPEC_CLOSE_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      IGNORING_DB_SPEC_STARTING_WITH,
			      sizeof(IGNORING_DB_SPEC_STARTING_WITH) - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_expected_col_spec_close(struct GenerateParseState *const restrict state)
{
	expected_col_spec_close(&state->argv);
	generate_parse_error(state);
}

inline void
expected_grp_spec_close(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_EXPECTED_GRP_SPEC_CLOSE_HEADER,
			  sizeof(ERROR_EXPECTED_GRP_SPEC_CLOSE_HEADER) - 1);

	ptr = put_string_inspect(ptr,
				 *(argv->arg.from),
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      IGNORING_DB_SPEC_STARTING_WITH,
			      sizeof(IGNORING_DB_SPEC_STARTING_WITH) - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_expected_grp_spec_close(struct GenerateParseState *const restrict state)
{
	expected_grp_spec_close(&state->argv);
	generate_parse_error(state);
}

inline void
grp_spec_for_fixed_data(const struct GenerateArgvState *const restrict argv)
{

	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_GRP_SPEC_FOR_FIXED_DATA,
			  sizeof(ERROR_GRP_SPEC_FOR_FIXED_DATA) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_grp_spec_for_fixed_data(struct GenerateParseState *const restrict state)
{
	grp_spec_for_fixed_data(&state->argv);
	generate_parse_error(state);
}

/* incomplete DB_SPEC */
inline void
inc_db_spec_col_name(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INC_DB_SPEC_HEADER,
			  sizeof(ERROR_INC_DB_SPEC_HEADER) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	ptr = put_string_size(ptr,
			      ERROR_INC_DB_SPEC_COL_NAME,
			      sizeof(ERROR_INC_DB_SPEC_COL_NAME) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_inc_db_spec_col_name(struct GenerateParseState *const restrict state)
{
	inc_db_spec_col_name(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}

inline void
inc_db_spec_tbl_name(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INC_DB_SPEC_HEADER,
			  sizeof(ERROR_INC_DB_SPEC_HEADER) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	ptr = put_string_size(ptr,
			      ERROR_INC_DB_SPEC_TBL_NAME,
			      sizeof(ERROR_INC_DB_SPEC_TBL_NAME) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_inc_db_spec_tbl_name(struct GenerateParseState *const restrict state)
{
	inc_db_spec_tbl_name(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}

inline void
inc_db_spec_row_count(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INC_DB_SPEC_HEADER,
			  sizeof(ERROR_INC_DB_SPEC_HEADER) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	ptr = put_string_size(ptr,
			      ERROR_INC_DB_SPEC_ROW_COUNT,
			      sizeof(ERROR_INC_DB_SPEC_ROW_COUNT) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_inc_db_spec_row_count(struct GenerateParseState *const restrict state)
{
	inc_db_spec_row_count(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}


inline void
inc_db_spec_col_flag(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_INC_DB_SPEC_HEADER,
			  sizeof(ERROR_INC_DB_SPEC_HEADER) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	ptr = put_string_size(ptr,
			      ERROR_INC_DB_SPEC_COL_FLAG,
			      sizeof(ERROR_INC_DB_SPEC_COL_FLAG) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_inc_db_spec_col_flag(struct GenerateParseState *const restrict state)
{
	inc_db_spec_col_flag(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}


/* confirm flag match
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
db_flag_match(struct GenerateArgvState *const restrict argv)
{
	const bool matched_db_flag = flag_match(*(argv->arg.from),
						'd',
						"database");

	if (matched_db_flag)
		argv->db_spec.from = argv->arg.from;
	else
		expected_db_flag(*(argv->arg.from));

	return matched_db_flag;
}

inline bool
tbl_flag_match(struct GenerateArgvState *const restrict argv)
{
	const bool matched_tbl_flag = flag_match(*(argv->arg.from),
					       't',
					       "table");

	if (!matched_tbl_flag)
		expected_tbl_flag(argv);

	return matched_tbl_flag;
}

inline bool
col_flag_match(struct GenerateArgvState *const restrict argv)
{
	const bool matched_col_flag = flag_match(*(argv->arg.from),
					       'c',
					       "column");

	if (!matched_col_flag)
		expected_col_flag(argv);

	return matched_col_flag;
}


/* parse UTF-8 identifiers from input
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
parse_db_name(struct String *const restrict db_name,
	      struct GenerateArgvState *const restrict argv)
{
	const octet_t *restrict octets
	= (const octet_t *restrict) *(argv->arg.from);

	if (*octets == '\0') {
		invalid_db_name_empty(argv);
		return false;
	}

	unsigned int width;

	size_t rem_code_points = DB_NAME_LENGTH_MAX;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u) {
			invalid_db_name_invalid(argv);
			return false;
		}

		octets += width;

		if (*octets == '\0') {
			db_name->bytes  = *(argv->arg.from);
			db_name->length = octets
					- ((const octet_t *const restrict)
					   db_name->bytes);
			return true;
		}

		--rem_code_points;

		if (rem_code_points == 0lu) {
			invalid_db_name_long(argv);
			return false;
		}
	}
}


inline bool
parse_tbl_name(struct String *const restrict tbl_name,
	      struct GenerateArgvState *const restrict argv)
{
	const octet_t *restrict octets
	= (const octet_t *restrict) *(argv->arg.from);

	if (*octets == '\0') {
		invalid_tbl_name_empty(argv);
		return false;
	}

	unsigned int width;

	size_t rem_code_points = TBL_NAME_LENGTH_MAX;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u) {
			invalid_tbl_name_invalid(argv);
			return false;
		}

		octets += width;

		if (*octets == '\0') {
			tbl_name->bytes  = *(argv->arg.from);
			tbl_name->length = octets
					- ((const octet_t *const restrict)
					   tbl_name->bytes);
			return true;
		}

		--rem_code_points;

		if (rem_code_points == 0lu) {
			invalid_tbl_name_long(argv);
			return false;
		}
	}
}


inline bool
parse_col_name(struct String *const restrict col_name,
	      struct GenerateArgvState *const restrict argv)
{
	const octet_t *restrict octets
	= (const octet_t *restrict) *(argv->arg.from);

	if (*octets == '\0') {
		invalid_col_name_empty(argv);
		return false;
	}

	unsigned int width;

	size_t rem_code_points = COL_NAME_LENGTH_MAX;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u) {
			invalid_col_name_invalid(argv);
			return false;
		}

		octets += width;

		if (*octets == '\0') {
			col_name->bytes  = *(argv->arg.from);
			col_name->length = octets
					- ((const octet_t *const restrict)
					   col_name->bytes);
			return true;
		}

		--rem_code_points;

		if (rem_code_points == 0lu) {
			invalid_col_name_long(argv);
			return false;
		}
	}
}


inline bool
parse_base_string(struct StringBuilder *const restrict base,
		  struct GenerateArgvState *const restrict argv)
{
	const char *const restrict base_bytes = *(argv->arg.from);

	const octet_t *restrict octets
	= (const octet_t *restrict) base_bytes;

	unsigned int width;

	size_t rem_code_points = BASE_STRING_LENGTH_MAX;

	while (1) {
		if (*octets == '\0') {
			string_builder_init(base,
					    base_bytes,
					    ((const char *const restrict)
					     octets) - base_bytes);
			return true;
		}

		width = utf8_width(octets);

		if (width == 0u) {
			invalid_base_string_invalid(argv);
			return false;
		}

		octets += width;

		--rem_code_points;

		if (rem_code_points == 0lu) {
			invalid_base_string_long(argv);
			return false;
		}
	}
}

inline bool
parse_fixed_string(struct StringBuilder *const restrict fixed,
		   struct GenerateArgvState *const restrict argv)
{
	const char *const restrict fixed_bytes = *(argv->arg.from);

	const octet_t *restrict octets
	= (const octet_t *restrict) fixed_bytes;

	unsigned int width;

	size_t rem_code_points = BASE_STRING_LENGTH_MAX;

	while (1) {
		if (*octets == '\0') {
			string_builder_init(fixed,
					    fixed_bytes,
					    (((const char *const restrict)
					     octets) + 1l) - fixed_bytes);
			return true;
		}

		width = utf8_width(octets);

		if (width == 0u) {
			invalid_fixed_string_invalid(argv);
			return false;
		}

		octets += width;

		--rem_code_points;

		if (rem_code_points == 0lu) {
			invalid_fixed_string_long(argv);
			return false;
		}
	}
}


/* parse ASCII numbers from input
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
parse_row_count(size_t *const restrict row_count,
		struct GenerateArgvState *const restrict argv)
{
	uintmax_t parsed;

	if (parse_uint(&parsed,
		       *(argv->arg.from)) == NULL) {
		invalid_row_count_invalid(argv);
		return false;
	}

	if (parsed == 0llu) {
		invalid_row_count_zero(argv);
		return false;
	}

	if (parsed > UPTO_MAX) {
		invalid_row_count_large(argv);
		return false;
	}

	*row_count = (size_t) parsed;
	return true;
}

inline bool
parse_hash_length(size_t *const restrict hash_length,
		  struct GenerateArgvState *const restrict argv)
{
	uintmax_t parsed;

	if (parse_uint(&parsed,
		       *(argv->arg.from)) == NULL) {
		invalid_hash_length_invalid(argv);
		return false;
	}

	if (parsed == 0llu) {
		invalid_hash_length_zero(argv);
		return false;
	}

	if (parsed > HASH_LENGTH_MAX) {
		invalid_hash_length_large(argv);
		return false;
	}

	*hash_length = (size_t) parsed;
	return true;
}

inline bool
parse_grp_count(size_t *const restrict grp_count,
		const size_t row_count,
		struct GenerateArgvState *const restrict argv)
{
	uintmax_t parsed;

	if (parse_uint(&parsed,
		       *(argv->arg.from)) == NULL) {
		invalid_grp_count_invalid(argv);
		return false;
	}

	if (parsed == 0llu) {
		invalid_grp_count_zero(argv);
		return false;
	}

	if (parsed > row_count) {
		invalid_grp_count_large(argv);
		return false;
	}

	*grp_count = (size_t) parsed;
	return true;
}


/* assign type according to MySQL data types, limits
 *─────────────────────────────────────────────────────────────────────────── */
inline void
type_set_char(struct PutLabelClosure *const restrict type,
	      const uintmax_t length)
{
	char *restrict ptr = &type->buffer[0];

	PUT_STRING_WIDTH(ptr, "CHAR(", 5);

	ptr = put_uint(ptr,
		       length);

	SET_STRING_WIDTH(ptr, ")", 2);

	type->put = PUT_STRING_WIDTH_MAP[ptr + 1l - &type->buffer[0]];
}

inline void
type_set_char_parsed_length(struct PutLabelClosure *const restrict type,
			    const char *restrict length)
{
	char *restrict ptr = &type->buffer[0];

	PUT_STRING_WIDTH(ptr, "CHAR(", 5);

	while (*length == '0')	/* ignore leading zeros */
		++length;

	ptr = put_string(ptr,
			 length);

	SET_STRING_WIDTH(ptr, ")", 2);

	type->put = PUT_STRING_WIDTH_MAP[ptr + 1l - &type->buffer[0]];
}

inline void
type_set_varchar(struct PutLabelClosure *const restrict type,
		 const uintmax_t length)
{
	char *restrict ptr = &type->buffer[0];

	PUT_STRING_WIDTH(ptr, "VARCHAR(", 8);

	ptr = put_uint(ptr,
		       length);

	SET_STRING_WIDTH(ptr, ")", 2);

	type->put = PUT_STRING_WIDTH_MAP[ptr + 1l - &type->buffer[0]];
}

inline void
type_set_timestamp(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "TIMESTAMP",
			 10);
	type->put = &put_string_width9;
}

inline void
type_set_datetime(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "DATETIME",
			 9);
	type->put = &put_string_width8;
}


inline void
type_set_tinyint(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "TINYINT",
			 8);
	type->put = &put_string_width7;
}

inline void
type_set_tinyint_unsigned(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "TINYINT UNSIGNED",
			 17);
	type->put = &put_string_width16;
}

inline void
type_set_smallint(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "SMALLINT",
			 9);
	type->put = &put_string_width8;
}

inline void
type_set_smallint_unsigned(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "SMALLINT UNSIGNED",
			 18);
	type->put = &put_string_width17;
}

inline void
type_set_mediumint(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "MEDIUMINT",
			 10);
	type->put = &put_string_width9;
}

inline void
type_set_mediumint_unsigned(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "MEDIUMINT UNSIGNED",
			 19);
	type->put = &put_string_width18;
}

inline void
type_set_int(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "INT",
			 4);
	type->put = &put_string_width3;
}

inline void
type_set_int_unsigned(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "INT UNSIGNED",
			 13);
	type->put = &put_string_width12;
}

inline void
type_set_bigint(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "BIGINT",
			 7);
	type->put = &put_string_width6;
}

inline void
type_set_bigint_unsigned(struct PutLabelClosure *const restrict type)
{
	SET_STRING_WIDTH(&type->buffer[0],
			 "BIGINT UNSIGNED",
			 16);
	type->put = &put_string_width15;
}

inline void
type_assign_integer_min(struct PutLabelClosure *const restrict type,
			const intmax_t min)
{
	if (min < SMALLINT_SIGNED_MIN) {
		if (min < MEDIUMINT_SIGNED_MIN) {
			if (min < INT_SIGNED_MIN) {
				type_set_bigint(type);
			} else {
				type_set_int(type);
			}
		} else {
			type_set_mediumint(type);
		}
	} else {
		if (min < TINYINT_SIGNED_MIN) {
			type_set_smallint(type);
		} else {
			type_set_tinyint(type);
		}
	}
}

inline void
type_assign_integer_max(struct PutLabelClosure *const restrict type,
			const intmax_t max)
{
	if (max > SMALLINT_SIGNED_MAX) {
		if (max > MEDIUMINT_SIGNED_MAX) {
			if (max > INT_SIGNED_MAX) {
				type_set_bigint(type);
			} else {
				type_set_int(type);
			}
		} else {
			type_set_mediumint(type);
		}
	} else {
		if (max > TINYINT_SIGNED_MAX) {
			type_set_smallint(type);
		} else {
			type_set_tinyint(type);
		}
	}
}

inline void
type_assign_u_integer_max(struct PutLabelClosure *const restrict type,
			  const uintmax_t max)
{
	if (max > SMALLINT_UNSIGNED_MAX) {
		if (max > MEDIUMINT_UNSIGNED_MAX) {
			if (max > INT_UNSIGNED_MAX) {
				type_set_bigint_unsigned(type);
			} else {
				type_set_int_unsigned(type);
			}
		} else {
			type_set_mediumint_unsigned(type);
		}
	} else {
		if (max > TINYINT_UNSIGNED_MAX) {
			type_set_smallint_unsigned(type);
		} else {
			type_set_tinyint_unsigned(type);
		}
	}
}

inline void
type_assign_integer_upto(struct PutLabelClosure *const restrict type,
			 const size_t upto)
{
#if LARGE_UPTO_MAX
	if (upto > SMALLINT_SIGNED_MAX) {
		if (upto > MEDIUMINT_SIGNED_MAX) {
			type_set_int(type);
		} else {
			type_set_mediumint(type);
		}
	} else {
#endif /* if LARGE_UPTO_MAX */

		if (upto > TINYINT_SIGNED_MAX) {
			type_set_smallint(type);
		} else {
			type_set_tinyint(type);
		}

#if LARGE_UPTO_MAX
	}
#endif /* if LARGE_UPTO_MAX */
}

inline void
type_assign_u_integer_upto(struct PutLabelClosure *const restrict type,
			   const size_t upto)
{
#if LARGE_UPTO_MAX
	if (upto > SMALLINT_UNSIGNED_MAX) {
		if (upto > MEDIUMINT_UNSIGNED_MAX) {
			type_set_int_unsigned(type);
		} else {
			type_set_mediumint_unsigned(type);
		}
	} else {
#endif /* if LARGE_UPTO_MAX */

		if (upto > TINYINT_UNSIGNED_MAX) {
			type_set_smallint_unsigned(type);
		} else {
			type_set_tinyint_unsigned(type);
		}

#if LARGE_UPTO_MAX
	}
#endif /* if LARGE_UPTO_MAX */
}


/* finished parsing
 *─────────────────────────────────────────────────────────────────────────── */
inline void
parse_table_complete(struct GenerateParseState *const restrict state)
{
	state->specs.tbl->col_specs.until = state->specs.col + 1l;
}

inline void
parse_valid_complete(struct GenerateParseState *const restrict state)
{
	parse_table_complete(state);
	state->specs.tbl->next = NULL;
	*(state->valid.last) = state->specs.db;
	state->valid.last = &state->specs.db->next;
	generator_counter_update(&state->generator,
				 &state->database);
}

inline void
parse_database_complete(struct GenerateParseState *const restrict state)
{
	parse_valid_complete(state);
	state->specs.db = (struct DbSpec *) state->specs.tbl->col_specs.until;
}

inline void
generate_parse_complete(struct GenerateParseState *const restrict state)
{
	parse_valid_complete(state);
	*(state->valid.last) = NULL;
}

inline void
parse_column_complete(struct GenerateParseState *const restrict state,
		      GenerateParseNode *const set_col_spec,
		      GenerateParseNode *const handle_grp_spec)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		set_col_spec(state);
		generate_parse_complete(state);
		return;
	}

	char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
		error_expected_col_spec_close(state);
		return;
	}

	++arg;
	char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break; /* parse long SPEC */

	case 'g':
		if (*rem == '\0')
			handle_grp_spec(state);
		else
			error_expected_col_spec_close(state);
		return;

	case 'c':
		if (*rem == '\0') {
NEXT_COL_SPEC:		set_col_spec(state);
			parse_next_col_spec(state);
		} else {
			error_expected_col_spec_close(state);
		}
		return;

	case 't':
		if (*rem == '\0') {
NEXT_TBL_SPEC:		set_col_spec(state);
			parse_table_complete(state);
			parse_next_tbl_spec(state);
		} else {
			error_expected_col_spec_close(state);
		}
		return;

	case 'd':
		if (*rem == '\0') {
NEXT_DB_SPEC:		set_col_spec(state);
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}

	default:
		error_expected_col_spec_close(state);
		return;
	}


	switch (*rem) {
	case 'g':
		if (strings_equal("roup", rem + 1l))
			handle_grp_spec(state);
		else
			error_expected_col_spec_close(state);
		return;

	case 'c':
		if (strings_equal("olumn", rem + 1l))
			goto NEXT_COL_SPEC;

		error_expected_col_spec_close(state);
		return;

	case 't':
		if (strings_equal("able", rem + 1l))
			goto NEXT_TBL_SPEC;

		error_expected_col_spec_close(state);
		return;

	case 'd':
		if (strings_equal("atabase", rem + 1l))
			goto NEXT_DB_SPEC;

	default:
		error_expected_col_spec_close(state);
	}
}

/* parse GRP_SPEC
 *─────────────────────────────────────────────────────────────────────────── */
inline void
no_grp_count(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_NO_GRP_COUNT,
			  sizeof(ERROR_NO_GRP_COUNT) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from - 1l);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_no_grp_count(struct GenerateParseState *const restrict state)
{
	no_grp_count(&state->argv);
	*(state->valid.last) = NULL;
	state->exit_status = EXIT_FAILURE;
}

inline void
multiple_grp_specs(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  ERROR_MULTIPLE_GRP_SPECS,
			  sizeof(ERROR_MULTIPLE_GRP_SPECS) - 1);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
error_multiple_grp_specs(struct GenerateParseState *const restrict state)
{
	multiple_grp_specs(&state->argv);
	++(state->argv.arg.from);
	generate_parse_error(state);
}

inline void
parse_grp_spec(struct GenerateParseState *const restrict state,
	       GenerateParseNode *const set_col_spec)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_no_grp_count(state);
		return;
	}

	struct ColSpec *const restrict col_spec = state->specs.col;
	struct GrpSpec *const restrict grp_spec = &col_spec->grp_spec;

	if (!parse_grp_count(&grp_spec->count,
			     state->specs.tbl->row_count,
			     &state->argv)) {
		generate_parse_error(state);
		return;
	}

	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		grp_spec->partition = &partition_groups_even;
		set_col_spec(state);
		generate_parse_complete(state);
		return;
	}

	char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
		error_expected_grp_spec_close(state);
		return;
	}

	++arg;
	char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break; /* parse long SPEC */

	case 'e':
		if (*rem == '\0') {
PART_GROUPS_EVEN:	grp_spec->partition = &partition_groups_even;
			parse_column_complete(state,
					      set_col_spec,
					      &error_multiple_grp_specs);
		} else {
			error_expected_grp_spec_close(state);
		}
		return;

	case 'l':
		if (*rem == '\0') {
PART_GROUPS_LINEAR:	grp_spec->partition = &partition_groups_linear;
			parse_column_complete(state,
					      set_col_spec,
					      &error_multiple_grp_specs);
		} else {
			error_expected_grp_spec_close(state);
		}
		return;

	case 'g':
		if (*rem == '\0')
			error_multiple_grp_specs(state);
		else
			error_expected_grp_spec_close(state);
		return;

	case 'c':
		if (*rem == '\0') {
NEXT_COL_SPEC:		grp_spec->partition = &partition_groups_even;
			set_col_spec(state);
			parse_next_col_spec(state);
		} else {
			error_expected_grp_spec_close(state);
		}
		return;

	case 't':
		if (*rem == '\0') {
NEXT_TBL_SPEC:		grp_spec->partition = &partition_groups_even;
			set_col_spec(state);
			parse_table_complete(state);
			parse_next_tbl_spec(state);
		} else {
			error_expected_grp_spec_close(state);
		}
		return;

	case 'd':
		if (*rem == '\0') {
NEXT_DB_SPEC:		grp_spec->partition = &partition_groups_even;
			set_col_spec(state);
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}

	default:
		error_expected_grp_spec_close(state);
		return;
	}

	switch (*rem) {
	case 'e':
		if (strings_equal("ven", rem + 1l))
			goto PART_GROUPS_EVEN;

		error_expected_grp_spec_close(state);
		return;

	case 'l':
		if (strings_equal("inear", rem + 1l))
			goto PART_GROUPS_LINEAR;

		error_expected_grp_spec_close(state);
		return;

	case 'g':
		if (strings_equal("roup", rem + 1l))
			error_multiple_grp_specs(state);
		else
			error_expected_grp_spec_close(state);
		return;

	case 'c':
		if (strings_equal("olumn", rem + 1l))
			goto NEXT_COL_SPEC;

		error_expected_grp_spec_close(state);
		return;

	case 't':
		if (strings_equal("able", rem + 1l))
			goto NEXT_TBL_SPEC;

		error_expected_grp_spec_close(state);
		return;

	case 'd':
		if (strings_equal("atabase", rem + 1l))
			goto NEXT_DB_SPEC;

	default:
		error_expected_grp_spec_close(state);
	}
}


/* set COL_SPEC
 *─────────────────────────────────────────────────────────────────────────── */
/* -c COL_NAME -i */
inline void
column_integer_default(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;
	const size_t row_count			= state->specs.tbl->row_count;
	size_t *const restrict counter_upto	= &state->database.counter_upto;

	type_assign_integer_upto(&col_spec->type,
				 row_count);

	col_spec->build = &build_column_integer_unique;

	if (row_count > *counter_upto)
		*counter_upto = row_count;
}

/* -c COL_NAME -i -g GRP_COUNT [PART_TYPE] */
inline void
column_integer_default_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;
	const size_t grp_count			= col_spec->grp_spec.count;
	size_t *const restrict counter_upto	= &state->database.counter_upto;

	type_assign_integer_upto(&col_spec->type,
				 grp_count);

	col_spec->build = &build_column_string_unique_group;

	if (grp_count > *counter_upto)
		*counter_upto = grp_count;
}

/* -c COL_NAME -i -u */
inline void
column_integer_unique(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;
	const size_t row_count			= state->specs.tbl->row_count;
	size_t *const restrict counter_upto	= &state->database.counter_upto;

	type_assign_integer_upto(&col_spec->type,
				 row_count);

	col_spec->build = &build_column_integer_unique;

	if (row_count > *counter_upto)
		*counter_upto = row_count;
}

/* -c COL_NAME -i -u -g GRP_COUNT [PART_TYPE] */
inline void
column_integer_unique_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;
	const size_t grp_count			= col_spec->grp_spec.count;
	size_t *const restrict counter_upto	= &state->database.counter_upto;

	type_assign_integer_upto(&col_spec->type,
				 grp_count);

	col_spec->build = &build_column_integer_unique_group;

	if (grp_count > *counter_upto)
		*counter_upto = grp_count;
}

/* -c COL_NAME -i -f FIXED_INT */
inline void
column_integer_fixed(struct GenerateParseState *const restrict state)
{
	state->specs.col->build = &build_column_integer_fixed;
}

/* -c COL_NAME -s -u BASE_STRING */
inline void
column_string_unique(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;
	const size_t row_count			= state->specs.tbl->row_count;
	size_t *const restrict counter_upto	= &state->database.counter_upto;

	type_set_varchar(&col_spec->type,
			 (uintmax_t)
			 (col_spec->type_q.string.base.length
			  + uint_digit_count(row_count)));

	col_spec->build = &build_column_string_unique;

	if (row_count > *counter_upto)
		*counter_upto = row_count;
}

/* -c COL_NAME -s -u BASE_STRING -g GRP_COUNT [PART_TYPE] */
inline void
column_string_unique_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;
	const size_t grp_count			= col_spec->grp_spec.count;
	size_t *const restrict counter_upto	= &state->database.counter_upto;

	type_set_varchar(&col_spec->type,
			 (uintmax_t)
			 (col_spec->type_q.string.base.length
			  + uint_digit_count(grp_count)));

	col_spec->build = &build_column_string_unique_group;

	if (grp_count > *counter_upto)
		*counter_upto = grp_count;
}

/* -c COL_NAME -s -f BASE_STRING */
inline void
column_string_fixed(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_char(&col_spec->type,
		      (uintmax_t)
		      col_spec->type_q.string.base.length);

	col_spec->build = &build_column_string_fixed;
}

/* -c COL_NAME -s -uu */
inline void
column_string_uuid(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	SET_UUID_TYPE(&col_spec->type.buffer[0]);

	col_spec->type.put = UUID_TYPE_PUT;

	col_spec->build = &build_column_string_uuid;

	state->database.ctor_flags |= UUID_CTOR_FLAG;
}

/* -c COL_NAME -s -uu -g GRP_COUNT [PART_TYPE] */
inline void
column_string_uuid_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	SET_UUID_TYPE(&col_spec->type.buffer[0]);

	col_spec->type.put = UUID_TYPE_PUT;

	col_spec->build = &build_column_string_uuid_group;

	state->database.ctor_flags |= UUID_CTOR_FLAG;
}

/* -c COL_NAME -s -h HASH_LENGTH */
inline void
column_string_hash(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_char_parsed_length(&col_spec->type,
				    state->argv.cache);

	col_spec->build = &build_column_string_hash;
}

/* -c COL_NAME -s -h HASH_LENGTH -g GRP_COUNT [PART_TYPE] */
inline void
column_string_hash_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_char_parsed_length(&col_spec->type,
				    state->argv.cache);

	col_spec->build = &build_column_string_hash_group;
}

/* -c COL_NAME -n1 */
inline void
column_string_names_first(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	SET_NAMES_FIRST_TYPE(&col_spec->type.buffer[0]);

	col_spec->type.put = NAMES_FIRST_TYPE_PUT;

	col_spec->build = &build_column_string_names_first;

	state->database.ctor_flags |= RAND_CTOR_FLAG;
}

/* -c COL_NAME -s -n1 -g GRP_COUNT [PART_TYPE] */
inline void
column_string_names_first_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	SET_NAMES_FIRST_TYPE(&col_spec->type.buffer[0]);

	col_spec->type.put = NAMES_FIRST_TYPE_PUT;

	col_spec->build = &build_column_string_names_first_group;

	state->database.ctor_flags |= RAND_CTOR_FLAG;
}

/* -c COL_NAME -s -nl */
inline void
column_string_names_last(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	SET_NAMES_LAST_TYPE(&col_spec->type.buffer[0]);

	col_spec->type.put = NAMES_LAST_TYPE_PUT;

	col_spec->build = &build_column_string_names_last;

	state->database.ctor_flags |= RAND_CTOR_FLAG;
}
/* -c COL_NAME -s -nl -g GRP_COUNT [PART_TYPE] */
inline void
column_string_names_last_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	SET_NAMES_LAST_TYPE(&col_spec->type.buffer[0]);

	col_spec->type.put = NAMES_LAST_TYPE_PUT;

	col_spec->build = &build_column_string_names_last_group;

	state->database.ctor_flags |= RAND_CTOR_FLAG;
}

/* -c COL_NAME -nf */
inline void
column_string_names_full(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	SET_NAMES_FULL_TYPE(&col_spec->type.buffer[0]);

	col_spec->type.put = NAMES_FULL_TYPE_PUT;

	col_spec->build = &build_column_string_names_full;

	state->database.ctor_flags |= RAND_CTOR_FLAG;
}

/* -c COL_NAME -s -nf -g GRP_COUNT [PART_TYPE] */
inline void
column_string_names_full_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	SET_NAMES_FULL_TYPE(&col_spec->type.buffer[0]);

	col_spec->type.put = NAMES_FULL_TYPE_PUT;

	col_spec->build = &build_column_string_names_full_group;

	state->database.ctor_flags |= RAND_CTOR_FLAG;
}

/* -c COL_NAME -s */
inline void
column_string_default(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;
	const size_t row_count			= state->specs.tbl->row_count;
	size_t *const restrict counter_upto	= &state->database.counter_upto;

	string_builder_init(&col_spec->type_q.string.base,
			    col_spec->name.bytes,
			    col_spec->name.length);

	type_set_varchar(&col_spec->type,
			 (uintmax_t)
			 (col_spec->type_q.string.base.length
			  + uint_digit_count(row_count)));

	col_spec->build = &build_column_string_unique;

	if (row_count > *counter_upto)
		*counter_upto = row_count;
}

/* -c COL_NAME -s -g GRP_COUNT [PART_TYPE] */
inline void
column_string_default_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;
	const size_t grp_count			= col_spec->grp_spec.count;
	size_t *const restrict counter_upto	= &state->database.counter_upto;

	string_builder_init(&col_spec->type_q.string.base,
			    col_spec->name.bytes,
			    col_spec->name.length);

	type_set_varchar(&col_spec->type,
			 (uintmax_t)
			 (col_spec->type_q.string.base.length
			  + uint_digit_count(grp_count)));

	col_spec->build = &build_column_string_unique_group;

	if (grp_count > *counter_upto)
		*counter_upto = grp_count;
}

/* -c COL_NAME -ts -u */
inline void
column_timestamp_unique(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_timestamp(&col_spec->type);
	col_spec->build = &build_column_timestamp_unique;
}

/* -c COL_NAME -ts -u -g GRP_COUNT [PART_TYPE] */
inline void
column_timestamp_unique_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_timestamp(&col_spec->type);
	col_spec->build = &build_column_timestamp_unique_group;
}

/* -c COL_NAME -ts -f */
inline void
column_timestamp_fixed(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_timestamp(&col_spec->type);
	col_spec->build = &build_column_timestamp_fixed;
}

/* -c COL_NAME -ts */
inline void
column_timestamp_default(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_timestamp(&col_spec->type);
	col_spec->build = &build_column_timestamp_unique;
}

/* -c COL_NAME -ts -g GRP_COUNT [PART_TYPE] */
inline void
column_timestamp_default_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_timestamp(&col_spec->type);
	col_spec->build = &build_column_timestamp_unique_group;
}


/* -c COL_NAME -dt -u */
inline void
column_datetime_unique(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_datetime(&col_spec->type);
	col_spec->build = &build_column_datetime_unique;
}

/* -c COL_NAME -dt -u -g GRP_COUNT [PART_TYPE] */
inline void
column_datetime_unique_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_datetime(&col_spec->type);
	col_spec->build = &build_column_datetime_unique_group;
}

/* -c COL_NAME -dt -f */
inline void
column_datetime_fixed(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_datetime(&col_spec->type);
	col_spec->build = &build_column_datetime_fixed;
}

/* -c COL_NAME -dt */
inline void
column_datetime_default(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_datetime(&col_spec->type);
	col_spec->build = &build_column_datetime_unique;
}

/* -c COL_NAME -dt -g GRP_COUNT [PART_TYPE] */
inline void
column_datetime_default_group(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	type_set_datetime(&col_spec->type);
	col_spec->build = &build_column_datetime_unique_group;
}

/* parse COL_TYPE_Q
 *─────────────────────────────────────────────────────────────────────────── */
inline void
parse_integer_default_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_integer_default_group);
}

inline void
parse_integer_default(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_integer_default,
			      &parse_integer_default_group);
}

inline void
parse_integer_unique_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_integer_unique_group);
}

inline void
parse_integer_unique(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_integer_unique,
			      &parse_integer_unique_group);
}

inline void
parse_integer_fixed(struct GenerateParseState *const restrict state)
{
	intmax_t parsed;
	char *restrict from;

	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_no_fixed_integer(state);
		return;
	}

	from = *(state->argv.arg.from);

	const char *const restrict until = parse_int(&parsed,
						     from);

	if (until == NULL) {
		error_invalid_fixed_integer_invalid(state);
		return;
	}

#if (INTMAX_MIN < BIGINT_SIGNED_MIN)
	if (parsed < BIGINT_SIGNED_MIN) {
		error_invalid_fixed_integer_small(state);
		return;
	}
#endif /* if (INTMAX_MIN < BIGINT_SIGNED_MIN) */
#if (INTMAX_MAX > BIGINT_SIGNED_MAX)
	if (parsed > BIGINT_SIGNED_MAX) {
		error_invalid_fixed_integer_large(state);
		return;
	}
#endif /* if (INTMAX_MAX > BIGINT_SIGNED_MAX) */

	struct ColSpec *const restrict col_spec = state->specs.col;

	if (parsed < 0ll) {
		type_assign_integer_min(&col_spec->type,
					parsed);

		do {
			++from;
		} while (*from == '0');

		--from;
		*from = '-';

		stub_builder_init(&col_spec->type_q.integer.fixed,
				  from,
				  until + 1l - from);

	} else if (parsed > 0ll) {
		type_assign_integer_max(&col_spec->type,
					parsed);

		while (*from == '0')
			++from;

		stub_builder_init(&col_spec->type_q.integer.fixed,
				  from,
				  until + 1l - from);
	} else {
		type_set_tinyint(&col_spec->type);

		struct StubBuilder *const restrict fixed_int
		= &col_spec->type_q.integer.fixed;

		fixed_int->put_cl.bytes = "0";
		fixed_int->put_cl.put	= put_string_width2;
		fixed_int->width	= 2u;
	}

	parse_column_complete(state,
			      &column_integer_fixed,
			      &error_grp_spec_for_fixed_data);
}


inline void
parse_string_default_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_string_default_group);
}

inline void
parse_string_default(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_string_default,
			      &parse_string_default_group);
}

inline void
parse_string_unique_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_string_unique_group);
}

inline void
parse_string_unique(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_no_base_string(state);
		return;
	}

	if (parse_base_string(&state->specs.col->type_q.string.base,
			      &state->argv))
		parse_column_complete(state,
				      &column_string_unique,
				      &parse_string_unique_group);
	else
		generate_parse_error(state);
}

inline void
parse_string_fixed(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_no_fixed_string(state);
		return;
	}

	if (parse_fixed_string(&state->specs.col->type_q.string.fixed,
			       &state->argv))
		parse_column_complete(state,
				      &column_string_fixed,
				      &error_grp_spec_for_fixed_data);
	else
		generate_parse_error(state);
}

inline void
parse_string_uuid_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_string_uuid_group);
}


inline void
parse_string_uuid(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_string_uuid,
			      &parse_string_uuid_group);
}

inline void
parse_string_hash_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_string_hash_group);
}

inline void
parse_string_hash(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_no_hash_length(state);
		return;
	}

	if (parse_hash_length(&state->specs.col->type_q.string.scale.fixed,
			      &state->argv)) {

		state->argv.cache = *(state->argv.arg.from);
		parse_column_complete(state,
				      &column_string_hash,
				      &parse_string_hash_group);
	} else {
		generate_parse_error(state);
	}
}

inline void
parse_string_names_first_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_string_names_first_group);
}

inline void
parse_string_names_first(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_string_names_first,
			      &parse_string_names_first_group);
}

inline void
parse_string_names_last_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_string_names_last_group);
}

inline void
parse_string_names_last(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_string_names_last,
			      &parse_string_names_last_group);
}

inline void
parse_string_names_full_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_string_names_full_group);
}

inline void
parse_string_names_full(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_string_names_full,
			      &parse_string_names_full_group);
}

inline void
parse_timestamp_default_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_timestamp_default_group);
}

inline void
parse_timestamp_default(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_timestamp_default,
			      &parse_timestamp_default_group);
}

inline void
parse_timestamp_fixed(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_timestamp_fixed,
			      &error_grp_spec_for_fixed_data);
}

inline void
parse_timestamp_unique_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_timestamp_unique_group);
}

inline void
parse_timestamp_unique(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_timestamp_unique,
			      &parse_timestamp_unique_group);
}

inline void
parse_datetime_default_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_datetime_default_group);
}

inline void
parse_datetime_default(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_datetime_default,
			      &parse_datetime_default_group);
}

inline void
parse_datetime_fixed(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_datetime_fixed,
			      &error_grp_spec_for_fixed_data);
}

inline void
parse_datetime_unique_group(struct GenerateParseState *const restrict state)
{
	parse_grp_spec(state,
		       &column_datetime_unique_group);
}

inline void
parse_datetime_unique(struct GenerateParseState *const restrict state)
{
	parse_column_complete(state,
			      &column_datetime_unique,
			      &parse_datetime_unique_group);
}


/* parse spec groups
 *─────────────────────────────────────────────────────────────────────────── */
inline void
parse_integer_random(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		column_integer_random_default(state);
		generate_parse_complete(state); /* done parsing */
		return;
	}

	const char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
		error_invalid_rand_spec(state);
		return;
	}

	++arg;
	const char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break;	/* parse long integer qualifier */

	case 'g':
		if (*rem == '\0')
			parse_integer_random_default_group(state);
		else
			error_invalid_rand_spec(state);
		return;

	case 'f':
		if (*rem == '\0')
			parse_integer_random_from(state);
		else
			error_invalid_rand_spec(state);
		return;

	case 'u':
		if (*rem == '\0')
			parse_integer_random_upto(state);
		else
			error_invalid_rand_spec(state);
		return;

	case 'r':
		if (*rem == '\0')
			parse_integer_random_range(state);
		else
			error_invalid_rand_spec(state);
		return;

	case 'c':
		if (*rem == '\0') {
NEXT_COL_SPEC:		column_integer_random_default(state);
			parse_next_col_spec(state);
		} else {
			error_invalid_rand_spec(state);
		}
		return;

	case 't':
		if (*rem == '\0') {
NEXT_TBL_SPEC:		column_integer_random_default(state);
			parse_table_complete(state);
			parse_next_tbl_spec(state);
		} else {
			error_invalid_rand_spec(state);
		}
		return;

	case 'd':
		if (*rem == '\0') {
NEXT_DB_SPEC:		column_integer_random_default(state);
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}

	default:
		error_invalid_rand_spec(state);
		return;
	}

	switch (*rem) {
	case 'g':
		if (strings_equal("roup", rem + 1l))
			parse_integer_random_default_group(state);
		else
			error_invalid_rand_spec(state);
		return;

	case 'f':
		if (strings_equal("rom", rem + 1l))
			parse_integer_random_from(state);
		else
			error_invalid_rand_spec(state);
		return;

	case 'u':
		if (strings_equal("nique", rem + 1l))
			parse_integer_random_upto(state);
		else
			error_invalid_rand_spec(state);
		return;

	case 'r':
		if (strings_equal("ange", rem + 1l))
			parse_integer_random_range(state);
		else
			error_invalid_rand_spec(state);
		return;

	case 'c':
		if (strings_equal("olumn", rem + 1l))
			goto NEXT_COL_SPEC;

		error_invalid_rand_spec(state);
		return;

	case 't':
		if (strings_equal("able", rem + 1l))
			goto NEXT_TBL_SPEC;

		error_invalid_rand_spec(state);
		return;

	case 'd':
		if (strings_equal("atabase", rem + 1l))
			goto NEXT_DB_SPEC;

	default:
		error_invalid_rand_spec(state);
	}
}

inline void
parse_integer_qualifier(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		column_integer_default(state);
		generate_parse_complete(state); /* done parsing */
		return;
	}

	const char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
		error_invalid_integer_type_q(state);
		return;
	}

	++arg;
	const char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break;	/* parse long integer qualifier */

	case 'g':
		if (*rem == '\0')
			parse_integer_default_group(state);
		else
			error_invalid_integer_type_q(state);
		return;

	case 'u':
		if (*rem == '\0')
			parse_integer_unique(state);
		else
			error_invalid_integer_type_q(state);
		return;

	case 'f':
		if (*rem == '\0')
			parse_integer_fixed(state);
		else
			error_invalid_integer_type_q(state);
		return;

	case 'r':
		if (*rem == '\0')
			parse_integer_random(state);
		else
			error_invalid_integer_type_q(state);
		return;

	case 'c':
		if (*rem == '\0') {
NEXT_COL_SPEC:		column_integer_default(state);
			parse_next_col_spec(state);
		} else {
			error_invalid_integer_type_q(state);
		}
		return;

	case 't':
		if (*rem == '\0') {
NEXT_TBL_SPEC:		column_integer_default(state);
			parse_table_complete(state);
			parse_next_tbl_spec(state);
		} else {
			error_invalid_integer_type_q(state);
		}
		return;

	case 'd':
		if (*rem == '\0') {
NEXT_DB_SPEC:		column_integer_default(state);
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}

	default:
		error_invalid_integer_type_q(state);
		return;
	}


	switch (*rem) {
	case 'g':
		if (strings_equal("roup", rem + 1l))
			parse_integer_default_group(state);
		else
			error_invalid_integer_type_q(state);
		return;

	case 'u':
		if (strings_equal("nique", rem + 1l))
			parse_integer_unique(state);
		else
			error_invalid_integer_type_q(state);
		return;

	case 'f':
		if (strings_equal("ixed", rem + 1l))
			parse_integer_fixed(state);
		else
			error_invalid_integer_type_q(state);
		return;

	case 'r':
		if (strings_equal("andom", rem + 1l))
			parse_integer_random(state);
		else
			error_invalid_integer_type_q(state);
		return;

	case 'c':
		if (strings_equal("olumn", rem + 1l))
			goto NEXT_COL_SPEC;

		error_invalid_integer_type_q(state);
		return;

	case 't':
		if (strings_equal("able", rem + 1l))
			goto NEXT_TBL_SPEC;

		error_invalid_integer_type_q(state);
		return;

	case 'd':
		if (strings_equal("atabase", rem + 1l))
			goto NEXT_DB_SPEC;

	default:
		error_invalid_integer_type_q(state);
	}
}


inline void
parse_string_qualifier(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		column_string_default(state);
		generate_parse_complete(state); /* done parsing */
		return;
	}

	const char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
		error_invalid_string_type_q(state);
		return;
	}

	++arg;
	const char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break;	/* parse long string qualifier */

	case 'g':
		if (*rem == '\0')
			parse_string_default_group(state);
		else
			error_invalid_string_type_q(state);
		return;

	case 'u':
		switch (*rem) {
		case '\0':
			parse_string_unique(state);
			return;

		case 'u':
			if (rem[1] == '\0') {
				parse_string_uuid(state);
				return;
			}

		default:
			error_invalid_string_type_q(state);
			return;
		}

	case 'f':
		if (*rem == '\0')
			parse_string_fixed(state);
		else
			error_invalid_string_type_q(state);
		return;

	case 'h':
		if (*rem == '\0')
			parse_string_hash(state);
		else
			error_invalid_string_type_q(state);
		return;

	case 'n':
		switch (*rem) {
		case '1':
			if (rem[1] == '\0')
				parse_string_names_first(state);
			else
				error_invalid_string_type_q(state);
			return;

		case 'l':
			if (rem[1] == '\0')
				parse_string_names_last(state);
			else
				error_invalid_string_type_q(state);
			return;

		case 'f':
			if (rem[1] == '\0') {
				parse_string_names_full(state);
				return;
			}

		default:
			error_invalid_string_type_q(state);
			return;
		}

	case 'c':
		if (*rem == '\0') {
NEXT_COL_SPEC:		column_string_default(state);
			parse_next_col_spec(state);
		} else {
			error_invalid_string_type_q(state);
		}
		return;

	case 't':
		if (*rem == '\0') {
NEXT_TBL_SPEC:		column_string_default(state);
			parse_table_complete(state);
			parse_next_tbl_spec(state);
		} else {
			error_invalid_string_type_q(state);
		}
		return;

	case 'd':
		if (*rem == '\0') {
NEXT_DB_SPEC:		column_string_default(state);
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}

	default:
		error_invalid_string_type_q(state);
		return;
	}


	switch (*rem) {
	case 'g':
		if (strings_equal("roup", rem + 1l))
			parse_string_default_group(state);
		else
			error_invalid_string_type_q(state);
		return;

	case 'u':
		switch (rem[1]) {
		case 'n':
			if (strings_equal("ique", rem + 2l))
				parse_string_unique(state);
			else
				error_invalid_string_type_q(state);
			return;

		case 'u':
			if (strings_equal("id", rem + 2l)) {
				parse_string_uuid(state);
				return;
			}

		default:
			error_invalid_string_type_q(state);
			return;
		}

	case 'f':
		if (strings_equal("ixed", rem + 1l))
			parse_string_fixed(state);
		else
			error_invalid_string_type_q(state);
		return;

	case 'h':
		if (strings_equal("ash", rem + 1l))
			parse_string_hash(state);
		else
			error_invalid_string_type_q(state);
		return;

	case 'n':
		arg = string_starts_with(rem + 1l,
					 "ames-");

		if (arg == NULL) {
			error_invalid_string_type_q(state);
			return;
		}

		switch (*arg) {
		case 'f':
			switch (arg[1]) {
			case 'i':
				if (strings_equal("rst", arg + 2l))
					parse_string_names_first(state);
				else
					error_invalid_string_type_q(state);
				return;

			case 'u':
				if (strings_equal("ll", arg + 2l)) {
					parse_string_names_full(state);
					return;
				}

			default:
				error_invalid_string_type_q(state);
				return;
			}

		case 'l':
			if (strings_equal("ast", arg + 1l)) {
				parse_string_names_last(state);
				return;
			}

		default:
			error_invalid_string_type_q(state);
			return;
		}

	case 'c':
		if (strings_equal("olumn", rem + 1l))
			goto NEXT_COL_SPEC;

		error_invalid_string_type_q(state);
		return;

	case 't':
		if (strings_equal("able", rem + 1l))
			goto NEXT_TBL_SPEC;

		error_invalid_string_type_q(state);
		return;

	case 'd':
		if (strings_equal("atabase", rem + 1l))
			goto NEXT_DB_SPEC;

	default:
		error_invalid_string_type_q(state);
	}
}

inline void
parse_timestamp_qualifier(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		column_timestamp_default(state);
		generate_parse_complete(state); /* done parsing */
		return;
	}

	const char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
		error_invalid_timestamp_type_q(state);
		return;
	}

	++arg;
	const char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break;	/* parse long string qualifier */
	case 'g':
		if (*rem == '\0')
			parse_timestamp_default_group(state);
		else
			error_invalid_timestamp_type_q(state);
		return;

	case 'f':
		if (*rem == '\0')
			parse_timestamp_fixed(state);
		else
			error_invalid_timestamp_type_q(state);
		return;

	case 'u':
		if (*rem == '\0')
			parse_timestamp_unique(state);
		else
			error_invalid_timestamp_type_q(state);
		return;

	case 'c':
		if (*rem == '\0') {
NEXT_COL_SPEC:		column_timestamp_default(state);
			parse_next_col_spec(state);
		} else {
			error_invalid_timestamp_type_q(state);
		}
		return;

	case 't':
		if (*rem == '\0') {
NEXT_TBL_SPEC:		column_timestamp_default(state);
			parse_table_complete(state);
			parse_next_tbl_spec(state);
		} else {
			error_invalid_timestamp_type_q(state);
		}
		return;

	case 'd':
		if (*rem == '\0') {
NEXT_DB_SPEC:		column_timestamp_default(state);
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}

	default:
		error_invalid_timestamp_type_q(state);
		return;
	}


	switch (*rem) {
	case 'g':
		if (strings_equal("roup", rem + 1l))
			parse_timestamp_default_group(state);
		else
			error_invalid_timestamp_type_q(state);
		return;
	case 'f':
		if (strings_equal("ixed", rem + 1l))
			parse_timestamp_fixed(state);
		else
			error_invalid_timestamp_type_q(state);
		return;

	case 'u':
		if (strings_equal("nique", rem + 1l))
			parse_timestamp_unique(state);
		else
			error_invalid_timestamp_type_q(state);
		return;

	case 'c':
		if (strings_equal("olumn", rem + 1l))
			goto NEXT_COL_SPEC;

		error_invalid_timestamp_type_q(state);
		return;

	case 't':
		if (strings_equal("able", rem + 1l))
			goto NEXT_TBL_SPEC;

		error_invalid_timestamp_type_q(state);
		return;

	case 'd':
		if (strings_equal("atabase", rem + 1l))
			goto NEXT_DB_SPEC;

	default:
		error_invalid_timestamp_type_q(state);
	}
}

inline void
parse_datetime_qualifier(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		column_datetime_default(state);
		generate_parse_complete(state); /* done parsing */
		return;
	}

	const char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
		error_invalid_datetime_type_q(state);
		return;
	}

	++arg;
	const char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break;	/* parse long string qualifier */
	case 'g':
		if (*rem == '\0')
			parse_datetime_default_group(state);
		else
			error_invalid_datetime_type_q(state);
		return;

	case 'f':
		if (*rem == '\0')
			parse_datetime_fixed(state);
		else
			error_invalid_datetime_type_q(state);
		return;

	case 'u':
		if (*rem == '\0')
			parse_datetime_unique(state);
		else
			error_invalid_datetime_type_q(state);
		return;

	case 'c':
		if (*rem == '\0') {
NEXT_COL_SPEC:		column_datetime_default(state);
			parse_next_col_spec(state);
		} else {
			error_invalid_datetime_type_q(state);
		}
		return;

	case 't':
		if (*rem == '\0') {
NEXT_TBL_SPEC:		column_datetime_default(state);
			parse_table_complete(state);
			parse_next_tbl_spec(state);
		} else {
			error_invalid_datetime_type_q(state);
		}
		return;

	case 'd':
		if (*rem == '\0') {
NEXT_DB_SPEC:		column_datetime_default(state);
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}

	default:
		error_invalid_datetime_type_q(state);
		return;
	}


	switch (*rem) {
	case 'g':
		if (strings_equal("roup", rem + 1l))
			parse_datetime_default_group(state);
		else
			error_invalid_datetime_type_q(state);
		return;
	case 'f':
		if (strings_equal("ixed", rem + 1l))
			parse_datetime_fixed(state);
		else
			error_invalid_datetime_type_q(state);
		return;

	case 'u':
		if (strings_equal("nique", rem + 1l))
			parse_datetime_unique(state);
		else
			error_invalid_datetime_type_q(state);
		return;

	case 'c':
		if (strings_equal("olumn", rem + 1l))
			goto NEXT_COL_SPEC;

		error_invalid_datetime_type_q(state);
		return;

	case 't':
		if (strings_equal("able", rem + 1l))
			goto NEXT_TBL_SPEC;

		error_invalid_datetime_type_q(state);
		return;

	case 'd':
		if (strings_equal("atabase", rem + 1l))
			goto NEXT_DB_SPEC;

	default:
		error_invalid_datetime_type_q(state);
	}
}

inline void
parse_col_type(struct GenerateParseState *const restrict state)
{
	const char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
		error_invalid_col_type(state);
		return;
	}

	++arg;
	const char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break;	/* parse long COL_TYPE */

	case 'i':
		if (*rem == '\0')
			parse_integer_qualifier(state);
		else
			error_invalid_col_type(state);
		return;

	case 's':
		if (*rem == '\0')
			parse_string_qualifier(state);
		else
			error_invalid_col_type(state);
		return;

	case 't':
		if (*rem == 's' && rem[1] == '\0')
			parse_timestamp_qualifier(state);
		else
			error_invalid_col_type(state);
		return;

	case 'd':
		if (*rem == 't' && rem[1] == '\0') {
			parse_datetime_qualifier(state);
			return;
		}

	default:
		error_invalid_col_type(state);
		return;
	}

	/* long COL_TYPE */
	switch (*rem) {
	case 'i':
		if (strings_equal("nteger", rem + 1l))
			parse_integer_qualifier(state);
		else
			error_invalid_col_type(state);
		return;

	case 's':
		if (strings_equal("tring", rem + 1l))
			parse_string_qualifier(state);
		else
			error_invalid_col_type(state);
		return;

	case 't':
		if (strings_equal("imestamp", rem + 1l))
			parse_timestamp_qualifier(state);
		else
			error_invalid_col_type(state);
		return;

	case 'd':
		if (strings_equal("atetime", rem + 1l)) {
			parse_datetime_qualifier(state);
			return;
		}

	default:
		error_invalid_col_type(state);
	}
}

inline void
parse_first_col_spec_safe(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (col_flag_match(&state->argv)) {
		struct ColSpec *const restrict col_spec
		= (struct ColSpec *const restrict) (state->specs.tbl + 1l);

		++(state->argv.arg.from);

		if (parse_col_name(&col_spec->name,
				   &state->argv)) {
			state->specs.tbl->col_specs.from = col_spec;
			state->specs.col = col_spec;

			++(state->argv.arg.from);

			parse_col_type(state);
			return;
		}
	}

	generate_parse_error(state);
}


inline void
parse_first_col_spec(struct GenerateParseState *const restrict state)
{
	if (!col_flag_match(&state->argv)) {
		generate_parse_error(state);
		return;
	}

	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_inc_db_spec_col_name(state);
		return;
	}

	struct ColSpec *const restrict col_spec
	= (struct ColSpec *const restrict) (state->specs.tbl + 1l);

	if (!parse_col_name(&col_spec->name,
			    &state->argv)) {
		generate_parse_error(state);
		return;
	}

	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_no_col_type(state);
		return;
	}

	state->specs.tbl->col_specs.from = col_spec;
	state->specs.col = col_spec;

	++(state->database.columns); /* update column counter */

	parse_col_type(state);
}


inline void
parse_next_col_spec(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_inc_db_spec_col_name(state);
		return;
	}

	++(state->specs.col);	/* increment col_spec interval */

	if (!parse_col_name(&state->specs.col->name,
			    &state->argv)) {
		generate_parse_error(state);
		return;
	}

	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_no_col_type(state);
	} else {
		++(state->database.columns); /* update column counter */
		parse_col_type(state);
	}
}


/* TBL_SPEC */
inline void
parse_first_tbl_spec(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (tbl_flag_match(&state->argv)) {

		struct TblSpec *const restrict tbl_spec
		= (struct TblSpec *const restrict) (state->specs.db + 1l);

		++(state->argv.arg.from);

		if (parse_tbl_name(&tbl_spec->name,
				   &state->argv)) {

			++(state->argv.arg.from);

			if (parse_row_count(&tbl_spec->row_count,
					    &state->argv)) {
				state->specs.db->tbl_specs = tbl_spec;
				state->specs.tbl = tbl_spec;

				/* set initial counter values */
				database_counter_init(&state->database,
						      tbl_spec->row_count);

				parse_first_col_spec_safe(state);
				return;
			}
		}
	}
	generate_parse_error(state);
}


inline void
parse_next_tbl_spec(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_inc_db_spec_tbl_name(state);
		return;
	}

	state->specs.tbl->next
	= (struct TblSpec *) state->specs.tbl->col_specs.until;

	state->specs.tbl = state->specs.tbl->next;

	if (!parse_tbl_name(&state->specs.tbl->name,
			    &state->argv)) {
		generate_parse_error(state);
		return;
	}

	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_inc_db_spec_row_count(state);
		return;
	}

	if (!parse_row_count(&state->specs.tbl->row_count,
			     &state->argv)) {
		generate_parse_error(state);
		return;
	}

	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		error_inc_db_spec_col_flag(state);
		return;
	}

	/* set counter values */
	state->database.rows += state->specs.tbl->row_count;

	if (state->specs.tbl->row_count > state->database.row_count_max)
		state->database.row_count_max = state->specs.tbl->row_count;

	state->database.tables += 1u;

	parse_first_col_spec(state);
}




/* DB_SPEC */
inline void
parse_first_db_spec(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (parse_db_name(&state->specs.db->name,
			  &state->argv))
		parse_first_tbl_spec(state);
	else
		generate_parse_error(state);
}


inline void
parse_next_db_spec(struct GenerateParseState *const restrict state)
{
	if (state->argv.arg.from < state->argv.db_spec.until) {
		state->argv.db_spec.from = state->argv.arg.from;

		++(state->argv.arg.from);

		if (parse_db_name(&state->specs.db->name,
				  &state->argv))
			parse_first_tbl_spec(state);
		else
			generate_parse_error(state);

	} else {
		if (state->argv.arg.from < state->argv.arg.until)
			short_db_spec(&state->argv); /* error spec too short */

		*(state->valid.last) = NULL; /* terminate valid db_specs */
		state->exit_status = EXIT_FAILURE;
	}
}


inline void
generate_parse_error(struct GenerateParseState *const restrict state)
{
	state->exit_status = EXIT_FAILURE;

	/* find next DB_SPEC */
	state->argv.arg.from = flag_match_next(state->argv.arg.from + 1l,
					       state->argv.arg.until,
					       'd',
					       "database");

	parse_next_db_spec(state);
}


inline void
parse_db_specs(struct GenerateParseState *const restrict state)
{
	if (db_flag_match(&state->argv))
		parse_first_db_spec(state);
	else
		generate_parse_error(state);
}


inline int
generate_dispatch(char *const restrict *const restrict arg,
		  const int rem_argc)
{
	if (rem_argc == 0lu) {
		generate_failure_no_db_spec();
		return EXIT_FAILURE;
	}
	/* calculate max required size for all components + their specs
	 *
	 *
	 * minimal valid (i.e. most memory dense) input for GENERATE MODE:
	 *
	 *                      ARGV - 9 args
	 * ┌──────────────────────────────────────────────────────┐
	 * │                     DB_SPEC - 8 args                 │
	 * │  ┌───────────────────────────────────────────────────┐
	 * │  │                        TBL_SPEC - 6 args          │
	 * │  │          ┌────────────────────────────────────────┐
	 * │  │          │                      COL_SPEC - 3 args │
	 * │  │          │                     ┌──────────────────┐
	 * │  │          │                     │                  │
	 * -g -D DB_NAME -T TBL_NAME ROW_COUNT -c COL_NAME COL_TYPE
	 *
	 * generates 1 database with 1 table with 1 column
	 *
	 *
	 * extreme valid cases (mac = argc - 1 for leading mode flag)
	 *
	 * (a) DB_SPEC count maximized, need memory for:
	 *                                      always 1 or 0
	 *	DbSpec  X DB_CNT  = mac / 8    ┌─────────────┐
	 *	TblSpec X TBL_CNT = DB_CNT  +  ((mac % 8) / 6)
	 *	ColSpec X COL_CNT = TBL_CNT + (((mac % 8) % 6) / 3)
	 *	                              └───────────────────┘
	 *	with                                always 0
	 *
	 *	((mac % 8) % 6) % 3
	 *
	 *	args leftover for storage-free COL_TYPE_Qs
	 *
	 *
	 * (b) TBL_SPEC count maximized, need memory for:
	 *
	 *	DbSpec  X DB_CNT  = 1
	 *	TblSpec X TBL_CNT = (mac - 2) / 6
	 *	ColSpec X COL_CNT = TBL_CNT + (((mac - 2) % 6) / 3)
	 *	                              └───────────────────┘
	 *	with                              always 1 or 0
	 *
	 *	((mac - 2) % 6) % 3
	 *
	 *	args leftover for COL_TYPE_Qs
	 *
	 *
	 * (c) COL_SPEC count maximized, need memory for:
	 *
	 *	DbSpec	X DB_CNT  = 1
	 *	TblSpec	X TBL_CNT = 1
	 *	ColSpec	X COL_CNT = (margc - 5) / 3
	 *
	 *	with
	 *
	 *	(margc - 5) % 3
	 *
	 *	args leftover for COL_TYPE_Qs
	 *
	 *
	 *						overhead
	 * struct ColSpec {
	 *	struct String name;			1 pointer + 1 size_t
	 *	union TypeQualifier type_q	        2 ldbls + 1 uint (max)
	 *	struct GrpSpec grp_spec;                1 pointer + 1 size_t
	 *	Procedure *build;			1 pointer
	 * };						────────────────
	 *						3 pointer + 2 size_t
	 *						+ 2 ldbls + 1 uint
	 *
	 * struct TblSpec {
	 *	struct String name;			1 pointer + 1 size_t
	 *	size_t row_count			1 size_t
	 *	struct ColSpecInterval col_specs;	2 pointers
	 *	struct TblSpec *next;			1 pointer
	 * };						────────────────
	 *						4 pointers + 2 size_t
	 *
	 * struct DbSpec {
	 *	struct String name;			1 pointer + 1 size_t
	 *	struct TblSpec *tbl_specs;		1 pointer
	 *	struct DbSpec *next;			1 pointer
	 * };						────────────────
	 *						3 pointers + 1 size_t
	 *
	 * worst case for allocing specs appears to be (c) */

	char *const restrict *const restrict arg_until = arg + rem_argc;
	char *const restrict *const restrict db_spec_until = arg_until
							   + 1l
							   - DB_SPEC_LENGTH_MIN;

	if (arg >= db_spec_until) {
		generate_failure_short_db_spec(arg,
					       arg_until);
		return EXIT_FAILURE;
	}

	struct DbSpec *const restrict
	spec_alloc = malloc(sizeof(struct DbSpec)
			    + sizeof(struct TblSpec)
			    + (sizeof(struct ColSpec)
			       * ((rem_argc - 5) / 3)));

	if (spec_alloc == NULL) {
		generate_failure_malloc();
		return EXIT_FAILURE;
	}

	/* initialize parsing state */
	struct GenerateParseState state;

	state.argv.arg.from	 = arg;
	state.argv.arg.until	 = arg_until;
	state.argv.db_spec.until = db_spec_until;

	state.specs.db = spec_alloc;

	state.generator.ctor_flags    = 0u;
	state.generator.rows	      = 0llu;
	state.generator.row_count_max = 0lu;
	state.generator.columns	      = 0u;
	state.generator.tables	      = 0u;
	state.generator.databases     = 0u;
	state.generator.counter_upto  = 0lu;

	state.valid.last  = &state.valid.head;

	state.exit_status = EXIT_SUCCESS;


	/* populate specs according to argv */
	parse_db_specs(&state);

	if (state.generator.databases == 0u) {
		generate_failure_no_valid_db_spec();
		free(spec_alloc);
		return EXIT_FAILURE;
	}
#if 0
	for (struct DbSpec *db_spec = state.valid.head;
	     db_spec != NULL;
	     db_spec = db_spec->next) {

		printf("db_name: %s\n", db_spec->name.bytes);

		for (struct TblSpec *tbl_spec = db_spec->tbl_specs;
		     tbl_spec != NULL;
		     tbl_spec = tbl_spec->next) {
			printf("\ttbl_name:  %s\n",  tbl_spec->name.bytes);
			printf("\trow_count: %zu\n", tbl_spec->row_count);

			for (struct ColSpec *col_spec = tbl_spec->col_specs.from;
			     col_spec < tbl_spec->col_specs.until;
			     ++col_spec) {
				printf("\t\tcol_name:  %s\n", col_spec->name.bytes);
			}
		}
	}

	printf("ctor_flags:    %u\n"
	       "rows:          %lu\n"
	       "row_count_max: %zu\n"
	       "columns:       %u\n"
	       "tables:        %u\n"
	       "databases:     %u\n"
	       "counter_upto:  %zu\n"
	       "exit_status:   EXIT_%s\n",
	       state.generator.ctor_flags,
	       state.generator.rows,
	       state.generator.row_count_max,
	       state.generator.columns,
	       state.generator.tables,
	       state.generator.databases,
	       state.generator.counter_upto,
	       state.exit_status == EXIT_SUCCESS ? "SUCCESS" : "FAILURE");

	free(spec_alloc);
	exit(0);
#endif

	mysql_seed_generate(&state.generator,
			    state.valid.head,
			    &state.exit_status);

	free(spec_alloc);

	return state.exit_status;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_ */
