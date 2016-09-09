#include "generate/generator.h"

/* init Generator FileHandle, Dirpath
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
database_dirpath_init(struct Dirpath *const restrict dirpath,
		      const struct String *const restrict db_name);

extern inline void
table_file_init(struct FileHandle *const restrict file,
		const struct String *const restrict tbl_name,
		const struct Dirpath *const restrict db_dirpath);

extern inline void
loader_file_init(struct FileHandle *const restrict file,
		 const struct String *const restrict db_name,
		 const struct Dirpath *const restrict db_dirpath);


/* Column Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
column_exit_on_failure(void *arg,
		       const char *restrict failure)
{
	struct Column *const restrict column
	= (struct Column *const restrict) arg;

	struct Table *const restrict table
	= column->parent;

	struct ThreadLog *const restrict generator_log
	= &table->parent->parent->log;

	mutex_lock_try_catch_open(&generator_log->lock);

	mutex_lock_muffle(&generator_log->lock);

	thread_log_append_string_size(generator_log,
				      COLUMN_FAILURE_MESSAGE_1,
				      sizeof(COLUMN_FAILURE_MESSAGE_1) - 1lu);

	thread_log_append_string_size(generator_log,
				      column->spec->name.bytes,
				      column->spec->name.length);

	thread_log_append_string_size(generator_log,
				      COLUMN_FAILURE_MESSAGE_2,
				      sizeof(COLUMN_FAILURE_MESSAGE_2) - 1lu);

	thread_log_append_string(generator_log,
				 failure);

	mutex_unlock_muffle(&generator_log->lock);

	mutex_lock_try_catch_close();

	handler_closure_call(&table->fail_cl,
			     failure);
	__builtin_unreachable();
}

extern inline void
column_init(struct Column *const restrict column,
	    const struct ColSpec *const restrict spec,
	    struct Rowspan *const restrict rowspans_from,
	    struct Table *const restrict parent);


/* Table Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
table_exit_on_failure(void *arg,
		      const char *restrict failure)
{
	struct Table *const restrict table
	= (struct Table *const restrict) arg;

	struct Database *const restrict database
	= table->parent;

	struct ThreadLog *const restrict generator_log
	= &database->parent->log;

	mutex_lock_try_catch_open(&generator_log->lock);

	mutex_lock_muffle(&generator_log->lock);

	thread_log_append_string_size(generator_log,
				      TABLE_FAILURE_MESSAGE_1,
				      sizeof(TABLE_FAILURE_MESSAGE_1) - 1lu);

	thread_log_append_string_size(generator_log,
				      table->spec->name.bytes,
				      table->spec->name.length);

	thread_log_append_string_size(generator_log,
				      TABLE_FAILURE_MESSAGE_2,
				      sizeof(TABLE_FAILURE_MESSAGE_2) - 1lu);

	thread_log_append_string(generator_log,
				 failure);

	mutex_unlock_muffle(&generator_log->lock);

	mutex_lock_try_catch_close();

	handler_closure_call(&table->fail_cl,
			     failure);
	__builtin_unreachable();
}


/* Database Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
database_exit_on_failure(void *arg,
			 const char *restrict failure)
{
	struct Database *const restrict database
	= (struct Database *const restrict) arg;

	struct Generator *const restrict generator
	= database->parent;

	struct ThreadLog *const restrict generator_log
	= &generator->log;

	mutex_lock_try_catch_open(&generator_log->lock);

	mutex_lock_muffle(&generator_log->lock);

	thread_log_append_string_size(generator_log,
				      DATABASE_FAILURE_MESSAGE_1,
				      sizeof(DATABASE_FAILURE_MESSAGE_1) - 1lu);

	thread_log_append_string_size(generator_log,
				      database->spec->name.bytes,
				      database->spec->name.length);

	thread_log_append_string_size(generator_log,
				      DATABASE_FAILURE_MESSAGE_2,
				      sizeof(DATABASE_FAILURE_MESSAGE_2) - 1lu);

	thread_log_append_string(generator_log,
				 failure);

	mutex_unlock_muffle(&generator_log->lock);

	mutex_lock_try_catch_close();

	handler_closure_call(&generator->fail_cl,
			     failure);
	__builtin_unreachable();
}


/* Generator Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
generator_exit_on_failure(void *arg,
			  const char *restrict failure)
{
	struct Generator *const restrict generator
	= (struct Generator *const restrict) arg;

	struct ThreadLog *const restrict generator_log
	= &generator->log;

	mutex_lock_try_catch_open(&generator_log->lock);

	mutex_lock_muffle(&generator_log->lock);

	thread_log_append_string_size(generator_log,
				      GENERATOR_FAILURE_MESSAGE,
				      sizeof(GENERATOR_FAILURE_MESSAGE) - 1lu);

	thread_log_append_string(generator_log,
				 failure);

	thread_log_append_close(generator_log);

	thread_log_dump_muffle(generator_log,
			       STDERR_FILENO);

	mutex_unlock_muffle(&generator_log->lock);

	mutex_lock_try_catch_close();

	/* exit all threads */
	thread_pool_exit_on_failure(&generator->pool,
				    failure);

	thread_exit();
	__builtin_unreachable();
}
