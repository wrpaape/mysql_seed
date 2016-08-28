#include "generate/column_u_integer_random.h"

#define BCUIR_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_u_integer_random")

#define BCUIR_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_u_integer_random_group")

#define BCUIRF_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_u_integer_random_from")

#define BCUIRF_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_u_integer_random_from_group")

#define BCUIRU_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_u_integer_random_upto")

#define BCUIRU_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_u_integer_random_upto_group")

#define BCUIRR_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_u_integer_random_range")

#define BCUIRR_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_u_integer_random_range_group")

/* worker thread entry points */
void
build_column_u_integer_random(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct IntegerRandSpec *const restrict rand_spec
	= &column->spec->type_q.u_integer.rand_spec;

	UGenerator *const gen_unbound = rand_spec->gen.unbound;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t size_est = rand_spec->width_max * row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCUIR_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	char *restrict ptr = column->contents;

	size_t rem_cells;

	do {
		from->cell = ptr;

		rem_cells = from->parent->row_count;

		do {
			ptr = put_uint(ptr,
				       gen_unbound());

			*ptr = '\0';
			++ptr;

			--rem_cells;

		} while (rem_cells > 0lu);

		/* add length of rowspan to row_block total */
		length_lock_increment(&from->parent->total,
				      ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}

void
build_column_u_integer_random_group(void *arg)
{
	size_t rem_cells;
	size_t rem_group;
	char *restrict ptr;
	char *restrict group_u_integer;
	size_t *restrict group;
	PutStringWidth *put_group_u_integer;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct IntegerRandSpec *const restrict rand_spec
	= &column->spec->type_q.u_integer.rand_spec;

	UGenerator *const gen_unbound = rand_spec->gen.unbound;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t group_count = column->spec->grp_spec.count;

	GroupPartitioner *const partition_groups
	= column->spec->grp_spec.partition;

	const size_t size_est = (sizeof(size_t) * group_count)
			      + (rand_spec->width_max * row_count);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCUIR_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	group = (size_t *restrict) column->contents;

	group_u_integer = partition_groups(group,
					 group_count,
					 row_count);

	ptr = put_uint(group_u_integer,
		       gen_unbound());
	*ptr = '\0';
	++ptr;

	put_group_u_integer = PUT_STRING_WIDTH_MAP[ptr - group_u_integer];

	rem_group = *group;

	rem_cells = from->parent->row_count;

	from->cell = ptr;

	while (1) {
		if (rem_cells > rem_group) {
			rem_cells -= (rem_group + 1lu);

			while (rem_group > 0lu) {
				ptr = put_group_u_integer(ptr,
							group_u_integer);
				--rem_group;
			}

			group_u_integer = ptr;

			ptr = put_uint(group_u_integer,
				       gen_unbound());
			*ptr = '\0';
			++ptr;

			put_group_u_integer
			= PUT_STRING_WIDTH_MAP[ptr - group_u_integer];

			++group;

			rem_group = *group - 1lu;

		} else {
			rem_group -= rem_cells;

			while (rem_cells > 0lu) {
				ptr = put_group_u_integer(ptr,
							group_u_integer);
				--rem_cells;
			}

			/* increment row_block length */
			length_lock_increment(&from->parent->total,
					      ptr - from->cell,
					      &column->fail_cl);

			/* skip to rowspan in next row */
			from += col_count;

			if (from >= until)
				break;

			from->cell = ptr;

			rem_cells = from->parent->row_count;
		}
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}

void
build_column_u_integer_random_from(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct IntegerRandSpec *const restrict rand_spec
	= &column->spec->type_q.u_integer.rand_spec;

	const struct BoundOffsetUGeneratorClosure *const restrict from_cl
	= &rand_spec->gen.from;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t size_est = rand_spec->width_max * row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCUIRF_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	char *restrict ptr = column->contents;

	size_t rem_cells;

	do {
		from->cell = ptr;

		rem_cells = from->parent->row_count;

		do {
			ptr = put_uint(ptr,
				       from_cl->generate(&from_cl->params));

			*ptr = '\0';
			++ptr;

			--rem_cells;

		} while (rem_cells > 0lu);

		/* add length of rowspan to row_block total */
		length_lock_increment(&from->parent->total,
				      ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}

void
build_column_u_integer_random_from_group(void *arg)
{
	size_t rem_cells;
	size_t rem_group;
	char *restrict ptr;
	char *restrict group_u_integer;
	size_t *restrict group;
	PutStringWidth *put_group_u_integer;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct IntegerRandSpec *const restrict rand_spec
	= &column->spec->type_q.u_integer.rand_spec;

	const struct BoundOffsetUGeneratorClosure *const restrict from_cl
	= &rand_spec->gen.from;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t group_count = column->spec->grp_spec.count;

	GroupPartitioner *const partition_groups
	= column->spec->grp_spec.partition;

	const size_t size_est = (sizeof(size_t) * group_count)
			      + (rand_spec->width_max * row_count);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCUIRF_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	group = (size_t *restrict) column->contents;

	group_u_integer = partition_groups(group,
					 group_count,
					 row_count);

	ptr = put_uint(group_u_integer,
		       from_cl->generate(&from_cl->params));
	*ptr = '\0';
	++ptr;

	put_group_u_integer = PUT_STRING_WIDTH_MAP[ptr - group_u_integer];

	rem_group = *group;

	rem_cells = from->parent->row_count;

	from->cell = ptr;

	while (1) {
		if (rem_cells > rem_group) {
			rem_cells -= (rem_group + 1lu);

			while (rem_group > 0lu) {
				ptr = put_group_u_integer(ptr,
							group_u_integer);
				--rem_group;
			}

			group_u_integer = ptr;

			ptr = put_uint(group_u_integer,
				       from_cl->generate(&from_cl->params));
			*ptr = '\0';
			++ptr;

			put_group_u_integer
			= PUT_STRING_WIDTH_MAP[ptr - group_u_integer];

			++group;

			rem_group = *group - 1lu;

		} else {
			rem_group -= rem_cells;

			while (rem_cells > 0lu) {
				ptr = put_group_u_integer(ptr,
							group_u_integer);
				--rem_cells;
			}

			/* increment row_block length */
			length_lock_increment(&from->parent->total,
					      ptr - from->cell,
					      &column->fail_cl);

			/* skip to rowspan in next row */
			from += col_count;

			if (from >= until)
				break;

			from->cell = ptr;

			rem_cells = from->parent->row_count;
		}
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}

void
build_column_u_integer_random_upto(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct IntegerRandSpec *const restrict rand_spec
	= &column->spec->type_q.u_integer.rand_spec;

	const struct BoundUGeneratorClosure *const restrict upto_cl
	= &rand_spec->gen.upto;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t size_est = rand_spec->width_max * row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCUIRU_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	char *restrict ptr = column->contents;

	size_t rem_cells;

	do {
		from->cell = ptr;

		rem_cells = from->parent->row_count;

		do {
			ptr = put_uint(ptr,
				       upto_cl->generate(&upto_cl->params));

			*ptr = '\0';
			++ptr;

			--rem_cells;

		} while (rem_cells > 0lu);

		/* add length of rowspan to row_block total */
		length_lock_increment(&from->parent->total,
				      ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}

void
build_column_u_integer_random_upto_group(void *arg)
{
	size_t rem_cells;
	size_t rem_group;
	char *restrict ptr;
	char *restrict group_u_integer;
	size_t *restrict group;
	PutStringWidth *put_group_u_integer;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct IntegerRandSpec *const restrict rand_spec
	= &column->spec->type_q.u_integer.rand_spec;

	const struct BoundUGeneratorClosure *const restrict upto_cl
	= &rand_spec->gen.upto;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t group_count = column->spec->grp_spec.count;

	GroupPartitioner *const partition_groups
	= column->spec->grp_spec.partition;

	const size_t size_est = (sizeof(size_t) * group_count)
			      + (rand_spec->width_max * row_count);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCUIRU_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	group = (size_t *restrict) column->contents;

	group_u_integer = partition_groups(group,
					 group_count,
					 row_count);

	ptr = put_uint(group_u_integer,
		       upto_cl->generate(&upto_cl->params));
	*ptr = '\0';
	++ptr;

	put_group_u_integer = PUT_STRING_WIDTH_MAP[ptr - group_u_integer];

	rem_group = *group;

	rem_cells = from->parent->row_count;

	from->cell = ptr;

	while (1) {
		if (rem_cells > rem_group) {
			rem_cells -= (rem_group + 1lu);

			while (rem_group > 0lu) {
				ptr = put_group_u_integer(ptr,
							group_u_integer);
				--rem_group;
			}

			group_u_integer = ptr;

			ptr = put_uint(group_u_integer,
				       upto_cl->generate(&upto_cl->params));
			*ptr = '\0';
			++ptr;

			put_group_u_integer
			= PUT_STRING_WIDTH_MAP[ptr - group_u_integer];

			++group;

			rem_group = *group - 1lu;

		} else {
			rem_group -= rem_cells;

			while (rem_cells > 0lu) {
				ptr = put_group_u_integer(ptr,
							group_u_integer);
				--rem_cells;
			}

			/* increment row_block length */
			length_lock_increment(&from->parent->total,
					      ptr - from->cell,
					      &column->fail_cl);

			/* skip to rowspan in next row */
			from += col_count;

			if (from >= until)
				break;

			from->cell = ptr;

			rem_cells = from->parent->row_count;
		}
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}

void
build_column_u_integer_random_range(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct IntegerRandSpec *const restrict rand_spec
	= &column->spec->type_q.u_integer.rand_spec;

	const struct BoundOffsetUGeneratorClosure *const restrict range_cl
	= &rand_spec->gen.range;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t size_est = rand_spec->width_max * row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCUIRR_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	char *restrict ptr = column->contents;

	size_t rem_cells;

	do {
		from->cell = ptr;

		rem_cells = from->parent->row_count;

		do {
			ptr = put_uint(ptr,
				       range_cl->generate(&range_cl->params));

			*ptr = '\0';
			++ptr;

			--rem_cells;

		} while (rem_cells > 0lu);

		/* add length of rowspan to row_block total */
		length_lock_increment(&from->parent->total,
				      ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}

void
build_column_u_integer_random_range_group(void *arg)
{
	size_t rem_cells;
	size_t rem_group;
	char *restrict ptr;
	char *restrict group_u_integer;
	size_t *restrict group;
	PutStringWidth *put_group_u_integer;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct IntegerRandSpec *const restrict rand_spec
	= &column->spec->type_q.u_integer.rand_spec;

	const struct BoundOffsetUGeneratorClosure *const restrict range_cl
	= &rand_spec->gen.range;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t group_count = column->spec->grp_spec.count;

	GroupPartitioner *const partition_groups
	= column->spec->grp_spec.partition;

	const size_t size_est = (sizeof(size_t) * group_count)
			      + (rand_spec->width_max * row_count);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCUIRR_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	group = (size_t *restrict) column->contents;

	group_u_integer = partition_groups(group,
					 group_count,
					 row_count);

	ptr = put_uint(group_u_integer,
		       range_cl->generate(&range_cl->params));
	*ptr = '\0';
	++ptr;

	put_group_u_integer = PUT_STRING_WIDTH_MAP[ptr - group_u_integer];

	rem_group = *group;

	rem_cells = from->parent->row_count;

	from->cell = ptr;

	while (1) {
		if (rem_cells > rem_group) {
			rem_cells -= (rem_group + 1lu);

			while (rem_group > 0lu) {
				ptr = put_group_u_integer(ptr,
							group_u_integer);
				--rem_group;
			}

			group_u_integer = ptr;

			ptr = put_uint(group_u_integer,
				       range_cl->generate(&range_cl->params));
			*ptr = '\0';
			++ptr;

			put_group_u_integer
			= PUT_STRING_WIDTH_MAP[ptr - group_u_integer];

			++group;

			rem_group = *group - 1lu;

		} else {
			rem_group -= rem_cells;

			while (rem_cells > 0lu) {
				ptr = put_group_u_integer(ptr,
							group_u_integer);
				--rem_cells;
			}

			/* increment row_block length */
			length_lock_increment(&from->parent->total,
					      ptr - from->cell,
					      &column->fail_cl);

			/* skip to rowspan in next row */
			from += col_count;

			if (from >= until)
				break;

			from->cell = ptr;

			rem_cells = from->parent->row_count;
		}
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}
