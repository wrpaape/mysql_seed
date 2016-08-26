#include "random/random.h"

/* global variables
 * ────────────────────────────────────────────────────────────────────────── */
rng32_t glob_rng32; /* global random number generator state */
rng64_t glob_rng64; /* global random number generator state */


/* constructors, destructors
 * ────────────────────────────────────────────────────────────────────────── */
extern inline bool
random_32_constructor(const char *restrict *const restrict failure);
extern inline bool
random_64_constructor(const char *restrict *const restrict failure);
extern inline bool
random_32_64_constructor(const char *restrict *const restrict failure);

extern inline uint32_t
random_uint32(void);
extern inline uint64_t
random_uint64(void);

extern inline bool
coin_flip(void);

extern inline uint32_t
random_uint32_threshold(const uint32_t span);
extern inline uint32_t
random_uint32_bound(const uint32_t threshold,
		    const uint32_t span);
extern inline uint64_t
random_uint64_threshold(const uint64_t span);
extern inline uint64_t
random_uint64_bound(const uint64_t threshold,
		    const uint64_t span);

extern inline uint32_t
random_uint32_from(const uint32_t from);
extern inline uint64_t
random_uint64_from(const uint64_t from);
extern inline int32_t
random_int32_from(const int32_t from);
extern inline int64_t
random_int64_from(const int64_t from);

extern inline uint32_t
random_uint32_upto(const uint32_t upto);
extern inline uint64_t
random_uint64_upto(const uint64_t upto);
extern inline int32_t
random_int32_upto(const int32_t upto);
extern inline int64_t
random_int64_upto(const int64_t upto);

extern inline int32_t
random_int32_bound_offset(const uint32_t threshold,
			  const uint32_t span,
			  const int32_t offset);
extern inline int32_t
random_int32_in_range(const int32_t lbound,
		      const int32_t rbound);

extern inline double
random_dbl_upto(const double rbound);
extern inline double
random_dbl_bound_offset(const double delta,
			const double offset);
extern inline double
random_dbl_in_range(const double lbound,
		    const double rbound);
extern inline void
shuffle_array_by_width(void *const restrict array,
		       const uint32_t length,
		       const size_t width);
extern inline void
shuffle_array_by_swap(void *const restrict array,
		      const uint32_t length,
		      const size_t width,
		      MemorySwap *const swap);
extern inline void
shuffle_array(void *const restrict array,
	      const uint32_t length,
	      const size_t width);
extern inline void
init_random_int32_array(int32_t *const restrict array,
			const size_t length);
extern inline int32_t *
create_random_int32_array(const size_t length);
extern inline void
init_random_int32_array_in_range(int32_t *const restrict array,
				 const size_t length,
				 const int32_t lbound,
				 const int32_t rbound);
extern inline int32_t *
create_random_int32_array_in_range(const size_t length,
				   const int32_t lbound,
				   const int32_t rbound);
