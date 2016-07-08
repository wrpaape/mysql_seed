#ifndef MEMORY_UTILS_WORD_REM_UTILS_H_
#define MEMORY_UTILS_WORD_REM_UTILS_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "memory/memory_utils.h"	/* Width<WIDTH>, word_t */
#include "utils/word_attrs.h"		/* WORD_SIZE */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
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


/* WORD_REM_SWITCH */
#if   !defined(WORD_SIZE)
#	error "'WORD_SIZE' is undefined"
#elif (WORD_SIZE <= 0lu)
#	error "'WORD_SIZE' <= 0"
#elif (WORD_SIZE == 1lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)
#elif (WORD_SIZE == 2lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu: HANDLE_CASE ## 0 (__VA_ARGS__);		\
	default:  HANDLE_CASE ## 1 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 3lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu: HANDLE_CASE ## 0 (__VA_ARGS__);		\
	case 1lu: HANDLE_CASE ## 1 (__VA_ARGS__);		\
	default:  HANDLE_CASE ## 2 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 4lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu: HANDLE_CASE ## 0 (__VA_ARGS__);		\
	case 1lu: HANDLE_CASE ## 1 (__VA_ARGS__);		\
	case 2lu: HANDLE_CASE ## 2 (__VA_ARGS__);		\
	default:  HANDLE_CASE ## 3 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 5lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu: HANDLE_CASE ## 0 (__VA_ARGS__);		\
	case 1lu: HANDLE_CASE ## 1 (__VA_ARGS__);		\
	case 2lu: HANDLE_CASE ## 2 (__VA_ARGS__);		\
	case 3lu: HANDLE_CASE ## 3 (__VA_ARGS__);		\
	default:  HANDLE_CASE ## 4 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 6lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu: HANDLE_CASE ## 0 (__VA_ARGS__);		\
	case 1lu: HANDLE_CASE ## 1 (__VA_ARGS__);		\
	case 2lu: HANDLE_CASE ## 2 (__VA_ARGS__);		\
	case 3lu: HANDLE_CASE ## 3 (__VA_ARGS__);		\
	case 4lu: HANDLE_CASE ## 4 (__VA_ARGS__);		\
	default:  HANDLE_CASE ## 5 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 7lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu: HANDLE_CASE ## 0 (__VA_ARGS__);		\
	case 1lu: HANDLE_CASE ## 1 (__VA_ARGS__);		\
	case 2lu: HANDLE_CASE ## 2 (__VA_ARGS__);		\
	case 3lu: HANDLE_CASE ## 3 (__VA_ARGS__);		\
	case 4lu: HANDLE_CASE ## 4 (__VA_ARGS__);		\
	case 5lu: HANDLE_CASE ## 5 (__VA_ARGS__);		\
	default:  HANDLE_CASE ## 6 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 8lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu: HANDLE_CASE ## 0 (__VA_ARGS__);		\
	case 1lu: HANDLE_CASE ## 1 (__VA_ARGS__);		\
	case 2lu: HANDLE_CASE ## 2 (__VA_ARGS__);		\
	case 3lu: HANDLE_CASE ## 3 (__VA_ARGS__);		\
	case 4lu: HANDLE_CASE ## 4 (__VA_ARGS__);		\
	case 5lu: HANDLE_CASE ## 5 (__VA_ARGS__);		\
	case 6lu: HANDLE_CASE ## 6 (__VA_ARGS__);		\
	default:  HANDLE_CASE ## 7 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 9lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu: HANDLE_CASE ## 0 (__VA_ARGS__);		\
	case 1lu: HANDLE_CASE ## 1 (__VA_ARGS__);		\
	case 2lu: HANDLE_CASE ## 2 (__VA_ARGS__);		\
	case 3lu: HANDLE_CASE ## 3 (__VA_ARGS__);		\
	case 4lu: HANDLE_CASE ## 4 (__VA_ARGS__);		\
	case 5lu: HANDLE_CASE ## 5 (__VA_ARGS__);		\
	case 6lu: HANDLE_CASE ## 6 (__VA_ARGS__);		\
	case 7lu: HANDLE_CASE ## 7 (__VA_ARGS__);		\
	default:  HANDLE_CASE ## 8 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 10lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu: HANDLE_CASE ## 0 (__VA_ARGS__);		\
	case 1lu: HANDLE_CASE ## 1 (__VA_ARGS__);		\
	case 2lu: HANDLE_CASE ## 2 (__VA_ARGS__);		\
	case 3lu: HANDLE_CASE ## 3 (__VA_ARGS__);		\
	case 4lu: HANDLE_CASE ## 4 (__VA_ARGS__);		\
	case 5lu: HANDLE_CASE ## 5 (__VA_ARGS__);		\
	case 6lu: HANDLE_CASE ## 6 (__VA_ARGS__);		\
	case 7lu: HANDLE_CASE ## 7 (__VA_ARGS__);		\
	case 8lu: HANDLE_CASE ## 8 (__VA_ARGS__);		\
	default:  HANDLE_CASE ## 9 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 11lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu: HANDLE_CASE ## 0  (__VA_ARGS__);		\
	case 1lu: HANDLE_CASE ## 1  (__VA_ARGS__);		\
	case 2lu: HANDLE_CASE ## 2  (__VA_ARGS__);		\
	case 3lu: HANDLE_CASE ## 3  (__VA_ARGS__);		\
	case 4lu: HANDLE_CASE ## 4  (__VA_ARGS__);		\
	case 5lu: HANDLE_CASE ## 5  (__VA_ARGS__);		\
	case 6lu: HANDLE_CASE ## 6  (__VA_ARGS__);		\
	case 7lu: HANDLE_CASE ## 7  (__VA_ARGS__);		\
	case 8lu: HANDLE_CASE ## 8  (__VA_ARGS__);		\
	case 9lu: HANDLE_CASE ## 9  (__VA_ARGS__);		\
	default:  HANDLE_CASE ## 10 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 12lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu:  HANDLE_CASE ## 0 (__VA_ARGS__);		\
	case 1lu:  HANDLE_CASE ## 1 (__VA_ARGS__);		\
	case 2lu:  HANDLE_CASE ## 2 (__VA_ARGS__);		\
	case 3lu:  HANDLE_CASE ## 3 (__VA_ARGS__);		\
	case 4lu:  HANDLE_CASE ## 4 (__VA_ARGS__);		\
	case 5lu:  HANDLE_CASE ## 5 (__VA_ARGS__);		\
	case 6lu:  HANDLE_CASE ## 6 (__VA_ARGS__);		\
	case 7lu:  HANDLE_CASE ## 7 (__VA_ARGS__);		\
	case 8lu:  HANDLE_CASE ## 8 (__VA_ARGS__);		\
	case 9lu:  HANDLE_CASE ## 9 (__VA_ARGS__);		\
	case 10lu: HANDLE_CASE ## 10(__VA_ARGS__);		\
	default:   HANDLE_CASE ## 11(__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 13lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu:  HANDLE_CASE ## 0 ( __VA_ARGS__);		\
	case 1lu:  HANDLE_CASE ## 1 ( __VA_ARGS__);		\
	case 2lu:  HANDLE_CASE ## 2 ( __VA_ARGS__);		\
	case 3lu:  HANDLE_CASE ## 3 ( __VA_ARGS__);		\
	case 4lu:  HANDLE_CASE ## 4 ( __VA_ARGS__);		\
	case 5lu:  HANDLE_CASE ## 5 ( __VA_ARGS__);		\
	case 6lu:  HANDLE_CASE ## 6 ( __VA_ARGS__);		\
	case 7lu:  HANDLE_CASE ## 7 ( __VA_ARGS__);		\
	case 8lu:  HANDLE_CASE ## 8 ( __VA_ARGS__);		\
	case 9lu:  HANDLE_CASE ## 9 ( __VA_ARGS__);		\
	case 10lu: HANDLE_CASE ## 10( __VA_ARGS__);		\
	case 11lu: HANDLE_CASE ## 11( __VA_ARGS__);		\
	default:   HANDLE_CASE ## 12( __VA_ARGS__);		\
	}
