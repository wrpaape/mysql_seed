#ifndef MYSQL_SEED_GENERATE_GROUP_H_
#define MYSQL_SEED_GENERATE_GROUP_H_


/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include <math.h>	/* log */

extern inline double
groups_linear_slope(const size_t group_count,
		    const size_t row_count)
{
	const double group_count_dbl = (double) group_count;

	const double group_max = ((((double) row_count) * 2.0)
				  / group_count_dbl) - 1.0;

	return (group_max - 1.0) / group_count_dbl;
}

extern inline double
groups_logarithmic_scale(const size_t group_count,
			 const size_t row_count)
{
	double scale;
}

void
partition_groups_linear(size_t *restrict group,
			const size_t group_count,
			const size_t row_count);

void
partition_groups_logarithmic(size_t *restrict group,
			     const size_t group_count,
			     const size_t row_count);


#endif /* ifndef MYSQL_SEED_GENERATE_GROUP_H_ */
