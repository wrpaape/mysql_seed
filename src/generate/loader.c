#include "generate/loader.h"

extern inline size_t
loader_estimate_size(const unsigned int tbl_count,
		     const unsigned int col_count);

extern inline char *
loader_put_header(char *restrict ptr,
		  const struct Database *const restrict database);

extern inline char *
loader_put_body(char *restrict ptr,
		const struct Database *const restrict database);

/* worker task entry point
 * ────────────────────────────────────────────────────────────────────────── */
void
build_loader(void *arg)
{
	struct Database *const restrict database
	= (struct Database *const restrict) arg;

	database_dirpath_init(&database->dirpath,
			      &database->spec->name);

	/* make database/<db_name> directory */
	dirpath_make_handle_cl(&database->dirpath,
			       &database->fail_cl);

	loader_file_init(&database->loader,
			 &database->spec->name,
			 &database->dirpath);

	const unsigned int tbl_count = database->tables.until
				     - database->tables.from;

	const unsigned int col_count = database->tables.until[-1].columns.until
				     - database->tables.from->columns.from;

	const size_t size_est = loader_estimate_size(tbl_count,
						     col_count);
	char *restrict contents = NULL;

	thread_try_ensure_open(&free,
			       contents);

	contents = malloc(size_est);

	if (UNLIKELY(contents == NULL)) {
		handler_closure_call(&database->fail_cl,
				     MALLOC_FAILURE_MESSAGE("build_loader"));
		__builtin_unreachable();
	}

	char *restrict ptr = loader_put_header(contents,
					       database);

	ptr = loader_put_body(ptr,
			      database);

	database->loader.contents.length = ptr - contents;
	database->loader.contents.bytes  = contents;


	/* write contents to file */
	file_handle_process(&database->loader,
			    &database->fail_cl);

	/* free contents */
	thread_try_ensure_close();
}
