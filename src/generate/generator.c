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

/* Rowspan Operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
rowspan_init(struct Rowspan *const restrict rowspan,
	     struct RowBlock *const restrict parent);


/* RowspanInterval Operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
rowspan_interval_init(struct RowspanInterval *const restrict interval,
		      struct Rowspan *const restrict from,
		      const struct Rowspan *const restrict until);

/* RowBlock Operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
row_block_init(struct RowBlock *const restrict row_block,
	       struct Rowspan *restrict rowspan,
	       const struct Rowspan *const restrict rowspans_until,
	       const size_t row_count);

/* RowBlockInterval Operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
row_block_interval_init(struct RowBlockInterval *const restrict interval,
			struct RowBlock *const restrict from,
			const struct RowBlock *const restrict until);

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
				      column->spec.name.bytes,
				      column->spec.name.length);

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
	    const struct Rowspan *const restrict rowspans_until,
	    const struct Table *const restrict parent);

/* ColumnInterval Operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
column_interval_init(struct ColumnInterval *const restrict interval,
		     struct Column *const restrict from,
		     const struct Column *const restrict until);

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
				      table->name.bytes,
				      table->name.length);

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
extern inline void
table_init(struct Table *const restrict table,

/* TableInterval Operations
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
table_interval_init(struct TableInterval *const restrict interval,
		    struct Table *const restrict from,
		    const struct Table *const restrict until);


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
				      database->name.bytes,
				      database->name.length);

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


/* Counter Operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
counter_init(struct Counter *const restrict counter,
	     const size_t upto);

void
counter_exit_on_failure(void *arg,
			const char *restrict failure)
{
	struct Counter *const restrict counter
	= (struct Counter *const restrict) arg;

	struct Generator *const restrict generator
	= counter->parent;

	struct ThreadLog *const restrict generator_log
	= &generator->log;

	mutex_lock_try_catch_open(&generator_log->lock);

	mutex_lock_muffle(&generator_log->lock);

	thread_log_append_string_size(generator_log,
				      COUNTER_FAILURE_MESSAGE,
				      sizeof(COUNTER_FAILURE_MESSAGE) - 1lu);

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
