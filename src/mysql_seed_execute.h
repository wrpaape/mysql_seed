#ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_
#define MYSQL_SEED_MYSQL_SEED_EXECUTE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "execute/execute.h"	/* execute mode */


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define FAILURE_NO_EXEC_SPEC						\
EXECUTE_FAILURE("no EXEC_SPEC provided") MORE_INFO_MESSAGE

#define FAILURE_EXEC_SPEC_SHORT						\
EXECUTE_FAILURE("EXEC_SPEC too short - need at least "			\
		EXEC_SPEC_LENGTH_MIN_STRING " arguments to load a "	\
		"single database into MySQL using default USER with "	\
		"no PASSWORD (" EXEC_SPEC_MINIMAL ")")

#define EXECUTE_EXPECTED_DB_FLAG_HEADER					\
PARSE_ERROR_HEADER("expected DATABASE flag instead of")

/* parsing DB_NAME */
#define EXECUTE_INVALID_DB_NAME_HEADER					\
PARSE_ERROR_HEADER("invalid DB_NAME")

#define EXECUTE_INVALID_DB_NAME_EMPTY					\
PARSE_ERROR_HEADER("invalid DB_NAME (empty), ignoring")			\

#define EXECUTE_INVALID_DB_NAME_REASON_INVALID				\
"\n" ERROR_WRAP("reason - includes one or more invalid UTF-8 "		\
		"codepoints, ignoring")

#define EXECUTE_INVALID_DB_NAME_REASON_LONG				\
"\n" ERROR_WRAP("reason - exceeded MySQL maximum of "			\
		DB_NAME_LENGTH_MAX_STRING " non-null UTF-8 codepoints,"	\
		" ignoring")


/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define EXECUTE_DISPATCH_MAP_LENGTH 7u


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
typedef int
ExecuteDispatchNode(char *const restrict *restrict arg);


/* global constants
 *─────────────────────────────────────────────────────────────────────────── */
extern ExecuteDispatchNode *const
EXECUTE_DISPATCH_MAP[EXECUTE_DISPATCH_MAP_LENGTH];


/* print errors
 *─────────────────────────────────────────────────────────────────────────── */
inline void
execute_expected_db_flag(const char *const restrict invalid)
{
	char buffer[ARG_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  EXECUTE_EXPECTED_DB_FLAG_HEADER,
			  sizeof(EXECUTE_EXPECTED_DB_FLAG_HEADER) - 1lu);

	ptr = put_string_inspect(ptr,
				 invalid,
				 LENGTH_INSPECT_MAX);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
execute_invalid_db_name_empty(void)
{
	write_muffle(STDERR_FILENO,
		     EXECUTE_INVALID_DB_NAME_EMPTY,
		     sizeof(EXECUTE_INVALID_DB_NAME_EMPTY) - 1lu);
}

inline void
execute_invalid_db_name_invalid(const char *const restrict db_name)
{
	char buffer[ARG_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  EXECUTE_INVALID_DB_NAME_HEADER,
			  sizeof(EXECUTE_INVALID_DB_NAME_HEADER) - 1lu);

	ptr = put_string_inspect(ptr,
				 db_name,
				 DB_NAME_LENGTH_MAX);

	ptr = put_string_size(ptr,
			      EXECUTE_INVALID_DB_NAME_REASON_INVALID,
			      sizeof(EXECUTE_INVALID_DB_NAME_REASON_INVALID)
			      - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
execute_invalid_db_name_long(const char *const restrict db_name)
{
	char buffer[ARG_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  EXECUTE_INVALID_DB_NAME_HEADER,
			  sizeof(EXECUTE_INVALID_DB_NAME_HEADER) - 1lu);

	ptr = put_string_inspect(ptr,
				 db_name,
				 DB_NAME_LENGTH_MAX);

	ptr = put_string_size(ptr,
			      EXECUTE_INVALID_DB_NAME_REASON_LONG,
			      sizeof(EXECUTE_INVALID_DB_NAME_REASON_LONG)
			      - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


/* parsing DB_NAME
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
execute_parse_db_name(struct String *const restrict db_name,
		      char *const restrict arg)
{
	const octet_t *restrict octets
	= (const octet_t *restrict) arg;

	if (*octets == '\0') {
		execute_invalid_db_name_empty();
		return false;
	}

	unsigned int width;
	unsigned int rem_code_points = DB_NAME_LENGTH_MAX;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u) {
			execute_invalid_db_name_invalid(arg);
			return false;
		}

		octets += width;

		if (*octets == '\0') {
			db_name->bytes  = arg;
			db_name->length = octets
					- ((const octet_t *const restrict)
					   db_name->bytes);
			return true;
		}

		--rem_code_points;

		if (rem_code_points == 0u) {
			execute_invalid_db_name_long(arg);
			return false;
		}
	}
}

inline bool
execute_db_flag_match(char *const restrict arg)
{
	const bool matched_db_flag = flag_match(arg,
						'd',
						"database");

	if (!matched_db_flag)
		execute_expected_db_flag(arg);

	return matched_db_flag;
}


/* if EXEC_SPEC is correct, at least 2 databases need to be loaded
 *─────────────────────────────────────────────────────────────────────────── */
inline int
execute_dispatch_large(char *const restrict *restrict arg,
		       char *const restrict *const restrict until)
{
	return EXIT_FAILURE;
}

/* ExecuteDispatchNodes
 *─────────────────────────────────────────────────────────────────────────── */
/* at least 1 database */
int
execute_dispatch6(char *const restrict *restrict arg);
int
execute_dispatch5(char *const restrict *restrict arg);
int
execute_dispatch4(char *const restrict *restrict arg);
int
execute_dispatch3(char *const restrict *restrict arg);
/* at most 1 database */
int
execute_dispatch2(char *const restrict *restrict arg);
/* irrecoverable failures */
int
execute_failure_short_exec_spec(char *const restrict *restrict arg);
int
execute_failure_no_exec_spec(char *const restrict *restrict arg);



/* dispatch load mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
execute_dispatch(char *const restrict *restrict arg,
		 const unsigned int rem_argc)
{
	return (rem_argc < EXECUTE_DISPATCH_MAP_LENGTH)
	     ? (EXECUTE_DISPATCH_MAP[rem_argc])(arg)
	     : execute_dispatch_large(arg,
				      arg + rem_argc);


	StringInterval

}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_ */
