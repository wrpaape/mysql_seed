#include "mysql_seed_log.h"


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
struct SeedLog seed_log = {
	.current_ptr = NULL,
	.end_ptr     = NULL,
	.lock	     = SEED_MUTEX_INITIALIZER,
	.buffer	     = {
		[0 ... LOG_BUFFER_LAST] = '\0'		/* ensure null-filled */
	}
};


/* initialize, reset
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_log_start(void)
{
	SEED_LOG_INIT();
}

extern inline void
seed_log_reset(void);

void
seed_log_stop(void)
{
	fputs(&seed_log.buffer[0],
	      stdout);
}


/* accesor functions
 *─────────────────────────────────────────────────────────────────────────── */
extern inline char *
seed_log_buffer_ptr(void);

extern inline char *
seed_log_current_ptr(void);

extern inline char *
seed_log_end_ptr(void);

extern inline size_t
seed_log_remaining_characters(void);

extern inline bool
seed_log_lock(const char *restrict *const restrict message_ptr);

extern inline void
seed_log_handle_lock(void);

extern inline bool
seed_log_unlock(const char *restrict *const restrict message_ptr);

extern inline void
seed_log_handle_unlock(void);


/* mutator functions
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
seed_log_append_string(const char *const restrict string);

extern inline void
seed_log_append_digits(const size_t n);

extern inline void
seed_log_append_number(const ssize_t n);

extern inline void
seed_log_append_string_length(const char *const restrict string,
			      const size_t length);

extern inline void
seed_log_append_digits_length(const size_t n,
			      const size_t length);

extern inline void
seed_log_append_number_length(const ssize_t n,
			      const size_t length);
