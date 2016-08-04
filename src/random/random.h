#ifndef MYSQL_SEED_RANDOM_RANDOM_H_
#define MYSQL_SEED_RANDOM_RANDOM_H_

/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <time.h>			/* unique seed */
#include <stdbool.h>			/* true, false */
#include "memory/memory_swap.h"		/* memory swap utils, <utils/utils.h> */
#include "random/random_types.h"	/* rng_t, rint_t, ruint_t */


/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */

rng_t glob_rng; /* global random number generator state */

void
glob_rng_ctor(void)
__attribute__((constructor (101)));

inline void
glob_rng_init(void)
{
	pcg32_srandom_r(&glob_rng, time(NULL), (intptr_t) &glob_rng);
}

inline urint_t
random_uint(void)
{
	return pcg32_random_r(&glob_rng);
}

inline bool
coin_flip(void)
{
	return (bool) (random_uint() & 1u);
}

inline urint_t
random_uint_upto(const urint_t rbound)
{
	const urint_t range_length = rbound + 1u;
	const urint_t valid_limit  = URINT_MAX - (URINT_MAX % range_length);

	urint_t random;

	do {
		random = random_uint();

	} while (random > valid_limit);

	return (urint_t) (random % range_length);
}

inline rint_t
random_int_in_range(const rint_t lbound,
		    const rint_t rbound)
{

	const urint_t range_length = rbound - lbound + 1u;
	const urint_t valid_limit  = URINT_MAX - (URINT_MAX % range_length);

	urint_t random;

	do {
		random = random_uint();

	} while (random > valid_limit);

	return ((rint_t) (random % range_length)) + lbound;
}

inline double
random_dbl_upto(const double rbound)
{
	return (((double) random_uint())
		/ ((double) URINT_MAX)) * rbound;
}

inline double
random_dbl_in_range(const double lbound,
		    const double rbound)
{
	return ((((double) random_uint()) / ((double) URINT_MAX))
	       * (rbound - lbound))
	       + lbound;
}

void
shuffle_array_by_width(void *const restrict array,
		       const urint_t length,
		       const size_t width);

void
shuffle_array_by_swap(void *const restrict array,
		      const urint_t length,
		      const size_t width,
		      MemorySwap *swap);

inline void
shuffle_array(void *const restrict array,
	      const urint_t length,
	      const size_t width)
{
	if (length == 0u)
		return;

	MemorySwap *swap = assign_memory_swap(width);

	if (swap == NULL)
		shuffle_array_by_width(array, length, width);
	else
		shuffle_array_by_swap(array, length, width, swap);
}

inline void
init_random_int_array(rint_t *const restrict array,
		      const size_t length)
{
	for (size_t i = 0lu; i < length; ++i)
		array[i] = (rint_t) random_uint();
}

inline rint_t *
create_random_int_array(const size_t length)
{
	rint_t *const restrict array = malloc(sizeof(rint_t) * length);

	if (array != NULL)
		init_random_int_array(array, length);

	return array;
}


inline void
init_random_int_array_in_range(rint_t *const restrict array,
			       const size_t length,
			       const rint_t lbound,
			       const rint_t rbound)
{
	for (size_t i = 0lu; i < length; ++i)
		array[i] = random_int_in_range(lbound, rbound);
}

inline rint_t *
create_random_int_array_in_range(const size_t length,
				 const rint_t lbound,
				 const rint_t rbound)
{
	rint_t *const restrict array = malloc(sizeof(rint_t) * length);

	if (array != NULL)
		init_random_int_array_in_range(array, length, lbound, rbound);

	return array;
}

#endif /* ifndef MYSQL_SEED_RANDOM_RANDOM_H_ */
