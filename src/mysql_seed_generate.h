#ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_
#define MYSQL_SEED_MYSQL_SEED_GENERATE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/loader.h"		/* build_loader */
#include "generate/column_id.h"		/* build_column_id */
#include "generate/column_string.h"	/* build_column_string_base */
#include "generate/table.h"		/* build_table_header */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define GENERATE_FAILURE(REASON)					\
"\n" FAILURE_HEADER_WRAP("generate", " - " REASON)

#define FAILURE_NO_DB_SPEC						\
GENERATE_FAILURE("no DB_SPEC provided") MORE_INFO_MESSAGE

#define FAILURE_DB_SPEC_SHORT						\
GENERATE_FAILURE("DB_SPEC too short - need at least "			\
		 DB_SPEC_LENGTH_MIN_STRING " arguments to describe "	\
		 "a database in generate mode, ignoring DB_SPEC "	\
		 "starting with:")

#define GENERATE_FAILURE_MALLOC						\
GENERATE_FAILURE(MALLOC_FAILURE_REASON)

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

#define ERROR_INCOMPLETE_DB_SPEC_HEADER					\
PARSE_ERROR_HEADER("incomplete DB_SPEC")

#define ERROR_INCOMPLETE_DB_SPEC_COL_NAME				\
"\n" ERROR_WRAP("reason: expected COL_NAME to follow COLUMN flag, "	\
		"ignoring above DB_SPEC") "\n"

#define ERROR_INCOMPLETE_DB_SPEC_TBL_NAME				\
"\n" ERROR_WRAP("reason: expected TBL_NAME to follow TABLE flag, "	\
		"ignoring above DB_SPEC") "\n"

#define ERROR_INCOMPLETE_DB_SPEC_ROW_COUNT				\
"\n" ERROR_WRAP("reason: expected ROW_COUNT to follow TBL_NAME, "	\
		"ignoring above DB_SPEC") "\n"

