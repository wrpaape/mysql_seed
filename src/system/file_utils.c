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
/* open */
inline bool
open_absolute_status(const char *const absolute_path,
		     const int open_flag)
inline void
open_absolute_muffle(const char *const absolute_path,
		     const int open_flag)

/* inspect file permissions */
extern inline char *
put_file_permissions_string(char *restrict buffer,
			    const int mode);
extern inline void
file_permissions_string(char *restrict buffer,
			const int mode);
