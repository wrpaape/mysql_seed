#include "mysql_seed_log.h"


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
struct SeedLog seed_log_prototype = {
	.current_ptr = NULL,
	.until_ptr   = NULL,
	.lock	     = SEED_MUTEX_INITIALIZER,
	.buffer	     = {
		[0 ... LOG_UNTIL] = '\0'		/* ensure null-filled */
	}
};


/* initialize, reset
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_log_start(void)
{
	seed_log_prototype.current_ptr = &seed_log_prototype.buffer[0];
	seed_log_prototype.until_ptr   = &seed_log_prototype.buffer[LOG_UNTIL];
}

/* accesor functions
 *─────────────────────────────────────────────────────────────────────────── */
extern inline char *
seed_log_buffer_ptr(struct SeedLog *const restrict log);

extern inline char *
seed_log_current_ptr(struct SeedLog *const restrict log);

extern inline char *
seed_log_end_ptr(struct SeedLog *const restrict log);

extern inline size_t
seed_log_remaining_characters(struct SeedLog *const restrict log);

extern inline bool
seed_log_lock(const char *restrict *const restrict message_ptr);

extern inline void
seed_log_handle_lock(struct SeedLog *const restrict log);

extern inline bool
seed_log_unlock(const char *restrict *const restrict message_ptr);

extern inline void
seed_log_handle_unlock(struct SeedLog *const restrict log);

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
