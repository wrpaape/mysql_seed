#ifndef MYSQL_SEED_UTILS_TYPES_UINT128_OPS_H_
#define MYSQL_SEED_UTILS_TYPES_UINT128_OPS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "utils/types/uint128.h"	/* uint128_t, stdint */


/* macros
 * ────────────────────────────────────────────────────────────────────────── */
#if HAVE_128_BIT_OPERATIONS
#	define UINT128_INITIALIZER(LOW, HIGH)				\
	(((uint128_t) LOW) | (((uint128_t) HIGH) << 64u))

#else
#	define UINT128_INITIALIZER(LOW, HIGH)				\
	{ .low = (uint64_t) LOW, .high = (uint64_t) HIGH }
#endif /* if HAVE_128_BIT_OPERATIONS */


/* global constants
 * ────────────────────────────────────────────────────────────────────────── */
extern const uint128_t UINT128_MAX;

inline void
uint128_add(uint128_t *const restrict acc,
	    const uint128_t *const restrict add)
{
#if HAVE_128_BIT_OPERATIONS
	*acc += *add;
#else
	const uint64_t sum_low = acc->low + add->low;

	acc->high += add->high; /* overflow is discarded */

	if (sum_low < acc->low)
		++(acc->high);

	acc->low = sum_low;
#endif /* if HAVE_128_BIT_OPERATIONS */
}

inline void
uint128_mult(uint128_t *const restrict acc,
	     const uint128_t *const restrict mult)
{
#if HAVE_128_BIT_OPERATIONS
	*acc *= *mult;
#else
	uint64_t acc_low;
	uint64_t acc_high;
	uint64_t mult_low;
	uint64_t mult_high;
	uint64_t product;

	acc_low	  = (uint64_t) ((uint32_t) acc->low);
	acc_high  = acc->low >> 32u;
	mult_low  = (uint64_t) ((uint32_t) mult->low);
	mult_high = mult->low >> 32u;

	product = acc_low * mult_low;

	acc->low = (uint64_t) ((uint32_t) product);

	product >>= 32u;

	product += (acc_high * mult_high);

	acc->low |= (product << 32u);

	product >>= 32u;

	acc_low	  = (uint64_t) ((uint32_t) acc->high);
	acc_high  = acc->high >> 32u;
	mult_low  = (uint64_t) ((uint32_t) mult->high);
	mult_high = mult->high >> 32u;

	product += (acc_low * mult_low);

	acc->high = (uint64_t) ((uint32_t) product);

	product >>= 32u;

	product += (uint64_t) (acc_high * mult_high);

	acc->high |= (product << 32u); /* overflow is discarded */
#endif /* if HAVE_128_BIT_OPERATIONS */
}

#include <stdio.h>

inline void
uint128_fma(uint128_t *const restrict acc,
	    const uint128_t *const restrict mult,
	    const uint128_t *const restrict add)
{
#if HAVE_128_BIT_OPERATIONS
	*acc = ((*acc) * (*mult)) + (*add);
#else
	uint128_mult(acc,
		     mult);
	uint128_add(acc,
		    add);
#endif /* if HAVE_128_BIT_OPERATIONS */
}

inline void
uint128_xor(uint128_t *const restrict acc,
	    const uint128_t *const restrict other)
{
#if HAVE_128_BIT_OPERATIONS
	*acc ^= *other;
#else
	acc->low  ^= other->low;
	acc->high ^= other->high;
#endif /* if HAVE_128_BIT_OPERATIONS */
}


#endif /* ifndef MYSQL_SEED_UTILS_TYPES_UINT128_OPS_H_ */
