#ifndef MYSQL_SEED_THREAD_THREAD_LOG_H_
#define MYSQL_SEED_THREAD_THREAD_LOG_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* Mutex */
#include "string/string_utils.h"	/* string utils */
#include "system/file_utils.h"		/* write */


/* cap log buffer at 1kb
 *─────────────────────────────────────────────────────────────────────────── */
#define THREAD_LOG_LABEL_SIZE_MAX 128lu
#define THREAD_LOG_BUFFER_LENGTH 1024lu
#define THREAD_LOG_HEADER_1(ACTION) ANSI_BRIGHT ANSI_BLACK_BG "\n\n"	\
ANSI_YELLOW "THREAD LOG " ACTION " FOR:\t"
#define THREAD_LOG_HEADER_2 ANSI_BLACK_BG "\n" ANSI_RESET

#define THREAD_LOG_LABEL_1 ANSI_WHITE_BG ANSI_BLUE
#define THREAD_LOG_LABEL_2 ANSI_BLACK_BG " " ANSI_BLUE_BG ANSI_WHITE

#define THREAD_LOG_OPEN_HEADER THREAD_LOG_HEADER_1("OPEN")
#define THREAD_LOG_CLOSE_HEADER  THREAD_LOG_HEADER_1("CLOSE")


/* declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct ThreadLogLabel {
	char buffer[THREAD_LOG_LABEL_SIZE_MAX];
	size_t length;
};

struct ThreadLog {
	Mutex lock;
	struct ThreadLogLabel label;
	char buffer[THREAD_LOG_BUFFER_LENGTH];
	char *restrict current;
	char *restrict until;
};

struct ThreadLogBufferBuffer {
	char bytes[THREAD_LOG_BUFFER_LENGTH];
};

#define SET_THREAD_LOG_BUFFER(PTR, BUFFER)				\
*((struct ThreadLogBufferBuffer *const restrict) (PTR))			\
= *((const struct ThreadLogBufferBuffer *const restrict) (BUFFER))


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
	return log->current;
}

inline char *
thread_log_end_ptr(struct ThreadLog *const restrict log)
{
	return log->until;
}

inline size_t
thread_log_remaining_characters(struct ThreadLog *const restrict log)
{
	return log->until - log->current;
}

inline size_t
thread_log_buffer_size(struct ThreadLog *const restrict log)
{
	return log->current - &log->buffer[0];
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
		       Handler *const handle,
		       void *arg)
{
	mutex_lock_handle(&log->lock,
			  handle,
			  arg);
}

inline void
thread_log_lock_handle_cl(struct ThreadLog *const restrict log,
			  const struct HandlerClosure *const restrict cl)
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
		       Handler *const handle,
		       void *arg)
{
	mutex_try_lock_handle(&log->lock,
			      handle,
			      arg);
}

inline void
thread_log_try_lock_handle_cl(struct ThreadLog *const restrict log,
			      const struct HandlerClosure *const restrict cl)
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
			 Handler *const handle,
			 void *arg)
{
	mutex_unlock_handle(&log->lock,
			    handle,
			    arg);
}

inline void
thread_log_unlock_handle_cl(struct ThreadLog *const restrict log,
			    const struct HandlerClosure *const restrict cl)
{
	mutex_unlock_handle_cl(&log->lock,
			       cl);
}

/* dump contents to file */
inline bool
thread_log_dump_status(struct ThreadLog *const restrict log,
		       const int file_descriptor)
{
	return write_status(file_descriptor,
			    &log->buffer[0],
			    thread_log_buffer_size(log));
}

inline void
thread_log_dump_muffle(struct ThreadLog *const restrict log,
		       const int file_descriptor)
{
	(void) write_status(file_descriptor,
			    &log->buffer[0],
			    thread_log_buffer_size(log));
}

inline bool
thread_log_dump_report(struct ThreadLog *const restrict log,
		       const int file_descriptor,
		       const char *restrict *const restrict failure)
{
	return write_report(file_descriptor,
			    &log->buffer[0],
			    thread_log_buffer_size(log),
			    failure);
}

inline void
thread_log_dump_handle(struct ThreadLog *const restrict log,
		       const int file_descriptor,
		       Handler *const handle,
		       void *arg)
{
	write_handle(file_descriptor,
		     &log->buffer[0],
		     thread_log_buffer_size(log),
		     handle,
		     arg);
}

inline void
thread_log_dump_handle_cl(struct ThreadLog *const restrict log,
			  const int file_descriptor,
			  const struct HandlerClosure *const restrict cl)
{
	write_handle_cl(file_descriptor,
			&log->buffer[0],
			thread_log_buffer_size(log),
			cl);
}


