#ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_
#define MYSQL_SEED_MYSQL_SEED_GENERATE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/generate_db.h" /* file/exit/string/parallelization utils */


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define INVALID_DATABASE_FLAG_HEADER INVALID_FLAG_HEADER("DATABASE")
#define NO_DATABASE_FLAG_MESSAGE     NO_FLAG_MESSAGE("DATABASE")
#define INVALID_DB_NAME_HEADER	     INVALID_SPEC_HEADER("DB_NAME")
#define NO_DB_NAME_MESSAGE	     NO_SPEC_MESSAGE("DB_NAME")
#define DBPG_MALLOC_FAILURE_MESSAGE  MALLOC_FAILURE_MESSAGE("dp_pool_grid_create")


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct DBPoolGrid {
	int exit_status;
	struct ThreadPool **pools;
	const struct ThreadPool **until_ptr;
	struct HandlerClosure fail_cl;
};


/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
print_no_database_flag(void)
{
	write_muffle(STDERR_FILENO,
		     NO_DATABASE_FLAG_MESSAGE,
		     sizeof(NO_DATABASE_FLAG_MESSAGE) - 1lu);

	return EXIT_FAILURE;
}

inline int
print_invalid_database_flag(char *const restrict flag)
{
	char buffer[ERROR_BUFFER_SIZE] = {
		INVALID_DATABASE_FLAG_HEADER
	};

	char *restrict
	ptr = put_string_inspect(&buffer[sizeof(INVALID_DATABASE_FLAG_HEADER)],
				 flag,
				 FLAG_LENGTH_MAX);

	ptr = put_string_size(ptr,
			      MORE_INFO_MESSAGE,
			      sizeof(MORE_INFO_MESSAGE) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);

	return EXIT_FAILURE;
}

/* Init File/DirHandles from input
 *─────────────────────────────────────────────────────────────────────────── */
/* inline void */
/* db_basic_handles_init(struct DirHandle *const restrict db_dir, */
/* 		      struct FileHandle *const restrict loader, */
/* 		      const char *const restrict db_name, */
/* 		      const struct HandlerClosure *const restrict fail_cl) */
/* { */
/* 	const char *restrict failure; */

/* 	size_t size; */

/* 	if (!validate_utf8_input_size(&size, */
/* 				      db_name, */
/* 				      DB_NAME_LENGTH_MAX, */
/* 				      &failure)) { */
/* 		fail_cl->handle(fail_cl->arg, */
/* 				failure); */
/* 		__builtin_unreachable(); */
/* 	} */

/* 	memory_copy(&db_dir->name.buffer[0], */
/* 		    db_name, */
/* 		    size); */

/* 	db_dir->name.length = size - 1lu; */

/* 	db_dir->path.length = db_dir->name.length + DB_DIRPATH_PFX_LENGTH; */

/* 	char *restrict ptr = &db_dir->path.buffer[0]; */

/* 	PUT_STRING_WIDTH(ptr, */
/* 			 DB_DIRPATH_PFX */
/* 			 DB_DIRPATH_PFX_NN_WIDTH); */

/* 	memory_copy(ptr, */
/* 		    db_name, */
/* 		    size); */
/* } */
/* inline void */
/* table_file_init(struct FileHandle *const restrict loader_file, */
/* 		 struct DirHandle *const restrict db_dir) */
/* { */
/* 	char *restrict ptr = &loader_file->name.buffer[0]; */

/* 	PUT_STRING_WIDTH(ptr, */
/* 			 LOADER_FILENAME_PFX, */
/* 			 LOADER_FILENAME_PFX_NN_WIDTH); */

/* 	ptr = put_string_size(ptr, */
/* 			      &db_dir->name.buffer[0], */
/* 			      db_dir->name.length); */

/* 	SET_STRING_WIDTH(ptr, */
/* 			 LOADER_FILENAME_SFX, */
/* 			 LOADER_FILENAME_SFX_WIDTH); */

/* 	loader_file->name.length = LOADER_FILENAME_PFX_LENGTH */
/* 				 + db_dir->name.length */
/* 				 + LOADER_FILENAME_SFX_LENGTH; */

/* 	const name_size = loader_file->name.length + 1lu; */

/* 	loader_file->path.length = name_size */
/* 				 + db_dir->path.length; */

/* 	ptr = put_string_size(&loader_file->path.buffer[0], */
/* 			      &db_dir->path.buffer[0], */
/* 			      db_dir->path.length); */

/* 	*ptr = PATH_DELIM; */
/* 	++ptr; */

/* 	memory_copy(ptr, */
/* 		    &loader_file->name.buffer[0], */
/* 		    name_size); */
/* } */

/* DBPoolGrid operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
db_pool_grid_destroy(struct DBPoolGrid *restrict db_pool_grid)
{
	free(db_pool_grid);
}

/* call only from main thread */
inline void
db_pool_grid_shutdown_failure(struct DBPoolGrid *restrict db_pool_grid,
			      const char *const restrict failure)
{
	const struct ThreadPool *restrict *const restrict until_ptr;
	struct ThreadPool *restrict *restrict pool_ptr;

	until_ptr = db_pool_grid->until_ptr;
	pool_ptr  = db_pool_grid->pools;

	/* signal shutdown */
	while ((pool_ptr < until_ptr) && (*pool_ptr != NULL)) {
		thread_pool_exit_on_failure(*pool_ptr,
					    failure);
		++pool_ptr;
	}

	until_ptr = pool_ptr;
	pool_ptr  = db_pool_grid->pools;

	/* ensure all shutdown and destroyed */
	while (pool_ptr < until_ptr) {
		thread_pool_await_exit_failure(*pool_ptr);

		thread_pool_destroy(*pool_ptr);

		++pool_ptr;
	}
}

