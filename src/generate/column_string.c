#include "generate/column_string.h"

#define BCSB_MALLOC_FAILURE MALLOC_FAILURE_MESSAGE("build_column_string_base")

/* worker thread entry point */
void
build_column_string_base(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct String *const restrict base
	= &column->spec->type.string.base;

	const size_t row_count = column->parent->spec->row_count;

	const size_t length_contents = counter_size_upto(row_count)
				     + (row_count * base->length);

	/* increment table length */
	length_lock_increment(&column->parent->total,
			      length_contents,
			      &column->fail_cl);

	char *restrict ptr = NULL;

	thread_try_catch_open(free,
			      ptr);

	ptr = malloc(length_contents);

	if (ptr == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCSB_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	const struct Rowspan *const restrict until = column->rowspans.until;
	struct Rowspan *restrict from		   = column->rowspans.from;

	struct Counter *const restrict counter
	= &column->parent->parent->parent->counter;

	/* wait for counter to be built */
	counter_await(counter,
		      &column->fail_cl);

	char *restrict *restrict count_ptr = counter->pointers;

	char *restrict *restrict count_until;

	do {
		from->cells = ptr;

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
				      ptr - from->cells,
				      &column->fail_cl);

		++from;
	} while (from < until);

	thread_try_catch_close();
}
