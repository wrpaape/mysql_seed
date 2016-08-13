#include "generate/column_timestamp.h"

/* "YYYY-MM-DD HH:MM:SS" */
#define BCTF_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_timestamp_fixed")
#define BCTU_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_timestamp_unique")
#define BCTU_GROUP_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_timestamp_unique_group")


extern inline void
timestamp_string_init(char *restrict string,
		      const struct Timestamp *const restrict timestamp);
extern inline void
timestamp_string_increment(char *restrict ptr);

void
build_column_timestamp_fixed(void *arg)
{
	char string[SIZE_TIMESTAMP_STRING];
	struct Timestamp timestamp;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t length_contents = row_count * sizeof(string);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCTF_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      length_contents,
			      &column->fail_cl);

	const struct Rowspan *const restrict until = table->rowspans_until;
	struct Rowspan *restrict from		   = column->rowspans_from;

	/* fetch current time */
	timestamp_now_handle_cl(&timestamp,
				&column->fail_cl);

	/* stringify current time */
	timestamp_string_init(&string[0],
			      &timestamp);

	char *restrict ptr = column->contents;

	const char *restrict contents_until;

	do {
		from->cell = ptr;

		contents_until = ptr
			       + (sizeof(string) * from->parent->row_count);

		do {
			PUT_TIMESTAMP_STRING(ptr,
					     &string[0]);
		} while (ptr < contents_until);

		length_lock_increment(&from->parent->total,
				      ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

	thread_try_catch_close();
}


void
build_column_timestamp_unique(void *arg)
{
	char string[SIZE_TIMESTAMP_STRING];
	struct Timestamp timestamp;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t length_contents = row_count * sizeof(string);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCTU_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      length_contents,
			      &column->fail_cl);

	const struct Rowspan *const restrict until = table->rowspans_until;
	struct Rowspan *restrict from		   = column->rowspans_from;

	/* fetch current time */
	timestamp_now_handle_cl(&timestamp,
				&column->fail_cl);

	/* stringify current time */
	timestamp_string_init(&string[0],
			      &timestamp);

	char *const restrict last_digit = &string[sizeof(string) - 2lu];

	char *restrict ptr = column->contents;

	const char *restrict contents_until;

	do {
		from->cell = ptr;

		contents_until = ptr
			       + (sizeof(string) * from->parent->row_count);

		while (1) {
			PUT_TIMESTAMP_STRING(ptr,
					     &string[0]);

			if (ptr == contents_until)
				break;

			timestamp_string_increment(last_digit);
		}

		length_lock_increment(&from->parent->total,
				      ptr - from->cell,
				      &column->fail_cl);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

	thread_try_catch_close();
}


/* TODO: build_column_timestamp_unique_group */
void
build_column_timestamp_unique_group(void *arg)
{
}
