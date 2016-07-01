#include "thread/thread_log.h"


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */

char thread_log_buffer_prototype[THREAD_LOG_BUFFER_LENGTH] = {
	[0 ... (sizeof(THREAD_LOG_HEADER_1) - 1)] = THREAD_LOG_HEADER_1,
	[sizeof(THREAD_LOG_HEADER_1) ... (THREAD_LOG_BUFFER_LENGTH - 1)] = '\0'
};


/* accesor functions
 *─────────────────────────────────────────────────────────────────────────── */
extern inline char *
thread_log_buffer_ptr(struct ThreadLog *const restrict log);

extern inline char *
thread_log_current_ptr(struct ThreadLog *const restrict log);

extern inline char *
thread_log_end_ptr(struct ThreadLog *const restrict log);

extern inline size_t
thread_log_remaining_characters(struct ThreadLog *const restrict log);


/* locking the log */
extern inline bool
thread_log_lock(struct ThreadLog *const restrict log);
extern inline void
thread_log_lock_muffle(struct ThreadLog *const restrict log);
extern inline bool
thread_log_lock_report(struct ThreadLog *const restrict log,
		       const char *restrict *const restrict failure);
extern inline void
thread_log_lock_handle(struct ThreadLog *const restrict log,
		       ThreadHandler *const handle,
		       void *arg);
extern inline void
thread_log_lock_handle_cl(struct ThreadLog *const restrict log,
			  ThreadHandlerClosure *const restrict cl);
/* locking the log (no block on failure) */
extern inline bool
thread_log_try_lock(struct ThreadLog *const restrict log);
extern inline void
thread_log_try_lock_muffle(struct ThreadLog *const restrict log);
extern inline enum ThreadFlag
thread_log_try_lock_report(struct ThreadLog *const restrict log,
/* unlocking the log... */
extern inline bool
thread_log_unlock(struct ThreadLog *const restrict log);
extern inline void
thread_log_unlock_muffle(struct ThreadLog *const restrict log);
extern inline bool
thread_log_unlock_report(struct ThreadLog *const restrict log,
			 const char *restrict *const restrict failure);
extern inline void
thread_log_unlock_handle(struct ThreadLog *const restrict log,
			 ThreadHandler *const handle,
			 void *arg);
extern inline void
thread_log_unlock_handle_cl(struct ThreadLog *const restrict log,
			    ThreadHandlerClosure *const restrict cl);

/* mutator functions
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_log_append_string(const char *const restrict string);

extern inline void
thread_log_append_digits(const size_t n);

extern inline void
thread_log_append_number(const ssize_t n);

extern inline void
thread_log_append_string_length(const char *const restrict string,
			      const size_t length);

extern inline void
thread_log_append_digits_length(const size_t n,
			      const size_t length);

extern inline void
thread_log_append_number_length(const ssize_t n,
			      const size_t length);
/* initialize, reset
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_log_init(struct ThreadLog *const restrict log,
		const char *const restrict label,
		const size_t id);
