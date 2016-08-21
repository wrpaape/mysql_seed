#ifndef MYSQL_SEED_RANDOM_PCG_RANDOM_H_
#define MYSQL_SEED_RANDOM_PCG_RANDOM_H_


/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "bitwise/bitwise_utils.h"	/* uint64|32_rotate_right */
#include "utils/uint128_ops.h"		/* uint128_t, uint128_X */



/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
struct pcg_state_setseq_64 {
	uint64_t state;
	uint64_t increment;
};

typedef struct pcg_state_setseq_64 pcg32_random_t;

struct pcg_state_setseq_128 {
	uint128_t state;
	uint128_t increment;
};

typedef struct pcg_state_setseq_128 pcg64_random_t;



/* global constants
 * ────────────────────────────────────────────────────────────────────────── */
extern const uint64_t PCG_DEFAULT_MULTIPLIER_64;
extern const uint128_t PCG_DEFAULT_MULTIPLIER_128;


/* helper functions
 * ────────────────────────────────────────────────────────────────────────── */
inline void
pcg32_random_t_init(pcg32_random_t *const restrict rng
		    const uint64_t *const restrict init_seq)
{
	rng->state     = 0llu;
	rng->increment = ((*init_seq) << 1u) | 1llu;
}

inline void
pcg_setseq_64_step_r(struct pcg_state_setseq_64 *const restrict rng)
{
	rng->state = (rng->state * PCG_DEFAULT_MULTIPLIER_64) + rng->increment;
}


inline void
pcg64_random_t_init(pcg64_random_t *const restrict rng
		    const uint128_t *const restrict init_seq)
{
#if HAVE_128_BIT_OPERATIONS
	rng->state     = 0llu;
	rng->increment = ((*init_seq) << 1u) | 1llu;
#else
	rng->state.low  = 0llu;
	rng->state.high = 0llu;
	rng->increment.low  = (init_seq->low << 1u) | 1llu;
	rng->increment.high = (init_seq->low >> 63u)
			    | (init_seq->high << 1u)
#endif /* if HAVE_128_BIT_OPERATIONS */
}

inline void
pcg_setseq_128_step_r(struct pcg_state_setseq_128 *const restrict rng)
{
	uint128_fma(&rng->state,
		    &PCG_DEFAULT_MULTIPLIER_128,
		    &rng->increment);
}

inline uint64_t
pcg_output_xsl_rr_128_64(const uint128_t *const restrict state)
{
#if HAVE_128_BIT_OPERATIONS
	const uint64_t value  = ((const uint64_t) *state)
			      ^ ((const uint64_t) ((*state) >> 64u));
	const uint64_t rotate = (const uint64_t) ((*state) >> 122u);
#else
	const uint64_t value  = state->low ^ state->high;
	const uint64_t rotate = state->high >> 58u;
#endif /* if HAVE_128_BIT_OPERATIONS */
	return uint64_rotate_right(value,
				   rotate);
}


/* API
 * ────────────────────────────────────────────────────────────────────────── */
inline void
pcg32_srandom_r(pcg32_random_t *const restrict rng,
		const uint64_t *const restrict init_state,
		const uint64_t *const restrict init_seq)
{
	pcg32_random_t_init(rng,
			    init_seq);

	pcg_setseq_64_step_r(rng);

	rng->state += *init_state;

	pcg_setseq_64_step_r(rng);
}

inline uint32_t
pcg32_random_r(pcg32_random_t *const restrict rng)
{
	const uint64_t state = rng->state;

	pcg_setseq_64_step_r(rng);

	return uint32_rotate_right((uint32_t) (((state >> 18u) ^ state) >> 27u),
				   (uint32_t) (state >> 59u));
}


inline void
pcg64_srandom_r(pcg64_random_t *const restrict rng,
		const uint128_t *const restrict init_state,
		const uint128_t *const restrict init_seq)
{
	pcg64_random_t_init(rng,
			    init_seq);

	pcg_setseq_128_step_r(rng);

	uint128_add(&rng->state,
		    init_state);

	pcg_setseq_128_step_r(rng);
}

inline uint64_t
pcg64_random_r(pcg64_random_t *const restrict rng)
{
	pcg_setseq_128_step_r(rng);

	return pcg_output_xsl_rr_128_64(&rng->state);
}


#endif /* ifndef MYSQL_SEED_RANDOM_PCG_RANDOM_H_
