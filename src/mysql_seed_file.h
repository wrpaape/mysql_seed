#ifndef MYSQL_SEED_MYSQL_SEED_FILE_H_
#define MYSQL_SEED_MYSQL_SEED_FILE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "system/exit_utils.h"		/* exit, file, string utils */
#include "thread/thread_utils.h"	/* memory_copy, parallelization utils */

/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define FLAG_LENGTH_MAX (sizeof("--generate") * 2lu)
#define SPEC_LENGTH_MAX (sizeof("NAME_FIRST") * 2lu)
#define ERROR_BUFFER_SIZE 128lu

/* MySQL string limits
 *─────────────────────────────────────────────────────────────────────────── */
#define DB_NAME_LENGTH_MAX  63lu /* non-null UTF8 codepoints */
#define DB_NAME_NN_SIZE_MAX (UTF8_SIZE_MAX * DB_NAME_LENGTH_MAX)
#define DB_NAME_SIZE_MAX    (DB_NAME_NN_SIZE_MAX + 1lu) /* '\0' */

#define COL_NAME_LENGTH_MAX  63lu /* non-null UTF8 codepoints */
#define COL_NAME_NN_SIZE_MAX (UTF8_SIZE_MAX * COL_NAME_LENGTH_MAX)
#define COL_NAME_SIZE_MAX    (COL_NAME_NN_SIZE_MAX + 1lu) /* '\0' */


/* file naming conventions
 *─────────────────────────────────────────────────────────────────────────── */
/* database root directory */
#define DB_ROOT_DIRNAME		 "database"
#define DB_ROOT_DIRNAME_WIDTH	 9
#define DB_ROOT_DIRNAME_SIZE	 9lu
#define DB_ROOT_DIRNAME_LENGTH	 8lu
#define DB_ROOT_DIRNAME_NN_WIDTH 8
#define DB_ROOT_DIRNAME_NN_SIZE  8lu

/* database directory */
#define DB_DIRNAME_SIZE_MAX	DB_NAME_SIZE_MAX
#define DB_DIRNAME_NN_SIZE_MAX	DB_NAME_NN_SIZE_MAX
#define DB_DIRNAME_LENGTH_MAX	DB_NAME_LENGTH_MAX

#define DB_DIRPATH_PFX		DB_ROOT_DIRNAME PATH_DELIM
#define DB_DIRPATH_PFX_WIDTH	10
#define DB_DIRPATH_PFX_SIZE	10lu
#define DB_DIRPATH_PFX_NN_WIDTH 9
#define DB_DIRPATH_PFX_NN_SIZE	9lu
#define DB_DIRPATH_PFX_LENGTH	9lu
#define DB_DIRPATH_LENGTH_MAX	(  DB_ROOT_DIRNAME_LENGTH		\
				+ DB_DIRNAME_LENGTH_MAX)
#define DB_DIRPATH_NN_SIZE_MAX	(  DB_ROOT_DIRNAME_NN_SIZE		\
				 + 1lu	/* PATH_DELIM */		\
				 + DB_DIRNAME_NN_SIZE_MAX)
#define DB_DIRPATH_SIZE_MAX	( DB_DIRPATH_NN_SIZE_MAX		\
				 + 1lu)	/* '\0' */

/* table loader script */
#define LOADER_FILENAME_PFX	     "load_"
#define LOADER_FILENAME_PFX_WIDTH    6
#define LOADER_FILENAME_PFX_SIZE     6lu
#define LOADER_FILENAME_PFX_LENGTH   5lu
#define LOADER_FILENAME_PFX_NN_WIDTH 5
#define LOADER_FILENAME_PFX_NN_SIZE  5lu
#define LOADER_FILENAME_SFX	     ".mysql"
#define LOADER_FILENAME_SFX_WIDTH    7
#define LOADER_FILENAME_SFX_SIZE     7lu
#define LOADER_FILENAME_SFX_LENGTH   6lu
#define LOADER_FILENAME_SFX_NN_WIDTH 6
#define LOADER_FILENAME_SFX_NN_SIZE  6lu
#define LOADER_FILENAME_NN_SIZE_MAX  (  LOADER_FILENAME_PFX_NN_SIZE	\
				      + DB_NAME_NN_SIZE_MAX		\
				      + LOADER_FILENAME_SFX_NN_SIZE)
#define LOADER_FILENAME_LENGTH_MAX   LOADER_FILENAME_NN_SIZE_MAX
#define LOADER_FILENAME_SIZE_MAX     (  LOADER_FILENAME_NN_SIZE_MAX	\
				      + 1lu)	/* '\0' */
#define LOADER_FILEPATH_NN_SIZE_MAX  (  DB_DIRPATH_NN_SIZE_MAX		\
				      + 1lu	/* PATH_DELIM */	\
				      + LOADER_FILENAME_NN_SIZE_MAX)