inline void
db_pool_grid_shutdown_success(struct DBPoolGrid *restrict db_pool_grid)
{
	const struct ThreadPool *restrict *const restrict until_ptr;
	struct ThreadPool *restrict *restrict pool_ptr;

	until_ptr = db_pool_grid->until_ptr;
	pool_ptr  = db_pool_grid->pools;

	/* signal shutdown */
	while (pool_ptr < until_ptr) {
		thread_pool_stop(*pool_ptr,
				 &db_pool_grid->fail_cl);
		++pool_ptr;
	}

	db_pool_grid->exit_status = EXIT_SUCCESS;

	pool_ptr = db_pool_grid->pools;

	/* ensure all shutdown and destroyed */
	while (pool_ptr < until_ptr) {

		if (thread_pool_exit_status(*pool_ptr,
					    &db_pool_grid->fail_cl)
		    != EXIT_SUCCESS)
			db_pool_grid->exit_status = EXIT_FAILURE;

		thread_pool_destroy(*pool_ptr);

		++pool_ptr;
	}
}

void
db_pool_grid_exit_on_failure(void *db_pools,
			     const char *const restrict failure)
__attribute__((noreturn));

inline void
db_pool_grid_init(struct DBPoolGrid *const restrict db_pool_grid,
		  struct ThreadPool *const restrict *const restrict pools,
		  const size_t count_pools)
{
	db_pool_grid->pools	     = pools;
	db_pool_grid->until_ptr	     = pools + count_pools;
	db_pool_grid->fail_cl.arg    = db_pool_grid;
	db_pool_grid->fail_cl.handle = &db_pool_grid_exit_on_failure;
}

inline struct DBPoolGrid *
db_pool_grid_create(const size_t count_db_specs)
{
	/* malloc buffer for tracking progress of individual database generator
	 * pools */
	struct DBPoolGrid *const restrict db_pool_grid
	= malloc(sizeof(struct DBPoolGrid)
		 + (sizeof(struct ThreadPool *) * count_db_specs));

	if (db_pool_grid != NULL) {
		struct ThreadPool *const restrict *const restrict pools
		= (struct ThreadPool *const restrict *const restrict)
		  (db_pool_grid + 1l);

		db_pool_grid_init(db_pool_grid,
				  pools,
				  count_pools);
	}

	return db_pool_grid;
}

inline int
db_pool_grid_process(struct DBPoolGrid *const restrict db_pool_grid,
		     char *restrict *const restrict db_spec,
		     char *restrict *const restrict next_db_spec,
		     char *const restrict *const restrict until_ptr)
{
	const struct ThreadPool *restrict *const restrict until_ptr;
	struct ThreadPool *restrict *restrict pool_ptr;

	pool_ptr  = db_pool_grid->pools;

	/* create ThreadPool for each db_spec */
	while (1) {
		*pool_ptr = generate_database(db_spec,
					      next_db_spec);

		if (*pool_ptr != NULL)
			++pool_ptr;

		if (next_db_spec == until_ptr)
			break;

		db_spec = next_db_spec;

		next_db_spec = flag_next_until(db_spec + DB_SPEC_LENGTH_MIN,
					       until_ptr,
					       'd',
					       "database");
	}

	db_pool_grid_shutdown_success(db_pool_grid);

	const int exit_status = db_pool_grid->exit_status;

	db_pool_grid_destroy(db_pool_grid);

	return exit_status;
}

/* create and monitor a ThreadPool for each db_spec
 *─────────────────────────────────────────────────────────────────────────── */



/* create a container for monitoring independent db generator pools
 *─────────────────────────────────────────────────────────────────────────── */
inline int
process_db_specs(char *restrict *const restrict db_spec,
		 char *const restrict *const restrict until_ptr)
{
	char *const restrict *const restrict next_db_spec_min
	= db_spec + DB_SPEC_LENGTH_MIN;

	const size_t count_db_specs = 1lu
				    + flag_count_until(next_db_spec_min,
						       until_ptr,
						       'd',
						       "database");

	struct DBPoolGrid *const restrict db_pool_grid =
	db_pool_grid_create(count_db_specs);

	if (db_pool_grid == NULL) {
		write_muffle(STDERR_FILENO,
			     DBPG_MALLOC_FAILURE_MESSAGE,
			     sizeof(DBPG_MALLOC_FAILURE_MESSAGE) - 1lu);
		return EXIT_FAILURE;
	}


	char *const restrict *const restrict next_db_spec
	= flag_next_until(next_db_spec_min,
			  until_ptr,
			  'd',
			  "database");

	return db_pool_grid_process(db_pool_grid,
				    db_spec,
				    next_db_spec,
				    until_ptr);
}


/* dispatch generate mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
generate_dispatch(char *const restrict *const restrict arg_ptr,
		  char *const restrict *const restrict until_ptr)
{
	if (arg_ptr == until_ptr)
		return print_no_database_flag();

	return flag_match(*arg_ptr,
			  'd',
			  "database")
		/* validate 1st flag of 1st DB_SPEC before continuing */
	     ?  process_db_specs(arg_ptr,
				 until_ptr,
				 count_dbs)
	     :  print_invalid_database_flag(*arg_ptr)
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_ */
