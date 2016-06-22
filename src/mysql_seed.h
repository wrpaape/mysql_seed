#ifndef MYSQL_SEED_MYSQL_SEED_H_
#define MYSQL_SEED_MYSQL_SEED_H_

#define DEFAULT_USER_COUNT 25000

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_create.h"
#include "mysql_seed_run.h"
#include "mysql_seed_exit.h"




/* parse stdin args
 *─────────────────────────────────────────────────────────────────────────── */
void
parse_input(struct SeedMode *const restrict mode,
	    const int argc,
	    char *const restrict *const restrict argv);


/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
seed_mode_init_exit_failure(struct SeedMode *const restrict mode,
			    const char *const restrict reason);

extern inline void
seed_mode_init_exit_help(struct SeedMode *const restrict mode,
			 const int argc,
			 char *const restrict *const restrict argv);

extern inline void
seed_mode_init_exit_invalid_option(struct SeedMode *const restrict mode,
				   const char *const restrict option);

#endif	/* MYSQL_SEED_MYSQL_SEED_H_ */
