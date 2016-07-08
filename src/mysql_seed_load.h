#ifndef MYSQL_SEED_MYSQL_SEED_LOAD_H_
#define MYSQL_SEED_MYSQL_SEED_LOAD_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "system/exit_utils.h"	/* exit, file, string utils */

/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define DB_NAME_LENGTH_MAX 64lu

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define INVALID_DATABASE_FLAG_HEADER INVALID_FLAG_HEADER("DATABASE")
#define NO_DATABASE_FLAG_MESSAGE NO_FLAG_HEADER("DATABASE")

/* print error  messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
static inline int
print_no_database_name(void);

static inline int
print_invalid_database_name(char *const restrict database_name);

/* dispatch load mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
load_dispatch(char *const restrict *const restrict arg_ptr,
	      char *const restrict *const restrict until_ptr)
{
	if (arg_ptr == until_ptr)
		return print_no_database_name();

	char *const restrict mode = *arg_ptr;
	char *const restrict rem  = mode + 1l;

	switch (*mode) {
	case 'g': return ((*rem == '\0') || strings_equal("enerate", rem))
		       ? print_help_generate()
		       : print_help_usage();

	case 'l': return ((*rem == '\0') || strings_equal("oad", rem))
		       ? print_help_load()
		       : print_help_usage();

	default:  return print_help_usage();
	}
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_LOAD_H_ */
