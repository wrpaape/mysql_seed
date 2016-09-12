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

extern inline bool
load_db_buffer_init(const struct String *const restrict db_name
		    int *const restrict exit_status);
