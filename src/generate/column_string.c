#include "generate/column_string.h"

#define BCSF_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_string_fixed")
#define BCSU_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("build_column_string_unique")
#define BCSU_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_string_unique_group")


/* worker thread entry points */
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

	size_t length_rowspan;

	do {
		length_rowspan = base_size * from->parent->row_count;

		length_lock_increment(&from->parent->total,
				      length_rowspan,
				      &column->fail_cl);

		contents_until = ptr + length_rowspan;

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

void
build_column_string_unique_group(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct String *const restrict base
	= &column->spec->type_qualifier.string.base;

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t group_count = column->spec->grp_spec.count;

	GroupPartitioner *const partition_groups
	= column->spec->grp_spec.partition;

	const size_t length_column = (base->length
				      + counter_size_mag_upto(group_count))
				   * row_count;

	const size_t length_contents = (sizeof(size_t) * group_count)
				     + length_column;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (column->contents == NULL) {
		handler_closure_call(&column->fail_cl,
				     BCSU_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}


	struct Counter *const restrict counter
	= &table->parent->parent->counter;

	const struct Rowspan *const restrict until = table->rowspans_until;
	struct Rowspan *restrict from		   = column->rowspans_from;

	size_t *restrict group = (size_t *restrict) column->contents;


	const size_t *const restrict group_until = partition_groups(group,
								    group_count,
								    row_count);

	/* wait for counter to be built */
	counter_await(counter,
		      &column->fail_cl);

	char *restrict ptr;

	char *restrict *restrict count_ptr;

	const char *restrict rowspan_until;

	char *restrict group_string;

	size_t group_string_size;

	const char *restrict group_string_until;

	count_ptr = counter->pointers;

	ptr = (char *restrict) group_until;

	group_string = ptr;

	ptr = put_string_size(ptr,
			      base->bytes,
			      base->length);

	ptr = put_string_stop(ptr,
			      *count_ptr);

	group_string_size = ptr - group_string;

	from->cell = group_string;

	rowspan_until	   = group_string
			   + (group_string_size * from->parent->row_count);

	group_string_until = group_string
			   + (group_string_size * (*group));

	while (1) {
		/* printf("\ngroup_string:       %s\n" */
		/*        "group_string_size:  %zu\n" */
		/*        "ptr:                %p\n" */
		/*        "group_string_until: %p\n" */
		/*        "rowspan_until:      %p\n" */
		/*        "group:              %p\n" */
		/*        "group_until:        %p\n" */
		/*        "from:               %p\n" */
		/*        "until:              %p\n" */
		/*        "delta:              %zd\n", */
		/*        group_string, */
		/*        group_string_size, */
		/*        ptr, */
		/*        group_string_until, */
		/*        rowspan_until, */
		/*        group, */
		/*        group_until, */
		/*        from, */
		/*        until, */
		/*        group_until - group); */
		/* fflush(stdout); */
		if (group_string_until > rowspan_until) {
			while (ptr < rowspan_until)
				ptr = put_string_size(ptr,
						      group_string,
						      group_string_size);

			length_lock_increment(&from->parent->total,
					      ptr - from->cell,
					      &column->fail_cl);

			/* skip to rowspan in next row */
			from += col_count;

			if (from >= until)
				break;

			from->cell = ptr;

			rowspan_until = ptr + (group_string_size
					       * from->parent->row_count);
		} else {
			while (ptr < group_string_until)
				ptr = put_string_size(ptr,
						      group_string,
						      group_string_size);

			++group;

			if (group == group_until)
				break;

			group_string = ptr;

			ptr = put_string_size(ptr,
					      base->bytes,
					      base->length);

			++count_ptr;

			ptr = put_string_stop(ptr,
					      *count_ptr);

			group_string_size = ptr - group_string;

			group_string_until = group_string
					   + (group_string_size * (*group));
		}
	}
	/* puts("DID IT"); */
	/* fflush(stdout); */

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - ((const char *restrict) group_until),
			      &column->fail_cl);



	/* increment final rowspan total */
	/* length_lock_increment(&from->parent->total, */
	/* 		      ptr - from->cell, */
	/* 		      &column->fail_cl); */


	thread_try_catch_close();
}
