#include "generate/column_integer_random.h"

#define BCIRF_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_from")

#define BCIRF_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_integer_random_from_group")

/* worker thread entry points */
void
build_column_integer_random(void *arg)
{
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

	const struct StubBuilder *const restrict fixed
	= &column->spec->type_q.integer.fixed;

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t length_contents = fixed->width * table->spec->row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCIRF_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      length_contents,
			      &column->fail_cl);

	const struct Rowspan *const restrict until = table->rowspans_until;
	struct Rowspan *restrict from		   = column->rowspans_from;

	char *restrict ptr = column->contents;

	const char *restrict contents_until;

	size_t length_rowspan;

	do {
		from->cell = ptr;

		length_rowspan = fixed->width * from->parent->row_count;

		contents_until = ptr + length_rowspan;

		length_lock_increment(&from->parent->total,
				      length_rowspan,
				      &column->fail_cl);

		do {
			ptr = put_stub_closure_call(&fixed->put_cl,
						    ptr);
		} while (ptr < contents_until);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

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
