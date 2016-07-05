#ifndef MYSQL_SEED_THREAD_THREAD_LOG_H_
#define MYSQL_SEED_THREAD_THREAD_LOG_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* Mutex, memcpy  */
#include "string/string_utils.h"	/* string utils */
#include "system/file_utils.h"		/* write */


/* cap log buffer at 1kb
 *─────────────────────────────────────────────────────────────────────────── */
#define THREAD_LOG_LABEL_LENGTH 128lu
#define THREAD_LOG_BUFFER_LENGTH 1024lu
#define THREAD_LOG_HEADER_1(ACTION) ANSI_BRIGHT ANSI_BLACK_BG "\n\n"	\
ANSI_YELLOW "THREAD LOG " ACTION " FOR:\t"
#define THREAD_LOG_HEADER_2 ANSI_BLACK_BG "\n\n" ANSI_RESET

#define THREAD_LOG_LABEL_1 ANSI_WHITE_BG ANSI_BLUE
#define THREAD_LOG_LABEL_2 ANSI_BLACK_BG " " ANSI_BLUE_BG ANSI_WHITE

#define THREAD_LOG_OPEN_HEADER THREAD_LOG_HEADER_1("OPEN")
#define THREAD_LOG_CLOSE_HEADER  THREAD_LOG_HEADER_1("CLOSE")


/* declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct ThreadLog {
	char *restrict current_ptr;
	char *restrict until_ptr;
	Mutex lock;
	char label[THREAD_LOG_LABEL_LENGTH];
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

inline size_t
thread_log_buffer_size(struct ThreadLog *const restrict log)
{
	return log->current_ptr - &log->buffer[0];
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

inline void
thread_log_append_close(struct ThreadLog *const restrict log)
{
	thread_log_append_string(log,
				 THREAD_LOG_CLOSE_HEADER);

	thread_log_append_string(log,
				 &log->label[0]);

	thread_log_append_string(log,
				 THREAD_LOG_HEADER_2);
}

/* initialize
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_log_init_label(struct ThreadLog *const restrict log,
		      const char *const restrict name)
{
	char *const restrict until_ptr = &log->label[THREAD_LOG_LABEL_LENGTH
						     - 1];

	char *restrict ptr = put_string(&log->label[0],
					THREAD_LOG_LABEL_1);
	ptr  = put_string_until(ptr,
				name,
				until_ptr);

	ptr  = put_string_until(ptr,
				THREAD_LOG_LABEL_2,
				until_ptr);

	ptr  = put_pointer_id_until(ptr,
				    log,
				    until_ptr);
	*ptr = '\0';
}

inline void
thread_log_init(struct ThreadLog *const restrict log,
		const char *const restrict name)
{
	mutex_init(&log->lock);

	(void) memcpy(&log->buffer[0],
		      &thread_log_buffer_prototype,
		      sizeof(thread_log_buffer_prototype));

	thread_log_init_label(log,
			      name);

	log->current_ptr =
		put_string(&log->buffer[sizeof(THREAD_LOG_OPEN_HEADER) - 1],
			   &log->label[0]);

	log->current_ptr = put_string(log->current_ptr,
				      THREAD_LOG_HEADER_2);

	log->until_ptr   = &log->buffer[THREAD_LOG_BUFFER_LENGTH - 1];
}

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_LOG_H_ */
