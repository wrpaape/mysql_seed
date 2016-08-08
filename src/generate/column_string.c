#include "generate/column_string.h"

#define BCSU_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_string_unique")

#define BCSF_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_string_fixed")

/* worker thread entry point */
void
build_column_string_unique(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct String *const restrict base
	= &column->spec->type_qualifier.string.base;

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t length_contents = counter_size_upto(row_count)
				     + (row_count * base->length);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCSU_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      length_contents,
			      &column->fail_cl);

	struct Counter *const restrict counter
	= &table->parent->parent->counter;

	const struct Rowspan *const restrict until = table->rowspans_until;
	struct Rowspan *restrict from		   = column->rowspans_from;

	char *restrict ptr = column->contents;

	/* wait for counter to be built */
	counter_await(counter,
		      &column->fail_cl);

	char *restrict *restrict count_ptr = counter->pointers;

	char *restrict *restrict count_until;

	do {
		from->cell = ptr;

		count_until = count_ptr + from->parent->row_count;

		do {
			ptr = put_string_size(ptr,
					      base->bytes,
					      base->length);

			ptr = put_string_stop(ptr,
					      *count_ptr);

			++count_ptr;
		} while (count_ptr < count_until);

		length_lock_increment(&from->parent->total,
				      ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

	thread_try_catch_close();
}

/* worker thread entry point */
void
build_column_string_fixed(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct String *const restrict base
	= &column->spec->type_qualifier.string.base;

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t base_size = base->length + 1lu;

	const size_t length_contents = base_size * table->spec->row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCSF_MALLOC_FAILURE);
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

	size_t size_rowspan;

	do {
		size_rowspan = base_size * from->parent->row_count;

		length_lock_increment(&from->parent->total,
				      size_rowspan,
				      &column->fail_cl);

		contents_until = ptr + size_rowspan;

		from->cell = ptr;

		do {
			ptr = put_string_size(ptr,
					      base->bytes,
					      base_size);

		} while (ptr < contents_until);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

	thread_try_catch_close();
}
