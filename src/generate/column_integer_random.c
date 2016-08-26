#include "generate/column_integer_random.h"

#define BCIRF_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_from")

#define BCIRF_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_from_group")

/* worker thread entry points */
void
build_column_integer_random(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct IntegerRandSpec *const restrict rand_spec
	= &column->spec->type_q.integer.rand_spec;

	IGenerator *const gen_unbound = rand_spec->gen.unbound;

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
				     BCIRF_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	char *restrict ptr = column->contents;

	size_t rem_cells;

	do {
		from->cell = ptr;

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
}

void
build_column_integer_random_from(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct IntegerRandSpec *const restrict rand_spec
	= &column->spec->type_q.integer.rand_spec;

	const struct BoundOffsetIGeneratorClosure *const restrict from_cl
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
				     BCIRF_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	struct Rowspan *restrict from = column->rowspans_from;

	char *restrict ptr = column->contents;

	size_t rem_cells;

	do {
		from->cell = ptr;

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
}

void
build_column_integer_random_upto(void *arg)
{
}

void
build_column_integer_random_upto_group(void *arg)
{
}

void
build_column_integer_random_range(void *arg)
{
}

void
build_column_integer_random_range_group(void *arg)
{
}
