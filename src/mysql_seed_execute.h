#ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_
#define MYSQL_SEED_MYSQL_SEED_EXECUTE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "system/stdio_utils.h"	/* read_password */
#include "execute/execute.h"	/* execute mode */


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define FAILURE_NO_EXEC_SPEC						\
EXECUTE_FAILURE("no EXEC_SPEC provided") MORE_INFO_MESSAGE

#define FAILURE_EXEC_SPEC_SHORT						\
EXECUTE_FAILURE("EXEC_SPEC too short - need at least "			\
		EXEC_SPEC_LENGTH_MIN_STRING " arguments to load a "	\
		"single database into MySQL using default USER with "	\
		"no PASSWORD (" EXEC_SPEC_MINIMAL ERROR_OPEN ")")	\
		MORE_INFO_MESSAGE

#define EXECUTE_EXPECTED_PWD_DB_FLAG_HEADER				\
PARSE_ERROR_HEADER("expected PASSWORD flag or DATABASE flag instead of")

#define EXECUTE_EXPECTED_USR_PWD_DB_FLAG_HEADER				\
PARSE_ERROR_HEADER("expected USER flag, PASSWORD flag, or DATABASE "	\
		   "flag instead of")

#define EXECUTE_PASSWORD_ALREADY_SET					\
PARSE_ERROR_HEADER("PASSWORD already set, ignoring flag")

#define EXECUTE_USER_ALREADY_SET_HEADER					\
PARSE_ERROR_HEADER("USER already set to ")

#define EXECUTE_NO_DB_NAMES						\
PARSE_ERROR_HEADER("no DB_NAMES provided")

#define EXECUTE_NO_VALID_DB_NAMES					\
PARSE_ERROR_HEADER("no valid DB_NAMES provided")


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

/* MySQL password prompt */
#define MYSQL_PASSWORD_PROMPT						\
"\n" ANSI_BRIGHT ANSI_WHITE "enter your MySQL password: " ANSI_RESET


/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define EXECUTE_DISPATCH_MAP_LENGTH 7u


/* print errors
 *─────────────────────────────────────────────────────────────────────────── */
inline void
execute_failure_no_exec_spec(void)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_NO_EXEC_SPEC,
		     sizeof(FAILURE_NO_EXEC_SPEC) - 1lu);
}

inline void
execute_failure_short_exec_spec(void)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_EXEC_SPEC_SHORT,
		     sizeof(FAILURE_EXEC_SPEC_SHORT) - 1lu);
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

inline void
execute_password_already_set(void)
{
	write_muffle(STDERR_FILENO,
		     EXECUTE_PASSWORD_ALREADY_SET,
		     sizeof(EXECUTE_PASSWORD_ALREADY_SET) - 1lu);
}

