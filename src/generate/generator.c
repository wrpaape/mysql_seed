#include "generate/generator.h"

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
	       struct Rowspan *const restrict rowspans_from,
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

	thread_log_append_string(generator_log,
				 COLUMN_FAILURE_MESSAGE_1);

	thread_log_append_string(generator_log,
				 column->name.bytes);

	thread_log_append_string(generator_log,
				 COLUMN_FAILURE_MESSAGE_2);

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
	    struct Table *const restrict parent,
	    struct CountString *const restrict counter,
	    struct Rowspan *const restrict rowspans_from,
	    const struct Rowspan *const restrict rowspans_until,
	    char *const restrict column_name_bytes,
	    const size_t column_name_length);

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

	thread_log_append_string(generator_log,
				 TABLE_FAILURE_MESSAGE_1);

	thread_log_append_string(generator_log,
				 table->name.bytes);

	thread_log_append_string(generator_log,
				 TABLE_FAILURE_MESSAGE_2);

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
	   struct Database *const restrict parent,
	   struct Column *const restrict columns_from,
	   const struct Column *const restrict columns_until,
	   struct RowBlock *const restrict rowblocks_from,
	   const struct RowBlock *const restrict rowblocks_until,
	   char *const restrict column_name_bytes,
	   const size_t column_name_length);

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

	thread_log_append_string(generator_log,
				 DATABASE_FAILURE_MESSAGE_1);

	thread_log_append_string(generator_log,
				 database->name.bytes);

	thread_log_append_string(generator_log,
				 DATABASE_FAILURE_MESSAGE_2);

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

	thread_log_append_string(generator_log,
				 COUNTER_FAILURE_MESSAGE_1);

	thread_log_append_string(generator_log,
				 counter->name.bytes);

	thread_log_append_string(generator_log,
				 COUNTER_FAILURE_MESSAGE_2);

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

	thread_log_append_string(generator_log,
				 GENERATOR_FAILURE_MESSAGE_1);

	thread_log_append_string(generator_log,
				 generator->name.bytes);

	thread_log_append_string(generator_log,
				 GENERATOR_FAILURE_MESSAGE_2);

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
