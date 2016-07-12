#include "random/random.h"

extern rng_t glob_rng; /* global random number generator state */

void
glob_rng_ctor(void)
{
	pcg32_srandom_r(&glob_rng, time(NULL), (intptr_t) &glob_rng);
}
extern inline void
glob_rng_init(void);
extern inline urint_t
random_uint(void);
extern inline bool
coin_flip(void);
extern inline urint_t
random_uint_upto(const urint_t rbound);
extern inline rint_t
random_int_in_range(const rint_t lbound,
		    const rint_t rbound);
extern inline double
random_dbl_upto(const double rbound);
extern inline double
random_dbl_in_range(const double lbound,
		    const double rbound);
extern inline void
init_random_int_array(rint_t *const restrict array,
		      const size_t length);
extern inline rint_t *
create_random_int_array(const size_t length);
extern inline void
init_random_int_array_in_range(rint_t *const restrict array,
			       const size_t length,
			       const rint_t lbound,
			       const rint_t rbound);
extern inline rint_t *
create_random_int_array_in_range(const size_t length,
				 const rint_t lbound,
				 const rint_t rbound);
extern inline void
shuffle_array(void *const restrict array,
	      const urint_t length,
	      const size_t width);
void
shuffle_array_by_width(void *const restrict array,
		       const urint_t length,
		       const size_t width)
{
	Width1 buffer[width];
	urint_t i_old, i_new;
	size_t o_old, o_new;


	Width1 *const bytes = (Width1 *) array;
	const urint_t i_last	= length - 1u;

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
		      const urint_t length,
		      const size_t width,
		      MemorySwap *swap)
{
	urint_t i_old, i_new;
	size_t o_old, o_new;

	Width1 *const bytes = (Width1 *) array;
	const urint_t i_last	= length - 1u;

	for (i_old = 0u, o_old = 0l; i_old < i_last; ++i_old, o_old += width) {

		i_new = random_uint_upto(i_last - i_old);
		o_new = (i_old + i_new) * width;

		swap(&bytes[o_old],
		     &bytes[o_new]);
	}
}
