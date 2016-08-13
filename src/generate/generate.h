#ifndef MYSQL_SEED_GENERATE_GENERATE_H_
#define MYSQL_SEED_GENERATE_GENERATE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/loader.h"		/* build_loader */
#include "generate/column_integer.h"	/* build_column_integer_X */
#include "generate/column_string.h"	/* build_column_string_X|uuid */
#include "generate/column_timestamp.h"	/* build_column_timestamp_X */
#include "generate/table.h"		/* build_table_header */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define GENERATE_FAILURE(REASON)					\
"\n" FAILURE_HEADER_WRAP("generate", " - " REASON)

#define GENERATE_FAILURE_MALLOC						\
GENERATE_FAILURE(MALLOC_FAILURE_REASON)

#define GENERATE_FAILURE_CTOR_HEADER					\
FAILURE_HEADER_WRAP("generate constructor", ":") "\n"

#define GENERATE_FAILURE_DTOR_HEADER					\
FAILURE_HEADER_WRAP("generate destructor", ":") "\n"

#define GENERATE_FAILURE_THREAD_POOL_HEADER				\
FAILURE_HEADER_WRAP("generate thread pool", ":") "\n"

/* constructor flags
 *─────────────────────────────────────────────────────────────────────────── */
#define NONE_CTOR_FLAG 0	/* 00000000 */
#define RAND_CTOR_FLAG 1	/* 00000001 */
#define UUID_CTOR_FLAG 3	/* 00000011 (depends on random ctor atm) */

/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct GeneratorCounter {
	unsigned int ctor_flags;
	uintmax_t rows;
	size_t row_count_max;
	unsigned int columns;
	unsigned int tables;
	unsigned int databases;
	size_t counter_upto;
};

struct DatabaseCounter {
	unsigned int ctor_flags;
	uintmax_t rows;
	size_t row_count_max;
	unsigned int columns;
	unsigned int tables;
	size_t counter_upto;
};

/* destructors
 *─────────────────────────────────────────────────────────────────────────── */
inline void
free_columns(struct Column *restrict from,
	     const struct Column *const restrict until)
{
	do {
		free(from->contents);
		++from;
	} while (from < until);
}

inline void
check_remove_loaders_dirs(struct Database *restrict from,
			  const struct Database *const restrict until)
{
	do {
		if (file_handle_unlink_status(&from->loader))
			dirpath_remove_muffle(&from->dirpath);
		++from;
	} while (from < until);
}

inline void
remove_loaders_dirs(struct Database *restrict from,
		    const struct Database *const restrict until)
{
	do {
		file_handle_unlink_muffle(&from->loader);
		dirpath_remove_muffle(&from->dirpath);
		++from;
	} while (from < until);
}

inline void
free_table_files(struct Table *restrict from,
		 const struct Table *const restrict until)
{
	do {
		free(from->file.contents.bytes);
		++from;
	} while (from < until);
}

inline void
remove_free_table_files(struct Table *restrict from,
			const struct Table *const restrict until)
{
	do {
		if (!file_handle_unlink_status(&from->file))
			free(from->file.contents.bytes);
		++from;
	} while (from < until);
}


