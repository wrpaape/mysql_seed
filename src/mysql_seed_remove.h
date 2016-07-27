#ifndef MYSQL_SEED_MYSQL_SEED_REMOVE
#define MYSQL_SEED_MYSQL_SEED_REMOVE

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h"	/* handle input strings */


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define REMOVE_FAILURE(REASON)						\
"\n" FAILURE_HEADER_WRAP("remove", " - " REASON)

#define FAILURE_NO_RM_SPEC						\
REMOVE_FAILURE("no RM_SPEC provided") MORE_INFO_MESSAGE


/* irrecoverable failures */
inline void
remove_failure_no_rm_spec(void)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_NO_RM_SPEC,
		     sizeof(FAILURE_NO_RM_SPEC) - 1lu);
}

/* remove all database directories in 'database' */
inline int
mysql_seed_remove_all(void)
{
	const char *restrict failure;
	int exit_status;

	if (!chdir_report(DB_ROOT_DIRNAME,
			  &failure)) {
		print_failure(failure);
		return EXIT_FAILURE;
	}

	exit_status = EXIT_SUCCESS;
}

/* remove all contents in a directory, then the directory itself */
inline int
mysql_seed_remove(char *const restrict *restrict db_names)
{

	const char *restrict failure;
	int exit_status;

	if (!chdir_report(DB_ROOT_DIRNAME,
			  &failure)) {
		print_failure(failure);
		return EXIT_FAILURE;
	}

	exit_status = EXIT_SUCCESS;

#ifdef WIN32

#else
	FTS *restrict tree;
	FTSENT *restrict entry;

	if (!fts_open_report(&tree,
			     db_names,
			     FTS_PHYSICAL | FTS_NOSTAT,
			     NULL,
			     &failure)) {
		print_failure(failure);
		return EXIT_FAILURE;
	}

	/* while (1) { */
	/* 	fts_read_handle_cl(&entry, */
	/* 			   tree, */
	/* 			   fail_cl); */

	/* 	if (entry == NULL) */
	/* 		break; */


	/* 	switch (entry->fts_info) { */
	/* 	case FTS_D:	/1* possibly populated directory, skip *1/ */
	/* 		continue; */

	/* 	case FTS_DP:	/1* empty directory, remove *1/ */
	/* 		rmdir_handle_cl(entry->fts_accpath, */
	/* 				fail_cl); */
	/* 		continue; */

	/* 	default:	/1* terminal file/link *1/ */
	/* 		unlink_handle_cl(entry->fts_accpath, */
	/* 				 fail_cl); */
	/* 	} */
	/* } */

	if (!fts_close_report(tree,
			      &failure)) {
		print_failure(failure);
		return EXIT_FAILURE;
	}

	return exit_status;
#endif /* ifdef WIN32 */
}

inline int
remove_dispatch(char *const restrict *const restrict arg,
		const int rem_argc)
{
	if (rem_argc == 0lu) {
		remove_failure_no_rm_spec();
		return EXIT_FAILURE;
	}

	const char *restrict rm_spec = *arg;

	if (*rm_spec != '-')
		return mysql_seed_remove(arg)

	++rm_spec;
	const char *const restrict rem = rm_spec + 1l;

	switch (*rm_spec) {
	case '-':	/* parse long rm_spec */
		return strings_equal("all", rem)
		     ? mysql_seed_remove_all()
		     : mysql_seed_remove(arg);

	case 'a':
		return (*rem == '\0')
		     ? mysql_seed_remove_all()
		     : mysql_seed_remove(arg);

	default:
		return mysql_seed_remove(arg);
	}
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_REMOVE */
