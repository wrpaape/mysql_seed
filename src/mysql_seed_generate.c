#include "mysql_seed_generate.h"

/* print error  messsage and return 'EXIT_FAILURE'
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
	static char buffer[128] = {
		INVALID_DATABASE_FLAG_HEADER
	};

	char *restrict
	ptr = put_string_inspect(&buffer[sizeof(INVALID_DATABASE_FLAG_HEADER)],
				 database_flag,
				 FLAG_LENGTH_MAX);

	(void) memcpy(ptr,
		      MORE_INFO_MESSAGE,
		      sizeof(MORE_INFO_MESSAGE) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     (ptr - &buffer[0]) + sizeof(MORE_INFO_MESSAGE));

	return EXIT_FAILURE;
}

/* dispatch generate mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
generate_dispatch(char *const restrict *const restrict arg_ptr,
		  char *const restrict *const restrict until_ptr);


