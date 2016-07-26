#include "mysql_seed_remove.h"

/* remove all contents in a directory, then the directory itself */
extern inline void
remove_all(char *const restrict path,
	   const struct HandlerClosure *const restrict fail_cl);

extern inline int
remove_dispatch(char *const restrict *const restrict arg,
		const int rem_argc);
