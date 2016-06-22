#ifndef MYSQL_SEED_MYSQL_SEED_LOG_H_
#define MYSQL_SEED_MYSQL_SEED_LOG_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_utils.h"	/* string utils */

/* cap log length
 *─────────────────────────────────────────────────────────────────────────── */
#define LOG_BUFFER_LENGTH 1024lu

/* declarations
 *─────────────────────────────────────────────────────────────────────────── */

struct SeedLog {
	char *restrict current_ptr;
	char *restrict end_ptr;
	char buffer[LOG_BUFFER_LENGTH];
};

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */

extern struct SeedLog seed_log;

void
seed_log_init(void) __attribute__((constructor));

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_LOG_H_ */
