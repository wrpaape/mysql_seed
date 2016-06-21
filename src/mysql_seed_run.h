#ifndef MYSQL_SEED_MYSQL_SEED_RUN_H_
#define MYSQL_SEED_MYSQL_SEED_RUN_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_mode.h"	/* SeedRunSpec, SeedModeSpec */


/* 'SeedModeHandler' dispatch function
 *─────────────────────────────────────────────────────────────────────────── */
void seed_run(const union SeedModeSpec *const restrict mode_spec);


/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_RUN_H_ */