/* Generator/DatbaseCounter operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
generator_counter_update(struct GeneratorCounter *const restrict generator,
			 struct DatabaseCounter *const restrict database)
{
	generator->ctor_flags |= database->ctor_flags;
	generator->rows	      += database->rows;

	if (database->row_count_max > generator->row_count_max)
		generator->row_count_max = database->row_count_max;

	generator->columns    += database->columns;
	generator->tables     += database->tables;
	++(generator->databases);

	if (database->counter_upto > generator->counter_upto)
		generator->counter_upto = database->counter_upto;
}

inline void
database_counter_init(struct DatabaseCounter *const restrict database,
		      const size_t row_count)
{
	database->ctor_flags	= NONE_CTOR_FLAG;
	database->rows		= row_count;
	database->row_count_max = row_count;
	database->tables	= 1u;
	database->columns	= 1u;
	database->counter_upto	= 0lu;
}


/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
inline void
generate_failure_constructor(const char *const restrict failure)
{
	char buffer[ERROR_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  GENERATE_FAILURE_CTOR_HEADER,
			  sizeof(GENERATE_FAILURE_CTOR_HEADER) - 1lu);

	ptr = put_string(ptr,
			 failure);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
generate_failure_destructor(const char *const restrict failure)
{
	char buffer[ERROR_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  GENERATE_FAILURE_DTOR_HEADER,
			  sizeof(GENERATE_FAILURE_DTOR_HEADER) - 1lu);

	ptr = put_string(ptr,
			 failure);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
generate_failure_malloc(void)
{
	write_muffle(STDERR_FILENO,
		     GENERATE_FAILURE_MALLOC,
		     sizeof(GENERATE_FAILURE_MALLOC) - 1lu);
}

inline void
generate_failure_thread_pool(const char *const restrict failure)
{
	char buffer[ERROR_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  GENERATE_FAILURE_THREAD_POOL_HEADER,
			  sizeof(GENERATE_FAILURE_THREAD_POOL_HEADER) - 1lu);

	ptr = put_string(ptr,
			 failure);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


/* generate mode constructors, destructors
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
mysql_seed_generate_constructors(const unsigned int ctor_flags)
{
	const char *restrict failure;

	/* ensure cwd at project root and trigger thread_utils constructor */
	if (   chdir_report(ROOT_ABSPATH,
			    &failure)
	    && thread_utils_constructor(&failure)) {
		switch (ctor_flags) {
		case RAND_CTOR_FLAG:
			if (random_constructor(&failure))
				return true;

			goto CONSTRUCTOR_FAILURE;

		case UUID_CTOR_FLAG:
			if (uuid_utils_constructor(&failure))
				return true;

			goto CONSTRUCTOR_FAILURE;

		default:
			return true;
		}
	} else {
CONSTRUCTOR_FAILURE:
		generate_failure_constructor(failure);
		return false;
	}
}

inline void
mysql_seed_generate_destructors(int *const restrict exit_status)
{
	const char *restrict failure;

	if (thread_utils_destructor(&failure))
		return;

	generate_failure_destructor(failure);
	*exit_status = EXIT_FAILURE;
}

inline void
mysql_seed_generate_destructors_muffle(void)
{
	thread_utils_destructor_muffle();
}


/* generate mode
 *─────────────────────────────────────────────────────────────────────────── */
