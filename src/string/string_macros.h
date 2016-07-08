#ifndef MYSQL_SEED_STRING_STRING_MACROS_H_
#define MYSQL_SEED_STRING_STRING_MACROS_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "string/string_token.h"	/* PUT_CHAR, ANSI escape sequences */


/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define STRINGIFY(X)	    #X
#define EXPAND_STRINGIFY(X) STRINGIFY(X)

/* system-dependent path-delimiter */
#ifdef WIN32
#	define PATH_DELIM '\\'
#	define PATH_DELIM_STRING "\\"
#else
#	define PATH_DELIM '/'
#	define PATH_DELIM_STRING "/"
#endif /* ifdef WIN32 */

#define PUT_PATH_DELIM(PTR) PUT_CHAR(PTR, PATH_DELIM)


/* ANSI escape macros
 *─────────────────────────────────────────────────────────────────────────── */
#define ANSI_WRAP(ANSI, STRING) ANSI_ ## ANSI  STRING ANSI_RESET
#define UNDERLINE_WRAP(STRING)  ANSI_UNDERLINE STRING ANSI_NO_UNDERLINE
#define BLINK_WRAP(STRING)	ANSI_BLINK     STRING ANSI_BLINK_OFF

#define LINE_INDENT(LINE)	"\t" LINE "\n"
#define LI_INDENT(LI)		LINE_INDENT("- " LI)

/* error macros
 *─────────────────────────────────────────────────────────────────────────── */
#define ERROR_OPEN		ANSI_BRIGHT ANSI_RED
#define ERROR_WRAP(STRING)	ERROR_OPEN STRING ANSI_RESET

#define ERROR_HEADER_OPEN(SOURCE, TYPE, ...)				\
"\n" ERROR_OPEN UNDERLINE_WRAP(SOURCE " " TYPE) __VA_ARGS__  "\n"

#define ERROR_HEADER_WRAP(SOURCE, TYPE, STRING)				\
	ERROR_HEADER_OPEN(SOURCE, TYPE, STRING ANSI_RESET)

#define ERROR_HEADER_REASON(SOURCE, TYPE, ...)				\
	ERROR_HEADER_OPEN(SOURCE, TYPE, " - reason" __VA_ARGS__ ":")

/* list headers */
#define ERROR_HEADER_REASONS(SOURCE, TYPE)				\
	ERROR_HEADER_REASON(SOURCE, TYPE, "s")
#define ERROR_HEADER_REASONS_QOTF(SOURCE, TYPE, QUANTITY, ...)		\
	ERROR_HEADER_REASON(SOURCE, TYPE,				\
			    __VA_ARGS__ " (" QUANTITY " of the following)")
#define ERROR_HEADER_REASONS_1OTF(SOURCE, TYPE) /* one */		\
	ERROR_HEADER_REASONS_QOTF(SOURCE, TYPE, "one")
#define ERROR_HEADER_REASONS_SOTF(SOURCE, TYPE) /* some */		\
	ERROR_HEADER_REASONS_QOTF(SOURCE, TYPE, "some", "s")
#define ERROR_HEADER_REASONS_AOTF(SOURCE, TYPE) /* all */		\
	ERROR_HEADER_REASONS_QOTF(SOURCE, TYPE, "all",  "s")



/* full message
 *─────────────────────────────────────────────────────────────────────────── */
/* one reason */
#define ERROR_REASON(SOURCE, TYPE, REASON)				\
		ERROR_HEADER_REASON(SOURCE, TYPE)			\
		LINE_INDENT(REASON) ANSI_RESET "\n"

#define ERROR_REASONS_1(SOURCE, TYPE, R1) ERROR_REASON(SOURCE, TYPE, R1)

/* multiple reasons */
#define _ERR_RSNS_MSG(EHR_SFX, SOURCE, TYPE, REASONS, ...)		\
	ERROR_HEADER_REASONS_ ## EHR_SFX (SOURCE, TYPE, ##__VA_ARGS__)	\
	REASONS ANSI_RESET "\n"

