#include "random/pcg_random.h"

/* global constants
 * ────────────────────────────────────────────────────────────────────────── */
const uint64_t
PCG_DEFAULT_MULTIPLIER_64 = 6364136223846793005llu;
const uint128_t
PCG_DEFAULT_MULTIPLIER_128 = UINT128_INITIALIZER(2549297995355413924llu,
						 4865540595714422341llu);

/* helper functions
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
pcg32_random_t_init(pcg32_random_t *const restrict rng
		    const uint64_t *const restrict init_seq);
extern inline void
pcg_setseq_64_step_r(struct pcg_state_setseq_64 *const restrict rng);
extern inline void
pcg64_random_t_init(pcg64_random_t *const restrict rng
extern inline void
pcg_setseq_128_step_r(struct pcg_state_setseq_128 *const restrict rng);
extern inline uint64_t
pcg_output_xsl_rr_128_64(const uint128_t *const restrict state);

/* API
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
pcg32_srandom_r(pcg32_random_t *const restrict rng,
		const uint64_t *const restrict init_state,
		const uint64_t *const restrict init_seq);
extern inline uint32_t
pcg32_random_r(pcg32_random_t *const restrict rng);
extern inline void
pcg64_srandom_r(pcg64_random_t *const restrict rng,
		const uint128_t *const restrict init_state,
		const uint128_t *const restrict init_seq);
extern inline uint64_t
pcg64_random_r(pcg64_random_t *const restrict rng);
