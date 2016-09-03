#include "system/file_utils.h"

/* access (absolute or relative path) */
extern inline bool
access_status(const char *const restrict path,
	      const int mode);
extern inline void
access_muffle(const char *const restrict path,
	      const int mode);
extern inline bool
access_report(const char *const restrict path,
	      const int mode,
	      const char *restrict *const restrict failure);
extern inline void
access_handle(const char *const restrict path,
	      const int mode,
	      Handler *const handle,
	      void *arg);
extern inline void
access_handle_cl(const char *const restrict path,
		 const int mode,
		 const struct HandlerClosure *const restrict fail_cl);

/* open (absolute or relative path, no mode) */
extern inline bool
open_status(int *const restrict file_descriptor,
	    const char *const path,
	    const int open_flag);
extern inline void
open_muffle(int *const restrict file_descriptor,
	    const char *const path,
	    const int open_flag);
extern inline bool
open_report(int *const restrict file_descriptor,
	    const char *const path,
	    const int open_flag,
	    const char *restrict *const restrict failure);
extern inline void
open_handle(int *const restrict file_descriptor,
	    const char *const path,
	    const int open_flag,
	    Handler *const handle,
	    void *arg);
extern inline void
open_handle_cl(int *const restrict file_descriptor,
	       const char *const path,
	       const int open_flag,
	       const struct HandlerClosure *const restrict fail_cl);

/* open (absolute or relative path, provide mode) */
extern inline bool
open_mode_status(int *const restrict file_descriptor,
		 const char *const path,
		 const int open_flag,
		 const mode_t mode);
extern inline void
open_mode_muffle(int *const restrict file_descriptor,
		 const char *const mode_path,
		 const int open_flag,
		 const mode_t mode);
extern inline bool
open_mode_report(int *const restrict file_descriptor,
		 const char *const mode_path,
		 const int open_flag,
		 const mode_t mode,
		 const char *restrict *const restrict failure);
extern inline void
open_mode_handle(int *const restrict file_descriptor,
		 const char *const mode_path,
		 const int open_flag,
		 const mode_t mode,
		 Handler *const handle,
		 void *arg);
extern inline void
open_mode_handle_cl(int *const restrict file_descriptor,
		    const char *const path,
		    const int open_flag,
		    const mode_t mode,
		    const struct HandlerClosure *const restrict fail_cl);

#ifndef WIN32
/* open (relative path, no mode) */
extern inline bool
open_relative_status(int *const restrict file_descriptor,
		     const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag);
extern inline void
open_relative_muffle(int *const restrict file_descriptor,
		     const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag);
extern inline bool
open_relative_report(int *const restrict file_descriptor,
		     const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag,
		     const char *restrict *const restrict failure);
extern inline void
open_relative_handle(int *const restrict file_descriptor,
		     const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag,
		     Handler *const handle,
		     void *arg);
extern inline void
open_relative_handle_cl(int *const restrict file_descriptor,
			const int directory_descriptor,
			const char *const relative_path,
			const int open_flag,
			const struct HandlerClosure *const restrict fail_cl);

/* open (relative path, provide mode) */
extern inline bool
open_relative_mode_status(int *const restrict file_descriptor,
			  const int directory_descriptor,
			  const char *const relative_path,
			  const int open_flag,
			  const mode_t mode);
extern inline void
open_relative_mode_muffle(int *const restrict file_descriptor,
			  const int directory_descriptor,
			  const char *const relative_mode_path,
			  const int open_flag,
			  const mode_t mode);
extern inline bool
open_relative_mode_report(int *const restrict file_descriptor,
			  const int directory_descriptor,
			  const char *const relative_mode_path,
			  const int open_flag,
			  const mode_t mode,
			  const char *restrict *const restrict failure);
extern inline void
open_relative_mode_handle(int *const restrict file_descriptor,
			  const int directory_descriptor,
			  const char *const relative_mode_path,
			  const int open_flag,
			  const mode_t mode,
			  Handler *const handle,
			  void *arg);
extern inline void
open_relative_mode_handle_cl(int *const restrict file_descriptor,
			     const int directory_descriptor,
			     const char *const relative_path,
			     const int open_flag,
			     const mode_t mode,
			     const struct HandlerClosure *const restrict fail_cl);
