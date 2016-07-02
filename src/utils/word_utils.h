#ifndef MYSQL_SEED_UTILS_WORD_UTILS_H_
#define MYSQL_SEED_UTILS_WORD_UTILS_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "utils/types/word.h"	/* word_t, WORD_MAX */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
#if   (CHAR_BIT == 8)
#	define OCTET_CHAR 1
#elif (CHAR_BIT == 16)
#	define OCTET_CHAR 2
#elif (CHAR_BIT == 24)
#	define OCTET_CHAR 3
#elif (CHAR_BIT == 32)
#	define OCTET_CHAR 4
#elif (CHAR_BIT == 40)
#	define OCTET_CHAR 5
#elif (CHAR_BIT == 48)
#	define OCTET_CHAR 6
#elif (CHAR_BIT == 56)
#	define OCTET_CHAR 7
#elif (CHAR_BIT == 64)
#	define OCTET_CHAR 8
#else
#	error "not supported for value of 'CHAR_BIT'"
#endif /* if (CHAR_BIT == 8) */

#if   (WORD_MAX == UINT64_MAX)
#	define OCTET_WORD 8
#	if   (OCTET_CHAR == 1)
#		define WORD_WIDTH	 8
#		define WORD_SIZE	 8lu
#		define MULT_WORD_SIZE(X) ((X) << 3)
#		define DIV_WORD_SIZE(X)  ((X) >> 3)
#		define REM_WORD_SIZE(X)  ((X) &  7lu)
#	elif (OCTET_CHAR == 2)
#		define WORD_WIDTH	 4
#		define WORD_SIZE	 4lu
#		define MULT_WORD_SIZE(X) ((X) << 2)
#		define DIV_WORD_SIZE(X)  ((X) >> 2)
#		define REM_WORD_SIZE(X)  ((X) & 3lu)
#	elif (OCTET_CHAR == 4)
#		define WORD_WIDTH	 2
#		define WORD_SIZE	 2lu
#		define MULT_WORD_SIZE(X) ((X) << 1)
#		define DIV_WORD_SIZE(X)  ((X) >> 1)
#		define REM_WORD_SIZE(X)  ((X) & 1lu)
#	elif (OCTET_CHAR == 8)
#		define WORD_WIDTH	 1
#		define WORD_SIZE	 1lu
#		define MULT_WORD_SIZE(X) (X)
#		define DIV_WORD_SIZE(X)  (X)
#		define REM_WORD_SIZE(X)  (0lu)
#	else
"		error 'WORD_WIDTH' not supported for 'CHAR_BIT'
#	endif /* if (OCTET_CHAR == 1) */
#elif (WORD_MAX == ((1llu << 56) - 1llu))
#	define OCTET_WORD 7
#	if   (OCTET_CHAR == 1)
#		define WORD_WIDTH	 7
#		define WORD_SIZE	 7lu
#		define MULT_WORD_SIZE(X) ((X) * 7lu)
#		define DIV_WORD_SIZE(X)  ((X) / 7lu)
#		define REM_WORD_SIZE(X)  ((X) % 7lu)
#	elif (OCTET_CHAR == 7)
#		define WORD_WIDTH	 1
#		define WORD_SIZE	 1lu
#		define MULT_WORD_SIZE(X) (X)
#		define DIV_WORD_SIZE(X)  (X)
#		define REM_WORD_SIZE(X)  (0lu)
#	else
"		error 'WORD_WIDTH' not supported for 'CHAR_BIT'
#	endif /* if (OCTET_CHAR == 1) */
#elif (WORD_MAX == ((1llu << 48) - 1llu))
#	define OCTET_WORD 6
#	if   (OCTET_CHAR == 1)
#		define WORD_WIDTH	 6
#		define WORD_SIZE	 6lu
#		define MULT_WORD_SIZE(X) ((X) * 6lu)
#		define DIV_WORD_SIZE(X)  ((X) / 6lu)
#		define REM_WORD_SIZE(X)  ((X) % 6lu)
#	elif (OCTET_CHAR == 2)
#		define WORD_WIDTH	 3
#		define WORD_SIZE	 3lu
#		define MULT_WORD_SIZE(X) ((X) * 3lu)
#		define DIV_WORD_SIZE(X)  ((X) / 3lu)
#		define REM_WORD_SIZE(X)  ((X) % 3lu)
#	elif (OCTET_CHAR == 3)
#		define WORD_WIDTH	 2
#		define WORD_SIZE	 2lu
#		define MULT_WORD_SIZE(X) ((X) << 1)
#		define DIV_WORD_SIZE(X)  ((X) >> 1)
#		define REM_WORD_SIZE(X)  ((X) & 1lu)
#	elif (OCTET_CHAR == 6)
#		define WORD_WIDTH	 1
#		define WORD_SIZE	 1lu
#		define MULT_WORD_SIZE(X) (X)
#		define DIV_WORD_SIZE(X)  (X)
#		define REM_WORD_SIZE(X)  (0lu)
#	else
"		error 'WORD_WIDTH' not supported for 'CHAR_BIT'
#	endif /* if (OCTET_CHAR == 1) */
#elif (WORD_MAX == ((1llu << 40) - 1llu))
#	define OCTET_WORD 5
#	if   (OCTET_CHAR == 1)
#		define WORD_WIDTH	 5
#		define WORD_SIZE	 5lu
#		define MULT_WORD_SIZE(X) ((X) * 5lu)
#		define DIV_WORD_SIZE(X)  ((X) / 5lu)
#		define REM_WORD_SIZE(X)  ((X) % 5lu)
#	elif (OCTET_CHAR == 5)
#		define WORD_WIDTH	 1
#		define WORD_SIZE	 1lu
#		define MULT_WORD_SIZE(X) (X)
#		define DIV_WORD_SIZE(X)  (X)
#		define REM_WORD_SIZE(X)  (0lu)
#	else
"		error 'WORD_WIDTH' not supported for 'CHAR_BIT'
#	endif /* if (OCTET_CHAR == 1) */
#elif (WORD_MAX == UINT32_MAX)
#	define OCTET_WORD 4
#	if   (OCTET_CHAR == 1)
#		define WORD_WIDTH	 4
#		define WORD_SIZE	 4lu
#		define MULT_WORD_SIZE(X) ((X) << 2)
#		define DIV_WORD_SIZE(X)  ((X) >> 2)
#		define REM_WORD_SIZE(X)  ((X) & 3lu)
#	elif (OCTET_CHAR == 2)
#		define WORD_WIDTH	 2
#		define WORD_SIZE	 2lu
#		define MULT_WORD_SIZE(X) ((X) << 1)
#		define DIV_WORD_SIZE(X)  ((X) >> 1)
#		define REM_WORD_SIZE(X)  ((X) & 1lu)
#	elif (OCTET_CHAR == 4)
#		define WORD_WIDTH	 1
#		define WORD_SIZE	 1lu
#		define MULT_WORD_SIZE(X) (X)
#		define DIV_WORD_SIZE(X)  (X)
#		define REM_WORD_SIZE(X)  (0lu)
#	else
"		error 'WORD_WIDTH' not supported for 'CHAR_BIT'
#	endif /* if (OCTET_CHAR == 1) */
#elif (WORD_MAX == ((1llu << 24) - 1llu))
#	define OCTET_WORD 3
#	if   (OCTET_CHAR == 1)
#		define WORD_WIDTH	 3
#		define WORD_SIZE	 3lu
#		define MULT_WORD_SIZE(X) ((X) * 3lu)
#		define DIV_WORD_SIZE(X)  ((X) / 3lu)
#		define REM_WORD_SIZE(X)  ((X) % 3lu)
#	elif (OCTET_CHAR == 3)
#		define WORD_WIDTH	 1
#		define WORD_SIZE	 1lu
#		define MULT_WORD_SIZE(X) (X)
#		define DIV_WORD_SIZE(X)  (X)
#		define REM_WORD_SIZE(X)  (0lu)
#	else
"		error 'WORD_WIDTH' not supported for 'CHAR_BIT'
#	endif /* if (OCTET_CHAR == 1) */
#elif (WORD_MAX == UINT16_MAX)
#	define OCTET_WORD 2
#	if   (OCTET_CHAR == 1)
#		define WORD_WIDTH	 2
#		define WORD_SIZE	 2lu
#		define MULT_WORD_SIZE(X) ((X) << 1)
#		define DIV_WORD_SIZE(X)  ((X) >> 1)
#		define REM_WORD_SIZE(X)  ((X) & 1lu)
#	elif (OCTET_CHAR == 2)
#		define WORD_WIDTH	 1
#		define WORD_SIZE	 1lu
#		define MULT_WORD_SIZE(X) (X)
#		define DIV_WORD_SIZE(X)  (X)
#		define REM_WORD_SIZE(X)  (0lu)
#	else
"		error 'WORD_WIDTH' not supported for 'CHAR_BIT'
#	endif /* if (OCTET_CHAR == 1) */
#elif (WORD_MAX == UINT8_MAX)
#	define OCTET_WORD 1
#	if   (OCTET_CHAR == 1)
#		define WORD_WIDTH	 1
#		define WORD_SIZE	 1lu
#		define MULT_WORD_SIZE(X) (X)
#		define DIV_WORD_SIZE(X)  (X)
#		define REM_WORD_SIZE(X)  (0lu)
#	else
"		error 'WORD_WIDTH' not supported for 'CHAR_BIT'
#	endif /* if (OCTET_CHAR == 1) */
#else
#	error "sizeof(word_t) is unknown to preprocessor: 'WORD_WIDTH' is undefined"
#endif

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS */

#endif /* ifndef MYSQL_SEED_UTILS_WORD_UTILS_H_ */
