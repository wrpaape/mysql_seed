#include "generate/table.h"

#define BTH_MALLOC_FAILURE MALLOC_FAILURE_MESSAGE("build_table_header")

extern inline size_t
table_size_contents(const struct Table *const restrict table);

extern inline char *
table_put_header(char *restrict ptr,
		 const struct Table *const restrict table);

void
build_table_header(void *arg)
{
	struct Table *const restrict table
	= (struct Table *const restrict) arg;

	table->file.contents.length = table_size_contents(table);

	thread_try_catch_open(&free_nullify_cleanup,
			      &table->file.contents.bytes);

	table->file.contents.bytes = malloc(table->file.contents.length);

	if (table->file.contents.bytes == NULL) {
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

		ptr += from->total.length;

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
