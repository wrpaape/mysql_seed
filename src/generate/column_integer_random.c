#include "generate/column_integer_random.h"

#define BCIR_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_integer_random")
#define BCIR_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_group")
#define BCIRF_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_from")
#define BCIRF_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_from_group")
#define BCIRU_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_upto")
#define BCIRU_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_upto_group")
#define BCIRR_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_range")
#define BCIRR_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_range_group")

/* worker thread entry points */
void
build_column_integer_random(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct IntegerRandSpec *const restrict rand_spec
	= &col_spec->type_q.integer.rand_spec;

	IGenerator *const gen_unbound = rand_spec->gen.unbound;

	struct Table *const restrict table = column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t size_est = rand_spec->width_max * row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCIR_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	char *restrict ptr = column->contents;

	size_t rem_cells;

	do {
		from->cell = ptr;
		from->join = join;

		rem_cells = from->parent->row_count;

		do {
			ptr = put_int(ptr,
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
build_column_integer_random_group(void *arg)
{
	size_t rem_cells;
	size_t rem_group;
	char *restrict ptr;
	char *restrict group_integer;
	size_t *restrict group;
	PutStringWidth *put_group_integer;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct IntegerRandSpec *const restrict rand_spec
	= &col_spec->type_q.integer.rand_spec;

	IGenerator *const gen_unbound = rand_spec->gen.unbound;

	struct Table *const restrict table = column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t group_count = col_spec->grp_spec.count;

	GroupPartitioner *const partition_groups = col_spec->grp_spec.partition;

	const size_t size_est = (sizeof(size_t) * group_count)
			      + (rand_spec->width_max * row_count);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCIR_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	group = (size_t *restrict) column->contents;

	group_integer = partition_groups(group,
					 group_count,
					 row_count);

	ptr = put_int(group_integer,
		      gen_unbound());
	*ptr = '\0';
	++ptr;

	put_group_integer = PUT_STRING_WIDTH_MAP[ptr - group_integer];

	rem_group = *group;

	rem_cells = from->parent->row_count;

	from->cell = ptr;
	from->join = join;

	while (1) {
		if (rem_cells > rem_group) {
			rem_cells -= (rem_group + 1lu);

			while (rem_group > 0lu) {
				ptr = put_group_integer(ptr,
							group_integer);
				--rem_group;
			}

			group_integer = ptr;

			ptr = put_int(group_integer,
				      gen_unbound());
			*ptr = '\0';
			++ptr;

			put_group_integer
			= PUT_STRING_WIDTH_MAP[ptr - group_integer];

			++group;

			rem_group = *group - 1lu;

		} else {
			rem_group -= rem_cells;

			while (rem_cells > 0lu) {
				ptr = put_group_integer(ptr,
							group_integer);
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
			from->join = join;

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
build_column_integer_random_from(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct IntegerRandSpec *const restrict rand_spec
	= &col_spec->type_q.integer.rand_spec;

	const struct BoundOffsetIGeneratorClosure *const restrict from_cl
	= &rand_spec->gen.from;

	struct Table *const restrict table = column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t size_est = rand_spec->width_max * row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCIRF_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	char *restrict ptr = column->contents;

	size_t rem_cells;

	do {
		from->cell = ptr;
		from->join = join;

		rem_cells = from->parent->row_count;

		do {
			ptr = put_int(ptr,
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
build_column_integer_random_from_group(void *arg)
{
	size_t rem_cells;
	size_t rem_group;
	char *restrict ptr;
	char *restrict group_integer;
	size_t *restrict group;
	PutStringWidth *put_group_integer;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct IntegerRandSpec *const restrict rand_spec
	= &col_spec->type_q.integer.rand_spec;

	const struct BoundOffsetIGeneratorClosure *const restrict from_cl
	= &rand_spec->gen.from;

	struct Table *const restrict table = column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t group_count = col_spec->grp_spec.count;

	GroupPartitioner *const partition_groups = col_spec->grp_spec.partition;

	const size_t size_est = (sizeof(size_t) * group_count)
			      + (rand_spec->width_max * row_count);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCIRF_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	group = (size_t *restrict) column->contents;

	group_integer = partition_groups(group,
					 group_count,
					 row_count);

	ptr = put_int(group_integer,
		      from_cl->generate(&from_cl->params));
	*ptr = '\0';
	++ptr;

	put_group_integer = PUT_STRING_WIDTH_MAP[ptr - group_integer];

	rem_group = *group;

	rem_cells = from->parent->row_count;

	from->cell = ptr;
	from->join = join;

	while (1) {
		if (rem_cells > rem_group) {
			rem_cells -= (rem_group + 1lu);

			while (rem_group > 0lu) {
				ptr = put_group_integer(ptr,
							group_integer);
				--rem_group;
			}

			group_integer = ptr;

			ptr = put_int(group_integer,
				      from_cl->generate(&from_cl->params));
			*ptr = '\0';
			++ptr;

			put_group_integer
			= PUT_STRING_WIDTH_MAP[ptr - group_integer];

			++group;

			rem_group = *group - 1lu;

		} else {
			rem_group -= rem_cells;

			while (rem_cells > 0lu) {
				ptr = put_group_integer(ptr,
							group_integer);
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
			from->join = join;

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
build_column_integer_random_upto(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct IntegerRandSpec *const restrict rand_spec
	= &col_spec->type_q.integer.rand_spec;

	const struct BoundIGeneratorClosure *const restrict upto_cl
	= &rand_spec->gen.upto;

	struct Table *const restrict table = column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t size_est = rand_spec->width_max * row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCIRU_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	char *restrict ptr = column->contents;

	size_t rem_cells;

	do {
		from->cell = ptr;
		from->join = join;

		rem_cells = from->parent->row_count;

		do {
			ptr = put_int(ptr,
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
build_column_integer_random_upto_group(void *arg)
{
	size_t rem_cells;
	size_t rem_group;
	char *restrict ptr;
	char *restrict group_integer;
	size_t *restrict group;
	PutStringWidth *put_group_integer;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct IntegerRandSpec *const restrict rand_spec
	= &col_spec->type_q.integer.rand_spec;

	const struct BoundIGeneratorClosure *const restrict upto_cl
	= &rand_spec->gen.upto;

	struct Table *const restrict table = column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t group_count = col_spec->grp_spec.count;

	GroupPartitioner *const partition_groups = col_spec->grp_spec.partition;

	const size_t size_est = (sizeof(size_t) * group_count)
			      + (rand_spec->width_max * row_count);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCIRU_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	group = (size_t *restrict) column->contents;

	group_integer = partition_groups(group,
					 group_count,
					 row_count);

	ptr = put_int(group_integer,
		      upto_cl->generate(&upto_cl->params));
	*ptr = '\0';
	++ptr;

	put_group_integer = PUT_STRING_WIDTH_MAP[ptr - group_integer];

	rem_group = *group;

	rem_cells = from->parent->row_count;

	from->cell = ptr;
	from->join = join;

	while (1) {
		if (rem_cells > rem_group) {
			rem_cells -= (rem_group + 1lu);

			while (rem_group > 0lu) {
				ptr = put_group_integer(ptr,
							group_integer);
				--rem_group;
			}

			group_integer = ptr;

			ptr = put_int(group_integer,
				      upto_cl->generate(&upto_cl->params));
			*ptr = '\0';
			++ptr;

			put_group_integer
			= PUT_STRING_WIDTH_MAP[ptr - group_integer];

			++group;

			rem_group = *group - 1lu;

		} else {
			rem_group -= rem_cells;

			while (rem_cells > 0lu) {
				ptr = put_group_integer(ptr,
							group_integer);
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
			from->join = join;

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
build_column_integer_random_range(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct IntegerRandSpec *const restrict rand_spec
	= &col_spec->type_q.integer.rand_spec;

	const struct BoundOffsetIGeneratorClosure *const restrict range_cl
	= &rand_spec->gen.range;

	struct Table *const restrict table = column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t size_est = rand_spec->width_max * row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCIRR_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	char *restrict ptr = column->contents;

	size_t rem_cells;

	do {
		from->cell = ptr;
		from->join = join;

		rem_cells = from->parent->row_count;

		do {
			ptr = put_int(ptr,
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
build_column_integer_random_range_group(void *arg)
{
	size_t rem_cells;
	size_t rem_group;
	char *restrict ptr;
	char *restrict group_integer;
	size_t *restrict group;
	PutStringWidth *put_group_integer;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct IntegerRandSpec *const restrict rand_spec
	= &col_spec->type_q.integer.rand_spec;

	const struct BoundOffsetIGeneratorClosure *const restrict range_cl
	= &rand_spec->gen.range;

	struct Table *const restrict table = column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t group_count = col_spec->grp_spec.count;

	GroupPartitioner *const partition_groups = col_spec->grp_spec.partition;

	const size_t size_est = (sizeof(size_t) * group_count)
			      + (rand_spec->width_max * row_count);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(size_est);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCIRR_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	group = (size_t *restrict) column->contents;

	group_integer = partition_groups(group,
					 group_count,
					 row_count);

	ptr = put_int(group_integer,
		      range_cl->generate(&range_cl->params));
	*ptr = '\0';
	++ptr;

	put_group_integer = PUT_STRING_WIDTH_MAP[ptr - group_integer];

	rem_group = *group;

	rem_cells = from->parent->row_count;

	from->cell = ptr;
	from->join = join;

	while (1) {
		if (rem_cells > rem_group) {
			rem_cells -= (rem_group + 1lu);

			while (rem_group > 0lu) {
				ptr = put_group_integer(ptr,
							group_integer);
				--rem_group;
			}

			group_integer = ptr;

			ptr = put_int(group_integer,
				      range_cl->generate(&range_cl->params));
			*ptr = '\0';
			++ptr;

			put_group_integer
			= PUT_STRING_WIDTH_MAP[ptr - group_integer];

			++group;

			rem_group = *group - 1lu;

		} else {
			rem_group -= rem_cells;

			while (rem_cells > 0lu) {
				ptr = put_group_integer(ptr,
							group_integer);
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
			from->join = join;

			rem_cells = from->parent->row_count;
		}
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}
