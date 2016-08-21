#ifndef MYSQL_SEED_RANDOM_RANDOM_H_
#define MYSQL_SEED_RANDOM_RANDOM_H_

/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <time.h>			/* unique seed */
#include <stdbool.h>			/* true, false */
#include "random/pcg_random.h"		/* psuedorandom number generator */
#include "memory/memory_swap.h"		/* memory swap utils, utils/utils.h */
#include "time/time_utils.h"		/* time_report */


/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */

/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
typedef pcg32_random_t rng32_t;
typedef pcg64_random_t rng64_t;



/* global variables
 * ────────────────────────────────────────────────────────────────────────── */
extern rng32_t glob_rng32; /* global random number generator state */
extern rng64_t glob_rng64; /* global random number generator state */

/* constructors, destructors
 * ────────────────────────────────────────────────────────────────────────── */
inline bool
random_constructor(const char *restrict *const restrict failure)
{
	time_t now;
	const bool success = time_report(&now,
					 failure);

	if (success) {
		const uint64_t seed64 = (const uint64_t) time;
		const uint32_t seed32 = (const uint32_t) seed64;

		pcg32_srandom_r(&glob_rng32,
				&seed32);

		pcg64_srandom_r(&glob_rng64,
				&seed64);
	}

	return success;
}


inline uint32_t
random_uint32(void)
{
	return pcg32_random_r(&glob_rng32);
}

inline uint64_t
random_uint64(void)
{
	return pcg64_random_r(&glob_rng64);
}

inline bool
coin_flip(void)
{
	return (bool) (random_uint32() & 1u);
}

inline uint32_t
do_random_uint32_upto(const uint32_t valid_limit,
		      const uint32_t range_length)
{
	uint32_t random;

	do {
		random = random_uint32();
	} while (random > valid_limit);

	return (uint32_t) (random % range_length);
}

inline uint32_t
random_uint32_upto(const uint32_t rbound)
{
	const uint32_t range_length = rbound + 1u;

	return do_random_uint32_upto(UINT32_MAX - (UINT32_MAX % range_length),
				     range_length);
}

inline int32_t
random_int32_scaled(const uint32_t delta,
		    const int32_t offset)
{
	return ((int32_t) random_uint32_upto(delta)) + offset;
}

inline int32_t
random_int32_in_range(const int32_t lbound,
		      const int32_t rbound)
{
	return random_int32_scaled((const uint32_t) (rbound - lbound),
				   lbound);
}

inline double
random_dbl_upto(const double rbound)
{
	return (((double) random_uint64()) / ((double) UINT64_MAX)) * rbound;
}

inline double
random_dbl_scaled(const double delta,
		  const double offset)
{
	return random_dbl_upto(delta) + offset;
}

inline double
random_dbl_in_range(const double lbound,
		    const double rbound)
{
	return random_dbl_scaled(rbound - lbound,
				 lbound);
}

inline void
shuffle_array_by_width(void *const restrict array,
		       const uint32_t length,
		       const size_t width)
{
	Width1 buffer[width];
	uint32_t i_old, i_new;
	size_t o_old, o_new;


	Width1 *const bytes = (Width1 *) array;
	const uint32_t i_last	= length - 1u;

	for (i_old = 0u, o_old = 0l; i_old < i_last; ++i_old, o_old += width) {

		i_new = random_uint_upto(i_last - i_old);
		o_new = (i_old + i_new) * width;

		memory_swap_buffer(&bytes[o_old],
				   &bytes[o_new],
				   &buffer[0l],
				   width);
	}
}

void
shuffle_array_by_swap(void *const restrict array,
		      const uint32_t length,
		      const size_t width,
		      MemorySwap *swap)
{
	uint32_t i_old, i_new;
	size_t o_old, o_new;

	Width1 *const bytes = (Width1 *) array;
	const uint32_t i_last	= length - 1u;

	for (i_old = 0u, o_old = 0l; i_old < i_last; ++i_old, o_old += width) {

		i_new = random_uint_upto(i_last - i_old);
		o_new = (i_old + i_new) * width;

		swap(&bytes[o_old],
		     &bytes[o_new]);
	}
}

inline void
shuffle_array(void *const restrict array,
	      const uint32_t length,
	      const size_t width)
{
	if (length == 0u)
		return;

	MemorySwap *swap = assign_memory_swap(width);

	if (swap == NULL)
		shuffle_array_by_width(array,
				       length,
				       width);
	else
		shuffle_array_by_swap(array,
				      length,
				      width,
				      swap);
}

inline void
init_random_int32_array(int32_t *const restrict array,
			const size_t length)
{
	for (size_t i = 0lu; i < length; ++i)
		array[i] = (int32_t) random_uint32();
}

inline int32_t *
create_random_int32_array(const size_t length)
{
	int32_t *const restrict array = malloc(sizeof(int32_t) * length);

	if (array != NULL)
		init_random_int_array(array,
				      length);

	return array;
}


inline void
init_random_int32_array_in_range(int32_t *const restrict array,
				 const size_t length,
				 const int32_t lbound,
				 const int32_t rbound)
{
	for (size_t i = 0lu; i < length; ++i)
		array[i] = random_int32_in_range(lbound,
						 rbound);
}

inline int32_t *
create_random_int32_array_in_range(const size_t length,
				   const int32_t lbound,
				   const int32_t rbound)
{
	int32_t *const restrict array = malloc(sizeof(int32_t) * length);

	if (array != NULL)
		init_random_int32_array_in_range(array,
						 length,
						 lbound,
						 rbound);

	return array;
}

#endif /* ifndef MYSQL_SEED_RANDOM_RANDOM_H_ */
