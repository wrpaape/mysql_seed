#ifndef MYSQL_SEED_MYSQL_SEED_LOG_H_
#define MYSQL_SEED_MYSQL_SEED_LOG_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <string.h>			/* memset */
#include "mysql_seed_utils.h"		/* string utils */
#include "mysql_seed_parallel.h"	/* SeedMutex, parallelization utils  */


/* cap log length
 *─────────────────────────────────────────────────────────────────────────── */
#define LOG_BUFFER_LENGTH 1024lu

/* declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct SeedLog {
	char *restrict current_ptr;
	char *restrict end_ptr;
	SeedMutex lock;
	char buffer[LOG_BUFFER_LENGTH];
};


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern struct SeedLog seed_log;


/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define LOG_BUFFER_LAST (LOG_BUFFER_LENGTH - 1)
#define SEED_LOG_INIT()							\
do {									\
	seed_log.current_ptr = &seed_log.buffer[0];			\
	seed_log.end_ptr     = &seed_log.buffer[LOG_BUFFER_LAST];	\
} while (0)



/* initialize, reset
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_log_init(void)
__attribute__((constructor));

inline void
seed_log_reset(void)
{
	memset(&seed_log,
	       0,
	       sizeof(seed_log));

	SEED_LOG_INIT();

	seed_mutex_init(&seed_log.lock);
}


/* accesor functions
 *─────────────────────────────────────────────────────────────────────────── */
inline char *
seed_log_buffer_ptr(void)
{
	return &seed_log.buffer[0];
}

inline char *
seed_log_current_ptr(void)
{
	return seed_log.current_ptr;
}

inline char *
seed_log_end_ptr(void)
{
	return seed_log.end_ptr;
}

inline size_t
seed_log_remaining_characters(void)
{
	return seed_log.end_ptr - seed_log.current_ptr;
}


/* mutator functions
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_log_append_string(const char *const restrict string)
{
	seed_log.current_ptr = put_string_until(seed_log.current_ptr,
						string,
						seed_log.end_ptr);
}

inline void
seed_log_append_digits(const size_t n)
{
	seed_log.current_ptr = put_digits_until(seed_log.current_ptr,
						n,
						seed_log.end_ptr);
}

inline void
seed_log_append_number(const ssize_t n)
{
	seed_log.current_ptr = put_number_until(seed_log.current_ptr,
						n,
						seed_log.end_ptr);
}

inline void
seed_log_append_string_length(const char *const restrict string,
			      const size_t length)
{
	char *const restrict length_ptr = seed_log.current_ptr
					+ length;

	seed_log.current_ptr = put_string_until(seed_log.current_ptr,
						string,
						(length_ptr > seed_log.end_ptr)
						? seed_log.end_ptr
						: length_ptr);
}

inline void
seed_log_append_digits_length(const size_t n,
			      const size_t length)
{
	char *const restrict length_ptr = seed_log.current_ptr
					+ length;

	seed_log.current_ptr = put_digits_until(seed_log.current_ptr,
						n,
						(length_ptr > seed_log.end_ptr)
						? seed_log.end_ptr
						: length_ptr);
}

inline void
seed_log_append_number_length(const ssize_t n,
			      const size_t length)
{
	char *const restrict length_ptr = seed_log.current_ptr
					+ length;

	seed_log.current_ptr = put_number_until(seed_log.current_ptr,
						n,
						(length_ptr > seed_log.end_ptr)
						? seed_log.end_ptr
						: length_ptr);
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_LOG_H_ */
