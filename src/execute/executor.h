#ifndef MYSQL_SEED_EXECUTE_EXECUTOR_H_
#define MYSQL_SEED_EXECUTE_EXECUTOR_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h"	/* exit, file, string utils */
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
	struct ExecSpec *exec_spec;
	int *exit_status;
};


struct ExecArg {
	struct Executor *executor;
};


void
load_database(void *arg);

#endif /* ifndef MYSQL_SEED_EXECUTE_EXECUTOR_H_ */
