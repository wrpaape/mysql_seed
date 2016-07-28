#ifndef MYSQL_SEED_STRING_SIZE_STRING_ATTRS_H_
#define MYSQL_SEED_STRING_SIZE_STRING_ATTRS_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdint.h>	/* SIZE_MAX */

#if   (SIZE_MAX == UINT64_MAX)
#	define HAVE_SIZE_STRING_ATTRS	1
#	define DIGIT_COUNT_SIZE_MAX	20u
#	define DIGIT_STRING_SIZE_MAX	"18446744073709551615"
#elif (SIZE_MAX == UINT32_MAX)
#	define HAVE_SIZE_STRING_ATTRS	1
#	define DIGIT_COUNT_SIZE_MAX	10u
#	define DIGIT_STRING_SIZE_MAX	"4294967295"
#elif (SIZE_MAX == UINT16_MAX)
#	define HAVE_SIZE_STRING_ATTRS	1
#	define DIGIT_COUNT_SIZE_MAX	5u
#	define DIGIT_STRING_SIZE_MAX	"65535"
#else
#	define HAVE_SIZE_STRING_ATTRS	0
#	undef  DIGIT_COUNT_SIZE_MAX
#	undef  DIGIT_STRING_SIZE_MAX
#endif	/* if (SIZE_MAX == UINT64_MAX) */

#endif /* ifndef MYSQL_SEED_STRING_SIZE_STRING_ATTRS_H_ */
