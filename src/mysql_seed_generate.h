#ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_
#define MYSQL_SEED_MYSQL_SEED_GENERATE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h" /* file/exit/string/parallelization utils */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define GENERATE_FAILURE(REASON)					\
FAILURE_HEADER_WRAP("generate", " - " REASON)

#define GENERATE_FAILURE_MALLOC						\
GENERATE_FAILURE(MALLOC_FAILURE_REASON)

#define GENERATE_FAILURE_NO_VALID_DB_SPEC				\
GENERATE_FAILURE("no valid DB_SPEC")

#define IGNORING_DB_SPEC						\
"\n" ERROR_WRAP("ignoring DB_SPEC") "\n"

#define IGNORING_DB_SPEC_STARTING_WITH					\
"\n" ERROR_WRAP("ignoring DB_SPEC starting with:") "\n"

/* parsing DB_SPEC */
#define FAILURE_NO_DB_SPEC						\
PARSE_FAILURE_MESSAGE("no DB_SPEC provided") MORE_INFO_MESSAGE

#define ERROR_DB_SPEC_SHORT						\
PARSE_ERROR_MESSAGE("DB_SPEC too short - need at least "		\
		    DB_SPEC_LENGTH_MIN_STRING " arguments to describe "	\
		    "a database in generate mode, ignoring final "	\
		    "DB_SPEC starting with:") "\n"

#define ERROR_EXPECTED_DB_FLAG_HEADER					\
PARSE_ERROR_HEADER("expected DATABASE flag instead of:")

/* parsing DB_NAME */
#define ERROR_INVALID_DB_NAME_HEADER					\
PARSE_ERROR_HEADER("invalid DB_NAME")

#define ERROR_INVALID_DB_NAME_EMPTY					\
PARSE_ERROR_HEADER("invalid DB_NAME (empty), ignoring DB_SPEC starting"	\
		   " with:")

