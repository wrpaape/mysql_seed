#ifndef MYSQL_SEED_EXECUTE_EXECUTE
#define MYSQL_SEED_EXECUTE_EXECUTE

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "execute/executor.h"	/* mysql API, ExecSpec, Executor */


/* error messages
 * ────────────────────────────────────────────────────────────────────────── */
#define EXECUTE_FAILURE(REASON)						\
"\n" FAILURE_HEADER_WRAP("execute", " - " REASON)

#define EXECUTE_FAILURE_MALLOC						\
EXECUTE_FAILURE(MALLOC_FAILURE_REASON)

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

	PUT_STRING_WIDTH(load_db_path,
			 LOADER_FILENAME_PFX,
			 LOADER_FILENAME_PFX_NN_WIDTH);

	load_db_path = put_string_size(load_db_path,
				       db_name->bytes,
				       db_name->length);

	SET_STRING_WIDTH(load_db_path,
			 LOADER_FILENAME_SFX,
			 LOADER_FILENAME_SFX_WIDTH);
}


inline int
mysql_seed_execute(const char *const restrict user,
		   const char *const restrict password,
		   const struct String *const restrict db_name)
{
	char load_db_path[PATH_MAX];
	MYSQL connection;
	struct StatBuffer stat_buffer;
	const char *restrict failure;
	int file_descriptor;

	if (mysql_init(&connection) == NULL) {
		mysql_init_failure(&connection);
		return EXIT_FAILURE;
	}

	if (mysql_real_connect(&connection,
			       MYSQL_DEFAULT_HOST,
			       user,
			       password,
			       MYSQL_DEFAULT_DB,
			       MYSQL_DEFAULT_PORT,
			       MYSQL_DEFAULT_SOCKET,
			       MYSQL_DEFAULT_FLAGS) == NULL) {
		mysql_real_connect_failure(&connection);
		mysql_close(&connection);
		return EXIT_FAILURE;
	}

	load_db_path_init(&load_db_path[0],
			  db_name);

	/* open the loader script */
	if (!open_report(&file_descriptor,
			 &load_db_path[0],
			 O_RDONLY,
			 &failure)) {
		print_failure(failure);
		close_muffle(file_descriptor);
		mysql_close(&connection);
		return EXIT_FAILURE;
	}

	/* load loader script into main memory buffer */
	if (UNLIKELY(!fstat_report(file_descriptor,
				   &stat_buffer,
				   &failure))) {
		print_failure(failure);
		close_muffle(file_descriptor);
		mysql_close(&connection);
		return EXIT_FAILURE;
	}

	char *const restrict load_db_buffer = malloc(stat_buffer.st_size);

	if (UNLIKELY(load_db_buffer == NULL)) {
		execute_failure_malloc();
		close_muffle(file_descriptor);
		mysql_close(&connection);
		return EXIT_FAILURE;
	}

	if (UNLIKELY(!read_report(file_descriptor,
				  load_db_buffer,
				  stat_buffer.st_size,
				  &failure))) {
		print_failure(failure);
		free(load_db_buffer);
		close_muffle(file_descriptor);
		mysql_close(&connection);
		return EXIT_FAILURE;
	}

	if (UNLIKELY(mysql_real_query(&connection,
				      load_db_buffer,
				      stat_buffer.st_size) != 0)) {
		mysql_real_query_failure(&connection);
		free(load_db_buffer);
		close_muffle(file_descriptor);
		mysql_close(&connection);
		return EXIT_FAILURE;
	}

	free(load_db_buffer);

	if (UNLIKELY(!close_report(file_descriptor,
				   &failure))) {
		print_failure(failure);
		mysql_close(&connection);
		return EXIT_FAILURE;
	}

	mysql_close(&connection);
	return EXIT_SUCCESS;
}

inline int
mysql_seed_execute_multi(const struct ExecSpec *const restrict exec_spec)
{
	return EXIT_FAILURE;
}

/* worker entry point */
void
load_database(void *arg);

#endif /* ifndef MYSQL_SEED_EXECUTE_EXECUTE */
