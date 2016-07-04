#ifndef MYSQL_SEED_UTILS_FAIL_SWITCH_H_
#define MYSQL_SEED_UTILS_FAIL_SWITCH_H_

/* external dependencies
 * ─────────────────────────────────────────────────────────────────────────── */
#include <stdbool.h>			/* bool */
#include <errno.h>			/* errno */
#include "string/string_macros.h"	/* error macros */

/* must define these in included file */
#undef FAIL_SWITCH_ROUTINE
#undef FAIL_SWITCH_STATUS_SUCCESS
#undef FAIL_SWITCH_ERRNO_FAILURE
#undef FAIL_SWITCH_FAILURE_POINTER

#define _FS_ROUTINE_STRING EXPAND_STRINGIFY(FAIL_SWITCH_ROUTINE)

#define _FS_HANDLE_FAILURE_CASE(FAILURE_CASE, REASON)			\
FAILURE_CASE:								\
	*(FAIL_SWITCH_FAILURE_POINTER) = REASON;			\
	return false;

#define _FS_HANDLE_FAILURE_STATUS(STATUS, REASON)			\
_FS_HANDLE_FAILURE_CASE(case STATUS, REASON)

#define _FS_HANDLE_DEFAULT_CASE()					\
_FS_HANDLE_FAILURE_CASE(default,					\
			FAILURE_REASON(_FS_ROUTINE_STRING, "unknown"))

/* diagnose failure according to return status
 * ────────────────────────────────────────────────────────────────────────── */
#define FAIL_SWITCH_STATUS_OPEN(...)					\
switch (FAIL_SWITCH_ROUTINE(__VA_ARGS__)) {				\
case FAIL_SWITCH_STATUS_SUCCESS:					\
	return true;

#define FAIL_SWITCH_STATUS_CASE_1(STATUS, R1)				\
_FS_HANDLE_FAILURE_STATUS(STATUS,					\
			  FAILURE_REASONS_1(_FS_ROUTINE_STRING, R1))

#define FAIL_SWITCH_STATUS_CASE_2(STATUS, R1, R2)			\
_FS_HANDLE_FAILURE_STATUS(STATUS,					\
			  FAILURE_REASONS_2(_FS_ROUTINE_STRING, R1,	\
								R2))

#define FAIL_SWITCH_STATUS_CASE_3(STATUS, R1, R2, R3)			\
_FS_HANDLE_FAILURE_STATUS(STATUS,					\
			  FAILURE_REASONS_3(_FS_ROUTINE_STRING, R1,	\
								R2,	\
								R3))

#define FAIL_SWITCH_STATUS_CASE_4(STATUS, R1, R2, R3, R4)		\
_FS_HANDLE_FAILURE_STATUS(STATUS,					\
			  FAILURE_REASONS_4(_FS_ROUTINE_STRING, R1,	\
								R2,	\
								R3,	\
								R4))

#define FAIL_SWITCH_STATUS_CLOSE()					\
_FS_HANDLE_DEFAULT_CASE()						\
}


/* diagnose failure according to errno
 * ────────────────────────────────────────────────────────────────────────── */
#define FAIL_SWITCH_ERRNO_OPEN(...)					\
if (FAIL_SWITCH_ROUTINE(__VA_ARGS__)					\
    != FAIL_SWITCH_ERRNO_FAILURE)					\
	return true;							\
switch (errno)	{


#define FAIL_SWITCH_ERRNO_CASE_1(ERRNO, R1)				\
_FS_HANDLE_FAILURE_STATUS(ERRNO,					\
			  FAILURE_REASONS_1(_FS_ROUTINE_STRING, R1))

#define FAIL_SWITCH_ERRNO_CASE_2(ERRNO, R1, R2)				\
_FS_HANDLE_FAILURE_STATUS(ERRNO,					\
			  FAILURE_REASONS_2(_FS_ROUTINE_STRING, R1,	\
							        R2))

#define FAIL_SWITCH_ERRNO_CASE_3(ERRNO, R1, R2, R3)			\
_FS_HANDLE_FAILURE_STATUS(ERRNO,					\
			  FAILURE_REASONS_3(_FS_ROUTINE_STRING, R1,	\
							        R2,	\
							        R3))

#define FAIL_SWITCH_ERRNO_CASE_4(ERRNO, R1, R2, R3, R4)			\
_FS_HANDLE_FAILURE_STATUS(ERRNO,					\
			  FAILURE_REASONS_4(_FS_ROUTINE_STRING, R1,	\
							        R2,	\
							        R3,	\
							        R4))

#define FAIL_SWITCH_ERRNO_CLOSE()					\
_FS_HANDLE_DEFAULT_CASE()						\
}

#endif /* ifndef MYSQL_SEED_UTILS_FAIL_SWITCH_H_ */
