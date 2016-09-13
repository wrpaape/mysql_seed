#include "system/stdio_utils.h"

/* global variables
 * ────────────────────────────────────────────────────────────────────────── */
#ifdef WIN32
HANDLE stdin_handle;
DWORD stdin_mode;
#else
struct termios stdin_attr;
#endif	/* idef WIN32 */


/* tty wrapper functions
 * ────────────────────────────────────────────────────────────────────────── */
#ifdef WIN32
/* get stdio file handle */
extern inline bool
get_std_handle_status(HANDLE *const restrict handle,
		      const DWORD std_device);
extern inline void
get_std_handle_muffle(HANDLE *const restrict handle,
		      const DWORD std_device);
extern inline bool
get_std_handle_report(HANDLE *const restrict handle,
		      const DWORD std_device,
		      const char *restrict *const restrict failure);
extern inline void
get_std_handle_handle(HANDLE *const restrict handle,
		      const DWORD std_device,
		      Handler *const handle,
		      void *arg);
extern inline void
get_std_handle_handle_cl(HANDLE *const restrict handle,
			 const DWORD std_device,
			 const struct HandlerClosure *const restrict fail_cl);

/* get stdio mode */
extern inline bool
get_console_mode_status(const HANDLE console,
			DWORD *const restrict mode);
extern inline void
get_console_mode_muffle(const HANDLE console,
			DWORD *const restrict mode);
extern inline bool
get_console_mode_report(const HANDLE console,
			DWORD *const restrict mode,
			const char *restrict *const restrict failure);
extern inline bool
get_console_mode_handle(const HANDLE console,
			DWORD *const restrict mode,
			Handler *const handle,
			void *arg);
extern inline bool
get_console_mode_handle_cl(const HANDLE console,
			   DWORD *const restrict mode,
			   const struct HandlerClosure *const restrict fail_cl);

/* set stdio mode */
extern inline bool
set_console_mode_status(const HANDLE console,
			const DWORD mode);
extern inline void
set_console_mode_muffle(const HANDLE console,
			const DWORD mode);
extern inline bool
set_console_mode_report(const HANDLE console,
			const DWORD mode,
			const char *restrict *const restrict failure);
extern inline bool
set_console_mode_handle(const HANDLE console,
			const DWORD mode,
			Handler *const handle,
			void *arg);
extern inline bool
set_console_mode_handle_cl(const HANDLE console,
			   const DWORD mode,
			   const struct HandlerClosure *const restrict fail_cl);
#else
/* get stdio attribute */
extern inline bool
tcgetattr_status(const int file_descriptor,
		 struct termios *const restrict attribute);
extern inline void
tcgetattr_muffle(const int file_descriptor,
		 struct termios *const restrict attribute);
extern inline bool
tcgetattr_report(const int file_descriptor,
		 struct termios *const restrict attribute,
		 const char *restrict *const restrict failure);
extern inline void
tcgetattr_handle(const int file_descriptor,
		 struct termios *const restrict attribute,
		 Handler *const handle,
		 void *arg);
extern inline void
tcgetattr_handle_cl(const int file_descriptor,
		    struct termios *const restrict attribute,
		    const struct HandlerClosure *const restrict fail_cl);

/* set stdio attribute */
extern inline bool
tcsetattr_status(const int file_descriptor,
		 const int actions,
		 const struct termios *const restrict attribute);
extern inline void
tcsetattr_muffle(const int file_descriptor,
		 const int actions,
		 const struct termios *const restrict attribute);
extern inline bool
tcsetattr_report(const int file_descriptor,
		 const int actions,
		 const struct termios *const restrict attribute,
		 const char *restrict *const restrict failure);
extern inline void
tcsetattr_handle(const int file_descriptor,
		 const int actions,
		 const struct termios *const restrict attribute,
		 Handler *const handle,
		 void *arg);
extern inline void
tcsetattr_handle_cl(const int file_descriptor,
		    const int actions,
		    const struct termios *const restrict attribute,
		    const struct HandlerClosure *const restrict fail_cl);
#endif	/* idef WIN32 */


/* restore stdin to original state */
void
catch_restore_stdin(int signal_name)
{
#ifdef WIN32
	set_console_mode_muffle(stdin_handle,
				stdin_mode);
#else
	tcsetattr_muffle(STDIN_FILENO,
			 TCSANOW,
			 &stdin_attr);
#endif	/* idef WIN32 */
}

extern inline bool
restore_stdin(const char *restrict *const restrict failure);


extern inline bool
flush_input_overflow(const char *restrict *const restrict failure);

extern inline bool
read_input(char *const restrict buffer,
	   const size_t size_max,
	   const char *restrict *const restrict failure);
