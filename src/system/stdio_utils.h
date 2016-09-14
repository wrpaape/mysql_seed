#ifndef MYSQL_SEED_SYSTEM_STDIO_UTILS_H_
#define MYSQL_SEED_SYSTEM_STDIO_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#ifndef WIN32
#	include <termios.h>	/* termios */
#endif	/* indef WIN32 */

#include "system/file_utils.h"	/* file/signal utils, unistd */


/* global variables
 * ────────────────────────────────────────────────────────────────────────── */
extern sig_t sigint_handler;
#ifdef WIN32
extern HANDLE stdin_handle;
extern DWORD stdin_mode;
#else
extern struct termios stdin_attr;
extern tcflag_t stdin_lflag;
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


/* set global variables for stdin operations */
inline bool
stdin_constructor(const char *restrict *const restrict failure)
{
#ifdef WIN32
	return LIKELY(get_std_handle_report(&stdin_handle,
					    STD_INPUT_HANDLE,
					    failure))
	    && get_console_mode_report(stdin_handle,
				       &stdin_mode,
				       failure);
#else
	const bool success = tcgetattr_report(STDIN_FILENO,
					      &stdin_attr,
					      failure);

	stdin_lflag = stdin_attr.c_lflag;

	return success;
#endif	/* idef WIN32 */
}



/* restore stdin to original state immediately */
void
catch_stdin_restore(int signal_name);

inline void
stdin_restore_muffle(void)
{
#ifdef WIN32
	set_console_mode_muffle(stdin_handle,
				stdin_mode);
#else
	stdin_attr.c_lflag = stdin_lflag;

	tcsetattr_muffle(STDIN_FILENO,
			 TCSANOW,
			 &stdin_attr);
#endif	/* idef WIN32 */
}

inline bool
stdin_restore_report(const char *restrict *const restrict failure)
{
#ifdef WIN32
	return set_console_mode_report(stdin_handle,
				       stdin_mode,
				       failure);
#else
	stdin_attr.c_lflag = stdin_lflag;

	return tcsetattr_report(STDIN_FILENO,
				TCSANOW,
				&stdin_attr,
				failure);
#endif	/* idef WIN32 */
}

/* flush stdin before restoring to original state */
inline void
stdin_flush_restore_muffle(void)
{
#ifdef WIN32
/* read stdin until EOF */
	char overflow[256];
	size_t size_read;

	char *const restrict last = overflow + 255;

	do {
		read_size_muffle(&size_read,
				 STDIN_FILENO,
				 &overflow[0],
				 sizeof(overflow));
	} while (   (size_read == sizeof(overflow))
		 && (*last != NL_CHAR));

	set_console_mode_muffle(stdin_handle,
				stdin_mode);
#else
	stdin_attr.c_lflag = stdin_lflag;

	tcsetattr_muffle(STDIN_FILENO,
			 TCSAFLUSH,
			 &stdin_attr);
#endif	/* idef WIN32 */
}

inline bool
stdin_flush_restore_report(const char *restrict *const restrict failure)
{
#ifdef WIN32
/* read stdin until EOF */
	char overflow[256];
	size_t size_read;

	char *const restrict last = overflow + 255;

	while (1) {
		if (UNLIKELY(!read_size_report(&size_read,
					       STDIN_FILENO,
					       &overflow[0],
					       sizeof(overflow),
					       failure))) {
			set_console_mode_muffle(stdin_handle,
						stdin_mode);
			return false;
		}

		if (   (size_read < sizeof(overflow))
		    || (*last == NL_CHAR))
			return set_console_mode_report(stdin_handle,
						       stdin_mode,
						       failure);
	}
#else
	stdin_attr.c_lflag = stdin_lflag;

	return tcsetattr_report(STDIN_FILENO,
				TCSAFLUSH,
				&stdin_attr,
				failure);
#endif	/* idef WIN32 */
}


/* restore original stdin tty state on SIGINT */
inline bool
stdin_hide_try_catch_open_report(const char *restrict *const restrict failure)
{
	return signal_report(&sigint_handler,
			     SIGINT,
			     &catch_stdin_restore,
			     failure);
}

inline void
stdin_hide_try_catch_close_muffle(void)
{
	return signal_muffle(&sigint_handler,
			     SIGINT,
			     sigint_handler);
}

inline bool
stdin_hide_try_catch_close_report(const char *restrict *const restrict failure)
{
	return signal_report(&sigint_handler,
			     SIGINT,
			     sigint_handler,
			     failure);
}


/* turn off echo */
inline bool
stdin_hide_report(const char *restrict *const restrict failure)
{
#ifdef WIN32
	return set_console_mode_report(stdin_handle,
				       stdin_mode & ~ENABLE_ECHO,
				       failure);
#else
	stdin_attr.c_lflag &= ~ECHO;

	return tcsetattr_report(STDIN_FILENO,
				TCSANOW,
				&stdin_attr,
				failure);
#endif	/* idef WIN32 */
}


