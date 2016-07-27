#ifndef MYSQL_SEED_MYSQL_SEED_H_
#define MYSQL_SEED_MYSQL_SEED_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_generate.h"	/* generate mode */
#include "mysql_seed_load.h"		/* load mode */
#include "mysql_seed_remove.h"		/* remove mode */
#include "mysql_seed_help.h"		/* help mode */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define FAILURE_NO_MODE_FLAG						\
PARSE_FAILURE_MESSAGE("MODE not specified") MORE_INFO_MESSAGE

#define FAILURE_INVALID_MODE_FLAG_HEADER				\
PARSE_FAILURE_HEADER("invalid MODE flag")

static inline int
mode_dispatch(char *const *const restrict from,
	      const int rem_argc);


/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
print_no_mode_flag(void);

static inline void
print_invalid_mode_flag(char *const restrict arg);

#endif	/* MYSQL_SEED_MYSQL_SEED_H_ */
