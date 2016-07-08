#ifndef MYSQL_SEED_MYSQL_SEED_H_
#define MYSQL_SEED_MYSQL_SEED_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
/* #include "mysql_seed_create.h"	/1* CreateSpec, string macros *1/ */
/* #include "mysql_seed_run.h"	/1* RunSpec *1/ */
#include "mysql_seed_help.h"	/* help dispatch, exit utils */


/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define MODE_FLAG_MAX_LENGTH (sizeof("--generate") - 1lu)


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define INVALID_MODE_FLAG_MESSAGE_1 ERROR_WRAP("invalid MODE flag: ")
#define INVALID_MODE_FLAG_MESSAGE_2 "\n\nmysql_seed -h for more info\n"



int
mode_dispatch(char *restrict *const restrict arg_ptr,
	      char *const restrict *const restrict until_ptr);

static inline int
print_invalid_mode_flag(char *const restrict mode_flag);

#endif	/* MYSQL_SEED_MYSQL_SEED_H_ */