/* set up environment for reading password on stdin */
inline bool
read_password_open_report(const char *restrict *const restrict failure)
{
	bool success;

	/* set up global variables for tty adjustment */
	success = stdin_constructor(failure);

	if (LIKELY(success)) {
		/* ensure tty is restored in case of SIGINT */
		success = stdin_hide_try_catch_open_report(failure);

		if (LIKELY(success)) {
			/* hide input from echoing */
			success = stdin_hide_report(failure);

			if (UNLIKELY(!success))
				stdin_hide_try_catch_close_muffle();
		}
	}

	return success;
}


/* tear down environment set up by read_password_open_report (without flush) */
inline void
read_password_close_muffle(void)
{
	/* immediately restore tty to original state */
	stdin_restore_muffle();
	/* restore signal handler for SIGINT */
	stdin_hide_try_catch_close_muffle();
}

inline bool
read_password_close_report(const char *restrict *const restrict failure)
{
	bool success;

	/* immediately restore tty to original state */
	success = stdin_restore_report(failure);

	/* restore signal handler for SIGINT */
	if (LIKELY(success))
		success = stdin_hide_try_catch_close_report(failure);
	else
		stdin_hide_try_catch_close_muffle();

	return success;
}


/* tear down environment set up by read_password_open_report (with flush) */
inline void
read_password_flush_close_muffle(void)
{
	/* flush stdin overflow before restoring tty to original state */
	stdin_flush_restore_muffle();
	/* restore signal handler for SIGINT */
	stdin_hide_try_catch_close_muffle();
}

inline bool
read_password_flush_close_report(const char *restrict *const restrict failure)
{
	bool success;

	/* flush stdin overflow before restoring tty to original state */
	success = stdin_flush_restore_report(failure);

	/* restore signal handler for SIGINT */
	if (LIKELY(success))
		success = stdin_hide_try_catch_close_report(failure);
	else
		stdin_hide_try_catch_close_muffle();

	return success;
}


/* read newline-terminated input from STDIN (size_max > 0)
 * and replace \n with \0 */
/* inline bool */
/* read_input(char *const restrict buffer, */
/* 	   const size_t size_max, */
/* 	   const char *restrict *const restrict failure) */
/* { */
/* 	return false; */
	/* size_t size_read; */
	/* bool success; */

	/* success = read_size_report(&size_read, */
	/* 			   STDIN_FILENO, */
	/* 			   buffer, */
	/* 			   size_max, */
	/* 			   failure); */

	/* if (LIKELY(success)) { */
	/* 	if (LIKELY(size_read > 0lu)) { */
	/* 		char *const restrict last = buffer + size_read - 1l; */

	/* 		/1* if (   (size_read == size_max) *1/ */
	/* 		/1*     && (*last != NL_CHAR)) *1/ */
	/* 		/1* 	success = flush_input_overflow(failure); *1/ */

	/* 		*last = '\0'; */
	/* 	} else { */
	/* 		*buffer = '\0'; */
	/* 	} */
	/* } */

	/* return success; */
/* } */


/* read password from newline-terminated stdin input → buffer (size_max > 0) */
inline bool
read_password(char *const restrict buffer,
	      const size_t size_max,
	      const char *restrict *const restrict failure)
{
	size_t size_read;
	bool success;

	success = read_password_open_report(failure);

	if (LIKELY(success)) {
		success = read_size_report(&size_read,
					   STDIN_FILENO,
					   buffer,
					   size_max,
					   failure);

		if (LIKELY(success)) {
			if (LIKELY(size_read > 0lu)) {
				char *const restrict last
				= buffer + size_read - 1l;

				/* if buffer is filled and the last character is
				 * not a newline, flush stdin before restoring
				 * tty state */
				success
				= (   (size_read == size_max)
				   && (*last != NL_CHAR))
				? read_password_flush_close_report(failure)
				: read_password_close_report(failure);

				/* terminate password */
				*last = '\0';
			} else {
				/* 0 bytes are read, restore w/out flushing */
				success = read_password_close_report(failure);

				/* terminate password */
				*buffer = '\0';
			}
		} else {
			read_password_close_muffle();
		}
	} else {
		read_password_close_muffle();
	}

	return success;
}


/* clear FAIL_SWITCH constant macros */
#undef FAIL_SWITCH_ROUTINE
#undef FAIL_SWITCH_ERRNO_FAILURE
#undef FAIL_SWITCH_FAILURE_POINTER

#endif /* ifndef MYSQL_SEED_SYSTEM_STDIO_UTILS_H_ */
