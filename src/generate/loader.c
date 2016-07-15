#include "generate/loader.h"

extern inline size_t
loader_estimate_size(const unsigned int tbl_count);

extern inline char *
loader_put_header(char *restrict ptr,
		  const struct Database *const restrict database);

inline char *
loader_put_body(char *restrict ptr,
		const struct Database *const restrict database);

/* worker task entry point
 * ────────────────────────────────────────────────────────────────────────── */
void
loader_build(void *arg)
{
	struct Database *const restrict database
	= (struct Database *const restrict) arg;

	const size_t size_est = loader_estimate_size(database->tables.until
						     - database->tables.from);
	char *restrict contents = NULL;

	thread_ensure_catch_open(free,
				 contents);

	contents = malloc(size_est);

	if (contents == NULL) {
		handle_closure_call(&database->fail_cl,
				    MALLOC_FAILURE_MESSAGE("loader_build"));
		__builtin_unreachable();
	}

	char *restrict ptr = loader_put_header(contents,
					       database);

	ptr = loader_put_body(ptr,
			      database);

	database->loader.contents.size  = ptr - contents;
	database->loader.contents.bytes = contents;

	/* write contents to file */
	file_handle_process(&database->loader,
			    &database->fail_cl);

	/* free contents */
	thread_ensure_catch_close();
}