#define LOADER_FILEPATH_LENGTH_MAX   LOADER_FILEPATH_NN_SIZE_MAX
#define LOADER_FILEPATH_SIZE_MAX     (  LOADER_FILEPATH_NN_SIZE_MAX	\
				      + 1lu)	/* '\0' */

/* table data file */
#define TABLE_FILENAME_SFX	    ".tsv"
#define TABLE_FILENAME_SFX_WIDTH    5
#define TABLE_FILENAME_SFX_SIZE	    5lu
#define TABLE_FILENAME_SFX_LENGTH   4lu
#define TABLE_FILENAME_SFX_NN_WIDTH 4
#define TABLE_FILENAME_SFX_NN_SIZE  4lu
#define TABLE_FILENAME_NN_SIZE_MAX  (  COL_NAME_SIZE_MAX		\
				     + TABLE_FILENAME_SFX_NN_SIZE)
#define TABLE_FILENAME_LENGTH_MAX   TABLE_FILENAME_NN_SIZE_MAX
#define TABLE_FILENAME_SIZE_MAX	    (  TABLE_FILENAME_NN_SIZE_MAX	\
				     + 1lu)	/* '\0' */
#define TABLE_FILEPATH_NN_SIZE_MAX  (  DB_DIRPATH_NN_SIZE_MAX		\
				     + 1lu	/* PATH_DELIM */	\
				     + TABLE_FILENAME_NN_SIZE_MAX)
#define TABLE_FILEPATH_LENGTH_MAX   TABLE_FILEPATH_NN_SIZE_MAX
#define TABLE_FILEPATH_SIZE_MAX	    (  TABLE_FILEPATH_NN_SIZE_MAX	\
				     + 1lu)	/* '\0' */

/* DirHandle sizing */
#define DIR_HANDLE_NAME_SIZE_MAX   DB_DIRNAME_SIZE_MAX
#define DIR_HANDLE_NAME_LENGTH_MAX DB_DIRNAME_LENGTH_MAX
#define DIR_HANDLE_PATH_SIZE_MAX   DB_DIRPATH_SIZE_MAX
#define DIR_HANDLE_PATH_LENGTH_MAX DB_DIRPATH_LENGTH_MAX

/* FileHandle sizing */
#if (LOADER_FILENAME_SIZE_MAX > TABLE_FILENAME_SIZE_MAX)
#	define FILE_HANDLE_NAME_SIZE_MAX   LOADER_FILENAME_SIZE_MAX
#	define FILE_HANDLE_NAME_LENGTH_MAX LOADER_FILENAME_LENGTH_MAX
#else
#	define FILE_HANDLE_NAME_SIZE_MAX   TABLE_FILENAME_SIZE_MAX
#	define FILE_HANDLE_NAME_LENGTH_MAX TABLE_FILENAME_LENGTH_MAX
#endif	/* if (LOADER_FILENAME_SIZE_MAX > TABLE_FILENAME_SIZE_MAX) */

#if (LOADER_FILEPATH_SIZE_MAX > TABLE_FILEPATH_SIZE_MAX)
#	define FILE_HANDLE_PATH_SIZE_MAX   LOADER_FILEPATH_SIZE_MAX
#	define FILE_HANDLE_PATH_LENGTH_MAX LOADER_FILEPATH_LENGTH_MAX
#else
#	define FILE_HANDLE_PATH_SIZE_MAX   TABLE_FILEPATH_SIZE_MAX
#	define FILE_HANDLE_PATH_LENGTH_MAX TABLE_FILEPATH_LENGTH_MAX
#endif	/* if (LOADER_FILEPATH_SIZE_MAX > TABLE_FILEPATH_SIZE_MAX) */


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define MORE_INFO_MESSAGE "\n\nmysql_seed -h for more info\n"

#define INVALID_SPEC_HEADER(SPEC)					\
ERROR_WRAP("error - invalid " SPEC ": ")

#define NO_SPEC_MESSAGE(SPEC)						\
ERROR_WRAP("error - no " SPEC " specified") MORE_INFO_MESSAGE

#define INVALID_FLAG_HEADER(FLAG) INVALID_SPEC_HEADER(FLAG " flag")
#define NO_FLAG_MESSAGE(FLAG)	  NO_SPEC_MESSAGE(FLAG " flag")


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
/* database/<db_name> */
struct Dirname {
	char buffer[DIR_HANDLE_NAME_SIZE_MAX];
	size_t length;
};

struct Dirpath {
	char buffer[DIR_HANDLE_PATH_SIZE_MAX];
	size_t length;
};

struct DirHandle {
	struct Dirname name;
	struct Dirpath path;
};


/* database/<db_name>/load_<db_name>.mysql or
 * database/<db_name>/<tbl_name>.tsv */
