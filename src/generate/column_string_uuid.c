#include "generate/column_string_uuid.h"

#define BCSUUID_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_string_uuid")
#define BCSUUID_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_string_uuid_group")

void
build_column_string_uuid(void *arg)
{
	char uuid_string[UUID_STRING_SIZE];

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t length_contents = UUID_STRING_SIZE
				     * table->spec->row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCSUUID_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      length_contents,
			      &column->fail_cl);

	/* init uuid_string */

	uuid_string_init(&uuid_string[0],
			 &column->fail_cl);

	char *const restrict time_low = &uuid_string[7u];

	const struct Rowspan *const restrict until = table->rowspans_until;
	struct Rowspan *restrict from		   = column->rowspans_from;

	char *restrict ptr = column->contents;

	const char *restrict contents_until;
	size_t size_rowspan;

	while (1) {
		size_rowspan = UUID_STRING_SIZE * from->parent->row_count;

		length_lock_increment(&from->parent->total,
				      size_rowspan,
				      &column->fail_cl);

		contents_until = ptr + size_rowspan;

		from->cell = ptr;

		while (1) {
			PUT_UUID_STRING(ptr,
					&uuid_string[0]);

			if (ptr < contents_until)
				uuid_string_increment_time(time_low);
			else
				break;
		}

		/* skip to rowspan in next row */
		from += col_count;

		if (from < until)
			uuid_string_increment_time(time_low);
		else
			break;
	}

	thread_try_catch_close();
}

/* TODO: build_column_string_uuid_group */
void
build_column_string_uuid_group(void *arg)
{
}
