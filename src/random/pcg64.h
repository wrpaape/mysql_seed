#ifndef MYSQL_SEED_RANDOM_PCG64_H_
#define MYSQL_SEED_RANDOM_PCG64_H_

#ifndef __SIZEOF_INT128__
#	error "128-bit operations required for 64-bit pcg random support"
#endif /* ifndef __SIZEOF_INT128__ */

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "bitwise/bitwise_utils.h" /* uint64_rotate_right */


/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
typedef __uint128_t uint128_t;

typedef uint128_t pcg64s_random_t;

struct pcg_state_setseq_128 {
	uint128_t state;
	uint128_t increment;
};

typedef struct pcg_state_setseq_128 pcg64_random_t;


#define PCG_128BIT_CONSTANT(HIGH, LOW) ((((uint128_t) HIGH) << 64) + LOW)

#define PCG_DEFAULT_MULTIPLIER_128				\
PCG_128BIT_CONSTANT(2549297995355413924llu, 4865540595714422341llu)

#define PCG_DEFAULT_INCREMENT_128				\
PCG_128BIT_CONSTANT(6364136223846793005llu, 1442695040888963407llu)



inline void
pcg_setseq_128_step_r(struct pcg_state_setseq_128 *const restrict rng)
{
	rng->state = (rng->state * PCG_DEFAULT_MULTIPLIER_128) + rng->increment;
}

inline void
pcg_oneseq_128_step_r(pcg64s_random_t *const restrict rng)
{
	*rng = ((*rng) * PCG_DEFAULT_MULTIPLIER_128)
	     + PCG_DEFAULT_INCREMENT_128;
}

inline uint64_t
pcg_output_xsl_rr_128_64(const uint128_t state)
{
	return uint64_rotate_right(((const uint64_t) (state >> 64u))
				   ^ ((const uint64_t) state),
				   state >> 122u);
}

inline void
pcg64_srandom_r(struct pcg_state_setseq_128 *const restrict rng,
		const uint128_t initstate,
		const uint128_t initseq)
{
	rng->state     = 0llu;
	rng->increment = (initseq << 1u) | 1llu;

	pcg_setseq_128_step_r(rng);

	rng->state += initstate;

	pcg_setseq_128_step_r(rng);
}

inline uint64_t
pcg64_random_r(struct pcg_state_setseq_128 *const restrict rng)
{
	pcg_setseq_128_step_r(rng);

	return pcg_output_xsl_rr_128_64(rng->state);
}


#endif /* ifndef MYSQL_SEED_RANDOM_PCG64_H_
