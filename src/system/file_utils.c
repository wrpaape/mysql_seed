#include "system/file_utils.h"

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

/* open (absolute path, no mode) */
extern inline bool
open_absolute_status(const char *const absolute_path,
		     const int open_flag);
extern inline void
open_absolute_muffle(const char *const absolute_path,
		     const int open_flag);
extern inline bool
open_absolute_report(const char *const absolute_path,
		     const int open_flag,
		     const char *restrict *const restrict failure);
extern inline void
open_absolute_handle(const char *const absolute_path,
		     const int open_flag,
		     Handler *const handle,
		     void *arg);
extern inline void
open_absolute_handle_cl(const char *const absolute_path,
			const int open_flag,
			const struct HandlerClosure *const restrict fail_cl);

/* open (absolute path, provide mode) */
extern inline bool
open_absolute_mode_status(const char *const absolute_path,
			  const int open_flag,
			  const mode_t mode);
extern inline void
open_absolute_mode_muffle(const char *const absolute_mode_path,
			  const int open_flag,
			  const mode_t mode);
extern inline bool
open_absolute_mode_report(const char *const absolute_mode_path,
			  const int open_flag,
			  const mode_t mode,
			  const char *restrict *const restrict failure);
extern inline void
open_absolute_mode_handle(const char *const absolute_mode_path,
			  const int open_flag,
			  const mode_t mode,
			  Handler *const handle,
			  void *arg);
extern inline void
open_absolute_mode_handle_cl(const char *const absolute_path,
			     const int open_flag,
			     const mode_t mode,
			     const struct HandlerClosure *const restrict fail_cl);

#ifndef WIN32
/* open (relative path, no mode) */
extern inline bool
open_relative_status(const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag);
extern inline void
open_relative_muffle(const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag);
extern inline bool
open_relative_report(const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag,
		     const char *restrict *const restrict failure);
extern inline void
open_relative_handle(const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag,
		     Handler *const handle,
		     void *arg);
extern inline void
open_relative_handle_cl(const int directory_descriptor,
			const char *const relative_path,
			const int open_flag,
			const struct HandlerClosure *const restrict fail_cl);

/* open (const int directory_descriptor,
	relative path, provide mode) */
extern inline bool
open_relative_mode_status(const int directory_descriptor,
			  const char *const relative_path,
			  const int open_flag,
			  const mode_t mode);
extern inline void
open_relative_mode_muffle(const int directory_descriptor,
			  const char *const relative_mode_path,
			  const int open_flag,
			  const mode_t mode);
extern inline bool
open_relative_mode_report(const int directory_descriptor,
			  const char *const relative_mode_path,
			  const int open_flag,
			  const mode_t mode,
			  const char *restrict *const restrict failure);
extern inline void
open_relative_mode_handle(const int directory_descriptor,
			  const char *const relative_mode_path,
			  const int open_flag,
			  const mode_t mode,
			  Handler *const handle,
			  void *arg);
extern inline void
open_relative_mode_handle_cl(const int directory_descriptor,
			     const char *const relative_path,
			     const int open_flag,
			     const mode_t mode,
			     const struct HandlerClosure *const restrict fail_cl);
#endif /* ifndef WIN32 */

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

/* mkdir (absolute path) */
extern inline bool
mkdir_absolute_status(const char *const restrict absolute_path,
		      const mode_t mode);
extern inline void
mkdir_absolute_muffle(const char *const restrict absolute_path,
		      const mode_t mode);
extern inline bool
mkdir_absolute_report(const char *const restrict absolute_path,
		      const mode_t mode,
		      const char *restrict *const restrict failure);
extern inline void
mkdir_absolute_handle(const char *const restrict absolute_path,
		      const mode_t mode,
		      Handler *const handle,
		      void *arg);
extern inline void
mkdir_absolute_handle_cl(const char *const restrict absolute_path,
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

/* inspect file permissions */
extern inline char *
put_file_permissions_string(char *restrict buffer,
			    const int mode);
extern inline void
file_permissions_string(char *restrict buffer,
			const int mode);
