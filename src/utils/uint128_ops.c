#include "utils/uint128_ops.h"


/* global constants
 * ────────────────────────────────────────────────────────────────────────── */
const uint128_t UINT128_MAX = UINT128_INITIALIZER(UINT64_MAX, UINT64_MAX);

extern inline void
uint128_add(uint128_t *const restrict acc,
	    const uint128_t *const restrict add);

extern inline void
uint128_mult(uint128_t *const restrict acc,
	     const uint128_t *const restrict mult);

extern inline void
uint128_fma(uint128_t *const restrict acc,
	    const uint128_t *const restrict mult,
	    const uint128_t *const restrict add);

extern inline void
uint128_xor(uint128_t *const restrict acc,
	    const uint128_t *const restrict other);
