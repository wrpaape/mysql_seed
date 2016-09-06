#ifndef MYSQL_SEED_MYSQL_SEED_REMOVE
#define MYSQL_SEED_MYSQL_SEED_REMOVE

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h"	/* handle input strings */


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
#ifdef WIN32
struct Win32DirNode {
	char path[MAX_PATH];
	HANDLE handle;
	struct Win32DirNode *parent;
};

#define MYSQL_SEED_REMOVE_MALLOC_FAILURE				\
MALLOC_FAILURE_MESSAGE("mysql_seed_remove")

#endif /* ifdef WIN32 */

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

#ifdef WIN32
inline void
mysql_seed_remove_malloc_failure(void)
{
	write_muffle(STDERR_FILENO,
		     MYSQL_SEED_REMOVE_MALLOC_FAILURE,
		     sizeof(MYSQL_SEED_REMOVE_MALLOC_FAILURE) - 1lu);
}

inline void
do_free_win32_dir_stack(struct Win32DirNode *restrict dir_node)
{
	struct Win32DirNode *restrict closed_node;

	do {
		(void) FindClose(dir_node->handle);

		closed_node = dir_node;

		dir_node = dir_node->parent;

		free(closed_node);
	} while (dir_node != NULL);
}

inline void
free_win32_dir_stack(struct Win32DirNode *restrict dir_node)
{
	if (dir_node != NULL)
		do_free_win32_dir_stack(dir_node);
}

