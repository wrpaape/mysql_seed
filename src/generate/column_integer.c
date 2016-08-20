#include "generate/column_integer.h"

#define BCIF_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_integer_fixed")

#define BCIU_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_integer_unique_group")

/* worker thread entry points */
void
build_column_integer_fixed(void *arg)
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
				     BCIF_MALLOC_FAILURE);
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
build_column_integer_unique(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	struct Rowspan *restrict from = column->rowspans_from;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	struct Counter *const restrict counter
	= &table->parent->parent->counter;

	/* wait for counter to be built */
	counter_await(counter,
		      &column->fail_cl);

	/* hook up rowspans */

	char *restrict *restrict count_ptr = counter->pointers;

	do {
		from->cell = *count_ptr;

		count_ptr += from->parent->row_count;

		/* add length of id rowspan to row_block total */
		length_lock_increment(&from->parent->total,
				      *count_ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

	/* add total length to table */
	length_lock_increment(&table->total,
			      *count_ptr - *(counter->pointers),
			      &column->fail_cl);
}


void
build_column_integer_unique_group(void *arg)
{
	size_t *restrict group;
	char *restrict ptr;
	PutStringWidth *put_digits;
	char *restrict *restrict count_ptr;
	char *restrict group_string;
	size_t rem_cells;
	size_t rem_group;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	struct Rowspan *restrict from = column->rowspans_from;

	struct Table *const restrict table
	= column->parent;

	const struct Rowspan *const restrict until = table->rowspans_until;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	struct Counter *const restrict counter
	= &table->parent->parent->counter;

	const size_t group_count = column->spec->grp_spec.count;

	GroupPartitioner *const partition_groups
	= column->spec->grp_spec.partition;

	const size_t column_alloc = counter_size_mag_upto(group_count)
				  * row_count;

	const size_t contents_alloc = (sizeof(size_t) * group_count)
				    + column_alloc;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(contents_alloc);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCIU_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	group = (size_t *restrict) column->contents;

	ptr = partition_groups(group,
			       group_count,
			       row_count);

	group_string = ptr;

	from->cell = ptr;

	rem_cells = from->parent->row_count - 1lu;

	rem_group = *group - 1lu;

	PUT_STRING_WIDTH(ptr, "1", 2);

	put_digits = put_string_width2;

	/* wait for counter to be built */
	counter_await(counter,
		      &column->fail_cl);

	/* hook up rowspans */
	count_ptr = counter->pointers;

	while (1) {
		if (rem_cells > rem_group) {
			rem_cells -= (rem_group + 1lu);

			while (rem_group > 0lu) {
				ptr = put_digits(ptr,
						 group_string);
				--rem_group;
			}


			group_string = ptr;

			++count_ptr;

			ptr = put_string_stop(ptr,
					      *count_ptr);

			put_digits
			= PUT_STRING_WIDTH_MAP[ptr - group_string];

			++group;

			rem_group = *group - 1lu;
		} else {
			rem_group -= rem_cells;

			while (rem_cells > 0lu) {
				ptr = put_digits(ptr,
						 group_string);
				--rem_cells;
			}

			/* increment row_block length */
			length_lock_increment(&from->parent->total,
					      ptr - from->cell,
					      &column->fail_cl);

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
