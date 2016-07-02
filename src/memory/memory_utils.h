#ifndef MEMORY_UTILS_MEMORY_UTILS_H_
#define MEMORY_UTILS_MEMORY_UTILS_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "utils/utils.h"	/* m/c/realloc/free, limits */
#include "utils/word_utils.h"	/* OCTET_CHAR, word_t, WORD_WIDTH/SIZE */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* byte buffers where sizeof(Width<WIDTH>) = WIDTH
 * ========================================================================== */
#if   (OCTET_CHAR == 1)
typedef uint_fast8_t  Width1;
typedef uint_fast16_t Width2;
typedef uint_fast32_t Width4;
typedef uint_fast64_t Width8;
typedef __uint128_t   Width16;
#elif (OCTET_CHAR == 2)
typedef uint_fast16_t Width1;
typedef uint_fast32_t Width2;
typedef uint_fast64_t Width4;
typedef __uint128_t   Width8;
#elif (OCTET_CHAR == 4)
typedef uint_fast32_t Width1;
typedef uint_fast64_t Width2;
typedef __uint128_t   Width4;
#elif (OCTET_CHAR == 8)
typedef uint_fast64_t Width1;
typedef __uint128_t   Width2;
#else	/* OCTET_CHAR = 3, 5, 6, or 7 */
typedef unsigned char Width1;
typedef struct Width2  { Width1 bytes[ 2]; } Width2;
#endif /* if (OCTET_CHAR == 1) */

#if (OCTET_CHAR > 1)
typedef struct Width16 { Width1 bytes[16]; } Width16;
#endif /* if (OCTET_CHAR > 1) */

#if (OCTET_CHAR > 2)
typedef struct Width8  { Width1 bytes[ 8]; } Width8;
#endif /* if (OCTET_CHAR > 2) */

#if (OCTET_CHAR == 3) || (OCTET_CHAR > 4)
typedef struct Width4  { Width1 bytes[ 4]; } Width4;
#endif /* if (OCTET_CHAR == 3) || (OCTET_CHAR > 4) */

/* shared by all cases of 'OCTET_CHAR' */
typedef struct Width3  { Width1 bytes[ 3]; } Width3;
typedef struct Width5  { Width1 bytes[ 5]; } Width5;
typedef struct Width6  { Width1 bytes[ 6]; } Width6;
typedef struct Width7  { Width1 bytes[ 7]; } Width7;
typedef struct Width9  { Width1 bytes[ 9]; } Width9;
typedef struct Width10 { Width1 bytes[10]; } Width10;
typedef struct Width11 { Width1 bytes[11]; } Width11;
typedef struct Width12 { Width1 bytes[12]; } Width12;
typedef struct Width13 { Width1 bytes[13]; } Width13;
typedef struct Width14 { Width1 bytes[14]; } Width14;
typedef struct Width15 { Width1 bytes[15]; } Width15;

/* max Width<WIDTH> */
typedef Width16 WidthMax;

/* Width<WORD_WIDTH> */
typedef word_t WidthWord;

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define WIDTH_MAX_WIDTH 16
#define WIDTH_MAX_SIZE 16ul

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* call memory action function */
#define MEMORY_ACTION_WIDTH(ACTION, WIDTH, ...)				\
memory_ ## ACTION ## WIDTH (__VA_ARGS__)

#define EXPAND_MEMORY_ACTION_WIDTH(ACTION, WIDTH, ...)			\
MACRO_EXPAND_ARGS(MEMORY_ACTION_WIDTH, ACTION, WIDTH, ##__VA_ARGS__)


#define WIDTH_REM_SWITCH(REM_SIZE, HANDLE_CASE, ...)	\
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

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* return a pointer to memory displaced 'offset' bytes from that referenced
 * by 'pointer' */
inline void *memory_offset(const void *const restrict pointer,
			   const ptrdiff_t offset)
{
	return (void *) (((const Width1 *const restrict) pointer) + offset);
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS */

#endif /* ifndef MEMORY_UTILS_MEMORY_UTILS_H_ */
