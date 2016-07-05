#ifndef MYSQL_SEED_MYSQL_SEED_CREATE_H_
#define MYSQL_SEED_MYSQL_SEED_CREATE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_mode.h"	/* SeedCreateSpec, SeedModeSpec */


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern int


/* 'SeedModeHandler' dispatch function
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_create(const union SeedModeSpec *const restrict mode_spec);


/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_CREATE_H_ */