struct Filename {
	char buffer[FILE_HANDLE_NAME_SIZE_MAX];
	size_t length;
};

struct Filepath {
	char buffer[FILE_HANDLE_PATH_SIZE_MAX];
	size_t length;
};

struct FileHandle {
	int descriptor;
	struct String contents;
	struct Filename name;
	struct Filepath path;
};

/* synchronized counter */
struct LengthLock {
	size_t length;
	Mutex lock;
};



/* create and open file for writing only, fail if it already exists */
#define FILE_HANDLE_OPEN_FLAG (O_EXCL | O_CREAT | O_WRONLY)

/* all can read, only owner can write */
#define FILE_HANDLE_MODE (S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)

#define DIR_HANDLE_MODE FILE_HANDLE_MODE

/* FileHandle Operations
 * ────────────────────────────────────────────────────────────────────────── */
/* open */
inline bool
file_handle_open_status(struct FileHandle *const restrict file)
{
	return open_mode_status(&file->descriptor,
				&file->path.buffer[0],
				FILE_HANDLE_OPEN_FLAG,
				FILE_HANDLE_MODE);
}

inline void
file_handle_open_muffle(struct FileHandle *const restrict file)
{
	open_mode_muffle(&file->descriptor,
			 &file->path.buffer[0],
			 FILE_HANDLE_OPEN_FLAG,
			 FILE_HANDLE_MODE);
}

inline bool
file_handle_open_report(struct FileHandle *const restrict file,
			const char *restrict *const restrict failure)
{
	return open_mode_report(&file->descriptor,
				&file->path.buffer[0],
				FILE_HANDLE_OPEN_FLAG,
				FILE_HANDLE_MODE,
				failure);
}

inline void
file_handle_open_handle(struct FileHandle *const restrict file,
			Handler *const handle,
			void *arg)
{
	open_mode_handle(&file->descriptor,
			 &file->path.buffer[0],
			 FILE_HANDLE_OPEN_FLAG,
			 FILE_HANDLE_MODE,
			 handle,
			 arg);
}

inline void
file_handle_open_handle_cl(struct FileHandle *const restrict file,
			   const struct HandlerClosure *const restrict fail_cl)
{
	open_mode_handle_cl(&file->descriptor,
			    &file->path.buffer[0],
			    FILE_HANDLE_OPEN_FLAG,
			    FILE_HANDLE_MODE,
			    fail_cl);
}

/* write */
inline bool
file_handle_write_status(const struct FileHandle *const restrict file)
{
	return write_status(file->descriptor,
			    file->contents.bytes,
			    file->contents.length);
}

inline void
file_handle_write_muffle(const struct FileHandle *const restrict file)
{
	write_muffle(file->descriptor,
		     file->contents.bytes,
		     file->contents.length);
}

inline bool
file_handle_write_report(const struct FileHandle *const restrict file,
			 const char *restrict *const restrict failure)
{
	return write_report(file->descriptor,
			    file->contents.bytes,
			    file->contents.length,
			    failure);
}

inline void
file_handle_write_handle(const struct FileHandle *const restrict file,
			Handler *const handle,
			void *arg)
{
	write_handle(file->descriptor,
		     file->contents.bytes,
		     file->contents.length,
		     handle,
		     arg);
}

inline void
file_handle_write_handle_cl(const struct FileHandle *const restrict file,
			    const struct HandlerClosure *const restrict fail_cl)
{
	write_handle_cl(file->descriptor,
			file->contents.bytes,
			file->contents.length,
			fail_cl);
}


/* close */
inline bool
file_handle_close_status(const struct FileHandle *const restrict file)
{
	return close_status(file->descriptor);
}

inline void
file_handle_close_muffle(const struct FileHandle *const restrict file)
{
	close_muffle(file->descriptor);
}

inline bool
file_handle_close_report(const struct FileHandle *const restrict file,
			 const char *restrict *const restrict failure)
{
	return close_report(file->descriptor,
			    failure);
}

inline void
file_handle_close_handle(const struct FileHandle *const restrict file,
			 Handler *const handle,
			 void *arg)
{
	close_handle(file->descriptor,
		     handle,
		     arg);
}

inline void
file_handle_close_handle_cl(const struct FileHandle *const restrict file,
			    const struct HandlerClosure *const restrict fail_cl)
{
	close_handle_cl(file->descriptor,
			fail_cl);
}


/* unlink */
inline bool
file_handle_unlink_status(const struct FileHandle *const restrict file)
{
	return unlink_status(&file->path.buffer[0]);
}

inline void
file_handle_unlink_muffle(const struct FileHandle *const restrict file)
{
	unlink_muffle(&file->path.buffer[0]);
}

inline bool
file_handle_unlink_report(const struct FileHandle *const restrict file,
			 const char *restrict *const restrict failure)
{
	return unlink_report(&file->path.buffer[0],
			     failure);
}