#define ERROR_INCOMPLETE_DB_SPEC_COL_FLAG				\
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
"\n" ERROR_WRAP("reason: not a number or overflows implementation-"	\
		"defined uintmax_t, ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_ROW_COUNT_REASON_ZERO				\
"\n" ERROR_WRAP("reason: ROW_COUNT must be ≥ 1, ignoring DB_SPEC "	\
		"starting with:") "\n"

#define ERROR_INVALID_ROW_COUNT_REASON_LARGE				\
"\n" ERROR_WRAP("reason: ROW_COUNT exceeds the system-dependent "	\
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

#define ERROR_INVALID_COL_TYPE_Q_REASON_NOTSUP				\
"\n" ERROR_WRAP("reason: not supported, ignoring DB_SPEC starting "	\
		"with:") "\n"

#define ERROR_NO_STRING_BASE						\
PARSE_ERROR_HEADER("no column base string provided, ignoring DB_SPEC "	\
		   "starting with")

#define ERROR_INVALID_STRING_BASE_EMPTY					\
PARSE_ERROR_HEADER("invalid column base string (empty), ignoring "	\
		   "DB_SPEC starting with")

#define ERROR_INVALID_STRING_BASE_HEADER				\
PARSE_ERROR_HEADER("invalid column base string")

#define ERROR_INVALID_STRING_BASE_REASON_INVALID			\
"\n" ERROR_WRAP("reason: includes one or more invalid UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_STRING_BASE_REASON_LONG				\
"\n" ERROR_WRAP("reason: exceeded maximum of "				\
		STRING_BASE_LENGTH_MAX_STRING " non-null UTF-8 "	\
		"codepoints, ignoring DB_SPEC starting with:") "\n"

/* parsing next SPEC */
#define ERROR_EXPECTED_COL_TBL_DB_FLAG_HEADER				\
PARSE_ERROR_HEADER("expected COLUMN flag, TABLE flag, DATABASE flag, "	\
		   "or end of arguments instead of")


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct GeneratorCounter {
	uintmax_t rows;
	size_t row_count_max;
	unsigned int columns;
	unsigned int tables;
	unsigned int databases;
};

struct DatabaseCounter {
	uintmax_t rows;
	size_t row_count_max;
	unsigned int columns;
	unsigned int tables;
};

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
};


struct GenerateParseState {
	struct GenerateArgvState argv;
	struct GenerateSpecState specs;
	struct GeneratorCounter generator;
	struct DatabaseCounter database;
	struct ValidDbSpecQueue valid;
	int exit_status;
};


/* Generator/DatbaseCounter operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
generator_counter_update(struct GeneratorCounter *const restrict generator,
			 struct DatabaseCounter *const restrict database)
{
	generator->rows      += database->rows;

	if (database->row_count_max > generator->row_count_max)
		generator->row_count_max = database->row_count_max;

	generator->columns   += database->columns;
	generator->tables    += database->tables;
	generator->databases += 1u;
}


/* print error messsage and return 'EXIT_FAILURE'
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
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		     FAILURE_DB_SPEC_SHORT
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(FAILURE_DB_SPEC_SHORT) - 1lu],
			   from,
			   until - 1l);

	*ptr = '\n';

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr + 1l - &buffer[0]);
}

inline void
generate_failure_malloc(void)
{
	write_muffle(STDERR_FILENO,
		     GENERATE_FAILURE_MALLOC,
		     sizeof(GENERATE_FAILURE_MALLOC) - 1lu);
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
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		     ERROR_DB_SPEC_SHORT
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(ERROR_DB_SPEC_SHORT) - 1lu],
			   argv->arg.from,
			   argv->arg.until - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
expected_db_flag(char *const restrict invalid)
{
	char buffer[ARG_INSPECT_BUFFER_SIZE] = {
		ERROR_EXPECTED_DB_FLAG_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_EXPECTED_DB_FLAG_HEADER) - 1lu,
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
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		     ERROR_INVALID_DB_NAME_EMPTY
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(ERROR_INVALID_DB_NAME_EMPTY) - 1lu],
			   argv->db_spec.from,
			   argv->arg.from);


	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_db_name_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_DB_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_DB_NAME_HEADER) - 1lu,
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
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_DB_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_DB_NAME_HEADER) - 1lu,
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
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_EXPECTED_TBL_FLAG_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_EXPECTED_TBL_FLAG_HEADER) - 1lu,
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
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		     ERROR_INVALID_TBL_NAME_EMPTY
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(ERROR_INVALID_TBL_NAME_EMPTY) - 1lu],
			   argv->db_spec.from,
			   argv->arg.from);


	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_tbl_name_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_TBL_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_TBL_NAME_HEADER) - 1lu,
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
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_TBL_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_TBL_NAME_HEADER) - 1lu,
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
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_EXPECTED_COL_FLAG_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_EXPECTED_COL_FLAG_HEADER) - 1lu,
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
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		     ERROR_INVALID_COL_NAME_EMPTY
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(ERROR_INVALID_COL_NAME_EMPTY) - 1lu],
			   argv->db_spec.from,
			   argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_col_name_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_COL_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_COL_NAME_HEADER) - 1lu,
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
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_COL_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_COL_NAME_HEADER) - 1lu,
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
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_ROW_COUNT_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_ROW_COUNT_HEADER) - 1lu,
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
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_ROW_COUNT_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_ROW_COUNT_HEADER) - 1lu,
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
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_ROW_COUNT_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_ROW_COUNT_HEADER) - 1lu,
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
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_NO_COL_TYPE
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(ERROR_NO_COL_TYPE) - 1lu],
			   argv->db_spec.from,
			   argv->arg.from - 1l);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


inline void
invalid_col_type_notsup(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_COL_TYPE_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_COL_TYPE_HEADER) - 1lu,
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
invalid_col_type_q_notsup(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_COL_TYPE_Q_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_COL_TYPE_Q_HEADER) - 1lu,
			     *(argv->arg.from),
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_COL_TYPE_Q_REASON_NOTSUP,
			      sizeof(ERROR_INVALID_COL_TYPE_Q_REASON_NOTSUP)
			      - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


inline void
no_string_base(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_NO_STRING_BASE
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(ERROR_NO_STRING_BASE) - 1lu],
			   argv->db_spec.from,
			   argv->arg.from - 1l);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_string_base_empty(const struct GenerateArgvState *const restrict argv)

{
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		     ERROR_INVALID_STRING_BASE_EMPTY
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(ERROR_INVALID_STRING_BASE_EMPTY) - 1lu],
			   argv->db_spec.from,
			   argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_string_base_invalid(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_STRING_BASE_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_STRING_BASE_HEADER) - 1lu,
			     *(argv->arg.from),
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_STRING_BASE_REASON_INVALID,
			      sizeof(ERROR_INVALID_STRING_BASE_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_string_base_long(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_STRING_BASE_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_STRING_BASE_HEADER) - 1lu,
			     *(argv->arg.from),
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_STRING_BASE_REASON_LONG,
			      sizeof(ERROR_INVALID_STRING_BASE_REASON_LONG)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
expected_col_tbl_db_flag(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_EXPECTED_COL_TBL_DB_FLAG_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_EXPECTED_COL_TBL_DB_FLAG_HEADER)
			     - 1lu,
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

/* incomplete DB_SPEC */
inline void
incomplete_db_spec_col_name(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INCOMPLETE_DB_SPEC_HEADER
	};

	char *restrict ptr
	= put_inspect_args(&buffer[0]
			   + sizeof(ERROR_INCOMPLETE_DB_SPEC_HEADER) - 1lu,
			   argv->db_spec.from,
			   argv->arg.from - 1l);

	ptr = put_string_size(ptr,
			      ERROR_INCOMPLETE_DB_SPEC_COL_NAME,
			      sizeof(ERROR_INCOMPLETE_DB_SPEC_COL_NAME) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
incomplete_db_spec_tbl_name(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INCOMPLETE_DB_SPEC_HEADER
	};

	char *restrict ptr
	= put_inspect_args(&buffer[0]
			   + sizeof(ERROR_INCOMPLETE_DB_SPEC_HEADER) - 1lu,
			   argv->db_spec.from,
			   argv->arg.from - 1l);

	ptr = put_string_size(ptr,
			      ERROR_INCOMPLETE_DB_SPEC_TBL_NAME,
			      sizeof(ERROR_INCOMPLETE_DB_SPEC_TBL_NAME) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
incomplete_db_spec_row_count(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INCOMPLETE_DB_SPEC_HEADER
	};

	char *restrict ptr
	= put_inspect_args(&buffer[0]
			   + sizeof(ERROR_INCOMPLETE_DB_SPEC_HEADER) - 1lu,
			   argv->db_spec.from,
			   argv->arg.from - 1l);

	ptr = put_string_size(ptr,
			      ERROR_INCOMPLETE_DB_SPEC_ROW_COUNT,
			      sizeof(ERROR_INCOMPLETE_DB_SPEC_ROW_COUNT) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


inline void
incomplete_db_spec_col_flag(const struct GenerateArgvState *const restrict argv)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INCOMPLETE_DB_SPEC_HEADER
	};

	char *restrict ptr
	= put_inspect_args(&buffer[0]
			   + sizeof(ERROR_INCOMPLETE_DB_SPEC_HEADER) - 1lu,
			   argv->db_spec.from,
			   argv->arg.from - 1l);

	ptr = put_string_size(ptr,
			      ERROR_INCOMPLETE_DB_SPEC_COL_FLAG,
			      sizeof(ERROR_INCOMPLETE_DB_SPEC_COL_FLAG) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
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

	size_t rem_length = DB_NAME_LENGTH_MAX;

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

		--rem_length;

		if (rem_length == 0lu) {
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

	size_t rem_length = TBL_NAME_LENGTH_MAX;

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

		--rem_length;

		if (rem_length == 0lu) {
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

	size_t rem_length = COL_NAME_LENGTH_MAX;

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

		--rem_length;

		if (rem_length == 0lu) {
			invalid_col_name_long(argv);
			return false;
		}
	}
}


inline bool
parse_string_base(struct String *const restrict base,
		  struct GenerateArgvState *const restrict argv)
{
	const octet_t *restrict octets
	= (const octet_t *restrict) *(argv->arg.from);

	if (*octets == '\0') {
		invalid_string_base_empty(argv);
		return false;
	}

	unsigned int width;

	size_t rem_length = STRING_BASE_LENGTH_MAX;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u) {
			invalid_string_base_invalid(argv);
			return false;
		}

		octets += width;

		if (*octets == '\0') {
			base->bytes  = *(argv->arg.from);
			base->length = octets
					- ((const octet_t *const restrict)
					   base->bytes);
			return true;
		}

		--rem_length;

		if (rem_length == 0lu) {
			invalid_string_base_long(argv);
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

	if (!parse_uint(&parsed,
			*(argv->arg.from))) {
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
parse_column_complete(struct GenerateParseState *const restrict state)
{
	if (state->argv.arg.from == state->argv.arg.until) {
		generate_parse_complete(state);
		return;
	}

	char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
EXPECTED_COL_TBL_DB_FLAG:
		expected_col_tbl_db_flag(&state->argv);
		++(state->argv.arg.from);
		generate_parse_error(state);
		return;
	}

	++arg;
	char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break; /* parse long SPEC */

	case 'c':
		if (*rem == '\0') {
			parse_next_col_spec(state);
			return;
		}
		goto EXPECTED_COL_TBL_DB_FLAG;

	case 'd':
		if (*rem == '\0') {
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}
		goto EXPECTED_COL_TBL_DB_FLAG;

	case 't':
		if (*rem == '\0') {
			parse_table_complete(state);
			parse_next_tbl_spec(state);
			return;
		}
		goto EXPECTED_COL_TBL_DB_FLAG;

	default:
		goto EXPECTED_COL_TBL_DB_FLAG;
	}

	switch (*rem) {
	case 'c':
		if (strings_equal("olumn", rem + 1l)) {
			parse_next_col_spec(state);
			return;
		}
		goto EXPECTED_COL_TBL_DB_FLAG;

	case 'd':
		if (strings_equal("atabase", rem + 1l)) {
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}
		goto EXPECTED_COL_TBL_DB_FLAG;

	case 't':
		if (strings_equal("able", rem + 1l)) {
			parse_table_complete(state);
			parse_next_tbl_spec(state);
			return;
		}
		goto EXPECTED_COL_TBL_DB_FLAG;

	default:
		goto EXPECTED_COL_TBL_DB_FLAG;
	}
}


/* parse spec groups
 *─────────────────────────────────────────────────────────────────────────── */
/* COL_SPEC */
inline void
col_spec_set_string_default(struct ColSpec *const restrict col_spec)
{
	col_spec->create = &build_column_string_base;
	col_spec->type.string.base = col_spec->name;
}

inline void
parse_string_qualifier(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		col_spec_set_string_default(state->specs.col);
		generate_parse_complete(state); /* done parsing */
		return;
	}

	const char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
INVALID_STRING_QUALIFIER_NOTSUP:
		invalid_col_type_q_notsup(&state->argv);
		++(state->argv.arg.from);
		generate_parse_error(state);
		return;
	}

	++arg;
	const char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break;	/* parse long string qualifier */

	case 'b':
		if (*rem == '\0') {
			++(state->argv.arg.from);

			if (state->argv.arg.from == state->argv.arg.until) {
INCOMPLETE_NO_STRING_BASE:
				no_string_base(&state->argv);
				*(state->valid.last) = NULL;
				state->exit_status = EXIT_FAILURE;
				return;
			}

			const bool valid_string_base
			= parse_string_base(&state->specs.col->type.string.base,
					    &state->argv);

			++(state->argv.arg.from);

			if (valid_string_base) {
				state->specs.col->create
				= &build_column_string_base;
				parse_column_complete(state);
			} else {
				generate_parse_error(state);
			}
			return;
		}
		goto INVALID_STRING_QUALIFIER_NOTSUP;

	case 'c':
		if (*rem == '\0') {
			col_spec_set_string_default(state->specs.col);
			parse_next_col_spec(state);
			return;
		}
		goto INVALID_STRING_QUALIFIER_NOTSUP;

	case 'd':
		if (*rem == '\0') {
			col_spec_set_string_default(state->specs.col);
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}
		goto INVALID_STRING_QUALIFIER_NOTSUP;

	case 't':
		if (*rem == '\0') {
			parse_table_complete(state);
			parse_next_tbl_spec(state);
			return;
		}
		goto INVALID_STRING_QUALIFIER_NOTSUP;

	default:
		goto INVALID_STRING_QUALIFIER_NOTSUP;
	}


	switch (*rem) {
	case 'b':
		if (strings_equal("ase", rem + 1l)) {
			++(state->argv.arg.from);

			if (state->argv.arg.from == state->argv.arg.until)
				goto INCOMPLETE_NO_STRING_BASE;

			const bool valid_string_base
			= parse_string_base(&state->specs.col->type.string.base,
					    &state->argv);

			++(state->argv.arg.from);

			if (valid_string_base) {
				state->specs.col->create
				= &build_column_string_base;
				parse_column_complete(state);
			} else {
				generate_parse_error(state);
			}
			return;
		}
		goto INVALID_STRING_QUALIFIER_NOTSUP;

	case 'c':
		if (strings_equal("olumn", rem + 1l)) {
			col_spec_set_string_default(state->specs.col);
			parse_next_col_spec(state);
			return;
		}
		goto INVALID_STRING_QUALIFIER_NOTSUP;

	case 'd':
		if (strings_equal("atabase", rem + 1l)) {
			col_spec_set_string_default(state->specs.col);
			parse_database_complete(state);
			parse_next_db_spec(state);
			return;
		}
		goto INVALID_STRING_QUALIFIER_NOTSUP;

	case 't':
		if (strings_equal("able", rem + 1l)) {
			parse_table_complete(state);
			parse_next_tbl_spec(state);
			return;
		}
		goto INVALID_STRING_QUALIFIER_NOTSUP;

	default:
		goto INVALID_STRING_QUALIFIER_NOTSUP;
	}
}

inline void
parse_col_type(struct GenerateParseState *const restrict state)
{
	const char *restrict arg = *(state->argv.arg.from);

	if (*arg != '-') {
INVALID_COL_TYPE_NOTSUP:
		invalid_col_type_notsup(&state->argv);
		++(state->argv.arg.from);
		generate_parse_error(state);
		return;
	}

	++arg;
	const char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break;	/* parse long COL_TYPE */

	case 's':
		if (*rem == '\0') {
			parse_string_qualifier(state);
			return;
		}
		goto INVALID_COL_TYPE_NOTSUP;

	default:
		goto INVALID_COL_TYPE_NOTSUP;
	}

	/* long COL_TYPE */
	switch (*rem) {
	case 's':
		if (strings_equal("tring", rem + 1l)) {
			parse_string_qualifier(state);
			return;
		}
		goto INVALID_COL_TYPE_NOTSUP;

	default:
		goto INVALID_COL_TYPE_NOTSUP;
	}
}

inline void
parse_first_col_spec_safe(struct GenerateParseState *const restrict state)
{
	const bool matched_col_flag = col_flag_match(&state->argv);

	++(state->argv.arg.from);

	if (matched_col_flag) {
		struct ColSpec *restrict col_spec
		= (struct ColSpec *restrict) (state->specs.tbl + 1l);

		/* reserve first column for 'id' */
		col_spec->name.bytes  = "id";
		col_spec->name.length = 2lu;
		col_spec->create = &build_column_id;

		state->specs.tbl->col_specs.from = col_spec;

		++col_spec;


		const bool valid_col_name = parse_col_name(&col_spec->name,
							   &state->argv);

		++(state->argv.arg.from);

		if (valid_col_name) {
			state->specs.col = col_spec;

			state->database.columns = 2u; /* set column counter */

			parse_col_type(state);

		} else {
			generate_parse_error(state);
		}
	} else {
		generate_parse_error(state);
	}
}


inline void
parse_first_col_spec(struct GenerateParseState *const restrict state)
{
	const bool matched_col_flag = col_flag_match(&state->argv);

	++(state->argv.arg.from);

	if (!matched_col_flag) {
		generate_parse_error(state);
		return;
	}

	if (state->argv.arg.from == state->argv.arg.until) {
		incomplete_db_spec_col_name(&state->argv);
TERMINATE_VALID_EXIT_FAILURE:
		*(state->valid.last) = NULL;
		state->exit_status = EXIT_FAILURE;
		return;
	}

	struct ColSpec *restrict col_spec
	= (struct ColSpec *restrict) (state->specs.tbl + 1l);

	/* reserve first column for 'id' */
	col_spec->name.bytes  = "id";
	col_spec->name.length = 2lu;
	col_spec->create = &build_column_id;

	state->specs.tbl->col_specs.from = col_spec;

	++col_spec;

	const bool valid_col_name = parse_col_name(&col_spec->name,
						   &state->argv);

	++(state->argv.arg.from);

	if (!valid_col_name) {
		generate_parse_error(state);
		return;
	}

	if (state->argv.arg.from == state->argv.arg.until) {
		no_col_type(&state->argv);
		goto TERMINATE_VALID_EXIT_FAILURE;
	}

	state->specs.col = col_spec;

	state->database.columns += 2u; /* set column counter */

	parse_col_type(state);
}


inline void
parse_next_col_spec(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		incomplete_db_spec_col_name(&state->argv);
TERMINATE_VALID_EXIT_FAILURE:
		*(state->valid.last) = NULL;
		state->exit_status = EXIT_FAILURE;
		return;
	}

	++(state->specs.col);

	const bool valid_col_name
	= parse_col_name(&state->specs.col->name,
			 &state->argv);

	++(state->argv.arg.from);

	if (!valid_col_name) {
		generate_parse_error(state);
		return;
	}

	if (state->argv.arg.from == state->argv.arg.until) {
		no_col_type(&state->argv);
		goto TERMINATE_VALID_EXIT_FAILURE;
	}

	state->database.columns += 1u;

	parse_col_type(state);
}