#endif /* ifndef WIN32 */


/* read */
extern inline bool
read_status(const int file_descriptor,
	    void *const restrict buffer,
	    const size_t size);
extern inline void
read_muffle(const int file_descriptor,
	    void *const restrict buffer,
	    const size_t size);
extern inline bool
read_report(const int file_descriptor,
	    void *const restrict buffer,
	    const size_t size,
	    const char *restrict *const restrict failure);
extern inline void
read_handle(const int file_descriptor,
	    void *const restrict buffer,
	    const size_t size,
	    Handler *const handle,
	    void *arg);
extern inline void
read_handle_cl(const int file_descriptor,
	       void *const restrict buffer,
	       const size_t size,
	       const struct HandlerClosure *const restrict fail_cl);

/* write */
extern inline bool
write_status(const int file_descriptor,
	     const void *const restrict buffer,
	     const size_t size);
extern inline void
write_muffle(const int file_descriptor,
	     const void *const restrict buffer,
	     const size_t size);
extern inline bool
write_report(const int file_descriptor,
	     const void *const restrict buffer,
	     const size_t size,
	     const char *restrict *const restrict failure);
extern inline void
write_handle(const int file_descriptor,
	     const void *const restrict buffer,
	     const size_t size,
	     Handler *const handle,
	     void *arg);
extern inline void
write_handle_cl(const int file_descriptor,
		const void *const restrict buffer,
		const size_t size,
		const struct HandlerClosure *const restrict fail_cl);

/* close */
extern inline bool
close_status(const int file_descriptor);
extern inline void
close_muffle(const int file_descriptor);
extern inline bool
close_report(const int file_descriptor,
	     const char *restrict *const restrict failure);
extern inline void
close_handle(const int file_descriptor,
	     Handler *const handle,
	     void *arg);
extern inline void
close_handle_cl(const int file_descriptor,
		const struct HandlerClosure *const restrict fail_cl);

/* unlink (absolute or relative path) */
extern inline bool
unlink_status(const char *const restrict path);
extern inline void
unlink_muffle(const char *const restrict path);
extern inline bool
unlink_report(const char *const restrict path,
	      const char *restrict *const restrict failure);
extern inline void
unlink_handle(const char *const restrict path,
	      Handler *const handle,
	      void *arg);
extern inline void
unlink_handle_cl(const char *const restrict path,
		 const struct HandlerClosure *const restrict fail_cl);

#ifndef WIN32
/* unlink (relative path) */
extern inline bool
unlink_relative_status(const int directory_descriptor,
		       const char *const restrict relative_path,
		       const int unlink_flag);
extern inline void
unlink_relative_muffle(const int directory_descriptor,
		       const char *const restrict relative_path,
		       const int unlink_flag);
extern inline bool
unlink_relative_report(const int directory_descriptor,
		       const char *const restrict relative_path,
		       const int unlink_flag,
		       const char *restrict *const restrict failure);
extern inline void
unlink_relative_handle(const int directory_descriptor,
		       const char *const restrict relative_path,
		       const int unlink_flag,
		       Handler *const handle,
		       void *arg);
extern inline void
unlink_relative_handle_cl(const int directory_descriptor,
			  const char *const restrict relative_path,
			  const int unlink_flag,
			  const struct HandlerClosure *const restrict fail_cl);
#endif /* ifndef WIN32 */

/* fetch info on a file */
extern inline bool
stat_status(const char *const restrict path,
	    struct StatBuffer *const restrict buffer);
extern inline void
stat_muffle(const char *const restrict path,
	    struct StatBuffer *const restrict buffer);
extern inline bool
stat_report(const char *const restrict path,
	    struct StatBuffer *const restrict buffer,
	    const char *restrict *const restrict failure);
extern inline void
stat_handle(const char *const restrict path,
	    struct StatBuffer *const restrict buffer,
	    Handler *const handle,
	    void *arg);
extern inline void
stat_handle_cl(const char *const restrict path,
	       struct StatBuffer *const restrict buffer,
	       const struct HandlerClosure *const restrict fail_cl);

