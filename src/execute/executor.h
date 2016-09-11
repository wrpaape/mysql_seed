#ifndef MYSQL_SEED_EXECUTE_EXECUTOR_H_
#define MYSQL_SEED_EXECUTE_EXECUTOR_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h"	/* exit, file, string utils */
#include "thread/thread_pool.h"	/* ThreadPool */
#include <my_global.h>		/* mysql API */
#include <mysql.h>		/* mysql API */


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
#define MYSQL_DEFAULT_FLAGS	0lu

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
	struct ArgvInterval db_names;
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


#endif /* ifndef MYSQL_SEED_EXECUTE_EXECUTOR_H_ */
