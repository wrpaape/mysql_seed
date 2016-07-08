#ifndef MYSQL_SEED_MYSQL_SEED_LOAD_H_
#define MYSQL_SEED_MYSQL_SEED_LOAD_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_input.h"	/* exit, file, string utils */

/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */

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
	return EXIT_FAILURE;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_LOAD_H_ */
