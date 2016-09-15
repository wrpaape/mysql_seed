#ifndef MYSQL_SEED_EXECUTE_EXECUTE
#define MYSQL_SEED_EXECUTE_EXECUTE

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "execute/executor.h"	/* mysql API, ExecSpec, Executor */


/* error messages
 * ────────────────────────────────────────────────────────────────────────── */
#define MYSQL_INIT_FAILURE_HEADER					\
FAILURE_HEADER_REASON("mysql_init")

#define MYSQL_REAL_CONNECT_FAILURE_HEADER				\
FAILURE_HEADER_REASON("mysql_real_connect")

#define MYSQL_REAL_QUERY_FAILURE_HEADER					\
FAILURE_HEADER_REASON("mysql_real_query")


/* macro constants
 * ────────────────────────────────────────────────────────────────────────── */
#define MYSQL_ERROR_BUFFER_SIZE 512lu

/* print error
 * ────────────────────────────────────────────────────────────────────────── */
inline void
mysql_init_failure(MYSQL *const restrict connection)
{
	char buffer[MYSQL_ERROR_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  MYSQL_INIT_FAILURE_HEADER,
			  sizeof(MYSQL_INIT_FAILURE_HEADER) - 1lu);

	ptr = put_string(ptr,
			 mysql_error(connection));

	PUT_STRING_WIDTH(ptr,
			 ERROR_CLOSE,
			 ERROR_CLOSE_WIDTH);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
mysql_real_connect_failure(MYSQL *const restrict connection)
{
	char buffer[MYSQL_ERROR_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  MYSQL_REAL_CONNECT_FAILURE_HEADER,
			  sizeof(MYSQL_REAL_CONNECT_FAILURE_HEADER) - 1lu);

	ptr = put_string(ptr,
			 mysql_error(connection));

	PUT_STRING_WIDTH(ptr,
			 ERROR_CLOSE,
			 ERROR_CLOSE_WIDTH);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
mysql_real_query_failure(MYSQL *const restrict connection)
{
	char buffer[MYSQL_ERROR_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  MYSQL_REAL_QUERY_FAILURE_HEADER,
			  sizeof(MYSQL_REAL_QUERY_FAILURE_HEADER) - 1lu);

	ptr = put_string(ptr,
			 mysql_error(connection));

	PUT_STRING_WIDTH(ptr,
			 ERROR_CLOSE,
			 ERROR_CLOSE_WIDTH);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


/* load database(s) into server
 * ────────────────────────────────────────────────────────────────────────── */
/* load a single database into MySQL server */
inline void
execute_single(MYSQL *const restrict connection,
	       const struct String *const restrict db_name,
	       int *const restrict exit_status)
{
	struct String query;
	const char *restrict failure;

	if (query_load_report(&query,
			      db_name,
			      &failure)) {
		if (UNLIKELY(mysql_real_query(connection,
					      query.bytes,
					      query.length) != 0)) {
			mysql_real_query_failure(connection);
			*exit_status = EXIT_FAILURE;
		}

		free(query.bytes);

	} else {
		print_failure(failure);
		*exit_status = EXIT_FAILURE;
	}
}

/* load a multiple databases into MySQL server in parallel */
inline void
execute_multiple(MYSQL *const restrict connection,
		 const struct StringInterval *const restrict db_names,
		 const unsigned int count_db_names,
		 int *const restrict exit_status)
{
}


/* connect to server then dispatch loading
 * ────────────────────────────────────────────────────────────────────────── */
inline void
mysql_seed_execute(const struct MysqlCredentials *const restrict creds,
		   const struct StringInterval *const restrict db_names,
		   const unsigned int count_db_names,
		   int *const restrict exit_status)
{
	MYSQL connection;

	if (UNLIKELY(mysql_init(&connection) == NULL)) {
		mysql_init_failure(&connection);
		*exit_status = EXIT_FAILURE;

	} else {
		if (MYSQL_REAL_CONNECT(&connection,
				       creds->user,
				       creds->password.bytes) == NULL) {
			mysql_real_connect_failure(&connection);
			*exit_status = EXIT_FAILURE;

		} else if (count_db_names == 1u) {
			execute_single(&connection,
				       db_names->from,
				       exit_status);

		} else {
			execute_multiple(&connection,
					 db_names,
					 count_db_names,
					 exit_status);
		}

		mysql_close(&connection);
	}
}

/* worker entry point */
void
load_database(void *arg);

#endif /* ifndef MYSQL_SEED_EXECUTE_EXECUTE */
