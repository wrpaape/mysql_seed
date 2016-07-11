#include "mysql_seed_file.h"

/* FileHandle Operations
 * ────────────────────────────────────────────────────────────────────────── */
/* open */
extern inline bool
file_handle_open_status(struct FileHandle *const restrict file);
extern inline void
file_handle_open_muffle(struct FileHandle *const restrict file);
extern inline bool
file_handle_open_report(struct FileHandle *const restrict file,
			const char *restrict *const restrict failure);
extern inline void
file_handle_open_handle(struct FileHandle *const restrict file,
			Handler *const handle,
			void *arg);
extern inline void
file_handle_open_handle_cl(struct FileHandle *const restrict file,
			   const struct HandlerClosure *const restrict fail_cl);

/* write */
extern inline bool
file_handle_write_status(const struct FileHandle *const restrict file);
extern inline void
file_handle_write_muffle(const struct FileHandle *const restrict file);
extern inline bool
file_handle_write_report(const struct FileHandle *const restrict file,
			 const char *restrict *const restrict failure);
extern inline void
file_handle_write_handle(const struct FileHandle *const restrict file,
			Handler *const handle,
			void *arg);
extern inline void
file_handle_write_handle_cl(const struct FileHandle *const restrict file,
			    const struct HandlerClosure *const restrict fail_cl);

/* close */
extern inline bool
file_handle_close_status(const struct FileHandle *const restrict file);
extern inline void
file_handle_close_muffle(const struct FileHandle *const restrict file);
extern inline bool
file_handle_close_report(const struct FileHandle *const restrict file,
			 const char *restrict *const restrict failure);
extern inline void
file_handle_close_handle(const struct FileHandle *const restrict file,
			 Handler *const handle,
			 void *arg);
extern inline void
file_handle_close_handle_cl(const struct FileHandle *const restrict file,
			    const struct HandlerClosure *const restrict fail_cl);

/* unlink */
extern inline bool
file_handle_unlink_status(const struct FileHandle *const restrict file);
extern inline void
file_handle_unlink_muffle(const struct FileHandle *const restrict file);
extern inline bool
file_handle_unlink_report(const struct FileHandle *const restrict file,
			 const char *restrict *const restrict failure);
extern inline void
file_handle_unlink_handle(const struct FileHandle *const restrict file,
			 Handler *const handle,
			 void *arg);
extern inline void
file_handle_unlink_handle_cl(const struct FileHandle *const restrict file,
			    const struct HandlerClosure *const restrict fail_cl);

/* cleanup */
void
file_handle_cleanup(void *arg)
{
	file_handle_close_muffle((const struct FileHandle *const restrict) arg);
	file_handle_unlink_muffle((const struct FileHandle *const restrict) arg);
}

/* atomic create-open-write-close */
extern inline void
file_handle_process(struct FileHandle *const restrict file,
		    const struct HandlerClosure *const restrict fail_cl);


/* DirHandle Operations
 * ────────────────────────────────────────────────────────────────────────── */
/* make */
extern inline bool
dir_handle_make_status(const struct DirHandle *const restrict dir);
extern inline void
dir_handle_make_muffle(const struct DirHandle *const restrict dir);
extern inline bool
dir_handle_make_report(const struct DirHandle *const restrict dir,
		       const char *restrict *const restrict failure);
extern inline void
dir_handle_make_handle(const struct DirHandle *const restrict dir,
		       Handler *const handle,
		       void *arg);
extern inline void
dir_handle_make_handle_cl(const struct DirHandle *const restrict dir,
			  const struct HandlerClosure *const restrict fail_cl);

/* remove */
extern inline bool
dir_handle_remove_status(const struct DirHandle *const restrict dir);
extern inline void
dir_handle_remove_muffle(const struct DirHandle *const restrict dir);
extern inline bool
dir_handle_remove_report(const struct DirHandle *const restrict dir,
			 const char *restrict *const restrict failure);
extern inline void
dir_handle_remove_handle(const struct DirHandle *const restrict dir,
			 Handler *const handle,
			 void *arg);
extern inline void
dir_handle_remove_handle_cl(const struct DirHandle *const restrict dir,
			    const struct HandlerClosure *const restrict fail_cl);

/* cleanup */
void
dir_handle_cleanup(void *arg)
{
	dir_handle_remove_muffle((const struct DirHandle *const restrict) arg);
}


/* LengthLock operations
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
length_lock_init(struct LengthLock *const restrict shared,
		 const size_t length_init);
extern inline void
length_lock_increment(struct LengthLock *const restrict shared,
		      const size_t increment,
		      const struct HandlerClosure *const restrict fail_cl);


/* Input operations
 * ────────────────────────────────────────────────────────────────────────── */
extern inline char **
flag_next(char *const restrict *restrict from,
	  const char *const restrict *const restrict until);
extern inline bool
flag_match(char *restrict arg,
	   const char short_flag,
	   const char *const restrict long_flag);
extern inline size_t
flag_match_count(char *const restrict *restrict from,
		 char *const restrict *const restrict until,
		 const char short_flag,
		 const char *const restrict long_flag);
extern inline char **
flag_match_next(char *const restrict *restrict from,
		char *const restrict *const restrict until,
		const char short_flag,
		const char *const restrict long_flag);


/* ArgvInterval operations
 * ────────────────────────────────────────────────────────────────────────── */
extern inline bool
argv_interval_init(struct ArgvInterval *const restrict interval,
		   char *const restrict *const restrict from,
		   const char *const restrict *const restrict until,
		   const size_t length_min);
extern inline char *
put_inspect_args(char *restrict buffer,
		 char *restrict *const restrict from,
		 char *const restrict *const restrict until);
