#ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_
#define MYSQL_SEED_MYSQL_SEED_GENERATE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_input.h"	/* handle input strings */

/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define DB_NAME_LENGTH_MAX 64lu


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define INVALID_DATABASE_FLAG_HEADER INVALID_FLAG_HEADER("DATABASE")
#define NO_DATABASE_FLAG_MESSAGE     NO_FLAG_MESSAGE("DATABASE")
#define INVALID_DB_NAME_HEADER	     INVALID_SPEC_HEADER("DB_NAME")
#define NO_DB_NAME_MESSAGE	     NO_SPEC_MESSAGE("DB_NAME")

/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
print_no_database_flag(void)
{
	write_muffle(STDERR_FILENO,
		     NO_DATABASE_FLAG_MESSAGE,
		     sizeof(NO_DATABASE_FLAG_MESSAGE));

	return EXIT_FAILURE;
}

inline int
print_invalid_database_flag(char *const restrict database_flag)
{
	char buffer[ERROR_BUFFER_SIZE] = {
		INVALID_DATABASE_FLAG_HEADER
	};

	char *restrict
	ptr = put_string_inspect(&buffer[sizeof(INVALID_DATABASE_FLAG_HEADER)],
				 database_flag,
				 FLAG_LENGTH_MAX);

	ptr = put_string_size(ptr,
			      MORE_INFO_MESSAGE,
			      sizeof(MORE_INFO_MESSAGE) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);

	return EXIT_FAILURE;
}


/* dispatch generate mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
generate_dispatch(char *const restrict *const restrict arg_ptr,
		  char *const restrict *const restrict until_ptr)
{
	if (arg_ptr == until_ptr)
		return print_no_database_flag();

	char *const restrict database_flag = *arg_ptr;

	if (*database_flag != '-')
		return print_invalid_database_flag(database_flag);

	char *const restrict next = database_flag + 1l;
	char *const restrict rem  = next + 1l;

	/* parse short database flag */
	switch (*next) {
	case '-': break;	/* parse long database flag */

	case 'd': return (*rem == '\0')
		       ? puts("TODO: dispatch databse")
		       : print_invalid_database_flag(database_flag);

	default:  return print_invalid_database_flag(database_flag);
	}

	/* parse long database flag */
	switch (*rem) {
	case 'd': return strings_equal("atabase", rem + 1l)
		       ? puts("TODO: dispatch databse")
		       : print_invalid_database_flag(database_flag);

	default:  return print_invalid_database_flag(database_flag);
	}
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_ */
