#include "generate/table.h"

#define BTH_MALLOC_FAILURE MALLOC_FAILURE_MESSAGE("build_table_header")

extern inline unsigned int
table_size_contents(struct Table *const restrict table);

extern inline char *
table_put_header(char *restrict ptr,
		 const struct Table *const restrict table);

void
build_table_header(void *arg)
{
	struct Table *const restrict table
	= (struct Table *const restrict) arg;


	const unsigned int count_joins = table_size_contents(table);

	thread_try_catch_open(&free_nullify_cleanup,
			      &table->file.contents.bytes);

	table->file.contents.bytes = malloc(table->file.contents.length);

	if (UNLIKELY(table->file.contents.bytes == NULL)) {
		handler_closure_call(&table->fail_cl,
				     BTH_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	char *restrict ptr = table_put_header(table->file.contents.bytes,
					      table);

	const struct RowBlock *const restrict upto = table->row_blocks.until - 1l;
	struct RowBlock *restrict from		   = table->row_blocks.from;

	while (1) {
		from->contents = ptr;

		if (from == upto)
			break;

		/* no FIELD_DELIMs for join columns */
		ptr += (from->total.length - (count_joins * from->row_count));

		++from;
	}

	thread_try_catch_close();
}


void
build_table_file(void *arg)
{
	struct Table *const restrict table
	= (struct Table *const restrict) arg;

	thread_try_ensure_open(free_nullify_cleanup, /* no-op if freed again */
			       &table->file.contents.bytes);

	file_handle_process(&table->file,
			    &table->fail_cl);

	thread_try_ensure_close();
}
