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

#define FAILURE_DB_SPEC_SHORT						\
PARSE_FAILURE_MESSAGE("DB_SPEC too short, need at least "		\
		      DB_SPEC_LENGTH_MIN_STRING " arguments to "	\
		      "describe a database in generate mode") MORE_INFO_MESSAGE

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


/* Generator/DatbaseCounter operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
generator_counter_reset(struct GeneratorCounter *const restrict gen_counter)
{
	gen_counter->rows      = 0llu;
	gen_counter->columns   = 0u;
	gen_counter->tables    = 0u;
	gen_counter->databases = 0u;
}

inline void
database_counter_reset(struct DatabaseCounter *const restrict db_counter)
{
	db_counter->rows    = 0llu;
	db_counter->columns = 0u;
	db_counter->tables  = 0u;
}

inline void
generator_counter_increment(struct GeneratorCounter *const restrict gen_counter,
			    struct DatabaseCounter *const restrict db_counter)
{
	gen_counter->rows      += db_counter->rows;
	gen_counter->columns   += db_counter->columns;
	gen_counter->tables    += db_counter->tables;
	gen_counter->databases += 1u;
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
db_spec_short(void)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_DB_SPEC_SHORT,
		     sizeof(FAILURE_DB_SPEC_SHORT) - 1lu);
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
inline void
invalid_db_name_empty(char *const restrict *restrict db_spec_start,
		      char *const restrict *restrict invalid)

{
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		     ERROR_INVALID_DB_NAME_EMPTY
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(ERROR_INVALID_DB_NAME_EMPTY) - 1lu],
			   db_spec_start,
			   invalid);


	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_db_name_invalid(char *const restrict *restrict db_spec_start,
			char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_DB_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_DB_NAME_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_DB_NAME_REASON_INVALID,
			      sizeof(ERROR_INVALID_DB_NAME_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_db_name_long(char *const restrict *restrict db_spec_start,
		     char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_DB_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_DB_NAME_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_DB_NAME_REASON_LONG,
			      sizeof(ERROR_INVALID_DB_NAME_REASON_LONG)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_tbl_name_empty(char *const restrict *restrict db_spec_start,
		       char *const restrict *restrict invalid)

{
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		     ERROR_INVALID_TBL_NAME_EMPTY
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(ERROR_INVALID_TBL_NAME_EMPTY) - 1lu],
			   db_spec_start,
			   invalid);


	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_tbl_name_invalid(char *const restrict *restrict db_spec_start,
			 char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_TBL_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_TBL_NAME_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_TBL_NAME_REASON_INVALID,
			      sizeof(ERROR_INVALID_TBL_NAME_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_tbl_name_long(char *const restrict *restrict db_spec_start,
		      char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_TBL_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_TBL_NAME_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_TBL_NAME_REASON_LONG,
			      sizeof(ERROR_INVALID_TBL_NAME_REASON_LONG)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_col_name_empty(char *const restrict *restrict db_spec_start,
		       char *const restrict *restrict invalid)

{
	char buffer[ARGV_INSPECT_BUFFER_SIZE] = {
		     ERROR_INVALID_COL_NAME_EMPTY
	};

	char *const restrict ptr
	= put_inspect_args(&buffer[sizeof(ERROR_INVALID_COL_NAME_EMPTY) - 1lu],
			   db_spec_start,
			   invalid);


	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_col_name_invalid(char *const restrict *restrict db_spec_start,
			 char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_COL_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_COL_NAME_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_COL_NAME_REASON_INVALID,
			      sizeof(ERROR_INVALID_COL_NAME_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_col_name_long(char *const restrict *restrict db_spec_start,
		      char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_COL_NAME_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_COL_NAME_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_COL_NAME_REASON_LONG,
			      sizeof(ERROR_INVALID_COL_NAME_REASON_LONG)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_row_count_invalid(char *const restrict *restrict db_spec_start,
			  char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_ROW_COUNT_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_ROW_COUNT_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_ROW_COUNT_REASON_INVALID,
			      sizeof(ERROR_INVALID_ROW_COUNT_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_row_count_zero(char *const restrict *restrict db_spec_start,
		       char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_ROW_COUNT_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_ROW_COUNT_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_ROW_COUNT_REASON_ZERO,
			      sizeof(ERROR_INVALID_ROW_COUNT_REASON_ZERO)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


inline void
invalid_row_count_large(char *const restrict *restrict db_spec_start,
			char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_ROW_COUNT_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_ROW_COUNT_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_ROW_COUNT_REASON_LARGE,
			      sizeof(ERROR_INVALID_ROW_COUNT_REASON_LARGE)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

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
expected_tbl_flag(char *const restrict *restrict db_spec_start,
			char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_EXPECTED_TBL_FLAG_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_EXPECTED_TBL_FLAG_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      IGNORING_DB_SPEC_STARTING_WITH,
			      sizeof(IGNORING_DB_SPEC_STARTING_WITH) - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
expected_col_flag(char *const restrict *restrict db_spec_start,
			char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_EXPECTED_COL_FLAG_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_EXPECTED_COL_FLAG_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      IGNORING_DB_SPEC_STARTING_WITH,
			      sizeof(IGNORING_DB_SPEC_STARTING_WITH) - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
invalid_col_type_invalid(char *const restrict *restrict db_spec_start,
			 char *const restrict *restrict invalid)
{
	char buffer[ARG_ARGV_INSPECT_BUFFER_SIZE] = {
		ERROR_INVALID_COL_TYPE_HEADER
	};

	char *restrict ptr
	= put_string_inspect(&buffer[0]
			     + sizeof(ERROR_INVALID_COL_TYPE_HEADER) - 1lu,
			     *invalid,
			     LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      ERROR_INVALID_COL_TYPE_REASON_INVALID,
			      sizeof(ERROR_INVALID_COL_TYPE_REASON_INVALID)
			      - 1lu);

	ptr = put_inspect_args(ptr,
			       db_spec_start,
			       invalid);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


/* parse UTF-8 identifiers from input
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
parse_db_name(struct String *const restrict db_name,
	      char *const restrict *const restrict db_spec_start,
	      char *const restrict *const restrict input)
{
	if (**input == '\0') {
		invalid_db_name_empty(db_spec_start,
				      input);
		return false;
	}

	const octet_t *restrict octets = (const octet_t *restrict) *input;

	unsigned int width;

	size_t rem_length = DB_NAME_LENGTH_MAX;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u) {
			invalid_db_name_invalid(db_spec_start,
						input);
			return false;
		}

		octets += width;

		if (*octets == '\0') {
			db_name->bytes  = *input;
			db_name->length = octets
					- ((const octet_t *const restrict)
					   *input);

			return true;
		}

		--rem_length;

		if (rem_length == 0lu) {
			invalid_db_name_long(db_spec_start,
					     input);
			return false;
		}
	}
}

inline bool
parse_tbl_name(struct String *const restrict tbl_name,
	       char *const restrict *const restrict db_spec_start,
	       char *const restrict *const restrict input)
{
	if (**input == '\0') {
		invalid_tbl_name_empty(db_spec_start,
				       input);
		return false;
	}

	const octet_t *restrict octets = (const octet_t *restrict) *input;

	unsigned int width;

	size_t rem_length = TBL_NAME_LENGTH_MAX;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u) {
			invalid_tbl_name_invalid(db_spec_start,
						 input);
			return false;
		}

		octets += width;

		if (*octets == '\0') {
			tbl_name->bytes  = *input;
			tbl_name->length = octets
					- ((const octet_t *const restrict)
					   *input);

			return true;
		}

		--rem_length;

		if (rem_length == 0lu) {
			invalid_tbl_name_long(db_spec_start,
					      input);
			return false;
		}
	}
}

inline bool
parse_col_name(struct String *const restrict col_name,
	       char *const restrict *const restrict db_spec_start,
	       char *const restrict *const restrict input)
{
	if (**input == '\0') {
		invalid_col_name_empty(db_spec_start,
				       input);
		return false;
	}

	const octet_t *restrict octets = (const octet_t *restrict) *input;

	unsigned int width;

	size_t rem_length = COL_NAME_LENGTH_MAX;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u) {
			invalid_col_name_invalid(db_spec_start,
						 input);
			return false;
		}

		octets += width;

		if (*octets == '\0') {
			col_name->bytes  = *input;
			col_name->length = octets
					- ((const octet_t *const restrict)
					   *input);

			return true;
		}

		--rem_length;

		if (rem_length == 0lu) {
			invalid_col_name_long(db_spec_start,
					      input);
			return false;
		}
	}
}

inline bool
parse_row_count(size_t *const restrict row_count,
		char *const restrict *const restrict db_spec_start,
		char *const restrict *const restrict input)
{
	uintmax_t parsed;

	if (!parse_uint(&parsed,
			*input)) {
		invalid_row_count_invalid(db_spec_start,
					  input);
		return false;
	}

	if (parsed == 0llu) {
		invalid_row_count_zero(db_spec_start,
				       input);
		return false;
	}

	if (parsed > UPTO_MAX) {
		invalid_row_count_large(db_spec_start,
					input);
		return false;
	}

	*row_count = (size_t) parsed;
	return true;
}


inline void
generate_scan_specs(struct GeneratorCounter *const restrict gen_counter,
		    struct DbSpec *restrict db_spec,
		    int *const restrict exit_status,
		    char *const restrict *restrict from,
		    char *const restrict *const restrict until)
{

	struct DatabaseCounter db_counter = {
		.tables	   = 0lu,
		.columns   = 0lu
	};

	char *const restrict *const restrict db_spec_start_max
	= until - DB_SPEC_LENGTH_MIN;

	char *const restrict *restrict db_spec_start;
	struct TblSpec *restrict tbl_spec;
	struct ColSpec *restrict col_spec;

	char *restrict arg;
	char *restrict rem;

	if (!flag_match(*from,
			'd',
			"database")) {
		expected_db_flag(*from);
		++from;
		*exit_status = EXIT_FAILURE;
		goto PARSE_NEXT_DB_SPEC;
	}

	db_spec_start = from;

	/* parse DB_SPECS */
	while (1) {

		from = db_spec_start + 1lu;

		/* parse DB_NAME */
		if (!parse_db_name(&db_spec->name,
				   db_spec_start,
				   from)) {
			++from;
			*exit_status = EXIT_FAILURE;
			goto PARSE_NEXT_DB_SPEC;
		}

		++from;

		/* validate TBL_SPEC start */
		if (!flag_match(*from,
				't',
				"table")) {
			expected_tbl_flag(db_spec_start,
						from);
			++from;
			*exit_status = EXIT_FAILURE;
			goto PARSE_NEXT_DB_SPEC;

		}

		/* advance to next available slot in spec_alloc */
		tbl_spec = (struct TblSpec *restrict) (db_spec + 1l);
		db_spec->tbl_specs = tbl_spec;

		++from;

		/* parse TBL_SPECS */
		while (1) {
			/* parse TBL_NAME */
			if (!parse_tbl_name(&tbl_spec->name,
					    db_spec_start,
					    from)) {
				++from;
				*exit_status = EXIT_FAILURE;
				goto PARSE_NEXT_DB_SPEC;
			}

			++from;

			/* parse ROW_COUNT */
			if (!parse_row_count(&tbl_spec->row_count,
					     db_spec_start,
					     from)) {
				++from;
				*exit_status = EXIT_FAILURE;
				goto PARSE_NEXT_DB_SPEC;
			}

			++from;

			/* validate COL_SPEC start */
			if (!flag_match(*from,
					'c',
					"column")) {
				expected_col_flag(db_spec_start,
							from);
				++from;
				*exit_status = EXIT_FAILURE;
				goto PARSE_NEXT_DB_SPEC;
			}

			/* advance to next available slot in spec_alloc */
			col_spec = (struct ColSpec *restrict) (tbl_spec + 1l);
			tbl_spec->col_specs.from = col_spec;

			++from;

			/* parse COL_SPECS */
			while (1) {
				/* parse COL_TYPE */

				arg = *from;
				if (*arg != '-') {
					invalid_col_type_invalid(db_spec_start,
								 from);
					++from;
					*exit_status = EXIT_FAILURE;
					goto PARSE_NEXT_DB_SPEC;
				}

				++arg;

				rem = arg + 1;

				switch (*arg) {
				case '-':
					break; /* parse long COL_TYPE flag */

				case 'f':
					if (*rem == '\0')

				case 'i':
					if (*rem == '\0')

				case 's':
					if (*rem == '\0')

				case 'u':
					if (*rem == '\0')

				default:
				}


				/* parse long COL_TYPE flag */
				switch (*rem) {
				case 'f':
					if (strings_equal("loat",
							  rem + 1l))

				case 'i':
					if (strings_equal("nteger",
							  rem + 1l))

				case 's':
					if (strings_equal("tring",
							  rem + 1l))

				case 'u':
					if (strings_equal("nsigned-integer",
							  rem + 1l))

				default:
				}



			}

			/* close ColSpecInterval */
			tbl_spec->col_specs.until = col_spec + 1l;

			/* increment running table and row counts */
			db_counter.rows	  += tbl_spec->row_count;
			db_counter.tables += 1u;
		}




		generator_counter_increment(gen_counter,
					    &db_counter);

		database_counter_reset(&db_counter);

PARSE_NEXT_DB_SPEC:
		db_spec_start = flag_match_next(from,
						until,
						'd',
						"database");

		if (db_spec_start > db_spec_start_max) {
			db_spec->next = NULL;
			return;
		}
	}
}


inline int
generate_dispatch(char *restrict *const restrict arg,
		  const int rem_argc)
{
	if (rem_argc < DB_SPEC_LENGTH_MIN) {

		if (rem_argc == 0lu)
			no_db_spec();
		else
			short_db_spec();

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

	struct GeneratorCounter gen_counter = {
		.rows      = 0llu,
		.columns   = 0u,
		.tables	   = 0u,
		.databases = 0u
	};

	int exit_status = EXIT_SUCCESS;

	generate_scan_specs(&gen_counter,
			    spec_alloc,
			    &exit_status,
			    arg,
			    &arg[0] + rem_argc);

	if (gen_counter.databases == 0u) {
		generate_failure_no_valid_db_spec();

		free(spec_alloc);

		return EXIT_FAILURE;
	}


	free(spec_alloc);

	return exit_status;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_ */