/* TBL_SPEC */
inline void
parse_first_tbl_spec(struct GenerateParseState *const restrict state)
{
	const bool matched_tbl_flag = tbl_flag_match(&state->argv);

	++(state->argv.arg.from);

	if (matched_tbl_flag) {

		struct TblSpec *const restrict tbl_spec
		= (struct TblSpec *const restrict) (state->specs.db + 1l);

		const bool valid_tbl_name = parse_tbl_name(&tbl_spec->name,
							   &state->argv);

		++(state->argv.arg.from);

		if (valid_tbl_name) {

			const bool valid_row_count
			= parse_row_count(&tbl_spec->row_count,
					  &state->argv);

			++(state->argv.arg.from);

			if (valid_row_count) {
				state->specs.db->tbl_specs = tbl_spec;
				state->specs.tbl = tbl_spec;

				/* set initial counter values */
				state->database.rows = tbl_spec->row_count;
				state->database.row_count_max
				= tbl_spec->row_count;
				state->database.tables = 1u;

				parse_first_col_spec_safe(state);

			} else {
				generate_parse_error(state);
			}
		} else {
			generate_parse_error(state);
		}
	} else {
		generate_parse_error(state);
	}
}


inline void
parse_next_tbl_spec(struct GenerateParseState *const restrict state)
{
	++(state->argv.arg.from);

	if (state->argv.arg.from == state->argv.arg.until) {
		incomplete_db_spec_tbl_name(&state->argv);
TERMINATE_VALID_EXIT_FAILURE:
		*(state->valid.last) = NULL;
		state->exit_status = EXIT_FAILURE;
		return;
	}

	state->specs.tbl->next
	= (struct TblSpec *) state->specs.tbl->col_specs.until;

	state->specs.tbl = state->specs.tbl->next;

	const bool valid_tbl_name
	= parse_tbl_name(&state->specs.tbl->name,
			 &state->argv);

	++(state->argv.arg.from);

	if (!valid_tbl_name) {
		generate_parse_error(state);
		return;
	}

	if (state->argv.arg.from == state->argv.arg.until) {
		incomplete_db_spec_row_count(&state->argv);
		goto TERMINATE_VALID_EXIT_FAILURE;
	}

	const bool valid_row_count
	= parse_row_count(&state->specs.tbl->row_count,
			  &state->argv);

	++(state->argv.arg.from);

	if (!valid_row_count) {
		generate_parse_error(state);
		return;
	}

	if (state->argv.arg.from == state->argv.arg.until) {
		incomplete_db_spec_col_flag(&state->argv);
		goto TERMINATE_VALID_EXIT_FAILURE;
	}

	/* state->specs.db->tbl_specs = state->specs.tbl; */

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
	const bool valid_db_name = parse_db_name(&state->specs.db->name,
						 &state->argv);

	++(state->argv.arg.from);

	if (valid_db_name)
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

		const bool valid_db_name
		= parse_db_name(&state->specs.db->name,
				&state->argv);

		++(state->argv.arg.from);

		if (valid_db_name)
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
	state->argv.arg.from = flag_match_next(state->argv.arg.from,
					       state->argv.arg.until,
					       'd',
					       "database");

	parse_next_db_spec(state);
}


