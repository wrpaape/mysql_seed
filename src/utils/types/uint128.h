#ifndef MYSQL_SEED_UTILS_TYPES_UINT128_H_
#define MYSQL_SEED_UTILS_TYPES_UINT128_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include <stdint.h>	/* uint64_t, UINT64_MAX */

/* #ifdef __SIZEOF_INT128__ */
#if 0
#	define HAVE_128_BIT_OPERATIONS 1
#else
#	define HAVE_128_BIT_OPERATIONS 0
#endif /* ifdef __SIZEOF_INT128__ */


/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
#if HAVE_128_BIT_OPERATIONS
	typedef __uint128_t uint128_t;
#else
	typedef struct __uint128 {
		uint64_t low;
		uint64_t high;
	} uint128_t;
#endif /* if HAVE_128_BIT_OPERATIONS */

#endif /* ifndef MYSQL_SEED_UTILS_TYPES_UINT128_H_ */
