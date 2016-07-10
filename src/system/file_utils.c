#include "system/file_utils.h"

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


/* inspect file permissions */
extern inline char *
put_file_permissions_string(char *restrict buffer,
			    const int mode);
extern inline void
file_permissions_string(char *restrict buffer,
			const int mode);
