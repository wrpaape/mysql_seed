#ifndef MYSQL_SEED_SYSTEM_STDIO_UTILS_H_
#define MYSQL_SEED_SYSTEM_STDIO_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#ifndef WIN32
#	include <termios.h>	/* termios */
#endif	/* indef WIN32 */

#include "system/file_utils.h"	/* unistd */


/* global variables
 * ────────────────────────────────────────────────────────────────────────── */
#ifdef WIN32
extern HANDLE stdin_handle;
extern DWORD stdin_mode;
#else
extern struct termios stdin_attr;
#endif	/* idef WIN32 */


/* tty wrapper functions
 * ────────────────────────────────────────────────────────────────────────── */
#ifdef WIN32
/* get stdio file handle */
inline bool
get_std_handle_status(HANDLE *const restrict handle,
		      const DWORD std_device)
{
	*handle = GetStdHandle(std_device);

	return *handle != INVALID_HANDLE_VALUE;
}

inline void
get_std_handle_muffle(HANDLE *const restrict handle,
		      const DWORD std_device)
{
	*handle = GetStdHandle(std_device);
}

inline bool
get_std_handle_report(HANDLE *const restrict handle,
		      const DWORD std_device,
		      const char *restrict *const restrict failure)
{
	*handle = GetStdHandle(std_device);

	const bool success = (*handle != INVALID_HANDLE_VALUE);

	if (UNLIKELY(!success))
		*failure = FAILURE_REASON("GetStdHandle",
					  "unknown");

	return success;
}

inline void
get_std_handle_handle(HANDLE *const restrict handle,
		      const DWORD std_device,
		      Handler *const handle,
		      void *arg)
{
	const char *restrict failure;

	if (LIKELY(get_std_handle_report(handle,
					 std_device,
					 &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
get_std_handle_handle_cl(HANDLE *const restrict handle,
			 const DWORD std_device,
			 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(get_std_handle_report(handle,
					 std_device,
					 &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}


/* get stdio mode */
inline bool
get_console_mode_status(const HANDLE console,
			DWORD *const restrict mode)
{
	return (bool) GetConsoleMode(console,
				     mode);
}

inline void
get_console_mode_muffle(const HANDLE console,
			DWORD *const restrict mode)
{
	(void) GetConsoleMode(console,
			      mode);
}

inline bool
get_console_mode_report(const HANDLE console,
			DWORD *const restrict mode,
			const char *restrict *const restrict failure)
{
	const bool success = (bool) GetConsoleMode(console,
						   mode);

	if (UNLIKELY(!success))
		*failure = FAILURE_REASON("GetConsoleMode",
					  "unknown");

	return success;
}

inline bool
get_console_mode_handle(const HANDLE console,
			DWORD *const restrict mode,
			Handler *const handle,
			void *arg)
{
	const char *restrict failure;

	if (LIKELY(get_console_mode_report(console,
					   mode,
					   &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline bool
get_console_mode_handle_cl(const HANDLE console,
			   DWORD *const restrict mode,
			   const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(get_console_mode_report(console,
					   mode,
					   &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}



#else
#endif	/* idef WIN32 */



void
catch_restore_tty(int signal_name);


inline bool
flush_input_overflow(const char *restrict *const restrict failure)
{
	char overflow[256];
	size_t size_read;

	char *const restrict last = overflow + 255;

	while (1) {
		if (UNLIKELY(!read_size_report(&size_read,
					       STDIN_FILENO,
					       &overflow[0],
					       sizeof(overflow),
					       failure)))
			return false;

		if (   (size_read < sizeof(overflow))
		    || (*last == NL_CHAR))
			return true;
	}
}


/* read newline-terminated input from STDIN (size_max > 0)
 * and replace \n with \0 */
inline bool
read_input(char *const restrict buffer,
	   const size_t size_max,
	   const char *restrict *const restrict failure)
{
	size_t size_read;
	bool success;

	success = read_size_report(&size_read,
				   STDIN_FILENO,
				   buffer,
				   size_max,
				   failure);

	if (LIKELY(success)) {
		if (LIKELY(size_read > 0lu)) {
			char *const restrict last = buffer + size_read - 1l;

			if (   (size_read == size_max)
			    && (*last != NL_CHAR))
				success = flush_input_overflow(failure);

			*last = '\0';
		} else {
			*buffer = '\0';
		}
	}

	return success;
}


#endif /* ifndef MYSQL_SEED_SYSTEM_STDIO_UTILS_H_ */
