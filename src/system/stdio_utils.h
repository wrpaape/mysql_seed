#ifndef MYSQL_SEED_SYSTEM_STDIO_UTILS_H_
#define MYSQL_SEED_SYSTEM_STDIO_UTILS_H_

#ifdef __cplusplus /* ensure C linkage */
extern "C" {
#	ifndef restrict /* use c++ compatible '__restrict__' */
#		define restrict __restrict__
#	endif
#	ifndef NULL_POINTER /* use c++ null pointer macro */
#		define NULL_POINTER nullptr
#	endif
#else
#	ifndef NULL_POINTER /* use traditional c null pointer macro */
#		define NULL_POINTER NULL
#	endif
#endif


/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "system/system_utils.h" /* get_winsize, EXIT_ON_FAILURE */
#include "system/file_utils.h"	 /* stream handlers, STDOUT/IN/ERR_FILENO */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* included from system_utils.h (<sys/ioctl.h>)
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

/* popen */
#define HANDLE_POPEN(STREAM, COMMAND, MODE)				\
do {									\
	STREAM = popen(COMMAND, MODE);					\
	if (STREAM == NULL_POINTER)					\
		EXIT_ON_FAILURE("failed open process"			\
				"\e24m]\n\n{\n"				\
				"\tcommand: '" #COMMAND "' (%s),\n"	\
				"\tmode:    '" #MODE    "' (%s)\n"	\
				"}\n\n"					\
				"reason: " POPEN_FAILURE,		\
				COMMAND,				\
				MODE);					\
} while (0)
#define POPEN_FAILURE							\
"(one of the following)\n"						\
"\t- fork(2) failure"							\
"\t- pipe(2) failure\n"							\
"\t- failed to allocate sufficient memory"


/* pclose */
#define HANDLE_PCLOSE(STREAM)						\
do {									\
	if (pclose(STREAM) == -1)					\
		EXIT_ON_FAILURE("failed close process"			\
				"\e24m]\n\n{\n"				\
				"\tstream: '" #STREAM " (%p) '\n"	\
				"}\n\n"					\
				"reason: " PCLOSE_FAILURE,		\
				STREAM);				\
} while (0)
#define PCLOSE_FAILURE							\
"(one of the following)\n"						\
"\t- 'stream' is not associated with a \"popened\" command"		\
"\t- 'stream' is already \"pclosed\"\n"					\
"\t- wait4(2) returned an error"

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline size_t shell_command_read(char *restrict buffer,
				 const size_t size,
				 const char *const restrict command)
{
	FILE *process;
	size_t nread;

	HANDLE_POPEN(process, command, "r");
	HANDLE_FREAD(nread, buffer, sizeof(char), size, process);
	HANDLE_PCLOSE(process);

	return nread;
}

inline void shell_command_gets(char *restrict buffer,
			       const size_t size,
			       const char *const restrict command)
{
	FILE *process;

	HANDLE_POPEN(process, command, "r");
	HANDLE_FGETS(buffer, size, process);
	HANDLE_PCLOSE(process);
}

inline void get_stdio_winsize(struct winsize *const restrict window)
{
	get_winsize(window, STDOUT_FILENO);
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS */


#ifdef __cplusplus /* close 'extern "C" {' */
}
#endif

#endif /* ifndef MYSQL_SEED_SYSTEM_STDIO_UTILS_H_ */
