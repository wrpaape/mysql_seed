#ifndef MYSQL_SEED_UTILS_CHAR_ATTRS_H_
#define MYSQL_SEED_UTILS_CHAR_ATTRS_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <limits.h>	/* CHAR_BIT */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#if   (CHAR_BIT == 8)
#	define HAVE_CHAR_ATTRS 1
#	define OCTET_CHAR      1
#elif (CHAR_BIT == 16)
#	define HAVE_CHAR_ATTRS 1
#	define OCTET_CHAR      2
#elif (CHAR_BIT == 24)
#	define HAVE_CHAR_ATTRS 1
#	define OCTET_CHAR      3
#elif (CHAR_BIT == 32)
#	define HAVE_CHAR_ATTRS 1
#	define OCTET_CHAR      4
#elif (CHAR_BIT == 40)
#	define HAVE_CHAR_ATTRS 1
#	define OCTET_CHAR      5
#elif (CHAR_BIT == 48)
#	define HAVE_CHAR_ATTRS 1
#	define OCTET_CHAR      6
#elif (CHAR_BIT == 56)
#	define HAVE_CHAR_ATTRS 1
#	define OCTET_CHAR      7
#elif (CHAR_BIT == 64)
#	define HAVE_CHAR_ATTRS 1
#	define OCTET_CHAR      8
#else
#	define HAVE_CHAR_ATTRS 0
#	undef  OCTET_CHAR
#endif /* if (CHAR_BIT == 8) */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS */

#endif /* ifndef MYSQL_SEED_UTILS_CHAR_ATTRS_H_ */
