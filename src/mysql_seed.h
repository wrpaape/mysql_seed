#ifndef MYSQL_SEED_MYSQL_SEED_H_
#define MYSQL_SEED_MYSQL_SEED_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_generate.h"	/* generate mode */
#include "mysql_seed_load.h"		/* load mode */
#include "mysql_seed_help.h"		/* help mode */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define INVALID_MODE_FLAG_HEADER INVALID_FLAG_HEADER("MODE")
#define NO_MODE_FLAG_MESSAGE NO_FLAG_HEADER("MODE")

static inline int
mode_dispatch(char *restrict *const restrict arg_ptr,
	      char *const restrict *const restrict until_ptr);


/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
print_no_mode_flag(void);

static inline int
print_invalid_mode_flag(char *const restrict mode_flag);

#endif	/* MYSQL_SEED_MYSQL_SEED_H_ */