/* two reasons */
#define ERROR_REASONS_2_1OTF(SOURCE, TYPE, R1, R2)			\
	_ERR_RSNS_MSG(1OTF, SOURCE, TYPE,				\
		      LI_INDENT(R1)					\
		      LI_INDENT(R2))

#define ERROR_REASONS_2(SOURCE, TYPE, R1, R2)				\
	ERROR_REASONS_2_1OTF(SOURCE, TYPE, R1, R2)

#define ERROR_REASONS_2_SOTF(SOURCE, TYPE, R1, R2)			\
	_ERR_RSNS_MSG(SOTF, SOURCE, TYPE,				\
		      LI_INDENT(R1)					\
		      LI_INDENT(R2))

#define ERROR_REASONS_2_AOTF(SOURCE, TYPE, R1, R2)			\
	_ERR_RSNS_MSG(AOTF, SOURCE, TYPE,				\
		      LI_INDENT(R1)					\
		      LI_INDENT(R2))

/* three reasons */
#define ERROR_REASONS_3_1OTF(SOURCE, TYPE, R1, R2, R3)			\
	_ERR_RSNS_MSG(1OTF, SOURCE, TYPE,				\
		      LI_INDENT(R1)					\
		      LI_INDENT(R2)					\
		      LI_INDENT(R3))

#define ERROR_REASONS_3(SOURCE, TYPE, R1, R2, R3)			\
	ERROR_REASONS_3_1OTF(SOURCE, TYPE, R1, R2, R3)

#define ERROR_REASONS_3_SOTF(SOURCE, TYPE, R1, R2, R3)			\
	_ERR_RSNS_MSG(SOTF, SOURCE, TYPE,				\
		      LI_INDENT(R1)					\
		      LI_INDENT(R2)					\
		      LI_INDENT(R3))

#define ERROR_REASONS_3_AOTF(SOURCE, TYPE, R1, R2, R3)			\
	_ERR_RSNS_MSG(AOTF, SOURCE, TYPE,				\
		      LI_INDENT(R1)					\
		      LI_INDENT(R2)					\
		      LI_INDENT(R3))

/* four reasons */
#define ERROR_REASONS_4_1OTF(SOURCE, TYPE, R1, R2, R3, R4)		\
	_ERR_RSNS_MSG(1OTF, SOURCE, TYPE,				\
		      LI_INDENT(R1)					\
		      LI_INDENT(R2)					\
		      LI_INDENT(R3)					\
		      LI_INDENT(R4))

#define ERROR_REASONS_4(SOURCE, TYPE, R1, R2, R3, R4)			\
	ERROR_REASONS_4_1OTF(SOURCE, TYPE, R1, R2, R3, R4)

#define ERROR_REASONS_4_SOTF(SOURCE, TYPE, R1, R2, R3, R4)		\
	_ERR_RSNS_MSG(SOTF, SOURCE, TYPE,				\
		      LI_INDENT(R1)					\
		      LI_INDENT(R2)					\
		      LI_INDENT(R3)					\
		      LI_INDENT(R4))

#define ERROR_REASONS_4_AOTF(SOURCE, TYPE, R1, R2, R3, R4)		\
	_ERR_RSNS_MSG(AOTF, SOURCE, TYPE,				\
		      LI_INDENT(R1)					\
		      LI_INDENT(R2)					\
		      LI_INDENT(R3)					\
		      LI_INDENT(R4))


/* exception
 *─────────────────────────────────────────────────────────────────────────── */
