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

/* same for all file system calls called below */
#define FAIL_SWITCH_ERRNO_FAILURE	-1
#define FAIL_SWITCH_FAILURE_POINTER	failure

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


/* set stdio mode */
inline bool
set_console_mode_status(const HANDLE console,
			const DWORD mode)
{
	return (bool) SetConsoleMode(console,
				     mode);
}

inline void
set_console_mode_muffle(const HANDLE console,
			const DWORD mode)
{
	(void) SetConsoleMode(console,
			      mode);
}

inline bool
set_console_mode_report(const HANDLE console,
			const DWORD mode,
			const char *restrict *const restrict failure)
{
	const bool success = (bool) SetConsoleMode(console,
						   mode);

	if (UNLIKELY(!success))
		*failure = FAILURE_REASON("SetConsoleMode",
					  "unknown");

	return success;
}

inline bool
set_console_mode_handle(const HANDLE console,
			const DWORD mode,
			Handler *const handle,
			void *arg)
{
	const char *restrict failure;

	if (LIKELY(set_console_mode_report(console,
					   mode,
					   &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline bool
set_console_mode_handle_cl(const HANDLE console,
			   const DWORD mode,
			   const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(set_console_mode_report(console,
					   mode,
					   &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}

#else

/* get stdio attribute */
inline bool
tcgetattr_status(const int file_descriptor,
		 struct termios *const restrict attribute)
{
	return tcgetattr(file_descriptor,
			 attribute) != -1;
}

inline void
tcgetattr_muffle(const int file_descriptor,
		 struct termios *const restrict attribute)
{
	(void) tcgetattr(file_descriptor,
			 attribute);
}

#undef	FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE tcgetattr
inline bool
tcgetattr_report(const int file_descriptor,
		 struct termios *const restrict attribute,
		 const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(file_descriptor,
			       attribute)
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'file_descriptor' is not a valid file "
				 "descriptor.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTTY,
				 "The file associated with 'file_descriptor' is"
				 " not a terminal.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
tcgetattr_handle(const int file_descriptor,
		 struct termios *const restrict attribute,
		 Handler *const handle,
		 void *arg)
{
	const char *restrict failure;

	if (LIKELY(tcgetattr_report(file_descriptor,
				    attribute,
				    &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
tcgetattr_handle_cl(const int file_descriptor,
		    struct termios *const restrict attribute,
		    const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(tcgetattr_report(file_descriptor,
				    attribute,
				    &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}


/* set stdio attribute */
inline bool
tcsetattr_status(const int file_descriptor,
		 const int actions,
		 const struct termios *const restrict attribute)
{
	return tcsetattr(file_descriptor,
			 actions,
			 attribute) != -1;
}

inline void
tcsetattr_muffle(const int file_descriptor,
		 const int actions,
		 const struct termios *const restrict attribute)
{
	(void) tcsetattr(file_descriptor,
			 actions,
			 attribute);
}

#undef	FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE tcsetattr
inline bool
tcsetattr_report(const int file_descriptor,
		 const int actions,
		 const struct termios *const restrict attribute,
		 const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(file_descriptor,
			       actions,
			       attribute)
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'file_descriptor' is not a valid file "
				 "descriptor.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "interrupted by a signal")
	FAIL_SWITCH_ERRNO_CASE_2(EINVAL,
				 "'actions' is not valid.",
				 "An attempt was made to change an attribute "
				 "represented in the termios structure to an "
				 "unsupported value.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTTY,
				 "The file associated with 'file_descriptor' is"
				 " not a terminal.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
tcsetattr_handle(const int file_descriptor,
		 const int actions,
		 const struct termios *const restrict attribute,
		 Handler *const handle,
		 void *arg)
{
	const char *restrict failure;

	if (LIKELY(tcsetattr_report(file_descriptor,
				    actions,
				    attribute,
				    &failure)))
		return;


	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
tcsetattr_handle_cl(const int file_descriptor,
		    const int actions,
		    const struct termios *const restrict attribute,
		    const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(tcsetattr_report(file_descriptor,
				    actions,
				    attribute,
				    &failure)))
		return;


	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}

#endif	/* idef WIN32 */



/* restore stdin to original state */
void
catch_restore_stdin(int signal_name);

inline bool
restore_stdin(const char *restrict *const restrict failure)
{
#ifdef WIN32
	return set_console_mode_report(stdin_handle,
				       stdin_mode,
				       failure);
#else
	return tcsetattr_report(STDIN_FILENO,
				TCSANOW,
				&stdin_attr,
				failure);
#endif	/* idef WIN32 */

}




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

/* clear FAIL_SWITCH constant macros */
#undef FAIL_SWITCH_ROUTINE
#undef FAIL_SWITCH_ERRNO_FAILURE
#undef FAIL_SWITCH_FAILURE_POINTER

#endif /* ifndef MYSQL_SEED_SYSTEM_STDIO_UTILS_H_ */