inline bool
remove_db_name(char *const restrict db_name,
	       int *const restrict exit_status)
{
	WIN32_FIND_DATA file_info;
	DWORD error_code;
	HANDLE cwd_handle;
	struct Win32DirNode *dir_node;
	struct Win32DirNode *parent;
	const char *restrict failure;

	if (!chdir_report(db_name,
			  &failure)) {
		print_failure(failure);
		*exit_status = EXIT_FAILURE;
		return true; /* can't enter first-gen directory, recoverable */
	}

	dir_node = NULL;

	while (1) {
		cwd_handle = FindFirstFile("*",
					   &file_info);

		if (cwd_handle == INVALID_HANDLE_VALUE) {
			PRINT_WIN32_FAILURE("FindFirstFile",
					    GetLastError());
			*exit_status = EXIT_FAILURE;
RETURN_TO_PARENT:
			if (dir_node == NULL)
				goto RETURN_TO_ROOT_AND_REMOVE_DB_NAME;

			if (!rmdir_report(&dir_node->path[0],
					  &failure)) {
				print_failure(failure);
				*exit_status = EXIT_FAILURE;
			}

			parent = dir_node->parent;
			free(dir_node);

			if (parent == NULL)
				goto RETURN_TO_ROOT_AND_REMOVE_DB_NAME;

			/* move up a directory */
			if (!chdir_report("..",
					  &failure)) {
				print_failure(failure);
				do_free_win32_dir_stack(parent);
				return false; /* irrecoverable */
			}

			dir_node   = parent;
			cwd_handle = dir_node->handle;

			goto NEXT_HARD_LINK;
		}

		/* skip dot directories ".", and ".." */
		while (is_dot_dir(&file_info.cFileName[0])) {
NEXT_HARD_LINK:
			if (!FindNextFile(cwd_handle,
					  &file_info)) {
				(void) FindClose(cwd_handle);

				error_code = GetLastError();

				if (error_code != ERROR_NO_MORE_FILES) {
					PRINT_WIN32_FAILURE("FindNextFile",
							    error_code);
					*exit_status = EXIT_FAILURE;
				}

				goto RETURN_TO_PARENT;
			}
		}

		/* file_info describes a hard link ────────────────────────── */

		/* if directory is found */
		if (file_info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

			/* enter directory */
			if (!chdir_report(&file_info.cFileName[0],
					  &failure)) {
				print_failure(failure);
				free_win32_dir_stack(dir_node);
				return false; /* irrecoverable */
			}

			/* push new dir_node then continue main loop */
			parent   = dir_node;
			dir_node = malloc(sizeof(struct Win32DirNode));

			if (dir_node == NULL) {
				mysql_seed_remove_malloc_failure();
				free_win32_dir_stack(parent);
				return false; /* irrecoverable */
			}

			copy_string_stop(&dir_node->path[0],
					 &file_info.cFileName[0]);

			dir_node->handle = cwd_handle;
			dir_node->parent = parent;

		} else {
			/* delete the file then search for the next hard link */
			if (!unlink_report(&file_info.cFileName[0],
					   &failure)) {
				print_failure(failure);
				*exit_status = EXIT_FAILURE;
			}

			goto NEXT_HARD_LINK;
		}
	}

RETURN_TO_ROOT_AND_REMOVE_DB_NAME:
	/* return to 'database' directory */
	if (!chdir_report("..",
			  &failure) {
		print_failure(failure);
		return false; /* irrecoverable */
	    }

	/* remove input first-gen 'db_name' directory */
	if (!rmdir_report(db_name,
			  &failure)) {
		print_failure(failure);
		*exit_status = EXIT_FAILURE;
	}

	return true;
}

#endif /* ifdef WIN32 */

/* remove all database directories in 'database' */
inline int
mysql_seed_remove_all(void)
{
	const char *restrict failure;
	int exit_status;
#ifdef WIN32
	WIN32_FIND_DATA file_info;
	DWORD error_code;
	HANDLE cwd_handle;
	struct Win32DirNode *dir_node;
	struct Win32DirNode *parent;

	/* ensure cwd at database root */
	if (!mysql_seed_chdir_db_root())
		return EXIT_FAILURE;

	exit_status = EXIT_SUCCESS;
	dir_node    = NULL;

	while (1) {
		cwd_handle = FindFirstFile("*",
					   &file_info);

		if (cwd_handle == INVALID_HANDLE_VALUE) {
			PRINT_WIN32_FAILURE("FindFirstFile",
					    GetLastError());
			exit_status = EXIT_FAILURE;
RETURN_TO_PARENT:
			if (dir_node == NULL)
				return exit_status;

			if (!rmdir_report(&dir_node->path[0],
					  &failure)) {
				print_failure(failure);
				exit_status = EXIT_FAILURE;
			}

			parent = dir_node->parent;
			free(dir_node);

			if (parent == NULL)
				return exit_status;

			/* move up a directory */
			if (!chdir_report("..",
					  &failure)) {
				print_failure(failure);
				do_free_win32_dir_stack(parent);
				return EXIT_FAILURE;
			}

			dir_node   = parent;
			cwd_handle = dir_node->handle;

			goto NEXT_HARD_LINK;
		}

		/* skip dot directories ".", and ".." */
		while (is_dot_dir(&file_info.cFileName[0])) {
NEXT_HARD_LINK:
			if (!FindNextFile(cwd_handle,
					  &file_info)) {
				(void) FindClose(cwd_handle);

				error_code = GetLastError();

				if (error_code != ERROR_NO_MORE_FILES) {
					PRINT_WIN32_FAILURE("FindNextFile",
							    error_code);
					exit_status = EXIT_FAILURE;
				}

				goto RETURN_TO_PARENT;
			}
		}

		/* file_info describes a hard link ────────────────────────── */

		/* if directory is found */
		if (file_info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

			/* enter directory */
			if (!chdir_report(&file_info.cFileName[0],
					  &failure)) {
				print_failure(failure);
				free_win32_dir_stack(dir_node);
				return EXIT_FAILURE;
			}

			/* push new dir_node then continue main loop */
			parent   = dir_node;
			dir_node = malloc(sizeof(struct Win32DirNode));

			if (dir_node == NULL) {
				mysql_seed_remove_malloc_failure();
				free_win32_dir_stack(parent);
				return EXIT_FAILURE;
			}

			copy_string_stop(&dir_node->path[0],
					 &file_info.cFileName[0]);

			dir_node->handle = cwd_handle;
			dir_node->parent = parent;

		} else {
			/* delete the file then search for the next hard link */
			if (!unlink_report(&file_info.cFileName[0],
					   &failure)) {
				print_failure(failure);
				exit_status = EXIT_FAILURE;
			}

			goto NEXT_HARD_LINK;
		}
	}
#else
	FTS *restrict tree;
	FTSENT *restrict entry;

	/* ensure cwd at project root */
	if (!mysql_seed_chdir_root())
		return EXIT_FAILURE;

	exit_status = EXIT_SUCCESS;

	char *const path_argv[] = {
		DB_ROOT_DIRNAME, NULL
	};

	if (!fts_open_report(&tree,
			     &path_argv[0],
			     FTS_PHYSICAL | FTS_NOSTAT,
			     NULL,
			     &failure)) {
		print_failure(failure);
		return EXIT_FAILURE;
	}

	while (1) {
		if (!fts_read_report(&entry,
				     tree,
				     &failure)) {

			print_failure(failure);
			exit_status = EXIT_FAILURE;

			if (entry == NULL)
				break;
			else
				continue;
		}

		switch (entry->fts_info) {
		case FTS_D:	/* possibly populated directory, skip */
			continue;

		case FTS_DP:
			if (entry->fts_level == 0) /* returning to root */
				goto FTS_CLOSE_AND_RETURN;

			if (!rmdir_report(entry->fts_accpath,
					  &failure)) {
				print_failure(failure);
				exit_status = EXIT_FAILURE;
			}
			continue;

		default:	/* terminal file/link */
			if (!unlink_report(entry->fts_accpath,
					   &failure)) {
				print_failure(failure);
				exit_status = EXIT_FAILURE;
			}
		}
	}

FTS_CLOSE_AND_RETURN:
	if (!fts_close_report(tree,
			      &failure)) {
		print_failure(failure);
		return EXIT_FAILURE;
	}

	return exit_status;
#endif /* ifdef WIN32 */
}

/* remove all contents in a directory, then the directory itself */
inline int
mysql_seed_remove(char *const *db_names)
{
	const char *restrict failure;
	int exit_status;

	/* ensure cwd at database root */
	if (!mysql_seed_chdir_db_root())
		return EXIT_FAILURE;

	exit_status = EXIT_SUCCESS;
#ifdef WIN32
	do {
		if (!remove_db_name(*db_names,
				    &exit_status))
			return EXIT_FAILURE;

		++db_names;
	} while (*db_names != NULL);
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

	while (1) {
		if (!fts_read_report(&entry,
				     tree,
				     &failure)) {

			print_failure(failure);
			exit_status = EXIT_FAILURE;

			if (entry == NULL)
				break;
			else
				continue;
		}

		if (entry == NULL)
			break;	/* traversal complete */


		switch (entry->fts_info) {
		case FTS_D:	/* possibly populated directory, skip */
			continue;

		case FTS_DP:	/* empty directory, remove */
			if (!rmdir_report(entry->fts_accpath,
					  &failure)) {
				print_failure(failure);
				exit_status = EXIT_FAILURE;
			}
			continue;

		default:	/* terminal file/link */
			if (!unlink_report(entry->fts_accpath,
					   &failure)) {
				print_failure(failure);
				exit_status = EXIT_FAILURE;
			}
		}
	}

	if (!fts_close_report(tree,
			      &failure)) {
		print_failure(failure);
		return EXIT_FAILURE;
	}
#endif /* ifdef WIN32 */
	return exit_status;
}

inline int
remove_dispatch(char *const *const restrict arg)
{
	const char *restrict rm_spec = *arg;

	if (rm_spec == NULL) {
		remove_failure_no_rm_spec();
		return EXIT_FAILURE;
	}

	if (*rm_spec != '-')
		return mysql_seed_remove(arg);

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
