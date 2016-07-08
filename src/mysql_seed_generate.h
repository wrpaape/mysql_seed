#ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_
#define MYSQL_SEED_MYSQL_SEED_GENERATE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_input.h"	/* handle input strings */

/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define DB_NAME_MAX_LENGTH


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define INVALID_DATABASE_FLAG_HEADER INVALID_FLAG_HEADER("DATABASE")
#define NO_DATABASE_FLAG_MESSAGE NO_FLAG_HEADER("DATABASE")

/* print error  messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
static inline int
print_no_database_flag(void);

static inline int
print_invalid_database_flag(char *const restrict database_flag);


/* dispatch generate mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
generate_dispatch(char *const restrict *const restrict arg_ptr,
		  char *const restrict *const restrict until_ptr);
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
