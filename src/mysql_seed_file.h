#ifndef MYSQL_SEED_MYSQL_SEED_FILE_H_
#define MYSQL_SEED_MYSQL_SEED_FILE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "system/exit_utils.h"		/* exit, file, string utils */
#include "memory/memory_copy_array.h"	/* memory_copy */

/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define FLAG_LENGTH_MAX (sizeof("--generate") * 2lu)
#define SPEC_LENGTH_MAX (sizeof("NAME_FIRST") * 2lu)
#define ERROR_BUFFER_SIZE 128lu

/* MySQL string limits
 *─────────────────────────────────────────────────────────────────────────── */
#define DB_NAME_LENGTH_MAX     64lu /* UTF8 length */
#define DB_NAME_NN_LENGTH_MAX  63lu /* non-null UTF8 codepoints */
#define DB_NAME_NN_SIZE_MAX    (UTF8_SIZE_MAX * DB_NAME_NN_LENGTH_MAX)
#define DB_NAME_SIZE_MAX       (DB_NAME_NN_SIZE_MAX + 1lu) /* '\0' */

#define COL_NAME_LENGTH_MAX    64lu /* UTF8 length */
#define COL_NAME_NN_LENGTH_MAX 63lu /* non-null UTF8 codepoints */
#define COL_NAME_NN_SIZE_MAX   (UTF8_SIZE_MAX * COL_NAME_NN_LENGTH_MAX)
#define COL_NAME_SIZE_MAX      (COL_NAME_NN_SIZE_MAX + 1lu) /* '\0' */


/* file naming conventions
 *─────────────────────────────────────────────────────────────────────────── */
/* database root directory */
#define DB_ROOT_DIRNAME		 "database"
#define DB_ROOT_DIRNAME_WIDTH	 9
#define DB_ROOT_DIRNAME_SIZE	 9lu
#define DB_ROOT_DIRNAME_NN_WIDTH 8
#define DB_ROOT_DIRNAME_NN_SIZE  8lu

/* database directory */
#define DB_DIRNAME_NN_SIZE_MAX DB_NAME_NN_SIZE_MAX
#define DB_DIRNAME_SIZE_MAX    DB_NAME_SIZE_MAX
#define DB_DIRPATH_NN_SIZE_MAX (  DB_ROOT_DIRNAME_NN_SIZE	\
				+ 1lu	/* PATH_DELIM */	\
				+ DB_DIRNAME_NN_SIZE_MAX)
#define DB_DIRPATH_LENGTH_MAX  DB_DIRNAME_NN_SIZE_MAX
#define DB_DIRPATH_SIZE_MAX    (  DB_DIRPATH_NN_SIZE_MAX	\
				+ 1lu)	/* '\0' */

/* table loader script */
#define LOADER_FILENAME_PFX	     "load_"
#define LOADER_FILENAME_PFX_WIDTH    6
#define LOADER_FILENAME_PFX_SIZE     6lu
#define LOADER_FILENAME_PFX_NN_WIDTH 5
#define LOADER_FILENAME_PFX_NN_SIZE  5lu
#define LOADER_FILENAME_SFX	     ".mysql"
#define LOADER_FILENAME_SFX_WIDTH    7
#define LOADER_FILENAME_SFX_SIZE     7lu
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



#define FAIL_SWITCH_ERRNO_FAILURE	0lu
#define FAIL_SWITCH_FAILURE_POINTER	failure


#define FAIL_SWITCH_FAILURE_ROUTINE	utf8_string_size_length
inline bool
handle_buffer_init_report(char *const restrict buffer,
			  size_t *const restrict length,
			  const char *const restrict bytes,
			  const size_t length_max,
			  const char *restrict *const restrict failure)
{
	const size_t size = utf8_string_size_length(bytes,
						    length_max);
	if (size > 0lu) {
		memory_copy(buffer,
			    bytes,
			    size);

		*length = size - 1lu;

		return true;
	}

	switch(errno) {
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "'bytes' contains byte sequence(s) that are "
				 "not valid UTF-8 code points")
	FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
				 "'bytes' exceeds maximum UTF-8 code point "
				 "length 'length'")
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

#undef FAIL_SWITCH_ERRNO_FAILURE
#undef FAIL_SWITCH_FAILURE_POINTER
#undef FAIL_SWITCH_FAILURE_ROUTINE

#endif	/* MYSQL_SEED_MYSQL_SEED_FILE_H_ */