inline void
parse_db_specs(struct GenerateParseState *const restrict state)
{
	const bool matched_db_flag = db_flag_match(&state->argv);

	++(state->argv.arg.from);

	if (matched_db_flag)
		parse_first_db_spec(state);
	else
		generate_parse_error(state);
}

inline void
generate_process(const struct GeneratorCounter *const restrict count,
		 const struct DbSpec *restrict db_spec,
		 int *const restrict exit_status)
{
}


inline int
generate_dispatch(char *restrict *const restrict arg,
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
	 * -g -d DB_NAME -t TBL_NAME ROW_COUNT -c COL_NAME COL_TYPE
	 *
	 * generates 1 database with 1 table with 2 columns (1st column of every
	 * table is reserved for primary key, 'id')
	 *
	 *
	 * extreme valid cases (mac = argc - 1 for leading mode flag)
	 *
	 * (a) DB_SPEC count maximized, need memory for:
	 *                                      always 1 or 0
	 *	DbSpec  X DB_CNT  = mac / 8    ┌─────────────┐
	 *	TblSpec X TBL_CNT = DB_CNT  +  ((mac % 8) / 6)
	 *	ColSpec X COL_CNT = (2 * TBL_CNT) + (((mac % 8) % 6) / 3)
	 *	                                    └───────────────────┘
	 *	with                                       always 0
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
	 *	ColSpec X COL_CNT = (2 * TBL_CNT) + (((mac - 2) % 6) / 3)
	 *	                                    └───────────────────┘
	 *	with                                     always 1 or 0
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
	 *	ColSpec	X COL_CNT = (margc - 5) / 3 + 1
	 *                                            └ TBL_CNT
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
	 *	union TypeQualifier			2 ldbls + 1 uint (max)
	 *	Procedure *create;			1 pointer
	 * };						────────────────
	 *						2 pointer + 1 size_t
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
			       * ((rem_argc - 6) / 3) + 1));

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

	state.generator.rows	      = 0llu;
	state.generator.row_count_max = 0lu;
	state.generator.columns	      = 0u;
	state.generator.tables	      = 0u;
	state.generator.databases     = 0u;

	state.valid.last  = &state.valid.head;

	state.exit_status = EXIT_SUCCESS;


	/* populate specs according to argv */
	parse_db_specs(&state);

	if (state.generator.databases == 0u) {
		generate_failure_no_valid_db_spec();

		free(spec_alloc);

		return EXIT_FAILURE;
	}

	/* for (struct DbSpec *db_spec = state.valid.head; */
	/*      db_spec != NULL; */
	/*      db_spec = db_spec->next) { */

	/* 	printf("db_name: %s\n", db_spec->name.bytes); */

	/* 	for (struct TblSpec *tbl_spec = db_spec->tbl_specs; */
	/* 	     tbl_spec != NULL; */
	/* 	     tbl_spec = tbl_spec->next) { */
	/* 		printf("\ttbl_name:  %s\n",  tbl_spec->name.bytes); */
	/* 		printf("\trow_count: %zu\n", tbl_spec->row_count); */

	/* 		for (struct ColSpec *col_spec = tbl_spec->col_specs.from; */
	/* 		     col_spec < tbl_spec->col_specs.until; */
	/* 		     ++col_spec) { */
	/* 			printf("\t\tcol_name:  %s\n", col_spec->name.bytes); */
	/* 		} */
	/* 	} */
	/* } */

	/* printf("rows:          %lu\n" */
	/*        "row_count_max: %zu\n" */
	/*        "columns:       %u\n" */
	/*        "tables:        %u\n" */
	/*        "databases:     %u\n" */
	/*        "exit_status:   EXIT_%s\n", */
	/*        state.generator.rows, */
	/*        state.generator.row_count_max, */
	/*        state.generator.columns, */
	/*        state.generator.tables, */
	/*        state.generator.databases, */
	/*        state.exit_status == EXIT_SUCCESS ? "SUCCESS" : "FAILURE"); */

	generate_process(&state.generator,
			 state.valid.head,
			 &state.exit_status);

	free(spec_alloc);

	return state.exit_status;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_ */