/* mkdir (absolute or relative path) */
extern inline bool
mkdir_status(const char *const restrict path,
	     const mode_t mode);
extern inline void
mkdir_muffle(const char *const restrict path,
	     const mode_t mode);
extern inline bool
mkdir_report(const char *const restrict path,
	     const mode_t mode,
	     const char *restrict *const restrict failure);
extern inline void
mkdir_handle(const char *const restrict path,
	     const mode_t mode,
	     Handler *const handle,
	     void *arg);
extern inline void
mkdir_handle_cl(const char *const restrict path,
		const mode_t mode,
		const struct HandlerClosure *const restrict fail_cl);

#ifndef WIN32
/* mkdir (relative path) */
extern inline bool
mkdir_relative_status(const int directory_descriptor,
		      const char *const restrict relative_path,
		      const mode_t mode);
extern inline void
mkdir_relative_muffle(const int directory_descriptor,
		      const char *const restrict relative_path,
		      const mode_t mode);
extern inline bool
mkdir_relative_report(const int directory_descriptor,
		      const char *const restrict relative_path,
		      const mode_t mode,
		      const char *restrict *const restrict failure);
extern inline void
mkdir_relative_handle(const int directory_descriptor,
		      const char *const restrict relative_path,
		      const mode_t mode,
		      Handler *const handle,
		      void *arg);
extern inline void
mkdir_relative_handle_cl(const int directory_descriptor,
			 const char *const restrict relative_path,
			 const mode_t mode,
			 const struct HandlerClosure *const restrict fail_cl);
#endif /* ifndef WIN32 */

/* chdir (absolute or relative path) */
extern inline bool
chdir_status(const char *const restrict path);
extern inline void
chdir_muffle(const char *const restrict path);
extern inline bool
chdir_report(const char *const restrict path,
	     const char *restrict *const restrict failure);
extern inline void
chdir_handle(const char *const restrict path,
	     Handler *const handle,
	     void *arg);
extern inline void
chdir_handle_cl(const char *const restrict path,
		const struct HandlerClosure *const restrict fail_cl);

/* rmdir (absolute or relative path) */
extern inline bool
rmdir_status(const char *const restrict path);
extern inline void
rmdir_muffle(const char *const restrict path);
extern inline bool
rmdir_report(const char *const restrict path,
	     const char *restrict *const restrict failure);
extern inline void
rmdir_handle(const char *const restrict path,
	     Handler *const handle,
	     void *arg);
extern inline void
rmdir_handle_cl(const char *const restrict path,
		const struct HandlerClosure *const restrict fail_cl);

#ifdef WIN32

/* find first file in directory other than "." and ".."  */
extern inline enum BoolStatus
find_first_contents_status(HANDLE *const restrict file,
			   const char *const restrict path,
			   WIN32_FIND_DATA *const restrict info);


#else
/* open a directory */
extern inline bool
opendir_status(DIR *restrict *const restrict dir,
	       const char *const restrict path);
extern inline void
opendir_muffle(DIR *restrict *const restrict dir,
	       const char *const restrict path);
extern inline bool
opendir_report(DIR *restrict *const restrict dir,
	       const char *const restrict path,
	       const char *restrict *const restrict failure);
extern inline void
opendir_handle(DIR *restrict *const restrict dir,
	       const char *const restrict path,
	       Handler *const handle,
	       void *arg);
extern inline void
opendir_handle_cl(DIR *restrict *const restrict dir,
		  const char *const restrict path,
		  const struct HandlerClosure *const restrict fail_cl);

/* read next entry of a directory */
extern inline bool
readdir_status(DIR *const restrict dir,
	       struct dirent *restrict *const restrict entry);
extern inline void
readdir_muffle(DIR *const restrict dir,
	       struct dirent *restrict *const restrict entry);
extern inline bool
readdir_report(DIR *const restrict dir,
	       struct dirent *restrict *const restrict entry,
	       const char *restrict *const restrict failure);
extern inline void
readdir_handle(DIR *const restrict dir,
	       struct dirent *restrict *const restrict entry,
	       Handler *const handle,
	       void *arg);