#define EXCEPTION_HEADER_OPEN(SOURCE, ...)				\
	ERROR_HEADER_OPEN(SOURCE, "exception", ##__VA_ARGS__)

#define EXCEPTION_HEADER_WRAP(SOURCE, STRING)				\
	ERROR_HEADER_WRAP(SOURCE, "exception", STRING)

#define EXCEPTION_HEADER_REASON(SOURCE, ...)				\
	ERROR_HEADER_REASON(SOURCE, "exception", ##__VA_ARGS__ )

/* list headers */
#define EXCEPTION_HEADER_REASONS(SOURCE)				\
	ERROR_HEADER_REASONS(SOURCE, "exception")
#define EXCEPTION_HEADER_REASONS_QOTF(SOURCE, QUANTITY, ...)		\
	ERROR_HEADER_REASONS_QOTF(SOURCE, "exception", QUANTITY, ##__VA_ARGS__)

#define EXCEPTION_HEADER_REASONS_1OTF(SOURCE) /* one */			\
	EXCEPTION_HEADER_REASONS_QOTF(SOURCE, "one")
#define EXCEPTION_HEADER_REASONS_SOTF(SOURCE) /* some */		\
	EXCEPTION_HEADER_REASONS_QOTF(SOURCE, "some", "s")
#define EXCEPTION_HEADER_REASONS_AOTF(SOURCE) /* all */			\
	EXCEPTION_HEADER_REASONS_QOTF(SOURCE, "all",  "s")

/* full message
 *─────────────────────────────────────────────────────────────────────────── */
/* one reason */
#define EXCEPTION_REASON(SOURCE, REASON)				\
	ERROR_REASON(SOURCE, "exception", REASON)

#define EXCEPTION_REASONS_1(SOURCE, R1)					\
	EXCEPTION_REASON(SOURCE, R1)

/* two reasons */
#define EXCEPTION_REASONS_2_1OTF(SOURCE, R1, R2)			\
	ERROR_REASONS_2_1OTF(SOURCE, "exception", R1, R2)

#define EXCEPTION_REASONS_2(SOURCE, R1, R2)				\
	ERROR_REASONS_2_1OTF(SOURCE, "exception", R1, R2)

#define EXCEPTION_REASONS_2_SOTF(SOURCE, R1, R2)			\
	ERROR_REASONS_2_SOTF(SOURCE, "exception", R1, R2)

#define EXCEPTION_REASONS_2_AOTF(SOURCE, R1, R2)			\
	ERROR_REASONS_2_AOTF(SOURCE, "exception", R1, R2)

/* three reasons */
#define EXCEPTION_REASONS_3_1OTF(SOURCE, R1, R2, R3)			\
	ERROR_REASONS_3_1OTF(SOURCE, "exception", R1, R2, R3)

#define EXCEPTION_REASONS_3(SOURCE, R1, R2, R3)				\
	ERROR_REASONS_3_1OTF(SOURCE, "exception", R1, R2, R3)

#define EXCEPTION_REASONS_3_SOTF(SOURCE, R1, R2, R3)			\
	ERROR_REASONS_3_SOTF(SOURCE, "exception", R1, R2, R3)

#define EXCEPTION_REASONS_3_AOTF(SOURCE, R1, R2, R3)			\
	ERROR_REASONS_3_AOTF(SOURCE, "exception", R1, R2, R3)

/* four reasons */
#define EXCEPTION_REASONS_4_1OTF(SOURCE, R1, R2, R3, R4)		\
	ERROR_REASONS_4_1OTF(SOURCE, "exception", R1, R2, R3, R4)

#define EXCEPTION_REASONS_4(SOURCE, R1, R2, R3, R4)			\
	ERROR_REASONS_4_1OTF(SOURCE, "exception", R1, R2, R3, R4)

#define EXCEPTION_REASONS_4_SOTF(SOURCE, R1, R2, R3, R4)		\
	ERROR_REASONS_4_SOTF(SOURCE, "exception", R1, R2, R3, R4)

#define EXCEPTION_REASONS_4_AOTF(SOURCE, R1, R2, R3, R4)		\
	ERROR_REASONS_4_AOTF(SOURCE, "exception", R1, R2, R3, R4)

/* failure
 *─────────────────────────────────────────────────────────────────────────── */
#define FAILURE_HEADER_OPEN(SOURCE, ...)				\
	ERROR_HEADER_OPEN(SOURCE, "failure", ##__VA_ARGS__)

#define FAILURE_HEADER_WRAP(SOURCE, STRING)				\
	ERROR_HEADER_WRAP(SOURCE, "failure", STRING)

#define FAILURE_HEADER_REASON(SOURCE, ...)				\
	ERROR_HEADER_REASON(SOURCE, "failure", ##__VA_ARGS__ )

/* list headers */
#define FAILURE_HEADER_REASONS(SOURCE)					\
	ERROR_HEADER_REASONS(SOURCE, "failure")
#define FAILURE_HEADER_REASONS_QOTF(SOURCE, QUANTITY, ...)		\
	ERROR_HEADER_REASONS_QOTF(SOURCE, "failure", QUANTITY, ##__VA_ARGS__)

#define FAILURE_HEADER_REASONS_1OTF(SOURCE) /* one */			\
	FAILURE_HEADER_REASONS_QOTF(SOURCE, "one")
#define FAILURE_HEADER_REASONS_SOTF(SOURCE) /* some */			\
	FAILURE_HEADER_REASONS_QOTF(SOURCE, "some", "s")
#define FAILURE_HEADER_REASONS_AOTF(SOURCE) /* all */			\
	FAILURE_HEADER_REASONS_QOTF(SOURCE, "all",  "s")

/* full message
 *─────────────────────────────────────────────────────────────────────────── */
/* one reason */
#define FAILURE_REASON(SOURCE, REASON)					\
	ERROR_REASON(SOURCE, "failure", REASON)

#define FAILURE_REASONS_1(SOURCE, R1)					\
	FAILURE_REASON(SOURCE, R1)

/* two reasons */
#define FAILURE_REASONS_2_1OTF(SOURCE, R1, R2)				\
	ERROR_REASONS_2_1OTF(SOURCE, "failure", R1, R2)

#define FAILURE_REASONS_2(SOURCE, R1, R2)				\
	ERROR_REASONS_2_1OTF(SOURCE, "failure", R1, R2)

#define FAILURE_REASONS_2_SOTF(SOURCE, R1, R2)				\
	ERROR_REASONS_2_SOTF(SOURCE, "failure", R1, R2)

#define FAILURE_REASONS_2_AOTF(SOURCE, R1, R2)				\
	ERROR_REASONS_2_AOTF(SOURCE, "failure", R1, R2)

/* three reasons */
#define FAILURE_REASONS_3_1OTF(SOURCE, R1, R2, R3)			\
	ERROR_REASONS_3_1OTF(SOURCE, "failure", R1, R2, R3)

#define FAILURE_REASONS_3(SOURCE, R1, R2, R3)				\
	ERROR_REASONS_3_1OTF(SOURCE, "failure", R1, R2, R3)

#define FAILURE_REASONS_3_SOTF(SOURCE, R1, R2, R3)			\
	ERROR_REASONS_3_SOTF(SOURCE, "failure", R1, R2, R3)

#define FAILURE_REASONS_3_AOTF(SOURCE, R1, R2, R3)			\
	ERROR_REASONS_3_AOTF(SOURCE, "failure", R1, R2, R3)

/* four reasons */
#define FAILURE_REASONS_4_1OTF(SOURCE, R1, R2, R3, R4)			\
	ERROR_REASONS_4_1OTF(SOURCE, "failure", R1, R2, R3, R4)

#define FAILURE_REASONS_4(SOURCE, R1, R2, R3, R4)			\
	ERROR_REASONS_4_1OTF(SOURCE, "failure", R1, R2, R3, R4)

#define FAILURE_REASONS_4_SOTF(SOURCE, R1, R2, R3, R4)			\
	ERROR_REASONS_4_SOTF(SOURCE, "failure", R1, R2, R3, R4)

#define FAILURE_REASONS_4_AOTF(SOURCE, R1, R2, R3, R4)			\
	ERROR_REASONS_4_AOTF(SOURCE, "failure", R1, R2, R3, R4)


/* failure messages
 *─────────────────────────────────────────────────────────────────────────── */
#define MALLOC_FAILURE_REASON						\
"malloc failure (out of memory)"

#define MALLOC_FAILURE_MESSAGE(SOURCE)					\
FAILURE_REASON(SOURCE, MALLOC_FAILURE_REASON)

#endif /* ifndef MYSQL_SEED_STRING_STRING_MACROS_H_ */
