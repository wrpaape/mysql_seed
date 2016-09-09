#ifndef MYSQL_SEED_EXECUTE_EXECUTOR_H_
#define MYSQL_SEED_EXECUTE_EXECUTOR_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */

/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define COUNT_EXECUTOR_WORKERS 4lu

/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct MysqlServer {
	Mutex query_lock;
	MYSQL *connection;
};

struct Credentials {
	const char *host;
	const char *user;
	const char *password;
	unsigned int port;
	const char *socket;
	unsigned long flags;
};

struct Executor {
	struct ThreadPool pool;	/* all child threads */
	struct Worker workers[COUNT_EXECUTOR_WORKERS];
	struct TaskStore load_databases;
	struct MysqlServer server;
	struct Credentials con_spec;
};


void
load_database(void *arg);

#endif /* ifndef MYSQL_SEED_EXECUTE_EXECUTOR_H_ */
