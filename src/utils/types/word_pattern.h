#ifndef UTILS_TYPES_WORD_PATTERN_H_
#define UTILS_TYPES_WORD_PATTERN_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "utils/word_attrs.h"		/* WORD_SIZE */
#include "utils/types/char_buffer.h"	/* CharBuffer */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#ifndef OCTET_WORD
#	error "WordPattern and WordPatternPtr are not defined - "	\
	      "unsupported WORD_SIZE"
#endif /* ifndef WORD_SIZE */

union WordPattern {
	word_t word;
	char string[WORD_SIZE];
	CharBuffer1  size_1;
#if (WORD_SIZE > 1lu)
	CharBuffer2  size_2;
#if (WORD_SIZE > 2lu)
	CharBuffer3  size_3;
#if (WORD_SIZE > 3lu)
	CharBuffer4  size_4;
#if (WORD_SIZE > 4lu)
	CharBuffer5  size_5;
#if (WORD_SIZE > 5lu)
	CharBuffer6  size_6;
#if (WORD_SIZE > 6lu)
	CharBuffer7  size_7;
#if (WORD_SIZE > 7lu)
	CharBuffer8  size_8;
#if (WORD_SIZE > 8lu)
	CharBuffer9  size_9;
#if (WORD_SIZE > 9lu)
	CharBuffer10 size_10;
#if (WORD_SIZE > 10lu)
	CharBuffer11 size_11;
#if (WORD_SIZE > 11lu)
	CharBuffer12 size_12;
#if (WORD_SIZE > 12lu)
	CharBuffer13 size_13;
#if (WORD_SIZE > 13lu)
	CharBuffer14 size_14;
#if (WORD_SIZE > 14lu)
	CharBuffer15 size_15;
#if (WORD_SIZE > 15lu)
	CharBuffer16 size_16;
#endif /* if (WORD_SIZE > 1) */
#endif /* if (WORD_SIZE > 2) */
#endif /* if (WORD_SIZE > 3) */
#endif /* if (WORD_SIZE > 4) */
#endif /* if (WORD_SIZE > 5) */
#endif /* if (WORD_SIZE > 6) */
#endif /* if (WORD_SIZE > 7) */
#endif /* if (WORD_SIZE > 8) */
#endif /* if (WORD_SIZE > 9) */
#endif /* if (WORD_SIZE > 10) */
#endif /* if (WORD_SIZE > 11) */
#endif /* if (WORD_SIZE > 12) */
#endif /* if (WORD_SIZE > 13) */
#endif /* if (WORD_SIZE > 14) */
#endif /* if (WORD_SIZE > 15) */
};

union WordPatternPtr {
	word_t *restrict word;
	char *restrict string;
	CharBuffer1  *restrict size_1;
#if (WORD_SIZE > 1lu)
	CharBuffer2  *restrict size_2;
#if (WORD_SIZE > 2lu)
	CharBuffer3  *restrict size_3;
#if (WORD_SIZE > 3lu)
	CharBuffer4  *restrict size_4;
#if (WORD_SIZE > 4lu)
	CharBuffer5  *restrict size_5;
#if (WORD_SIZE > 5lu)
	CharBuffer6  *restrict size_6;
#if (WORD_SIZE > 6lu)
	CharBuffer7  *restrict size_7;
#if (WORD_SIZE > 7lu)
	CharBuffer8  *restrict size_8;
#if (WORD_SIZE > 8lu)
	CharBuffer9  *restrict size_9;
#if (WORD_SIZE > 9lu)
	CharBuffer10 *restrict size_10;
#if (WORD_SIZE > 10lu)
	CharBuffer11 *restrict size_11;
#if (WORD_SIZE > 11lu)
	CharBuffer12 *restrict size_12;
#if (WORD_SIZE > 12lu)
	CharBuffer13 *restrict size_13;
#if (WORD_SIZE > 13lu)
	CharBuffer14 *restrict size_14;
#if (WORD_SIZE > 14lu)
	CharBuffer15 *restrict size_15;
#if (WORD_SIZE > 15lu)
	CharBuffer16 *restrict size_16;
#endif /* if (WORD_SIZE > 1) */
#endif /* if (WORD_SIZE > 2) */
#endif /* if (WORD_SIZE > 3) */
#endif /* if (WORD_SIZE > 4) */
#endif /* if (WORD_SIZE > 5) */
#endif /* if (WORD_SIZE > 6) */
#endif /* if (WORD_SIZE > 7) */
#endif /* if (WORD_SIZE > 8) */
#endif /* if (WORD_SIZE > 9) */
#endif /* if (WORD_SIZE > 10) */
#endif /* if (WORD_SIZE > 11) */
#endif /* if (WORD_SIZE > 12) */
#endif /* if (WORD_SIZE > 13) */
#endif /* if (WORD_SIZE > 14) */
#endif /* if (WORD_SIZE > 15) */
};

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * HELPER MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */


/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER MACROS */
#endif /* ifndef UTILS_TYPES_WORD_PATTERN_H_ */