#elif (WORD_SIZE == 14lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu:  HANDLE_CASE ## 0  (__VA_ARGS__);		\
	case 1lu:  HANDLE_CASE ## 1  (__VA_ARGS__);		\
	case 2lu:  HANDLE_CASE ## 2  (__VA_ARGS__);		\
	case 3lu:  HANDLE_CASE ## 3  (__VA_ARGS__);		\
	case 4lu:  HANDLE_CASE ## 4  (__VA_ARGS__);		\
	case 5lu:  HANDLE_CASE ## 5  (__VA_ARGS__);		\
	case 6lu:  HANDLE_CASE ## 6  (__VA_ARGS__);		\
	case 7lu:  HANDLE_CASE ## 7  (__VA_ARGS__);		\
	case 8lu:  HANDLE_CASE ## 8  (__VA_ARGS__);		\
	case 9lu:  HANDLE_CASE ## 9  (__VA_ARGS__);		\
	case 10lu: HANDLE_CASE ## 10 (__VA_ARGS__);		\
	case 11lu: HANDLE_CASE ## 11 (__VA_ARGS__);		\
	case 12lu: HANDLE_CASE ## 12 (__VA_ARGS__);		\
	default:   HANDLE_CASE ## 13 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 15lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu:  HANDLE_CASE ## 0  (__VA_ARGS__);		\
	case 2lu:  HANDLE_CASE ## 2  (__VA_ARGS__);		\
	case 3lu:  HANDLE_CASE ## 3  (__VA_ARGS__);		\
	case 4lu:  HANDLE_CASE ## 4  (__VA_ARGS__);		\
	case 5lu:  HANDLE_CASE ## 5  (__VA_ARGS__);		\
	case 6lu:  HANDLE_CASE ## 6  (__VA_ARGS__);		\
	case 7lu:  HANDLE_CASE ## 7  (__VA_ARGS__);		\
	case 8lu:  HANDLE_CASE ## 8  (__VA_ARGS__);		\
	case 9lu:  HANDLE_CASE ## 9  (__VA_ARGS__);		\
	case 10lu: HANDLE_CASE ## 10 (__VA_ARGS__);		\
	case 11lu: HANDLE_CASE ## 11 (__VA_ARGS__);		\
	case 12lu: HANDLE_CASE ## 12 (__VA_ARGS__);		\
	case 13lu: HANDLE_CASE ## 13 (__VA_ARGS__);		\
	default:   HANDLE_CASE ## 14 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 16lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu:  HANDLE_CASE ## 0  (__VA_ARGS__);		\
	case 1lu:  HANDLE_CASE ## 1  (__VA_ARGS__);		\
	case 2lu:  HANDLE_CASE ## 2  (__VA_ARGS__);		\
	case 3lu:  HANDLE_CASE ## 3  (__VA_ARGS__);		\
	case 4lu:  HANDLE_CASE ## 4  (__VA_ARGS__);		\
	case 5lu:  HANDLE_CASE ## 5  (__VA_ARGS__);		\
	case 6lu:  HANDLE_CASE ## 6  (__VA_ARGS__);		\
	case 7lu:  HANDLE_CASE ## 7  (__VA_ARGS__);		\
	case 8lu:  HANDLE_CASE ## 8  (__VA_ARGS__);		\
	case 9lu:  HANDLE_CASE ## 9  (__VA_ARGS__);		\
	case 10lu: HANDLE_CASE ## 10 (__VA_ARGS__);		\
	case 11lu: HANDLE_CASE ## 11 (__VA_ARGS__);		\
	case 12lu: HANDLE_CASE ## 12 (__VA_ARGS__);		\
	case 13lu: HANDLE_CASE ## 13 (__VA_ARGS__);		\
	case 14lu: HANDLE_CASE ## 14 (__VA_ARGS__);		\
	default:   HANDLE_CASE ## 15 (__VA_ARGS__);		\
	}
