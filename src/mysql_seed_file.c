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
dirpath_make_status(const struct Dirpath *const restrict path);
extern inline void
dirpath_make_muffle(const struct Dirpath *const restrict path);
extern inline bool
dirpath_make_report(const struct Dirpath *const restrict path,
		    const char *restrict *const restrict failure);
extern inline void
dirpath_make_handle(const struct Dirpath *const restrict path,
		    Handler *const handle,
		    void *arg);
extern inline void
dirpath_make_handle_cl(const struct Dirpath *const restrict path,
		       const struct HandlerClosure *const restrict fail_cl);

/* remove */
extern inline bool
dirpath_remove_status(const struct Dirpath *const restrict path);
extern inline void
dirpath_remove_muffle(const struct Dirpath *const restrict path);
extern inline bool
dirpath_remove_report(const struct Dirpath *const restrict path,
		      const char *restrict *const restrict failure);
extern inline void
dirpath_remove_handle(const struct Dirpath *const restrict path,
		      Handler *const handle,
		      void *arg);
extern inline void
dirpath_remove_handle_cl(const struct Dirpath *const restrict path,
			 const struct HandlerClosure *const restrict fail_cl);

/* cleanup */
void
dirpath_cleanup(void *arg)
{
	dirpath_remove_muffle((const struct DirHandle *const restrict) arg);
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
extern inline char *const restrict *restrict
flag_next(char *const restrict *restrict from,
	  char *const restrict *const restrict until);
extern inline bool
flag_match(char *restrict arg,
	   const char short_flag,
	   const char *const restrict long_flag);
extern inline size_t
flag_match_count(char *const restrict *restrict from,
		 char *const restrict *const restrict until,
		 const char short_flag,
		 const char *const restrict long_flag);
inline char *const restrict *restrict
flag_match_next(char *const restrict *restrict from,
		char *const restrict *const restrict until,
		const char short_flag,
		const char *const restrict long_flag);


/* Argv operations
 * ────────────────────────────────────────────────────────────────────────── */
extern inline char *
put_inspect_args(char *restrict buffer,
		 char *const restrict *restrict from,
		 char *const restrict *const restrict until);
