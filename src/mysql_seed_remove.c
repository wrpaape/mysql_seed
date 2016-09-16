#include "mysql_seed_remove.h"

/* remove all contents in a directory, then the directory itself */

extern inline void
remove_failure_no_rm_spec(void);

#ifdef WIN32
extern inline void
remove_failure_malloc(void);

extern inline void
do_free_win32_dir_stack(struct Win32DirNode *restrict dir_node);

extern inline void
free_win32_dir_stack(struct Win32DirNode *restrict dir_node);

extern inline bool
remove_db_name(char *const restrict db_name,
	       int *const restrict exit_status);
#endif /* ifdef WIN32 */

/* remove all database directories in 'database' */
extern inline int
mysql_seed_remove_all(void);

/* remove all contents in a directory, then the directory itself */
extern inline int
mysql_seed_remove(char *const *db_names);

extern inline int
remove_dispatch(char *const *const restrict arg,
		const unsigned int rem_argc);
