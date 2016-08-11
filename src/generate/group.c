#include "generate/group.h"

extern inline double
groups_linear_slope(const size_t group_count,
		    const size_t row_count);

extern inline double
groups_logarithmic_scale(const size_t group_count,
			 const size_t row_count);

/* group[i] = slope * i + 1.0		(group[0] = 1) */
void
partition_groups_linear(size_t *restrict group,
			const size_t group_count,
			const size_t row_count)
{
	if (group_count == 1lu) {
		*group = row_count;
		return;
	}

	const double slope = groups_linear_slope(group_count,
						 row_count);

	size_t sum_rows = 1lu;

	double group_acc = 1.0;

	size_t *const restrict last = group + group_count - 1lu;

	*group = 1lu;

	do {
		++group;

		group_acc += slope;

		*group = (size_t) group_acc;

		sum_rows += *group;

	} while (group < last);

	*group += (row_count - sum_rows);
}

/* group[i] = log(scale * i + M_E)	(group[0] = 1) */
void
partition_groups_logarithmic(size_t *restrict group,
			     const size_t group_count,
			     const size_t row_count)
{
}