/* mutator functions
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_log_append_string(struct ThreadLog *const restrict log,
			 const char *const restrict string)
{
	log->current = put_string_until(log->current,
					    string,
					    log->until);
}

inline void
thread_log_append_uint(struct ThreadLog *const restrict log,
		       const uintmax_t n)
{
	log->current = put_uint_until(log->current,
					  n,
					  log->until);
}

inline void
thread_log_append_int(struct ThreadLog *const restrict log,
		      const intmax_t n)
{
	log->current = put_int_until(log->current,
					 n,
					 log->until);
}

inline void
thread_log_append_pointer_id(struct ThreadLog *const restrict log,
			     void *const restrict pointer)
{
	log->current = put_pointer_id_until(log->current,
						pointer,
						log->until);
}

inline void
thread_log_append_string_size(struct ThreadLog *const restrict log,
			      const char *const restrict string,
			      const size_t size)
{
	log->current = put_string_size_until(log->current,
					     string,
					     size,
					     log->until);
}

inline void
thread_log_append_string_length(struct ThreadLog *const restrict log,
				const char *const restrict string,
				const size_t length)
{
	char *const restrict length_ptr = log->current
					+ length;

	log->current = put_string_until(log->current,
					    string,
					    (length_ptr > log->until)
					    ? log->until
					    : length_ptr);
}

inline void
thread_log_append_uint_length(struct ThreadLog *const restrict log,
			      const uintmax_t n,
			      const size_t length)
{
	char *const restrict length_ptr = log->current
					+ length;

	log->current = put_uint_until(log->current,
					  n,
					  (length_ptr > log->until)
					  ? log->until
					  : length_ptr);
}

inline void
thread_log_append_int_length(struct ThreadLog *const restrict log,
			     const intmax_t n,
			     const size_t length)
{
	char *const restrict length_ptr = log->current
					+ length;

	log->current = put_int_until(log->current,
					 n,
					 (length_ptr > log->until)
					 ? log->until
					 : length_ptr);
}

inline void
thread_log_append_pointer_id_length(struct ThreadLog *const restrict log,
				    void *const restrict pointer,
				    const size_t length)
{
	char *const restrict length_ptr = log->current
					+ length;

	log->current = put_pointer_id_until(log->current,
						pointer,
						(length_ptr > log->until)
						? log->until
						: length_ptr);
}

inline void
thread_log_append_close(struct ThreadLog *const restrict log)
{
	thread_log_append_string_size(log,
				      THREAD_LOG_CLOSE_HEADER,
				      sizeof(THREAD_LOG_CLOSE_HEADER) - 1lu);

	thread_log_append_string_size(log,
				      &log->label.buffer[0],
				      log->label.length);

	thread_log_append_string_size(log,
				      THREAD_LOG_HEADER_2,
				      sizeof(THREAD_LOG_HEADER_2) - 1lu);
}

/* initialize
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_log_label_init(struct ThreadLogLabel *const restrict label,
		      const char *const restrict name)
{
	char *const restrict until = &label->buffer[0]
				   + THREAD_LOG_LABEL_SIZE_MAX;

	char *restrict ptr = put_string_size(&label->buffer[0],
					     THREAD_LOG_LABEL_1,
					     sizeof(THREAD_LOG_LABEL_1) - 1lu);
	ptr = put_string_until(ptr,
			       name,
			       until);

	ptr = put_string_size_until(ptr,
				    THREAD_LOG_LABEL_2,
				    sizeof(THREAD_LOG_LABEL_2) - 1lu,
				    until);

	ptr = put_pointer_id_until(ptr,
				   label,
				   until);

	label->length = ptr - &label->buffer[0];
}

inline void
thread_log_init(struct ThreadLog *const restrict log,
		const char *const restrict name)
{
	mutex_init(&log->lock);

	SET_THREAD_LOG_BUFFER(&log->buffer[0],
			      &thread_log_buffer_prototype[0]);

	thread_log_label_init(&log->label,
			      name);

	log->until = &log->buffer[THREAD_LOG_BUFFER_LENGTH - 1];

	log->current
	= put_string_size_until(&log->buffer[sizeof(THREAD_LOG_OPEN_HEADER)
					     - 1],
				&log->label.buffer[0],
				log->label.length,
				log->until);

	thread_log_append_string_size(log,
				      THREAD_LOG_HEADER_2,
				      sizeof(THREAD_LOG_HEADER_2) - 1lu);
}

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_LOG_H_ */
