#ifndef MYSQL_SEED_UTILS_TYPES_WIDTH_H_
#define MYSQL_SEED_UTILS_TYPES_WIDTH_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "utils/char_attrs.h"	/* <limits.h>, OCTET_CHAR */
#include "utils/types/word.h"	/* word_t */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#ifndef OCTET_CHAR
#	error "Width<WIDTH> types are not defined - unsupported CHAR_BIT"
#endif /* ifndef WORD_SIZE */

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
#define WIDTH_MAX_SIZE  16ul

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS */


#endif /* ifndef MYSQL_SEED_UTILS_TYPES_WIDTH_H_ */
