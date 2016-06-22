#include "mysql_seed_log.h"

#define LOG_BUFFER_LAST (LOG_BUFFER_LENGTH - 1lu)

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
char log_buffer[LOG_BUFFER_LENGTH] = {
};


char *restrict log_ptr = &log_buffer[0];		/* point at start */

struct SeedLog seed_log = {
	.buffer = {
		[0 ... LOG_BUFFER_LAST] = '\0';		/* ensure null-filled */
	}
};


void
seed_log_init(void)
{
	seed_log.current_ptr = &seed_log.buffer[0];
	seed_log.end_ptr     = &seed_log.buffer[LOG_BUFFER_LAST];
}


void
seed_log_