inline void
mysql_seed_generate(const struct GeneratorCounter *const restrict count,
		    const struct DbSpec *restrict db_spec,
		    int *const restrict exit_status)
{
	const char *restrict failure;
	struct Database *restrict database;
	struct Table *restrict table;
	struct Column *restrict column;
	struct Rowspan *restrict rowspan;
	const struct Rowspan *restrict rowspans_until;
	struct RowBlock *restrict row_block;
	const struct RowBlock *restrict row_blocks_until;
	struct TaskNode *restrict prev_node;
	struct TaskNode *restrict next_node;
	struct TblSpec *restrict tbl_spec;
	struct ColSpec *restrict col_spec;
	size_t count_row_blocks_mod;
	size_t count_row_blocks_div;
	unsigned int col_count;

	if (!mysql_seed_generate_constructors(count->ctor_flags)) {
		*exit_status = EXIT_FAILURE;
		return;
	}

	const size_t row_block_row_count_max
	= (count->row_count_max < COUNT_WORKERS)
	? count->row_count_max
	: (count->row_count_max / COUNT_WORKERS);

	const size_t count_row_blocks_max = (count->rows
					     / row_block_row_count_max)
					  + count->columns;

	const size_t count_tasks_max
	= 1lu			/* build_counter */
	+ count->columns	/* build_column_X */
	+ count->databases	/* build_loader */
	+ (count->tables * 2lu) /* build_table_header + write_file */
	+ count_row_blocks_max; /* build_table_contents */

	const size_t count_rowspans_max = count_row_blocks_max
					* count->columns;

	struct Database *const restrict generator_alloc
	= malloc(  (sizeof(struct Database) * count->databases)
		 + (sizeof(struct Table)    * count->tables)
		 + (sizeof(struct Column)   * count->columns)
		 + (sizeof(struct Rowspan)  * count_rowspans_max)
		 + (sizeof(struct RowBlock) * count_row_blocks_max)
		 + (sizeof(struct TaskNode) * count_tasks_max));

	if (generator_alloc == NULL) {
		generate_failure_malloc();
		mysql_seed_generate_destructors_muffle();
		*exit_status = EXIT_FAILURE;
		return;
	}

	/* divvy up memory */
	database = generator_alloc;

	struct Table *const restrict tables
	= (struct Table *const restrict) (database + count->databases);
	table = tables;

	struct Column *const restrict columns
	= (struct Column *const restrict) (table + count->tables);
	column = columns;

	struct Rowspan *const restrict rowspans
	= (struct Rowspan *const restrict) (column + count->columns);
	rowspan = rowspans;

	struct RowBlock *const restrict row_blocks
	= (struct RowBlock *const restrict) (rowspan + count_rowspans_max);
	row_block = row_blocks;

	struct TaskNode *const restrict task_nodes
	= (struct TaskNode *const restrict) (row_block + count_row_blocks_max);


	/* Hook up generator pointers
	 * ────────────────────────────────────────────────────────────────── */
	struct Generator generator;

	generator.build.counter_columns_loaders.head = task_nodes;

	/* ensure Counter gets assigned first task if needed */
	if (count->counter_upto > 0) {
		/* initialize counter */
		counter_init(&generator.counter,
			     &generator,
			     count->counter_upto);

		prev_node = task_nodes;

		procedure_closure_init(&prev_node->task,
				       &build_counter,
				       &generator.counter);

		prev_node->prev	= NULL;
		next_node = prev_node + 1l;
		prev_node->next = next_node;


	} else {
		/* nullify so no-op on free */
		counter_nullify_internals(&generator.counter);
		prev_node = NULL;
		next_node = task_nodes;
	}

	/* initialize thread log */
	thread_log_init(&generator.log,
			"generator");

	generator.databases.from = database;		     /* <databases> */

	generator.db_specs = db_spec;

	handler_closure_init(&generator.fail_cl,
			     &generator_exit_on_failure,
			     &generator);

	while (1) {
		database->spec = db_spec;

		database->tables.from = table;		     /* <tables> */

		handler_closure_init(&database->fail_cl,
				     &database_exit_on_failure,
				     database);

		database->parent = &generator;

		procedure_closure_init(&next_node->task,
				       &build_loader,
				       database);

		next_node->prev = prev_node;
		prev_node = next_node;
		++next_node;

		tbl_spec = db_spec->tbl_specs;
		do {
			/* no-op if freed before allocation */
			table->file.contents.bytes = NULL;

			length_lock_init(&table->total,
					 0lu);

			table->spec = tbl_spec;

			count_row_blocks_mod = tbl_spec->row_count
					     % row_block_row_count_max;
			count_row_blocks_div = tbl_spec->row_count
					     / row_block_row_count_max;

			row_blocks_until = row_block + count_row_blocks_div;

			if (count_row_blocks_mod > 0u) {
				++row_blocks_until;
				row_block->row_count = count_row_blocks_mod;
			} else {
				row_block->row_count = row_block_row_count_max;
			}

			/* open first row_block's rowspan interval */
			row_block->rowspans.from = rowspan;

			table->row_blocks.from = row_block;  /* <row_blocks> */

			table->columns.from = column;	     /* <columns> */

			col_spec = tbl_spec->col_specs.from;
			do {
				rowspan->parent = row_block;

				column_init(column,
					    col_spec,
					    rowspan,
					    table);

				procedure_closure_init(&next_node->task,
						       col_spec->build,
						       column);

				next_node->prev = prev_node;
				prev_node->next = next_node;

				prev_node = next_node;
				++next_node;

				++column;
				++rowspan;
				++col_spec;
			} while (col_spec < tbl_spec->col_specs.until);

			col_count = column - table->columns.from;

			table->columns.until = column;	     /* </columns> */

			while (1) {
				length_lock_init(&row_block->total,
						 0lu);

				row_block->rowspans.until = rowspan;

				++row_block;

				if (row_block == row_blocks_until)
					break;

				row_block->rowspans.from = rowspan;

				row_block->row_count = row_block_row_count_max;

				rowspans_until = rowspan + col_count;

				do {
					rowspan->parent = row_block;
					++rowspan;
				} while (rowspan < rowspans_until);
			}

			table->row_blocks.until = row_block; /* </row_blocks> */

			table->parent = database;

			table->rowspans_until = rowspan;

			table->col_count = col_count;

			++table;

			tbl_spec = tbl_spec->next;
		} while (tbl_spec != NULL);

		database->tables.until = table;		     /* </tables> */

		++database;

		db_spec = db_spec->next;

		if (db_spec == NULL) {
			prev_node->next = NULL;
			break;
		}

		prev_node->next = next_node;
	}

	/* terminate first task store */
	generator.build.counter_columns_loaders.last = prev_node;

	generator.databases.until = database;		     /* </databases> */


	/* initialize thread pool */
	thread_pool_init(&generator.pool,
			 &generator.build.counter_columns_loaders,
			 &generator.workers[0],
			 COUNT_WORKERS);

	if (!thread_pool_start(&generator.pool,
			       &failure)) {
		generate_failure_thread_pool(failure);

		free(generator_alloc);

		mysql_seed_generate_destructors_muffle();

		*exit_status = EXIT_FAILURE;
		return;
	}

	/* build next set of tasks */
	generator.build.table_headers.head = next_node;

	next_node->prev = NULL;

	table = tables;

	while (1) {
		procedure_closure_init(&next_node->task,
				       &build_table_header,
				       table);
		++table;
		if (table == (const struct Table *const restrict) columns)
			break;

		prev_node = next_node;

		++next_node;

		prev_node->next = next_node;
		next_node->prev = prev_node;
	}

	generator.build.table_headers.last = next_node;

	next_node->next = NULL;

	/* wait for first set of tasks to complete */
	if (!thread_pool_await(&generator.pool,
			       &failure))
		goto LIVE_POOL_FAILURE_A;


	switch (thread_pool_alive(&generator.pool,
				  &failure)) {
	case THREAD_TRUE:
		break;

	case THREAD_ERROR:	/* pool may still be alive */
LIVE_POOL_FAILURE_A:
		puts("I'M DOING IT");
		fflush(stdout);
		thread_pool_exit_on_failure(&generator.pool,
					    failure);

		thread_pool_await_exit_failure(&generator.pool);

	default:		/* thread died for reasons already reported */
		/* free table files */
		free_table_files(tables,
				 (const struct Table *const restrict) columns);

		/* free columns */
		free_columns(columns,
			     (const struct Column *const restrict) rowspans);

		/* free counter */
		counter_free_internals(&generator.counter);

		/* delete database directories and loaders */
		check_remove_loaders_dirs(generator_alloc,
					  database);

		/* free initial allocation */
		free(generator_alloc);

		/* call generate destructors */
		mysql_seed_generate_destructors_muffle();

		*exit_status = EXIT_FAILURE;
		return;
	}

	/* assign second set of tasks */
	if (!thread_pool_reload(&generator.pool,
				&generator.build.table_headers,
				&failure))
		goto LIVE_POOL_FAILURE_A;

	/* build next set of tasks */
	++next_node;

	generator.build.table_contents.head = next_node;

	next_node->prev = NULL;

	row_blocks_until = row_block;
	row_block = row_blocks;

	while (1) {
		procedure_closure_init(&next_node->task,
				       &build_row_block,
				       row_block);
		++row_block;
		if (row_block == row_blocks_until)
			break;

		prev_node = next_node;

		++next_node;

		prev_node->next = next_node;
		next_node->prev = prev_node;
	}

	generator.build.table_contents.last = next_node;

	next_node->next = NULL;

	/* wait for second set of tasks to complete */
	if (!thread_pool_await(&generator.pool,
			       &failure))
		goto LIVE_POOL_FAILURE_B;

	switch (thread_pool_alive(&generator.pool,
				  &failure)) {
	case THREAD_TRUE:
		break;

	case THREAD_ERROR:	/* pool may still be alive */
LIVE_POOL_FAILURE_B:
		thread_pool_exit_on_failure(&generator.pool,
					    failure);

		thread_pool_await_exit_failure(&generator.pool);

	default:		/* thread died for reasons already reported */
DEAD_POOL_FAILURE_B:
		/* free table files */
		free_table_files(tables,
				 (const struct Table *const restrict) columns);

		/* free columns */
		free_columns(columns,
			     (const struct Column *const restrict) rowspans);

		/* free counter */
		counter_free_internals(&generator.counter);

		/* delete database directories and loaders */
		remove_loaders_dirs(generator_alloc,
				    database);

		/* free initial allocation */
		free(generator_alloc);

		/* call generate destructors */
		mysql_seed_generate_destructors_muffle();

		*exit_status = EXIT_FAILURE;
		return;
	}

	/* assign third set of tasks */
	if (!thread_pool_reload(&generator.pool,
				&generator.build.table_contents,
				&failure))
		goto LIVE_POOL_FAILURE_B;

	/* build fourth and final set of tasks */
	++next_node;

	generator.build.table_files.head = next_node;

	next_node->prev = NULL;

	table = tables;

	while (1) {
		procedure_closure_init(&next_node->task,
				       &build_table_file,
				       table);
		++table;
		if (table == (const struct Table *const restrict) columns)
			break;

		prev_node = next_node;

		++next_node;

		prev_node->next = next_node;
		next_node->prev = prev_node;
	}

	generator.build.table_files.last = next_node;

	next_node->next = NULL;

	/* wait for third set of tasks to complete */
	if (!thread_pool_await(&generator.pool,
			       &failure))
		goto LIVE_POOL_FAILURE_B;


	switch (thread_pool_alive(&generator.pool,
				  &failure)) {
	case THREAD_TRUE:
		break;

	case THREAD_ERROR:
		goto LIVE_POOL_FAILURE_B;

	default:
		goto DEAD_POOL_FAILURE_B;
	}

	/* assign fourth and final set of tasks */
	if (!thread_pool_reload(&generator.pool,
				&generator.build.table_files,
				&failure))
		goto LIVE_POOL_FAILURE_B;

	/* free columns */
	free_columns(columns,
		     (const struct Column *const restrict) rowspans);

	/* wait for fourth and final set of tasks to complete */
	if (   thread_pool_await(&generator.pool,
				 &failure)
	    && thread_pool_stop(&generator.pool,
				&failure)) {

		if (thread_pool_await_exit_success(&generator.pool,
						   &failure)) {
			if (   thread_pool_exit_status(&generator.pool)
			    == EXIT_SUCCESS)
				mysql_seed_generate_destructors(exit_status);
			else
				goto DEAD_POOL_FAILURE_C;
		} else {
			generate_failure_thread_pool(failure);

			thread_pool_cancel(&generator.pool);

			goto DEAD_POOL_FAILURE_C;
		}
	} else {
		thread_pool_exit_on_failure(&generator.pool,
					    failure);

		thread_pool_await_exit_failure(&generator.pool);

DEAD_POOL_FAILURE_C:
		/* remove those that were created, free contents of files not
		 * yet created */
		remove_free_table_files(tables,
					(const struct Table *const restrict)
					columns);

		/* delete database directories and loaders loaders */
		remove_loaders_dirs(generator_alloc,
				    database);

		/* call generate destructors */
		mysql_seed_generate_destructors_muffle();

		*exit_status = EXIT_FAILURE;
	}

	/* free counter */
	counter_free_internals(&generator.counter);

	/* free initial allocation */
	free(generator_alloc);
}

#endif /* ifndef MYSQL_SEED_GENERATE_GENERATE_H_ */
