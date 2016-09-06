#include "mysql_seed_remove.h"

/* remove all contents in a directory, then the directory itself */

extern inline void
remove_failure_no_rm_spec(void);

#ifdef WIN32
extern inline void
free_win32_dir_nodes(struct Win32DirNode *restrict dir_node);
extern inline void
do_free_win32_dir_nodes(struct Win32DirNode *restrict dir_node);
#endif /* ifdef WIN32 */

/* remove all database directories in 'database' */
extern inline int
mysql_seed_remove_all(void);

/* remove all contents in a directory, then the directory itself */
extern inline int
mysql_seed_remove(char *const *db_names);

extern inline int
remove_dispatch(char *const *const restrict arg);
