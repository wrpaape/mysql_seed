#ifndef MYSQL_SEED_UTILS_WORD_ATTRS_H_
#define MYSQL_SEED_UTILS_WORD_ATTRS_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "utils/types/word.h"	/* word_t, WORD_MAX */
#include "utils/char_attrs.h"	/* OCTET_CHAR */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#if HAVE_CHAR_ATTRS
#	if   (WORD_MAX == UINT64_MAX)
#		define OCTET_WORD 8
#		if   (OCTET_CHAR == 1)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 8
#			define WORD_SIZE	 8lu
#			define MULT_WORD_SIZE(X) ((X) << 3)
#			define DIV_WORD_SIZE(X)  ((X) >> 3)
#			define REM_WORD_SIZE(X)  ((X) &  7lu)
#		elif (OCTET_CHAR == 2)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 4
#			define WORD_SIZE	 4lu
#			define MULT_WORD_SIZE(X) ((X) << 2)
#			define DIV_WORD_SIZE(X)  ((X) >> 2)
#			define REM_WORD_SIZE(X)  ((X) & 3lu)
#		elif (OCTET_CHAR == 4)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 2
#			define WORD_SIZE	 2lu
#			define MULT_WORD_SIZE(X) ((X) << 1)
#			define DIV_WORD_SIZE(X)  ((X) >> 1)
#			define REM_WORD_SIZE(X)  ((X) & 1lu)
#		elif (OCTET_CHAR == 8)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 1
#			define WORD_SIZE	 1lu
#			define MULT_WORD_SIZE(X) (X)
#			define DIV_WORD_SIZE(X)  (X)
#			define REM_WORD_SIZE(X)  (0lu)
#		else
#			define HAVE_WORD_ATTRS	 0
#			undef  WORD_WIDTH
#			undef  WORD_SIZE
#			undef  MULT_WORD_SIZE
#			undef  DIV_WORD_SIZE
#			undef  REM_WORD_SIZE
#		endif /* if (OCTET_CHAR == 1) */
#	elif (WORD_MAX == ((1llu << 56) - 1llu))
#		define OCTET_WORD 7
#		if   (OCTET_CHAR == 1)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 7
#			define WORD_SIZE	 7lu
#			define MULT_WORD_SIZE(X) ((X) * 7lu)
#			define DIV_WORD_SIZE(X)  ((X) / 7lu)
#			define REM_WORD_SIZE(X)  ((X) % 7lu)
#		elif (OCTET_CHAR == 7)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 1
#			define WORD_SIZE	 1lu
#			define MULT_WORD_SIZE(X) (X)
#			define DIV_WORD_SIZE(X)  (X)
#			define REM_WORD_SIZE(X)  (0lu)
#		else
#			define HAVE_WORD_ATTRS	 0
#			undef  WORD_WIDTH
#			undef  WORD_SIZE
#			undef  MULT_WORD_SIZE
#			undef  DIV_WORD_SIZE
#			undef  REM_WORD_SIZE
#		endif /* if (OCTET_CHAR == 1) */
#	elif (WORD_MAX == ((1llu << 48) - 1llu))
#		define OCTET_WORD 6
#		if   (OCTET_CHAR == 1)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 6
#			define WORD_SIZE	 6lu
#			define MULT_WORD_SIZE(X) ((X) * 6lu)
#			define DIV_WORD_SIZE(X)  ((X) / 6lu)
#			define REM_WORD_SIZE(X)  ((X) % 6lu)
#		elif (OCTET_CHAR == 2)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 3
#			define WORD_SIZE	 3lu
#			define MULT_WORD_SIZE(X) ((X) * 3lu)
#			define DIV_WORD_SIZE(X)  ((X) / 3lu)
#			define REM_WORD_SIZE(X)  ((X) % 3lu)
#		elif (OCTET_CHAR == 3)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 2
#			define WORD_SIZE	 2lu
#			define MULT_WORD_SIZE(X) ((X) << 1)
#			define DIV_WORD_SIZE(X)  ((X) >> 1)
#			define REM_WORD_SIZE(X)  ((X) & 1lu)
#		elif (OCTET_CHAR == 6)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 1
#			define WORD_SIZE	 1lu
#			define MULT_WORD_SIZE(X) (X)
#			define DIV_WORD_SIZE(X)  (X)
#			define REM_WORD_SIZE(X)  (0lu)
#		else
#			define HAVE_WORD_ATTRS	 0
#			undef  WORD_WIDTH
#			undef  WORD_SIZE
#			undef  MULT_WORD_SIZE
#			undef  DIV_WORD_SIZE
#			undef  REM_WORD_SIZE
#		endif /* if (OCTET_CHAR == 1) */
#	elif (WORD_MAX == ((1llu << 40) - 1llu))
#		define OCTET_WORD 5
#		if   (OCTET_CHAR == 1)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 5
#			define WORD_SIZE	 5lu
#			define MULT_WORD_SIZE(X) ((X) * 5lu)
#			define DIV_WORD_SIZE(X)  ((X) / 5lu)
#			define REM_WORD_SIZE(X)  ((X) % 5lu)
#		elif (OCTET_CHAR == 5)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 1
#			define WORD_SIZE	 1lu
#			define MULT_WORD_SIZE(X) (X)
#			define DIV_WORD_SIZE(X)  (X)
#			define REM_WORD_SIZE(X)  (0lu)
#		else
#			define HAVE_WORD_ATTRS	 0
#			undef  WORD_WIDTH
#			undef  WORD_SIZE
#			undef  MULT_WORD_SIZE
#			undef  DIV_WORD_SIZE
#			undef  REM_WORD_SIZE
#		endif /* if (OCTET_CHAR == 1) */
#	elif (WORD_MAX == UINT32_MAX)
#		define OCTET_WORD 4
#		if   (OCTET_CHAR == 1)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 4
#			define WORD_SIZE	 4lu
#			define MULT_WORD_SIZE(X) ((X) << 2)
#			define DIV_WORD_SIZE(X)  ((X) >> 2)
#			define REM_WORD_SIZE(X)  ((X) & 3lu)
#		elif (OCTET_CHAR == 2)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 2
#			define WORD_SIZE	 2lu
#			define MULT_WORD_SIZE(X) ((X) << 1)
#			define DIV_WORD_SIZE(X)  ((X) >> 1)
#			define REM_WORD_SIZE(X)  ((X) & 1lu)
#		elif (OCTET_CHAR == 4)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 1
#			define WORD_SIZE	 1lu
#			define MULT_WORD_SIZE(X) (X)
#			define DIV_WORD_SIZE(X)  (X)
#			define REM_WORD_SIZE(X)  (0lu)
#		else
#			define HAVE_WORD_ATTRS	 0
#			undef  WORD_WIDTH
#			undef  WORD_SIZE
#			undef  MULT_WORD_SIZE
#			undef  DIV_WORD_SIZE
#			undef  REM_WORD_SIZE
#		endif /* if (OCTET_CHAR == 1) */
#	elif (WORD_MAX == ((1llu << 24) - 1llu))
#		define OCTET_WORD 3
#		if   (OCTET_CHAR == 1)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 3
#			define WORD_SIZE	 3lu
#			define MULT_WORD_SIZE(X) ((X) * 3lu)
#			define DIV_WORD_SIZE(X)  ((X) / 3lu)
#			define REM_WORD_SIZE(X)  ((X) % 3lu)
#		elif (OCTET_CHAR == 3)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 1
#			define WORD_SIZE	 1lu
#			define MULT_WORD_SIZE(X) (X)
#			define DIV_WORD_SIZE(X)  (X)
#			define REM_WORD_SIZE(X)  (0lu)
#		else
#			define HAVE_WORD_ATTRS	 0
#			undef  WORD_WIDTH
#			undef  WORD_SIZE
#			undef  MULT_WORD_SIZE
#			undef  DIV_WORD_SIZE
#			undef  REM_WORD_SIZE
#		endif /* if (OCTET_CHAR == 1) */
#	elif (WORD_MAX == UINT16_MAX)
#		define OCTET_WORD 2
#		if   (OCTET_CHAR == 1)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 2
#			define WORD_SIZE	 2lu
#			define MULT_WORD_SIZE(X) ((X) << 1)
#			define DIV_WORD_SIZE(X)  ((X) >> 1)
#			define REM_WORD_SIZE(X)  ((X) & 1lu)
#		elif (OCTET_CHAR == 2)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 1
#			define WORD_SIZE	 1lu
#			define MULT_WORD_SIZE(X) (X)
#			define DIV_WORD_SIZE(X)  (X)
#			define REM_WORD_SIZE(X)  (0lu)
#		else
#			define HAVE_WORD_ATTRS	 0
#			undef  WORD_WIDTH
#			undef  WORD_SIZE
#			undef  MULT_WORD_SIZE
#			undef  DIV_WORD_SIZE
#			undef  REM_WORD_SIZE
#		endif /* if (OCTET_CHAR == 1) */
#	elif (WORD_MAX == UINT8_MAX)
#		define OCTET_WORD 1
#		if   (OCTET_CHAR == 1)
#			define HAVE_WORD_ATTRS	 1
#			define WORD_WIDTH	 1
#			define WORD_SIZE	 1lu
#			define MULT_WORD_SIZE(X) (X)
#			define DIV_WORD_SIZE(X)  (X)
#			define REM_WORD_SIZE(X)  (0lu)
#		else
#			define HAVE_WORD_ATTRS	 0
#			undef  WORD_WIDTH
#			undef  WORD_SIZE
#			undef  MULT_WORD_SIZE
#			undef  DIV_WORD_SIZE
#			undef  REM_WORD_SIZE
#		endif /* if (OCTET_CHAR == 1) */
#	endif /* if (WORD_MAX == UINT64_MAX) */
#else
#			define HAVE_WORD_ATTRS	 0
#			undef  OCTET_WORD
#			undef  WORD_WIDTH
#			undef  WORD_SIZE
#			undef  MULT_WORD_SIZE
#			undef  DIV_WORD_SIZE
#			undef  REM_WORD_SIZE
#endif /* if HAVE_CHAR_ATTRS */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS */

#endif /* ifndef MYSQL_SEED_UTILS_WORD_ATTRS_H_ */
