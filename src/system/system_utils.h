#ifndef MYSQL_SEED_SYSTEM_UTILS_H_
#define MYSQL_SEED_SYSTEM_UTILS_H_


/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <sys/ioctl.h>			/* iotcl */
#include <sys/uio.h>			/* read, write */
#include <sys/types.h>			/* ssize_t, chmod API */
#include <sys/stat.h>			/* mkdir */
#include <sys/param.h>			/* MAXPATHLEN */
#include "utils/fail_switch_open.h"	/* stdbool, errno, FAIL_SWITCH */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* included from <sys/ioctl.h>
 *
 * struct winsize {
 *	unsigned short ws_row;		rows, in characters
 *	unsigned short ws_col;		columns, in characters
 *	unsigned short ws_xpixel;	horizontal size, pixels
 *	unsigned short ws_ypixel;	vertical size, pixels
 * }; */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define get_winsize_imp(WINDOW, FILEDES)				\
ioctl(FILEDES, TIOCGWINSZ, WINDOW)

/* ioctl */
#define HANDLE_IOCTL(FILEDES, REQUEST, ...)				\
do {									\
	const int status = ioctl(FILEDES, REQUEST, ##__VA_ARGS__);	\
	if (status == -1)						\
		EXIT_ON_FAILURE("failed device request"			\
				"\e24m]\n\n{\n"				\
				"\tfildes:  '" #FILEDES ",'\n"		\
				"\trequest: '" #REQUEST "'\n"		\
				"}\n\n"					\
				"reason: %s",				\
				IOCTL_FAILURE(errno));			\
} while (0)
#define IOCTL_FAILURE(ERRNO)						\
  ((ERRNO == EBADF)							\
? "'fildes', is not a valid descriptor"					\
: ((ERRNO == EINVAL)							\
? "'request' or 'argp' is not valid."					\
: ((ERRNO == ENOTTY)							\
? "(one of the following)\n"						\
  "\t- 'fildes' is not associated with a character special device.\n"	\
  "\t- The specified request does not apply to the kind of object that"	\
   " the descriptor 'fildes' references."				\
: "unknown")))

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define FAIL_SWITCH_ROUTINE		get_winsize_imp
#define FAIL_SWITCH_ERRNO_FAILURE	-1
#define FAIL_SWITCH_FAILURE_POINTER	failure

inline bool
get_winsize_report(struct winsize *const restrict window,
		   const int filedes,
		   const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(window,
			       filedes)

	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'fildes', is not a valid descriptor.")

	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "'request' or 'argp' is not valid.")

	FAIL_SWITCH_ERRNO_CASE_2(ENOTTY,
				 "'fildes' is not associated with a character "
				 "special device.",
				 "The specified request does not apply to the "
				 "kind of object that the descriptor 'fildes' "
				 "references.")

	FAIL_SWITCH_ERRNO_CLOSE()

	/* if (get_winsize_imp(window, */
	/* 		    fildes) != -1) */
	/* 	return true; */

	/* switch (errno) { */
	/* case: EBADF */
	/* 	*failure = "get_winsize failure'fildes', is not a valid descriptor.\n"; */
	/* 	return false; */

	/* case: EINVAL */
	/* 	*failure = "'request' or 'argp' is not valid.\n"; */
	/* 	return false; */

	/* case: ENOTTY */
	/* 	*failure = "(one of the following)\n" */
	/* 		   "\t- 'fildes' is not associated with a character " */
	/* 			"special device.\n"; */
	/* 		   "\t- The specified request does not apply to the " */
	/* 			"kind of object that the descriptor 'fildes' " */
	/* 			"references.\n"; */
	/* default: */
	/* 	*failure = "unknown"; */
	/* 	return false; */
	/* } */
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS */


#endif /* ifndef MYSQL_SEED_SYSTEM_UTILS_H_ */
