#ifndef MYSQL_SEED_MYSQL_SEED_REMOVE
#define MYSQL_SEED_MYSQL_SEED_REMOVE

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h"	/* handle input strings */


inline int
remove_dispatch(char *const restrict *const restrict arg,
		const int rem_argc)
{
	return EXIT_FAILURE;
}

/* remove all contents in a directory, then the directory itself */
inline void
remove_all(char *const restrict path,
	   const struct HandlerClosure *const restrict fail_cl)
{
#ifdef WIN32

#else
	char *path_argv[] = {
		path, NULL
	};

	FTS *restrict tree;
	FTSENT *restrict entry;

	fts_open_handle_cl(&tree,
			   &path_argv[0],
			   FTS_LOGICAL | FTS_NOSTAT,
			   NULL,
			   fail_cl);

	while (1) {
		fts_read_handle_cl(&entry,
				   tree,
				   fail_cl);

		if (entry == NULL)
			break;


		switch (entry->fts_info) {
		case FTS_D:	/* possibly populated directory, skip */
			continue;

		case FTS_DP:	/* empty directory, remove */
			rmdir_handle_cl(entry->fts_accpath,
					fail_cl);
			continue;

		default:	/* terminal file/link */
			unlink_handle_cl(entry->fts_accpath,
					 fail_cl);
		}
	}

	fts_close_handle_cl(tree,
			    fail_cl);
#endif /* ifdef WIN32 */
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_REMOVE */
