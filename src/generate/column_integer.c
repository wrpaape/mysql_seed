#include "generate/column_integer.h"

/* worker thread entry point */
void
build_column_integer_unique(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	struct Rowspan *restrict from		   = column->rowspans_from;

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
