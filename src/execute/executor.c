#include "execute/executor.h"

/* print error
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
execute_failure_malloc(void);

/* helper functions
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
load_db_path_init(char *restrict load_db_path,
		  const struct String *const restrict db_name);

/* call from main thread */
extern inline bool
load_db_buffer_init_report(struct String *const restrict load_db_buffer,
			   const struct String *const restrict db_name,
			   const char *restrict *const restrict failure);

/* call from worker thread */
extern inline void
load_db_buffer_init_handle_cl(struct String *const restrict load_db_buffer,
			      const struct String *const restrict db_name,
			      const struct HandlerClosure *const restrict fail_cl);