inline void
execute_user_already_set(const char *const restrict user)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  EXECUTE_USER_ALREADY_SET_HEADER,
			  sizeof(EXECUTE_USER_ALREADY_SET_HEADER) - 1lu);

	ptr = put_string_inspect(ptr,
				 user,
				 MYSQL_USER_NN_SIZE_MAX);

	ptr = put_string_size(ptr,
			      IGNORING_FLAG,
			      sizeof(IGNORING_FLAG) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
execute_no_db_names(void)
{
	write_muffle(STDERR_FILENO,
		     EXECUTE_NO_DB_NAMES,
		     sizeof(EXECUTE_NO_DB_NAMES) - 1lu);
}

inline void
execute_no_valid_db_names(void)
{
	write_muffle(STDERR_FILENO,
		     EXECUTE_NO_VALID_DB_NAMES,
		     sizeof(EXECUTE_NO_VALID_DB_NAMES) - 1lu);
}


/* parsing MySQL credentials
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
read_mysql_password(char *const restrict buffer);
{
	const char *restrict failure;

	const bool success
	= LIKELY(write_report(STDIN_FILENO,
			      MYSQL_PASSWORD_PROMPT,
			      sizeof(MYSQL_PASSWORD_PROMPT) - 1lu,
			      &failure))
       && LIKELY(read_password(buffer,
			       MYSQL_PASSWORD_SIZE_MAX,
			       &failure))
       && write_report(STDIN_FILENO,
		       ANSI_CLEAR_LINE "\n",
		       sizeof(ANSI_CLEAR_LINE "\n") - 1lu,
		       &failure);

	if (UNLIKELY(!success))
		print_failure(failure);

	return success;
}

inline char *const restrict *restrict
execute_parse_pwd_short_first(struct MysqlCredentials *const restrict creds,
			      char *const restrict rem_flag,
			      char *const restrict *restrict from,
			      char *const restrict *restrict until)
{
	if (*rem_flag == '\0') {
		if (UNLIKELY(!read_mysql_password(&creds->password->buffer[0])))
			return NULL;
	} else {
		creds->password->bytes = rem_flag;
	}

	++from;
	if (from == until) {
		execute_no_db_names();
		return NULL;
	}

	const char *restrict arg = *from;
}

inline char *const restrict *restrict
execute_parse_user_short_first(struct MysqlCredentials *const restrict creds,
			       char *const restrict rem_flag,
			       char *const restrict *restrict from,
			       char *const restrict *restrict until)
{
	if (*rem_flag == '\0') {
		++from;
		if (from == until) {
			execute_no_db_names();
			return NULL;
		}

		creds->user = from;

	} else {
		creds->user = rem_flag;
	}

	++from;
	if (from == until) {
		execute_no_db_names();
		return NULL;
	}

	const char *restrict arg = *from;

	if (*arg != '-') {
DEFAULT_PASSWORD:
		creds->password->bytes = MYSQL_DEFAULT_PASSWORD;
		return from;
	}

	++arg;
	const char *const restrict rem = arg + 1l;


	switch (*arg) {
	case '-':
		arg = string_starts_with(rem,
					 "password");
		if (arg == NULL)
			goto DEFAULT_PASSWORD;



	case 'p':

	default:
		goto DEFAULT_PASSWORD;
	}
}

inline char *const restrict *restrict
execute_parse_credentials(struct MysqlCredentials *const restrict creds,
			  char *const restrict *restrict from,
			  char *const restrict *restrict until)
{
	const char *restrict arg = *from;

	if (*arg != '-') {
DEFAULT_CREDENTIALS:
		creds->password->bytes = MYSQL_DEFAULT_PASSWORD;
		creds->user	       = MYSQL_DEFAULT_USER:
		return from;
	}

	++arg;
	const char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		break; /* parse long SPEC */

	case 'p':
		return execute_parse_pwd_short_first(creds,
						     rem,
						     from,
						     until);

	case 'u':
		return execute_parse_user_short_first(creds,
						      rem,
						      from,
						      until);

	default:
		goto DEFAULT_CREDENTIALS;
	}


	switch (*rem) {
	case 'p':
		arg = string_starts_with(rem + 1l,
					 "password=");

		if (arg == NULL)
			goto DEFAULT_CREDENTIALS;

		return execute_parse_password_first(creds,
						    arg,
						    from,
						    until);

	case 'u':
		arg = string_starts_with(rem + 1l,
					 "user=");

		if (arg == NULL)
			goto DEFAULT_CREDENTIALS;

		return execute_parse_user_first(creds,
						arg,
						from,
						until);

	default:
		goto DEFAULT_CREDENTIALS;
	}
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


inline struct String *
execute_parse_db_names_recover(struct String *restrict db_names,
			       char *const restrict *restrict from,
			       char *const restrict *restrict until)
{
	while (from < until) {
		if (execute_parse_db_name(db_names,
					  *from))
			++db_names;

		++from;
	}

	return db_names;
}

inline struct String *
execute_parse_db_names(struct String *restrict db_names,
		       char *const restrict *restrict from,
		       char *const restrict *restrict until,
		       int *const restrict exit_status)
{
	while (from < until) {
		if (!execute_parse_db_name(db_names,
					   *from)) {
			*exit_status = EXIT_FAILURE;
			return execute_parse_db_names_recover(db_names,
							      from + 1l,
							      until);
		}

		++db_names;
		++from;
	}

	return db_names;
}


/* dispatch load mode according to 'from'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
execute_dispatch(char *const restrict *restrict from,
		 const unsigned int rem_argc)
{
	return EXIT_FAILURE;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_ */
