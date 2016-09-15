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

#define EXECUTE_NO_DB_NAMES						\
EXECUTE_FAILURE("no DB_NAMEs provided")

#define EXECUTE_NO_USER_OR_DB_NAMES					\
EXECUTE_FAILURE("no USER when standalone USER_FLAG was specified and "	\
		"no DB_NAMEs provided")

#define EXECUTE_NO_VALID_DB_NAMES					\
EXECUTE_FAILURE("no valid DB_NAMEs provided")


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
execute_no_db_names(void)
{
	write_muffle(STDERR_FILENO,
		     EXECUTE_NO_DB_NAMES,
		     sizeof(EXECUTE_NO_DB_NAMES) - 1lu);
}

inline void
execute_no_user_or_db_names(void)
{
	write_muffle(STDERR_FILENO,
		     EXECUTE_NO_USER_OR_DB_NAMES,
		     sizeof(EXECUTE_NO_USER_OR_DB_NAMES) - 1lu);
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
read_mysql_password(struct MysqlPassword *const restrict password)
{
	const char *restrict failure;

	const bool success
	= LIKELY(write_report(STDIN_FILENO,
			      MYSQL_PASSWORD_PROMPT,
			      sizeof(MYSQL_PASSWORD_PROMPT) - 1lu,
			      &failure))
       && LIKELY(read_password(&password->buffer[0],
			       MYSQL_PASSWORD_SIZE_MAX,
			       &failure))
       && write_report(STDIN_FILENO,
		       ANSI_CLEAR_LINE "\n",
		       sizeof(ANSI_CLEAR_LINE "\n") - 1lu,
		       &failure);

	if (LIKELY(success))
		password->bytes = &password->buffer[0];
	else
		print_failure(failure);

	return success;
}


inline char *const restrict *restrict
execute_parse_user(const char *restrict *const restrict user,
		   char *const restrict *restrict from,
		   char *const restrict *restrict until)
{
	++from;
	if (from == until) {
		execute_no_db_names();
		return NULL;
	}

	const char *restrict arg = *from;

	if (*arg != '-') {
DEFAULT_USER:
		*user = MYSQL_DEFAULT_USER;
		return from;
	}

	++arg;
	const char *const restrict rem = arg + 1l;

	switch (*arg) {
	case '-':
		arg = string_starts_with(rem,
					 "user");

		if (arg == NULL)
			goto DEFAULT_USER;

		switch (*arg) {
		case '\0':
			++from;
			if (from == until) {
				execute_no_user_or_db_names();
				return NULL;
			}

			*user = *from;
			goto PARSE_COMPLETE;

		case '=':
			*user = arg + 1l;
			goto PARSE_COMPLETE;

		default:
			goto DEFAULT_USER;
		}


	case 'u':
		if (*rem == '\0') {
			++from;
			if (from == until) {
				execute_no_user_or_db_names();
				return NULL;
			}

			*user = *from;
		} else {
			*user = rem;
		}
		break;

	default:
		goto DEFAULT_USER;
	}

PARSE_COMPLETE:
	++from;
	if (from < until)
		return from;

	execute_no_db_names();
	return NULL;
}


inline char *const restrict *restrict
execute_parse_pwd(struct MysqlPassword *const restrict password,
		  char *const restrict *restrict from,
		  char *const restrict *restrict until)
{
	++from;
	if (from == until) {
		execute_no_db_names();
		return NULL;
	}

	const char *restrict arg = *from;

	if (*arg != '-') {
DEFAULT_PASSWORD:
		password->bytes = MYSQL_DEFAULT_PASSWORD;
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

		switch (*arg) {
		case '\0':
			if (UNLIKELY(!read_mysql_password(password)))
				return NULL;

			goto PARSE_COMPLETE;

		case '=':
			password->bytes = arg + 1l;
			goto PARSE_COMPLETE;

		default:
			goto DEFAULT_PASSWORD;
		}


	case 'p':
		if (*rem == '\0') {
			if (UNLIKELY(!read_mysql_password(password)))
				return NULL;
		} else {
			password->bytes = rem;
		}
		break;

	default:
		goto DEFAULT_PASSWORD;
	}

PARSE_COMPLETE:
	++from;
	if (from < until)
		return from;

	execute_no_db_names();
	return NULL;
}


inline char *const restrict *restrict
execute_parse_pwd_short_first(struct MysqlCredentials *const restrict creds,
			      const char *restrict rem_flag,
			      char *const restrict *restrict from,
			      char *const restrict *restrict until)
{
	if (*rem_flag == '\0') {
		if (UNLIKELY(!read_mysql_password(&creds->password)))
			return NULL;
	} else {
		creds->password.bytes = rem_flag;
	}

	return execute_parse_user(&creds->user,
				  from,
				  until);
}

inline char *const restrict *restrict
execute_parse_pwd_long_first(struct MysqlCredentials *const restrict creds,
			     const char *restrict rem_flag,
			     char *const restrict *restrict from,
			     char *const restrict *restrict until)
{
	rem_flag = string_starts_with(rem_flag,
				      "assword");

	if (rem_flag == NULL) {
DEFAULT_CREDENTIALS:
		creds->password.bytes = MYSQL_DEFAULT_PASSWORD;
		creds->user	      = MYSQL_DEFAULT_USER;
		return from;
	}

	switch (*rem_flag) {
	case '\0':
		if (UNLIKELY(!read_mysql_password(&creds->password)))
			return NULL;

		break;

	case '=':
		creds->password.bytes = rem_flag + 1l;
		break;

	default:
		goto DEFAULT_CREDENTIALS;
	}

	return execute_parse_user(&creds->user,
				  from,
				  until);
}


inline char *const restrict *restrict
execute_parse_user_short_first(struct MysqlCredentials *const restrict creds,
			       const char *restrict rem_flag,
			       char *const restrict *restrict from,
			       char *const restrict *restrict until)
{
	if (*rem_flag == '\0') {
		++from;
		if (from == until) {
			execute_no_user_or_db_names();
			return NULL;
		}

		creds->user = *from;

	} else {
		creds->user = rem_flag;
	}

	return execute_parse_pwd(&creds->password,
				 from,
				 until);
}


inline char *const restrict *restrict
execute_parse_user_long_first(struct MysqlCredentials *const restrict creds,
			      const char *restrict rem_flag,
			      char *const restrict *restrict from,
			      char *const restrict *restrict until)
{
	rem_flag = string_starts_with(rem_flag,
				      "ser");

	if (rem_flag == NULL) {
DEFAULT_CREDENTIALS:
		creds->password.bytes = MYSQL_DEFAULT_PASSWORD;
		creds->user	      = MYSQL_DEFAULT_USER;
		return from;
	}

	switch (*rem_flag) {
	case '\0':
		++from;
		if (from == until) {
			execute_no_user_or_db_names();
			return NULL;
		}

		creds->user = *from;
		break;

	case '=':
		creds->user = rem_flag + 1l;
		break;

	default:
		goto DEFAULT_CREDENTIALS;
	}

	return execute_parse_pwd(&creds->password,
				 from,
				 until);
}


inline char *const restrict *restrict
execute_parse_credentials(struct MysqlCredentials *const restrict creds,
			  char *const restrict *restrict from,
			  char *const restrict *restrict until)
{
	const char *restrict arg = *from;

	if (*arg != '-') {
DEFAULT_CREDENTIALS:
		creds->password.bytes = MYSQL_DEFAULT_PASSWORD;
		creds->user	      = MYSQL_DEFAULT_USER;
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
		return execute_parse_pwd_long_first(creds,
						    rem + 1l,
						    from,
						    until);

	case 'u':
		return execute_parse_user_long_first(creds,
						     rem + 1l,
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
	do {
		if (!execute_parse_db_name(db_names,
					   *from)) {
			*exit_status = EXIT_FAILURE;
			return execute_parse_db_names_recover(db_names,
							      from + 1l,
							      until);
		}

		++db_names;
		++from;
	} while (from < until);

	return db_names;
}


/* dispatch load mode according to 'from'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
execute_dispatch(char *const restrict *restrict from,
		 const unsigned int rem_argc)
{
	if (rem_argc == 0lu) {
		execute_failure_no_exec_spec();
		return EXIT_FAILURE;
	}


	char *const restrict *restrict until = from + rem_argc;


	struct MysqlCredentials creds;

	from = execute_parse_credentials(&creds,
					 from,
					 until);

	if (from == NULL)
		return EXIT_FAILURE;




	struct StringInterval db_names;

	db_names.from = malloc(sizeof(struct String) * (until - from));

	if (UNLIKELY(db_names.from == NULL)) {
		execute_failure_malloc();
		return EXIT_FAILURE;
	}

	int exit_status = EXIT_SUCCESS;

	db_names.until
	= execute_parse_db_names(db_names.from,
				 from,
				 until,
				 &exit_status);

	const unsigned int count_db_names
	= db_names.until - db_names.from;

	/* printf("got user: %s\n    pass: %s\n", */
	/*        creds.user, creds.password.bytes); */

	/* for (struct String *db = db_names.from; db < db_names.until; ++db) */
	/* 	printf("\t%s\n", db->bytes); */

	/* exit(0); */

	if (count_db_names > 0u)
		mysql_seed_execute(&creds,
				   &db_names,
				   count_db_names,
				   &exit_status);
	else
		execute_no_valid_db_names();

	free(db_names.from);

	return exit_status;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_ */