#define ERROR_INVALID_DB_NAME_REASON_LONG				\
"\n" ERROR_WRAP("reason: exceeded MySql maximum of "			\
		DB_NAME_LENGTH_MAX_STRING " non-null UTF-8 codepoints,"	\
		" ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_DB_NAME_REASON_INVALID				\
"\n" ERROR_WRAP("reason: includes one or more invalid UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

/* parsing TBL_SPEC */
#define ERROR_EXPECTED_TBL_FLAG_HEADER					\
PARSE_ERROR_HEADER("expected TABLE flag instead of:")

/* parsing TBL_NAME */
#define ERROR_INVALID_TBL_NAME_HEADER					\
PARSE_ERROR_HEADER("invalid TBL_NAME")

#define ERROR_INVALID_TBL_NAME_EMPTY					\
PARSE_ERROR_HEADER("invalid TBL_NAME (empty), ignoring DB_SPEC "	\
		   "starting with:")

#define ERROR_INVALID_TBL_NAME_REASON_LONG				\
"\n" ERROR_WRAP("reason: exceeded MySql maximum of "			\
		TBL_NAME_LENGTH_MAX_STRING " non-null UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_TBL_NAME_REASON_INVALID				\
"\n" ERROR_WRAP("reason: includes one or more invalid UTF-8 codepoints"	\
		", ignoring DB_SPEC starting with:") "\n"

/* parsing COL_SPEC */
#define ERROR_EXPECTED_COL_FLAG_HEADER					\
PARSE_ERROR_HEADER("expected COLUMN flag instead of:")

/* parsing COL_NAME */
#define ERROR_INVALID_COL_NAME_HEADER					\
PARSE_ERROR_HEADER("invalid COL_NAME")

#define ERROR_INVALID_COL_NAME_EMPTY					\
PARSE_ERROR_HEADER("invalid COL_NAME (empty), ignoring DB_SPEC "	\
		   "starting with:")

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
#define ERROR_INVALID_COL_TYPE_HEADER					\
PARSE_ERROR_HEADER("invalid COL_TYPE")

#define ERROR_INVALID_COL_TYPE_REASON_INVALID				\
"\n" ERROR_WRAP("reason: invalid, ignoring DB_SPEC starting with:") "\n"

#define ERROR_INVALID_COL_TYPE_REASON_NOTSUP				\
"\n" ERROR_WRAP("reason: not supported, ignoring DB_SPEC starting with:") "\n"


/* parsing COL_TYPE_Q */
#define ERROR_INVALID_COL_TYPE_Q_HEADER					\
PARSE_ERROR_HEADER("invalid COL_TYPE_Q")

#define ERROR_INVALID_COL_TYPE_Q_REASON_INVALID				\
"\n" ERROR_WRAP("reason: not supported, ignoring DB_SPEC starting "	\
		"with:") "\n"

/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct GeneratorCounter {
	uintmax_t rows;
	unsigned int columns;
	unsigned int tables;
	unsigned int databases;
};

struct DatabaseCounter {
	uintmax_t rows;
	unsigned int columns;
	unsigned int tables;
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
	int exit_status;
};


/* Generator/DatbaseCounter operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
database_counter_reset(struct DatabaseCounter *const restrict database)
{
	database->rows    = 0llu;
	database->columns = 0u;
	database->tables  = 0u;
}

inline void
generator_counter_increment(struct GeneratorCounter *const restrict generator,
			    struct DatabaseCounter *const restrict database)
{
	generator->rows      += database->rows;
	generator->columns   += database->columns;
	generator->tables    += database->tables;
	generator->databases += 1u;
}


/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
/* irrecoverable failures */
inline void
no_db_spec(void)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_NO_DB_SPEC,
		     sizeof(FAILURE_NO_DB_SPEC) - 1lu);
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
			   argv->db_spec.from,
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
invalid_col_type_invalid(const struct GenerateArgvState *const restrict argv)
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
			      ERROR_INVALID_COL_TYPE_REASON_INVALID,
			      sizeof(ERROR_INVALID_COL_TYPE_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       argv->db_spec.from,
			       argv->arg.from);

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

	if (!matched_db_flag)
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

extern inline bool
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
parse_next_db_spec(struct GenerateParseState *const restrict state);
inline void
generate_parse_error(struct GenerateParseState *const restrict state);


/* finished parsing
 *─────────────────────────────────────────────────────────────────────────── */
inline void
parse_db_spec_complete(struct GenerateParseState *const restrict state)
{
}

inline void
parse_generate_complete(struct GenerateParseState *const restrict state)
{
	state->specs.db->next  = NULL;

	state->specs.tbl->col_specs.until = state->specs.col + 1l;

	state->specs.tbl->next = NULL;

	generator_counter_increment(&state->generator,
				    &state->database);
}


/* parse spec groups
 *─────────────────────────────────────────────────────────────────────────── */
/* COL_SPEC */
inline void
parse_string_qualifiers(struct GenerateParseState *const restrict state)
{
	struct ColSpec *const restrict col_spec = state->specs.col;

	++(state->argv.arg.from);

	if (state->argv.arg.from < state->argv.arg.until) {

		const char *restrict arg;
		const char *restrict rem;

		arg = *(state->argv.arg.from);
		rem = arg + 1l;

		switch (*arg) {
		case '-':
			break;	/* parse long string qualifier */

		case 'r':
			if (*rem == '\0')
		}


		switch (*arg) {

INVALID_FLOAT_QUALIFIER:
		}
	} else {
		col_spec->create = NULL;	/* TODO: default string */

		parse_generate_complete(state); /* done parsing */
	}
}

inline void
parse_col_type(struct GenerateParseState *const restrict state)
{
	const char *restrict arg;
	const char *restrict rem;

	arg = *(state->argv.arg.from);

	if (*arg == '-') {
		++arg;
		rem = arg + 1l;


		switch (*arg) {
		case '-':
			break;	/* parse long COL_TYPE */

		case 's':
			if (*rem == '\0')
				parse_string_qualifiers(state)
			else
				goto INVALID_COL_TYPE;

		default:
			goto INVALID_COL_TYPE;
		}

		/* long COL_TYPE */
		switch (*rem) {
		case 's':
			if (strings_equal("tring", rem + 1))
				parse_string_qualifiers(state)
			else
				goto INVALID_COL_TYPE;

		default:
			goto INVALID_COL_TYPE;
		}

	} else {
INVALID_COL_TYPE:
		invalid_col_type_invalid(&state->argv);

		++(state->argv.arg.from);

		generate_parse_error(state);
	}
}

inline void
parse_first_col_spec(struct GenerateParseState *const restrict state)
{
	const bool matched_col_flag = col_flag_match(&state->argv);

	++(state->argv.arg.from);

	if (matched_col_flag) {
		struct ColSpec *const restrict col_spec
		= (struct ColSpec *const restrict) (state->specs.tbl + 1l);

		const bool valid_col_name = parse_col_name(&col_spec->name,
							   &state->argv);

		++(state->argv.arg.from);

		if (valid_col_name) {
			state->specs.tbl->col_specs.from = col_spec;

			state->specs.col = col_spec;

			/* set column counter */
			state->database.columns = 1u;

			parse_col_type(state);

		} else {
			generate_parse_error(state);
		}
	} else {
		generate_parse_error(state);
	}
}


/* TBL_SPEC */
inline void
parse_rem_tbl_specs(struct GenerateParseState *const restrict state)
{
}


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

				/* set initial counter values */
				state->database.rows   = tbl_spec->row_count;
				state->database.tables = 1u;

				parse_first_col_spec(state);

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


/* DB_SPEC */
inline void
parse_next_db_spec(struct GenerateParseState *const restrict state)
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
generate_parse_error(struct GenerateParseState *const restrict state)
{
	state->exit_status = EXIT_FAILURE;

	/* find next DB_SPEC */
	state->argv.db_spec.from = flag_match_next(state->argv.arg.from,
						   state->argv.arg.until,
						   'd',
						   "database");

	if (state->argv.db_spec.from < state->argv.db_spec.until) {
		state->argv.arg.from = state->argv.db_spec.from + 1l;

		parse_next_db_spec(state);

	} else {
		state->specs.db->next = NULL; /* done parsing */

		if (state->argv.db_spec.from < state->argv.arg.until)
			short_db_spec(&state->argv); /* error spec too short */
	}
}


inline void
parse_db_specs(struct GenerateParseState *const restrict state)
{

	const bool matched_db_flag = db_flag_match(&state->argv);

	++(state->argv.arg.from);

	if (matched_db_flag)
		parse_next_db_spec(state);
	else
		generate_parse_error(state);
}



inline int
generate_dispatch(char *restrict *const restrict arg,
		  const int rem_argc)
{
	if (rem_argc == 0lu) {
		no_db_spec();

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
	 *	with                               always 1 or 0
	 *
	 *	((mac - 2) % 6) % 3
	 *
	 *	args leftover for COL_TYPE_Qs
	 *
	 *
	 * (c) COL_SPEC count maximized, need memory for:
	 *
	 *	DbSpec	X DB_CNT =  1
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

	struct DbSpec *const restrict
	spec_alloc = malloc(sizeof(struct DbSpec)
			    + sizeof(struct TblSpec)
			    + (sizeof(struct ColSpec) * ((rem_argc - 6) / 3)));

	if (spec_alloc == NULL) {
		generate_failure_malloc();

		return EXIT_FAILURE;
	}

	char *const restrict *const restrict arg_until = arg + rem_argc;

	/* initialize parsing state */
	struct GenerateParseState state = {
		.argv = {
			.arg = {
				.from  = arg,
				.until = arg_until
			},
			.db_spec = {
				.until = arg_until - DB_SPEC_LENGTH_MIN
			}
		},
		.specs = {
			.db = spec_alloc
		},
		.generator = {
			.rows      = 0llu,
			.columns   = 0u,
			.tables	   = 0u,
			.databases = 0u
		},
		.exit_status = EXIT_SUCCESS
	};

	/* populate specs according to argv */
	parse_db_specs(&state);







	if (state.generator.databases == 0u) {
		generate_failure_no_valid_db_spec();

		free(spec_alloc);

		return EXIT_FAILURE;
	}


	free(spec_alloc);

	return state.exit_status;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_ */
