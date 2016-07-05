#ifndef MYSQL_SEED_STRING_PTR_STRING_ATTRS_H_
#define MYSQL_SEED_STRING_PTR_STRING_ATTRS_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <limits.h>	/* UINTPTR_MAX */

#if   (UINTPTR_MAX == UINT64_MAX)
#	define HAVE_PTR_STRING_ATTRS	1
#	define DIGIT_COUNT_UINTPTR_MAX	20u
#	define LENGTH_MAX_POINTER_ID	10u
#elif (UINTPTR_MAX == UINT32_MAX)
#	define HAVE_PTR_STRING_ATTRS	1
#	define DIGIT_COUNT_UINTPTR_MAX	10u
#	define LENGTH_MAX_POINTER_ID	5u
#elif (UINTPTR_MAX == UINT16_MAX)
#	define HAVE_PTR_STRING_ATTRS	1
#	define DIGIT_COUNT_UINTPTR_MAX	5u
#	define LENGTH_MAX_POINTER_ID	3u
#elif (UINTPTR_MAX == UINT8_MAX)
#	define HAVE_PTR_STRING_ATTRS	1
#	define DIGIT_COUNT_UINTPTR_MAX	3u
#	define LENGTH_MAX_POINTER_ID	2u
#else
#	define HAVE_PTR_STRING_ATTRS	0
#	undef  DIGIT_COUNT_UINTPTR_MAX
#	undef  LENGTH_MAX_POINTER_ID
#endif	/* if (UINTPTR_MAX == UINT64_MAX) */

#endif /* ifndef MYSQL_SEED_STRING_PTR_STRING_ATTRS_H_ */
