#ifndef MYSQL_SEED_GENERATE_GENERATE_H_
#define MYSQL_SEED_GENERATE_GENERATE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/loader.h"		/* build_loader */
#include "generate/column_id.h"		/* build_column_id */
#include "generate/column_string.h"	/* build_column_string_base */
#include "generate/table.h"		/* build_table_header */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define GENERATE_FAILURE(REASON)					\
"\n" FAILURE_HEADER_WRAP("generate", " - " REASON)

#define GENERATE_FAILURE_MALLOC						\
GENERATE_FAILURE(MALLOC_FAILURE_REASON)


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct GeneratorCounter {
	uintmax_t rows;
	size_t row_count_max;
	unsigned int columns;
	unsigned int tables;
	unsigned int databases;
};

struct DatabaseCounter {
	uintmax_t rows;
	size_t row_count_max;
	unsigned int columns;
	unsigned int tables;
};


/* Generator/DatbaseCounter operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
generator_counter_update(struct GeneratorCounter *const restrict generator,
			 struct DatabaseCounter *const restrict database)
{
	generator->rows      += database->rows;

	if (database->row_count_max > generator->row_count_max)
		generator->row_count_max = database->row_count_max;

	generator->columns   += database->columns;
	generator->tables    += database->tables;
	generator->databases += 1u;
}


/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
inline void
generate_failure_malloc(void)
{
	write_muffle(STDERR_FILENO,
		     GENERATE_FAILURE_MALLOC,
		     sizeof(GENERATE_FAILURE_MALLOC) - 1lu);
}


/* generate mode
 *─────────────────────────────────────────────────────────────────────────── */
inline void
mysql_seed_generate(const struct GeneratorCounter *const restrict count,
		    const struct DbSpec *restrict db_spec,
		    int *const restrict exit_status)
{
	struct Database *restrict database;
	struct Table *restrict table;
	struct Column *restrict column;
	struct Rowspan *restrict rowspan;
	struct RowBlock *restrict row_block;
	struct RowBlock *restrict row_block_div_until;
	struct TaskNode *restrict prev_node;
	struct TaskNode *restrict next_node;
	struct TblSpec *restrict tbl_spec;
	struct ColSpec *restrict col_spec;
	size_t count_row_blocks_mod;
	size_t count_row_blocks_div;
	unsigned int col_count;

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
		*exit_status = EXIT_FAILURE;
		return;
	}

	database = generator_alloc;

	/* divvy up memory */
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
	prev_node = task_nodes;


	/* Hook up generator pointers
	 * ────────────────────────────────────────────────────────────────── */
	struct Generator generator;

	/* ensure Counter gets assigned first task */
	generator.build.counter_columns_loaders.head = prev_node;

	procedure_closure_init(&prev_node->task,
			       &build_counter,
			       &generator.counter);

	prev_node->prev	= NULL;
	next_node = prev_node + 1l;

	generator.db_specs = db_spec;

	handler_closure_init(&generator->fail_cl,
			     &generator_exit_on_failure,
			     &generator);

	/* initialize counter */
	counter_init(&generator.counter,
		     &generator,
		     count->row_count_max);

	generator.databases.from = database;		     /* <databases> */
	do {
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
		prev_node->next = next_node;

		prev_node = next_node;
		++next_node;

		tbl_spec = db_spec->tbl_specs;
		do {

			length_lock_init(&table->total,
					 0lu);

			table->spec = tbl_spec;

			count_row_blocks_mod = tbl_spec->row_count
					     % row_block_row_count_max;
			count_row_blocks_div = tbl_spec->row_count
					     / row_block_row_count_max;

			row_block_div_until = row_block + count_row_blocks_div;

			length_lock_init(&row_block->total,
					 0lu);
			table->row_blocks.from = row_block;  /* <row_blocks> */

			table->columns.from = column;	     /* <columns> */

			col_spec = tbl_spec->col_specs.from;
			do {

				column->spec = col_spec;

				column->rowspans.from = rowspan;  /* <rspns> */



				++column;

				++col_spec;
			} while (col_spec < tbl_spec->col_specs.until);

			table->row_blocks.until = row_block; /* </row_blocks> */

			table->columns.until = column;	     /* </columns> */

			table->parent = database;

			table->col_count = col_count

			++table;

			tbl_spec = tbl_spec->next;
		} while (tbl_spec != NULL);


		database->tables.until = table;		     /* </tables> */

		++database;

		db_spec = db_spec->next;
	} while (db_spec != NULL);

	generator.databases.until = database;		     /* </databases> */

	/* terminate first task store */
	prev_node->next = NULL;

	generator.build.counter_columns_loaders.last = prev_node;


	/* initialize thread pool */




	free(generator_alloc);
}

#endif /* ifndef MYSQL_SEED_GENERATE_GENERATE_H_ */
