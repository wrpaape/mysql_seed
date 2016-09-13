#include "system/stdio_utils.h"

/* global variables
 * ────────────────────────────────────────────────────────────────────────── */
#ifdef WIN32
HANDLE stdin_handle;
DWORD stdin_mode;
#else
extern struct termios stdin_attr;
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
#else
#endif	/* idef WIN32 */


void
catch_restore_tty(int signal_name)
{
#ifdef WIN32
	(void) SetConsoleMode(stdin_handle,
			      stdin_mode);
#else
	(void) tcsetattr(STDIN_FILENO,
			 TCSANOW,
			 &stdin_attr);

#endif	/* idef WIN32 */
}

extern inline bool
flush_input_overflow(const char *restrict *const restrict failure);

extern inline bool
read_input(char *const restrict buffer,
	   const size_t size_max,
	   const char *restrict *const restrict failure);
