#include "execute/executor.h"

/* print error
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
execute_failure_malloc(void);

/* helper functions
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
query_path_set(char *restrict query_path,
	       const struct String *const restrict db_name);

/* call from main thread */
extern inline bool
query_load_report(struct String *const restrict query,
		  const struct String *const restrict db_name,
		  const char *restrict *const restrict failure);

/* call from worker thread */
extern inline void
query_load_handle_cl(struct String *const restrict query,
		     const struct String *const restrict db_name,
		     const struct HandlerClosure *const restrict fail_cl);
