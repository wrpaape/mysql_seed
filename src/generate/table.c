#include "generate/table.h"

extern inline size_t
table_size_contents(const struct Table *const restrict table);


void
build_table_header_exit_cleanup(void *arg)
{
	struct Table *const restrict table
	= (struct Table *const restrict) arg;
}

void
build_table_header(void *arg)
{
	struct Table *const restrict table
	= (struct Table *const restrict) arg;

	table->file.contents.bytes  = NULL;
	table->file.contents.length = table_size_contents(table);

	thread_try_catch_open(&build_table_header_exit_cleanup,
			      table);



	thread_try_catch_close();
}