inline void
file_handle_unlink_handle(const struct FileHandle *const restrict file,
			 Handler *const handle,
			 void *arg)
{
	unlink_handle(&file->path.buffer[0],
		      handle,
		      arg);
}

inline void
file_handle_unlink_handle_cl(const struct FileHandle *const restrict file,
			    const struct HandlerClosure *const restrict fail_cl)
{
	unlink_handle_cl(&file->path.buffer[0],
			 fail_cl);
}


/* cleanup */
void
file_handle_cleanup(void *arg);


/* atomic create-open-write-close */
inline void
file_handle_process(struct FileHandle *const restrict file,
		    const struct HandlerClosure *const restrict fail_cl)
{
	thread_try_catch_open(&file_handle_cleanup,
			      file);

	file_handle_open_handle_cl(file,
				   fail_cl);

	file_handle_write_handle_cl(file,
				    fail_cl);

	file_handle_close_handle_cl(file,
				    fail_cl);

	thread_try_catch_close()
}


/* DirHandle Operations
 * ────────────────────────────────────────────────────────────────────────── */
/* make */
inline bool
dir_handle_make_status(const struct DirHandle *const restrict dir)
{
	return mkdir_status(&dir->path.buffer[0],
			    DIR_HANDLE_MODE);
}

inline void
dir_handle_make_muffle(const struct DirHandle *const restrict dir)
{
	mkdir_muffle(&dir->path.buffer[0],
		     DIR_HANDLE_MODE);
}

inline bool
dir_handle_make_report(const struct DirHandle *const restrict dir,
		       const char *restrict *const restrict failure)
{
	return mkdir_report(&dir->path.buffer[0],
			    DIR_HANDLE_MODE,
			    failure);
}

inline void
dir_handle_make_handle(const struct DirHandle *const restrict dir,
		       Handler *const handle,
		       void *arg)
{
	mkdir_handle(&dir->path.buffer[0],
		     DIR_HANDLE_MODE,
		     handle,
		     arg);
}

inline void
dir_handle_make_handle_cl(const struct DirHandle *const restrict dir,
			  const struct HandlerClosure *const restrict fail_cl)
{
	mkdir_handle_cl(&dir->path.buffer[0],
			DIR_HANDLE_MODE,
			fail_cl);
}

/* remove */
inline bool
dir_handle_remove_status(const struct DirHandle *const restrict dir)
{
	return rmdir_status(&dir->path.buffer[0]);
}

inline void
dir_handle_remove_muffle(const struct DirHandle *const restrict dir)
{
	rmdir_muffle(&dir->path.buffer[0]);
}

inline bool
dir_handle_remove_report(const struct DirHandle *const restrict dir,
			 const char *restrict *const restrict failure)
{
	return rmdir_report(&dir->path.buffer[0],
			    failure);
}

inline void
dir_handle_remove_handle(const struct DirHandle *const restrict dir,
			 Handler *const handle,
			 void *arg)
{
	rmdir_handle(&dir->path.buffer[0],
		     handle,
		     arg);
}

inline void
dir_handle_remove_handle_cl(const struct DirHandle *const restrict dir,
			    const struct HandlerClosure *const restrict fail_cl)
{
	rmdir_handle_cl(&dir->path.buffer[0],
			fail_cl);
}

/* cleanup */
void
dir_handle_cleanup(void *arg);


/* Input operations
 * ────────────────────────────────────────────────────────────────────────── */
inline bool
flag_match(char *restrict arg,
	   const char short_flag,
	   const char *const restrict long_flag)
{
	if (*arg != '-')
		return false;

	++arg;

	/* check short flag match (i.e. -h) */
	if (*arg == short_flag) {
		++arg;

		if (*arg == '\0')
			return true;
	}

	if (*arg != '-')
		return false;

	++arg;

	/* check long flag match (i.e. --help) */
	return strings_equal(arg,
			     long_flag);
}

inline size_t
flag_count_until(char *const restrict *restrict arg_ptr,
		 char *const restrict *const restrict until_ptr,
		 const char short_flag,
		 const char *const restrict long_flag)
{
	size_t count_flags;

	for (count_flags = 0lu; arg_ptr < until_ptr; ++arg_ptr)
		if (flag_match(*arg_ptr,
			       short_flag,
			       long_flag))
			++count_flags;

	return count_flags;
}

inline char **
flag_next_until(char *const restrict *restrict arg_ptr,
		char *const restrict *const restrict until_ptr,
		const char short_flag,
		const char *const restrict long_flag)
{
	while (arg_ptr < until_ptr) {

		if (flag_match(*arg_ptr,
			       short_flag,
			       long_flag))
			return arg_ptr;

		++arg_ptr;
	}

	return until_ptr;
}

#endif	/* MYSQL_SEED_MYSQL_SEED_FILE_H_ */