#elif (WORD_SIZE == 17lu)
#	define WORD_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
	switch (REM_SIZE) {					\
	case 0lu:  HANDLE_CASE ## 0  (__VA_ARGS__);		\
	case 1lu:  HANDLE_CASE ## 1  (__VA_ARGS__);		\
	case 2lu:  HANDLE_CASE ## 2  (__VA_ARGS__);		\
	case 3lu:  HANDLE_CASE ## 3  (__VA_ARGS__);		\
	case 4lu:  HANDLE_CASE ## 4  (__VA_ARGS__);		\
	case 5lu:  HANDLE_CASE ## 5  (__VA_ARGS__);		\
	case 6lu:  HANDLE_CASE ## 6  (__VA_ARGS__);		\
	case 7lu:  HANDLE_CASE ## 7  (__VA_ARGS__);		\
	case 8lu:  HANDLE_CASE ## 8  (__VA_ARGS__);		\
	case 9lu:  HANDLE_CASE ## 9  (__VA_ARGS__);		\
	case 10lu: HANDLE_CASE ## 10 (__VA_ARGS__);		\
	case 11lu: HANDLE_CASE ## 11 (__VA_ARGS__);		\
	case 12lu: HANDLE_CASE ## 12 (__VA_ARGS__);		\
	case 13lu: HANDLE_CASE ## 13 (__VA_ARGS__);		\
	case 14lu: HANDLE_CASE ## 14 (__VA_ARGS__);		\
	case 15lu: HANDLE_CASE ## 15 (__VA_ARGS__);		\
	default:   HANDLE_CASE ## 16 (__VA_ARGS__);		\
	}
#else
#	error "'WORD_SIZE' > 'WIDTH_MAX_SIZE' + 1"
#endif /* if (WORD_SIZE <= 0lu) */


/* PUT_WORDS_LOOP_LENGTH */
/* put at least 1 word */
#define PUT_WORDS_LOOP_LENGTH(X, Y, LENGTH, EXIT_LOOP)			\
void *const restrict end_ptr = (void *const restrict)			\
	(((word_t *const restrict) X) + (LENGTH));			\
PUT_WORDS_LOOP(X, Y, end_ptr, EXIT_LOOP)

/* PUT_WORDS_LOOP */
/* put at least 1 word */
#define PUT_WORDS_LOOP(X, Y, END_PTR, EXIT_LOOP)			\
while (1) {								\
	*((word_t *restrict) X) = *((const word_t *restrict) Y);	\
	X = (void *restrict) (((word_t *restrict) X) + 1l);		\
	if (x == END_PTR)						\
		EXIT_LOOP						\
	Y = (void *restrict) (((word_t *restrict) Y) + 1l);		\
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS */


#endif /* ifndef MEMORY_UTILS_WORD_REM_UTILS_H_ */
