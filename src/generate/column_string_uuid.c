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

	const bool join = (column->spec->name.bytes == NULL);

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t length_contents = UUID_STRING_SIZE
				     * table->spec->row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCSUUID_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	/* init uuid_string */
	uuid_string_init(&uuid_string[0],
			 &column->fail_cl);

	char *const restrict time_low = &uuid_string[7u];

	/* increment table length */
	length_lock_increment(&table->total,
			      length_contents,
			      &column->fail_cl);

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
		from->join = join;

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

void
build_column_string_uuid_group(void *arg)
{
	const char *restrict group_contents_until;
	const char *restrict rowspan_contents_until;
	size_t size_rowspan;

	char uuid_string[UUID_STRING_SIZE];

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t length_column = UUID_STRING_SIZE * row_count;

	const size_t group_count = col_spec->grp_spec.count;

	GroupPartitioner *const partition_groups
	= col_spec->grp_spec.partition;

	const size_t length_contents = (sizeof(size_t) * group_count)
				     + length_column;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCSUUID_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	/* init uuid_string */
	uuid_string_init(&uuid_string[0],
			 &column->fail_cl);

	char *const restrict time_low = &uuid_string[7u];

	/* increment table length */
	length_lock_increment(&table->total,
			      length_column,
			      &column->fail_cl);

	const struct Rowspan *const restrict until = table->rowspans_until;
	struct Rowspan *restrict from		   = column->rowspans_from;

	size_t *restrict group = (size_t *restrict) column->contents;

	char *restrict ptr = partition_groups(group,
					      group_count,
					      row_count);

	from->cell = ptr;
	from->join = join;

	size_rowspan = UUID_STRING_SIZE * from->parent->row_count;

	length_lock_increment(&from->parent->total,
			      size_rowspan,
			      &column->fail_cl);

	rowspan_contents_until = ptr + size_rowspan;
	group_contents_until   = ptr + (UUID_STRING_SIZE * (*group));

	while (1) {
		if (rowspan_contents_until > group_contents_until) {
			while (ptr < group_contents_until)
				PUT_UUID_STRING(ptr,
						&uuid_string[0]);

			uuid_string_increment_time(time_low);

			++group;

			group_contents_until = ptr +
					       (UUID_STRING_SIZE * (*group));

		} else {
			while (ptr < rowspan_contents_until)
				PUT_UUID_STRING(ptr,
						&uuid_string[0]);

			/* skip to rowspan in next row */
			from += col_count;

			if (from >= until)
				break;

			from->cell = ptr;
			from->join = join;

			size_rowspan = UUID_STRING_SIZE
				     * from->parent->row_count;

			length_lock_increment(&from->parent->total,
					      size_rowspan,
					      &column->fail_cl);

			rowspan_contents_until = ptr + size_rowspan;
		}
	}

	thread_try_catch_close();
}
