#ifndef MYSQL_SEED_GENERATE_GROUP_H_
#define MYSQL_SEED_GENERATE_GROUP_H_


/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include <math.h>	/* log */
#include <stddef.h>	/* size_t */

/* macro constants
 * ────────────────────────────────────────────────────────────────────────── */
#if LARGE_UPTO_MAX
#	define GROUPS_EXP_SCALE_MAX_CEIL 24.0
#else
#	define GROUPS_EXP_SCALE_MAX_CEIL 11.7
#endif /* if LARGE_UPTO_MAX */


/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
typedef size_t *
GroupPartitioner(size_t *restrict group,
		 const size_t group_count,
		 const size_t row_count);

inline double
groups_linear_slope(const size_t group_count,
		    const size_t row_count)
{
	const double group_count_dbl = (double) group_count;

	const double group_max = ((((double) row_count) * 2.0)
				  / group_count_dbl) - 1.0;

	return (group_max - 1.0) / group_count_dbl;
}

size_t *
partition_groups_linear(size_t *restrict group,
			const size_t group_count,
			const size_t row_count);

size_t *
partition_groups_even(size_t *restrict group,
		      const size_t group_count,
		      const size_t row_count);

/* group[i] = e^(scale * i)		(group[0] = 1)
 *
 * 1 ≤ group_count ≤ row_count
 *
 * when group_count = row_count → scale = 0 (flat line)
 *
 * when group_count = 1 → scale = scale_max = ?
 *
 *   ∫ e^(scale * i)di
 *
 *			   i = group_count
 * → e^(scale * i) / scale |                = row_count
 *			   i = 0
 *
 * → row_count = (e^(scale * group_count) - 1) / scale
 *
 * → row_count = (e^scale_max - 1) / scale_max     if (group_count = 1)
 *
 * → when row_count = 1, scale_max = 0
 *
 * → when row_count = UPTO_MAX (small|large), scale_max ≈ 11.5|24
 *
 * → 0 ≤ scale ≤ 11.5|24
 */
/* extern inline double */
/* groups_exponential_scale(const size_t group_count, */
/* 			 const size_t row_count) */
/* { */
/* 	const double group_count_dbl = (double) group_count; */
/* 	const double row_count_dbl   = (double) row_count; */

/* 	double scale; */

/* 	return scale; */
/* } */
/* size_t */
/* partition_groups_exponential(size_t *restrict group, */
/* 			     const size_t group_count, */
/* 			     const size_t row_count); */
#endif /* ifndef MYSQL_SEED_GENERATE_GROUP_H_ */
