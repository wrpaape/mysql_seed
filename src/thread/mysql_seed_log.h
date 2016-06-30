#ifndef MYSQL_SEED_MYSQL_SEED_LOG_H_
#define MYSQL_SEED_MYSQL_SEED_LOG_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <string.h>			/* memset */
#include "mysql_seed_utils.h"		/* string utils */
#include "mysql_seed_parallel.h"	/* SeedMutex, parallelization utils  */


/* cap log buffer at 1kb
 *─────────────────────────────────────────────────────────────────────────── */
#define LOG_BUFFER_LENGTH 1024lu
#define LOG_UNTIL (LOG_BUFFER_LENGTH - 1)

/* declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct SeedLog {
	char *restrict current_ptr;
	char *restrict until_ptr;
	SeedMutex lock;
	char buffer[LOG_BUFFER_LENGTH];
};


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern struct SeedLog seed_log_prototype;


/* initialize, reset, destroy
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_log_init(struct SeedLog *const restrict log)
{
	memcpy(log,
	       &seed_log_prototype,
	       sizeof(seed_log_prototype));
}

/* accesor functions
 *─────────────────────────────────────────────────────────────────────────── */
inline char *
seed_log_buffer_ptr(struct SeedLog *const restrict log)
{
	return &log->buffer[0];
}

inline char *
seed_log_current_ptr(struct SeedLog *const restrict log)
{
	return log->current_ptr;
}

inline char *
seed_log_end_ptr(struct SeedLog *const restrict log)
{
	return log->until_ptr;
}

inline size_t
seed_log_remaining_characters(struct SeedLog *const restrict log)
{
	return log->until_ptr - log->current_ptr;
}

inline bool
seed_log_lock(struct SeedLog *const restrict log,
	      const char *restrict *const restrict message_ptr)
{
	return seed_mutex_lock(&log->lock,
			       message_ptr);
}

inline void
seed_log_handle_lock(struct SeedLog *const restrict log)
{
	seed_mutex_handle_lock(&log->lock);
}

inline bool
seed_log_unlock(struct SeedLog *const restrict log,
		const char *restrict *const restrict message_ptr)
{
	return seed_mutex_unlock(&log->lock,
				 message_ptr);
}

inline void
seed_log_handle_unlock(struct SeedLog *const restrict log)
{
	seed_mutex_handle_unlock(&log->lock);
}


/* mutator functions
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_log_append_string(struct SeedLog *const restrict log,
		       const char *const restrict string)
{
	log->current_ptr = put_string_until(log->current_ptr,
						string,
						log->until_ptr);
}

inline void
seed_log_append_digits(struct SeedLog *const restrict log,
		       const size_t n)
{
	log->current_ptr = put_digits_until(log->current_ptr,
						n,
						log->until_ptr);
}

inline void
seed_log_append_number(struct SeedLog *const restrict log,
		       const ssize_t n)
{
	log->current_ptr = put_number_until(log->current_ptr,
						n,
						log->until_ptr);
}

inline void
seed_log_append_string_length(struct SeedLog *const restrict log,
			      const char *const restrict string,
			      const size_t length)
{
	char *const restrict length_ptr = log->current_ptr
					+ length;

	log->current_ptr = put_string_until(log->current_ptr,
						string,
						(length_ptr > log->until_ptr)
						? log->until_ptr
						: length_ptr);
}

inline void
seed_log_append_digits_length(struct SeedLog *const restrict log,
			      const size_t n,
			      const size_t length)
{
	char *const restrict length_ptr = log->current_ptr
					+ length;

	log->current_ptr = put_digits_until(log->current_ptr,
						n,
						(length_ptr > log->until_ptr)
						? log->until_ptr
						: length_ptr);
}

inline void
seed_log_append_number_length(struct SeedLog *const restrict log,
			      const ssize_t n,
			      const size_t length)
{
	char *const restrict length_ptr = log->current_ptr
					+ length;

	log->current_ptr = put_number_until(log->current_ptr,
						n,
						(length_ptr > log->until_ptr)
						? log->until_ptr
						: length_ptr);
}

/* constructors, destructors
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_log_start(void)
__attribute__((constructor));

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_LOG_H_ */