extern inline void
readdir_handle_cl(DIR *const restrict dir,
		  struct dirent *restrict *const restrict entry,
		  const struct HandlerClosure *const restrict fail_cl);

/* close a directory */
extern inline bool
closedir_status(DIR *const restrict dir);
extern inline void
closedir_muffle(DIR *const restrict dir);
extern inline bool
closedir_report(DIR *const restrict dir,
		const char *restrict *const restrict failure);
extern inline void
closedir_handle(DIR *const restrict dir,
	       Handler *const handle,
	       void *arg);
extern inline void
closedir_handle_cl(DIR *const restrict dir,
		   const struct HandlerClosure *const restrict fail_cl);

/* UNIX file tree traversal - open */
extern inline bool
fts_open_status(FTS *restrict *const restrict tree,
		char *const *path_argv,
		const int options,
		int (*compare)(const FTSENT **,
			       const FTSENT **));
extern inline void
fts_open_muffle(FTS *restrict *const restrict tree,
		char *const *path_argv,
		const int options,
		int (*compare)(const FTSENT **,
			       const FTSENT **));
extern inline bool
fts_open_report(FTS *restrict *const restrict tree,
		char *const *path_argv,
		const int options,
		int (*compare)(const FTSENT **,
			       const FTSENT **),
		const char *restrict *const restrict failure);
extern inline void
fts_open_handle(FTS *restrict *const restrict tree,
		char *const *path_argv,
		const int options,
		int (*compare)(const FTSENT **,
			       const FTSENT **),
		Handler *const handle,
		void *arg);
extern inline void
fts_open_handle_cl(FTS *restrict *const restrict tree,
		   char *const *path_argv,
		   const int options,
		   int (*compare)(const FTSENT **,
				  const FTSENT **),
		   const struct HandlerClosure *const restrict fail_cl);

/* close FTS */
extern inline bool
fts_close_status(FTS *const restrict tree);

extern inline void
fts_close_muffle(FTS *const restrict tree);
extern inline bool
fts_close_report(FTS *const restrict tree,
		 const char *restrict *const restrict failure);
extern inline void
fts_close_handle(FTS *const restrict tree,
		 Handler *const handle,
		 void *arg);
extern inline void
fts_close_handle_cl(FTS *const restrict tree,
		    const struct HandlerClosure *const restrict fail_cl);

/* read next entry in FTS */
extern inline bool
fts_read_status(FTSENT *restrict *const restrict entry,
		FTS *const restrict tree);
extern inline void
fts_read_muffle(FTSENT *restrict *const restrict entry,
		FTS *const restrict tree);
extern inline bool
fts_read_report(FTSENT *restrict *const restrict entry,
		FTS *const restrict tree,
		const char *restrict *const restrict failure);
extern inline void
fts_read_handle(FTSENT *restrict *const restrict entry,
		FTS *const restrict tree,
		Handler *const handle,
		void *arg);
extern inline void
fts_read_handle_cl(FTSENT *restrict *const restrict entry,
		   FTS *const restrict tree,
		   const struct HandlerClosure *const restrict fail_cl);

/* set entry in FTS */
extern inline bool
fts_set_status(FTS *const restrict tree,
	       FTSENT *const restrict entry,
	       const int options);
extern inline void
fts_set_muffle(FTS *const restrict tree,
	       FTSENT *const restrict entry,
	       const int options);
extern inline bool
fts_set_report(FTS *const restrict tree,
	       FTSENT *const restrict entry,
	       const int options,
	       const char *restrict *const restrict failure);
extern inline void
fts_set_handle(FTS *const restrict tree,
	       FTSENT *const restrict entry,
	       const int options,
	       Handler *const handle,
	       void *arg);
extern inline void
fts_set_handle_cl(FTS *const restrict tree,
		  FTSENT *const restrict entry,
		  const int options,
		  const struct HandlerClosure *const restrict fail_cl);

/* compare FTS entries by name */
extern inline int
ftsent_compare_names(const FTSENT **x,
		     const FTSENT **y);
#endif /* ifdef WIN32 */

/* inspect file permissions */
extern inline char *
put_file_permissions_string(char *restrict buffer,
			    const int mode);
extern inline void
file_permissions_string(char *restrict buffer,
			const int mode);
