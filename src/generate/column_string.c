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
	printf("enter build_column_string_fixed, %p\n", pthread_self()); fflush(stdout);
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct StringBuilder *const restrict fixed
	= &col_spec->type_q.string.fixed;

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	/* do not account for FIELD_DELIM or \n in length of join columns */
	const size_t size_column     = fixed->length;
	const size_t length_column   = size_column - join;
	const size_t length_contents = length_column * table->spec->row_count;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (UNLIKELY(column->contents == NULL)) {
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

	struct RowBlock *restrict row_block;

	do {
		from->cell = ptr;
		from->join = join;

		row_block = from->parent;

		contents_until = ptr + (size_column * row_block->row_count);

		length_lock_increment(&row_block->total,
				      length_column * row_block->row_count,
				      &column->fail_cl);

		do {
			ptr = put_string_closure_call(&fixed->put_cl,
						      ptr);
		} while (ptr < contents_until);

		/* skip to rowspan in next row */
		from += col_count;
	} while (from < until);

	thread_try_catch_close();

	printf("exit build_column_string_fixed, %p\n", pthread_self()); fflush(stdout);
}


void
build_column_string_unique(void *arg)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct StringBuilder *const restrict base
	= &col_spec->type_q.string.base;

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t length_contents = counter_size_upto(row_count)
				     + (row_count * base->length);

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(length_contents);

	if (UNLIKELY(column->contents == NULL)) {
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
		from->join = join;

		count_until = count_ptr + from->parent->row_count;

		do {
			ptr = put_string_closure_call(&base->put_cl,
						      ptr);

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
	struct PutStringClosure put_group_cl;
	char *restrict ptr;
	char *restrict *restrict count_ptr;
	char *restrict group_string;
	size_t rem_cells;
	size_t rem_group;

	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	const struct ColSpec *const restrict col_spec = column->spec;

	const bool join = (col_spec->name.bytes == NULL);

	const struct StringBuilder *const restrict base
	= &col_spec->type_q.string.base;

	struct Table *const restrict table
	= column->parent;

	const unsigned int col_count = table->col_count;

	const size_t row_count = table->spec->row_count;

	const size_t group_count = column->spec->grp_spec.count;

	GroupPartitioner *const partition_groups
	= column->spec->grp_spec.partition;

	const size_t column_alloc = (base->length
				     + counter_size_mag_upto(group_count))
				  * row_count;

	const size_t contents_alloc = (sizeof(size_t) * group_count)
				    + column_alloc;

	thread_try_catch_open(&free_nullify_cleanup,
			      &column->contents);

	column->contents = malloc(contents_alloc);

	if (UNLIKELY(column->contents == NULL)) {
		handler_closure_call(&column->fail_cl,
				     BCSU_GROUP_MALLOC_FAILURE);
		__builtin_unreachable();
	}


	struct Counter *const restrict counter
	= &table->parent->parent->counter;

	const struct Rowspan *const restrict until = table->rowspans_until;
	struct Rowspan *restrict from		   = column->rowspans_from;

	size_t *restrict group = (size_t *restrict) column->contents;

	ptr = partition_groups(group,
			       group_count,
			       row_count);

	put_string_closure_init(&put_group_cl,
				ptr,
				base->length + 2lu);

	from->cell = ptr;
	from->join = join;

	rem_cells = from->parent->row_count - 1lu;

	rem_group = *group - 1lu;

	ptr = put_string_closure_call(&base->put_cl,
				      ptr);

	PUT_STRING_WIDTH(ptr, "1", 2);


	/* wait for counter to be built */
	counter_await(counter,
		      &column->fail_cl);

	count_ptr = counter->pointers;

	while (1) {
		if (rem_cells > rem_group) {
			rem_cells -= (rem_group + 1lu);

			while (rem_group > 0lu) {
				ptr = put_string_closure_call(&put_group_cl,
							      ptr);
				--rem_group;
			}

			group_string = ptr;

			ptr = put_string_closure_call(&base->put_cl,
						      ptr);

			++count_ptr;

			ptr = put_string_stop(ptr,
					      *count_ptr);

			put_string_closure_init(&put_group_cl,
						group_string,
						ptr - group_string);

			++group;

			rem_group = *group - 1lu;
		} else {
			rem_group -= rem_cells;

			while (rem_cells > 0lu) {
				ptr = put_string_closure_call(&put_group_cl,
							      ptr);
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
			from->join = join;

			rem_cells = from->parent->row_count;
		}
	}

	/* increment table length */
	length_lock_increment(&table->total,
			      ptr - column->rowspans_from->cell,
			      &column->fail_cl);

	thread_try_catch_close();
}
