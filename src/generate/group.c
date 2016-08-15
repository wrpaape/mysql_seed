#include "generate/group.h"

extern inline double
groups_linear_slope(const size_t group_count,
		    const size_t row_count);

/* extern inline double */
/* groups_exponential_scale(const size_t group_count, */
/* 			 const size_t row_count); */

/* group[i] = slope * i + 1.0		(group[0] = 1) */
void *
partition_groups_linear(size_t *restrict group,
			const size_t group_count,
			const size_t row_count)
{
	const double slope = groups_linear_slope(group_count,
						 row_count);

	size_t *const restrict from  = group;
	size_t *const restrict until = group + group_count;

	double group_acc = 1.0;
	size_t sum_rows  = 1lu;

	*group = 1lu;
	++group;

	while (group < until) {
		group_acc += slope;

		*group = (size_t) group_acc;

		sum_rows += *group;

		++group;
	}

	/* spread undershoot evenly, with leftovers padding groups upfront */
	const size_t undershoot = row_count - sum_rows;


	const size_t undershoot_div = undershoot / group_count;
	const size_t undershoot_rem = undershoot % group_count;

	const size_t group_extra = undershoot_div + 1lu;

	const size_t *const restrict extra_until = from + undershoot_rem;

	for (group = from; group < extra_until; ++group)
		*group += group_extra;

	if (undershoot_div > 0lu) {
		do {
			*group += undershoot_div;
			++group;
		} while (group < until);
	}

	return (void *) until;
}

void *
partition_groups_even(size_t *restrict group,
		      const size_t group_count,
		      const size_t row_count)
{
	size_t *const restrict until = group + group_count;

	const size_t group_div = row_count / group_count;
	const size_t group_rem = row_count % group_count;

	const size_t *const restrict extra_until = group + group_rem;

	const size_t group_extra = group_div + 1lu;

	while (group < extra_until) {
		*group = group_extra;
		++group;
	}

	do {
		*group = group_div;
		++group;
	} while (group < until);

	return (void *) until;
}

/* group[i] = e^(scale * i)		(group[0] = 1) */
/* size_t */
/* partition_groups_exponential(size_t *restrict group, */
/* 			     const size_t group_count, */
/* 			     const size_t row_count) */
/* { */
/* 	if (group_count == 1lu) { */
/* 		*group = row_count; */
/* 		return; */
/* 	} */
/* } */
