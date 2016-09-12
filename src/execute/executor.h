#ifndef MYSQL_SEED_EXECUTE_EXECUTOR_H_
#define MYSQL_SEED_EXECUTE_EXECUTOR_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h"	/* exit, file, string utils */
#include "thread/thread_pool.h"	/* ThreadPool */
#include <my_global.h>		/* mysql API */
#include <mysql.h>		/* mysql API */


/* error messages
 * ────────────────────────────────────────────────────────────────────────── */
#define EXECUTE_FAILURE(REASON)						\
"\n" FAILURE_HEADER_WRAP("execute", " - " REASON)

#define EXECUTE_FAILURE_MALLOC						\
EXECUTE_FAILURE(MALLOC_FAILURE_REASON)


/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define COUNT_EXECUTOR_WORKERS 4lu

/* default MySQL connection parameters */
#define MYSQL_DEFAULT_HOST	NULL
#define MYSQL_DEFAULT_USER	NULL
#define MYSQL_DEFAULT_PASSWORD	NULL
#define MYSQL_DEFAULT_DB	NULL
#define MYSQL_DEFAULT_PORT	0u
#define MYSQL_DEFAULT_SOCKET	NULL
#define MYSQL_DEFAULT_FLAGS	CLIENT_MULTI_STATEMENTS

/* -d DB_NAME */
#define EXEC_SPEC_LENGTH_MIN		2lu
#define EXEC_SPEC_LENGTH_MIN_STRING	"2"
#define EXEC_SPEC_MINIMAL		"-d DB_NAME"


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct MysqlServer {
	Mutex query_lock;
	MYSQL *connection;
};


struct ExecSpec {
	struct StringInterval db_names;
	const char *restrict user;
	const char *restrict password;
};


struct Executor {
	struct ThreadPool pool;	/* all child threads */
	struct Worker workers[COUNT_EXECUTOR_WORKERS];
	struct TaskStore load_databases;
	struct ThreadLog log;
	struct MysqlServer server;
	const struct ExecSpec *restrict exec_spec;
	int *exit_status;
};


struct ExecArg {
	struct Executor *executor;
};


/* print error
 * ────────────────────────────────────────────────────────────────────────── */
inline void
execute_failure_malloc(void)
{
	write_muffle(STDERR_FILENO,
		     EXECUTE_FAILURE_MALLOC,
		     sizeof(EXECUTE_FAILURE_MALLOC) - 1lu);
}

/* helper functions
 * ────────────────────────────────────────────────────────────────────────── */
inline void
load_db_path_init(char *restrict load_db_path,
		  const struct String *const restrict db_name)
{
	load_db_path = put_string_size(load_db_path,
				       DB_ROOT_ABSPATH_PFX,
				       sizeof(DB_ROOT_ABSPATH_PFX) - 1lu);

	load_db_path = put_string_size(load_db_path,
				       db_name->bytes,
				       db_name->length);

	PUT_STRING_WIDTH(load_db_path,
			 PATH_DELIM_STRING LOADER_FILENAME_PFX,
			 LOADER_FILENAME_PFX_WIDTH);

	load_db_path = put_string_size(load_db_path,
				       db_name->bytes,
				       db_name->length);

	SET_STRING_WIDTH(load_db_path,
			 LOADER_FILENAME_SFX,
			 LOADER_FILENAME_SFX_WIDTH);
}

inline bool
load_db_buffer_init(const struct String *const restrict db_name
		    int *const restrict exit_status)
{
	char load_db_path[PATH_MAX];
	struct StatBuffer stat_buffer;
	int file_descriptor;
	bool success;

	/* open the loader script */
	if (!open_report(&file_descriptor,
			 &load_db_path[0],
			 O_RDONLY,
			 &failure)) {
		print_failure(failure);
		goto EXECUTE_FAILURE_STACK1;
	}






}


#endif /* ifndef MYSQL_SEED_EXECUTE_EXECUTOR_H_ */
