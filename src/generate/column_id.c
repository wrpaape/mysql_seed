#include "generate/column_id.h"

/* worker thread entry point */
void
build_column_id(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct Rowspan *const restrict until = column->rowspans.until;
	struct Rowspan *restrict from		   = column->rowspans.from;

	struct Counter *const restrict counter
	= &column->parent->parent->parent->counter;

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
		++from;
	} while (from < until);

	/* add total length to table */
	length_lock_increment(&column->parent->total,
			      *count_ptr - *(counter->pointers),
			      &column->fail_cl);
}
