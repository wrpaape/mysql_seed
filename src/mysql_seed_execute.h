#ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_
#define MYSQL_SEED_MYSQL_SEED_EXECUTE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h"	/* exit, file, string utils */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define INVALID_DATABASE_FLAG_HEADER INVALID_FLAG_HEADER("DATABASE")
#define NO_DATABASE_FLAG_MESSAGE NO_FLAG_MESSAGE("DATABASE")

/* print error  messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
/* static inline int */
/* print_no_database_name(void); */

/* static inline int */
/* print_invalid_database_name(char *const restrict db_name); */

/* dispatch load mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
execute_dispatch(char *const restrict *const restrict arg_ptr,
		 const int rem_argc)
{
	return EXIT_FAILURE;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_EXECUTE_H_ */
