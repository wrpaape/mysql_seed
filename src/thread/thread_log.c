#include "thread/thread_log.h"


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */

const char thread_log_buffer_prototype[THREAD_LOG_BUFFER_LENGTH] = {
	THREAD_LOG_OPEN_HEADER
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
extern inline size_t
thread_log_buffer_size(struct ThreadLog *const restrict log);

/* locking the log */
extern inline bool
thread_log_lock_status(struct ThreadLog *const restrict log);
extern inline void
thread_log_lock_muffle(struct ThreadLog *const restrict log);
extern inline bool
thread_log_lock_report(struct ThreadLog *const restrict log,
		       const char *restrict *const restrict failure);
extern inline void
thread_log_lock_handle(struct ThreadLog *const restrict log,
		       Handler *const handle,
		       void *arg);
extern inline void
thread_log_lock_handle_cl(struct ThreadLog *const restrict log,
			  const struct HandlerClosure *const restrict cl);
/* locking the log (no block on failure) */
extern inline bool
thread_log_try_lock_status(struct ThreadLog *const restrict log);
extern inline void
thread_log_try_lock_muffle(struct ThreadLog *const restrict log);
extern inline enum BoolStatus
thread_log_try_lock_report(struct ThreadLog *const restrict log,
			   const char *restrict *const restrict failure);
extern inline void
thread_log_try_lock_handle(struct ThreadLog *const restrict log,
			   Handler *const handle,
			   void *arg);
extern inline void
thread_log_try_lock_handle_cl(struct ThreadLog *const restrict log,
			      const struct HandlerClosure *const restrict cl);
/* unlocking the log... */
extern inline bool
thread_log_unlock_status(struct ThreadLog *const restrict log);
extern inline void
thread_log_unlock_muffle(struct ThreadLog *const restrict log);
extern inline bool
thread_log_unlock_report(struct ThreadLog *const restrict log,
			 const char *restrict *const restrict failure);
extern inline void
thread_log_unlock_handle(struct ThreadLog *const restrict log,
			 Handler *const handle,
			 void *arg);
extern inline void
thread_log_unlock_handle_cl(struct ThreadLog *const restrict log,
			    const struct HandlerClosure *const restrict cl);

/* dump contents to file */
extern inline bool
thread_log_dump_status(struct ThreadLog *const restrict log,
		       const int file_descriptor);
extern inline void
thread_log_dump_muffle(struct ThreadLog *const restrict log,
		       const int file_descriptor);
extern inline bool
thread_log_dump_report(struct ThreadLog *const restrict log,
		       const int file_descriptor,
		       const char *restrict *const restrict failure);
extern inline void
thread_log_dump_handle(struct ThreadLog *const restrict log,
		       const int file_descriptor,
		       Handler *const handle,
		       void *arg);
extern inline void
thread_log_dump_handle_cl(struct ThreadLog *const restrict log,
			  const int file_descriptor,
			  const struct HandlerClosure *const restrict cl);

/* mutator functions
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_log_append_string(struct ThreadLog *const restrict log,
			 const char *const restrict string);
extern inline void
thread_log_append_uint(struct ThreadLog *const restrict log,
		       const uintmax_t n);
extern inline void
thread_log_append_int(struct ThreadLog *const restrict log,
		      const intmax_t n);
extern inline void
thread_log_append_pointer_id(struct ThreadLog *const restrict log,
			     void *const restrict pointer);
extern inline void
thread_log_append_string_size(struct ThreadLog *const restrict log,
			      const char *const restrict string,
			      const size_t size);
extern inline void
thread_log_append_string_width(struct ThreadLog *const restrict log,
			       const char *const restrict string,
			       const unsigned int width);
extern inline void
thread_log_append_string_length(struct ThreadLog *const restrict log,
				const char *const restrict string,
				const size_t length);
extern inline void
thread_log_append_uint_length(struct ThreadLog *const restrict log,
			      const uintmax_t n,
			      const size_t length);
extern inline void
thread_log_append_int_length(struct ThreadLog *const restrict log,
			     const intmax_t n,
			     const size_t length);
extern inline void
thread_log_append_pointer_id_length(struct ThreadLog *const restrict log,
				    void *const restrict pointer,
				    const size_t length);
extern inline void
thread_log_append_close(struct ThreadLog *const restrict log);

/* initialize, reset
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_log_label_init(struct ThreadLogLabel *const restrict label,
		      const char *const restrict name);
extern inline void
thread_log_init(struct ThreadLog *const restrict log,
		const char *const restrict label);
