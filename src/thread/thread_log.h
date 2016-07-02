#ifndef MYSQL_SEED_THREAD_THREAD_LOG_H_
#define MYSQL_SEED_THREAD_THREAD_LOG_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* Mutex, memcpy  */
#include "string/string_utils.h"	/* string utils */


/* cap log buffer at 1kb
 *─────────────────────────────────────────────────────────────────────────── */
#define THREAD_LOG_BUFFER_LENGTH 1024lu
#define THREAD_LOG_HEADER_1						\
ANSI_WHITE_BG "\n\n" ANSI_BLACK ANSI_BRIGHT ANSI_UNDERLINE		\
"THREAD LOG FOR" ANSI_NO_UNDERLINE ":\n\t"
#define THREAD_LOG_HEADER_2 " (" ANSI_BLACK_BG ANSI_WHITE
#define THREAD_LOG_HEADER_3 ANSI_WHITE_BG ANSI_BLACK ")\n" ANSI_RESET

/* declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct ThreadLog {
	char *restrict current_ptr;
	char *restrict until_ptr;
	Mutex lock;
	char buffer[THREAD_LOG_BUFFER_LENGTH];
};


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern const char thread_log_buffer_prototype[THREAD_LOG_BUFFER_LENGTH];

/* accesor functions
 *─────────────────────────────────────────────────────────────────────────── */
inline char *
thread_log_buffer_ptr(struct ThreadLog *const restrict log)
{
	return &log->buffer[0];
}

inline char *
thread_log_current_ptr(struct ThreadLog *const restrict log)
{
	return log->current_ptr;
}

inline char *
thread_log_end_ptr(struct ThreadLog *const restrict log)
{
	return log->until_ptr;
}

inline size_t
thread_log_remaining_characters(struct ThreadLog *const restrict log)
{
	return log->until_ptr - log->current_ptr;
}

/* locking the log... */
inline bool
thread_log_lock_status(struct ThreadLog *const restrict log)
{
	return mutex_lock_status(&log->lock);
}

inline void
thread_log_lock_muffle(struct ThreadLog *const restrict log)
{
	mutex_lock_muffle(&log->lock);
}

inline bool
thread_log_lock_report(struct ThreadLog *const restrict log,
		       const char *restrict *const restrict failure)
{
	return mutex_lock_report(&log->lock,
				 failure);
}

inline void
thread_log_lock_handle(struct ThreadLog *const restrict log,
		       ThreadHandler *const handle,
		       void *arg)
{
	mutex_lock_handle(&log->lock,
			  handle,
			  arg);
}

inline void
thread_log_lock_handle_cl(struct ThreadLog *const restrict log,
			  struct ThreadHandlerClosure *const restrict cl)
{
	mutex_lock_handle_cl(&log->lock,
			     cl);
}

/* locking the log (no block on failure) */
inline bool
thread_log_try_lock_status(struct ThreadLog *const restrict log)
{
	return mutex_try_lock_status(&log->lock);
}

inline void
thread_log_try_lock_muffle(struct ThreadLog *const restrict log)
{
	mutex_try_lock_muffle(&log->lock);
}

inline enum ThreadFlag
thread_log_try_lock_report(struct ThreadLog *const restrict log,
			   const char *restrict *const restrict failure)
{
	return mutex_try_lock_report(&log->lock,
				     failure);
}

inline void
thread_log_try_lock_handle(struct ThreadLog *const restrict log,
		       ThreadHandler *const handle,
		       void *arg)
{
	mutex_try_lock_handle(&log->lock,
			      handle,
			      arg);
}

inline void
thread_log_try_lock_handle_cl(struct ThreadLog *const restrict log,
			      struct ThreadHandlerClosure *const restrict cl)
{
	mutex_try_lock_handle_cl(&log->lock,
				 cl);
}

/* unlocking the log... */
inline bool
thread_log_unlock_status(struct ThreadLog *const restrict log)
{
	return mutex_unlock_status(&log->lock);
}

inline void
thread_log_unlock_muffle(struct ThreadLog *const restrict log)
{
	mutex_unlock_muffle(&log->lock);
}

inline bool
thread_log_unlock_report(struct ThreadLog *const restrict log,
			 const char *restrict *const restrict failure)
{
	return mutex_unlock_report(&log->lock,
				   failure);
}

inline void
thread_log_unlock_handle(struct ThreadLog *const restrict log,
			 ThreadHandler *const handle,
			 void *arg)
{
	mutex_unlock_handle(&log->lock,
			    handle,
			    arg);
}

inline void
thread_log_unlock_handle_cl(struct ThreadLog *const restrict log,
			    struct ThreadHandlerClosure *const restrict cl)
{
	mutex_unlock_handle_cl(&log->lock,
			       cl);
}





/* mutator functions
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_log_append_string(struct ThreadLog *const restrict log,
			 const char *const restrict string)
{
	log->current_ptr = put_string_until(log->current_ptr,
					    string,
					    log->until_ptr);
}

inline void
thread_log_append_digits(struct ThreadLog *const restrict log,
			 const size_t n)
{
	log->current_ptr = put_digits_until(log->current_ptr,
						n,
						log->until_ptr);
}

inline void
thread_log_append_number(struct ThreadLog *const restrict log,
			 const ssize_t n)
{
	log->current_ptr = put_number_until(log->current_ptr,
					    n,
					    log->until_ptr);
}

inline void
thread_log_append_pointer_id(struct ThreadLog *const restrict log,
			     void *const restrict pointer)
{
	log->current_ptr = put_pointer_id_until(log->current_ptr,
						pointer,
						log->until_ptr);
}

inline void
thread_log_append_string_length(struct ThreadLog *const restrict log,
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
thread_log_append_digits_length(struct ThreadLog *const restrict log,
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
thread_log_append_number_length(struct ThreadLog *const restrict log,
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

inline void
thread_log_append_pointer_id_length(struct ThreadLog *const restrict log,
				    void *const restrict pointer,
				    const size_t length)
{
	char *const restrict length_ptr = log->current_ptr
					+ length;

	log->current_ptr = put_pointer_id_until(log->current_ptr,
						pointer,
						(length_ptr > log->until_ptr)
						? log->until_ptr
						: length_ptr);
}

/* initialize
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_log_init(struct ThreadLog *const restrict log,
		const char *const restrict label)
{
	mutex_init(&log->lock);

	memcpy(&log->buffer[0],
	       &thread_log_buffer_prototype,
	       sizeof(thread_log_buffer_prototype));

	log->until_ptr   = &log->buffer[THREAD_LOG_BUFFER_LENGTH - 1];
	log->current_ptr = &log->buffer[sizeof(THREAD_LOG_HEADER_1) - 1];

	thread_log_append_string(log,
				 label);

	thread_log_append_string(log,
				 THREAD_LOG_HEADER_2);

	thread_log_append_pointer_id(log,
				     (void *) log);

	thread_log_append_string(log,
				 THREAD_LOG_HEADER_3);
}

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_LOG_H_ */
