#ifndef MYSQL_SEED_GENERATE_GENERATOR_H_
#define MYSQL_SEED_GENERATE_GENERATOR_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h"	/* file/exit/string/parallelization utils */
#include "thread/thread_pool.h"	/* ThreadPool */


/* minimum valid spec lengths
 *─────────────────────────────────────────────────────────────────────────── */
/* -c COL_NAME COL_TYPE */
#define COL_SPEC_LENGTH_MIN 3lu

/* -t TBL_NAME ROW_COUNT COL_SPEC */
#define TBL_SPEC_LENGTH_MIN (3lu + COL_SPEC_LENGTH_MIN)

/* -d DB_NAME TBL_SPEC */
#define DB_SPEC_LENGTH_MIN  (2lu + TBL_SPEC_LENGTH_MIN)


/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */

/* GENERATOR COMPONENT SPECS
 * ──────────────────────────────────────────────────────────────────────────
 * ────────────────────────────────────────────────────────────────────────── */
/* -c username STRING BASE tastyham		      → tastyham1
 *							tastyham2
 *			   				...
 *			   				tastyham<ROW_COUNT> */
struct StringLengthRange {
	size_t min;
	size_t max;
};

union StringLengthScale {
	struct StringLengthRange range;
	size_t from;
	size_t upto;
	size_t fixed;
};

union StringQualifier {
	union StringLengthScale length_scale;
	const char *base;
};

/* -c temperature UNSIGNED RANGE 500 200000	      → 580
 *							100000
 *							(random in 500..200000)
 *			   				...  */
struct IntegerUnsignedRange {
	uintmax_t min;
	uintmax_t max;
};

union IntegerUnsignedScale {
	struct IntegerUnsignedRange range;
	uintmax_t from;
	uintmax_t upto;
	uintmax_t fixed;
};

/* -c temperature SIGNED RANGE -100 100		      → 45
 *							100
 *							(random in -100..100)
 *			   				...  */
struct IntegerSignedRange {
	intmax_t min;
	intmax_t max;
};

union IntegerSignedScale {
	struct IntegerSignedRange range;
	intmax_t from;
	intmax_t upto;
	intmax_t fixed;
};

union IntegerQualifier {
	union IntegerUnsignedScale unsigned_scale;
	union IntegerSignedScale signed_scale;
};

/* -c temperature FLOAT RANGE 1 500.25		      → 300.2334
 *							1.0000000
 *							(random in 1..500.25)
 *			   				...  */
struct FloatRange {
	long double min;
	long double max;
};

union FloatScale {
	struct FloatRange range;
	long double from;
	long double upto;
	long double fixed;
};

struct FloatQualifier {
	union FloatScale scale;
	unsigned int precision;
};

union TypeQualifier {
	union StringQualifier string;
	union IntegerQualifier integer;
	struct FloatQualifier flt_pt;
};

struct ColSpec {
	struct String name;
	union TypeQualifier type;
	Procedure *build;
};

struct ColSpecInterval {
	const struct ColSpec *restrict from;
	const struct ColSpec *restrict until;
};

struct TblSpec {
	struct String name;
	size_t row_count;
	struct ColSpecInterval col_specs;
};

struct TblSpecInterval {
	const struct TblSpec *restrict from;
	const struct TblSpec *restrict until;
};

struct DbSpec {
	struct String name;
	struct TblSpecInterval tbl_specs;
	struct DbSpec *next;		/* next valid db_spec */
};

struct DbSpecInterval {
	const struct DbSpec *restrict from;
	const struct DbSpec *restrict until;
};



/* GENERATOR COMPONENTS
 * ──────────────────────────────────────────────────────────────────────────
 * ────────────────────────────────────────────────────────────────────────── */
struct RowBlock;

struct Rowspan {
	struct RowBlock *parent;	/* get row_count, update total block length */
	char *cell;			/* points to first cell */
};

struct RowspanInterval {
	struct Rowspan *restrict from;
	const struct Rowspan *restrict until;
};

struct RowBlock {
	struct LengthLock total;		/* total block string length */
	struct RowspanInterval rowspans;	/* X COL_COUNT */
	size_t row_count;			/* either div or mod */
	char *contents;				/* table file block */
};


struct RowBlockInterval {
	struct RowBlock *restrict from;
	const struct RowBlock *restrict until;
};

struct Table;

struct Column {
	const struct ColSpec *spec;		/* from raw input */
	char *contents;
	struct RowspanInterval rowspans;	/* X BLK_COUNT */
	struct HandlerClosure fail_cl;		/* cleanup self, then table */
	struct Table *parent;			/* length, counter, cleanup */
};

struct ColumnInterval {
	struct Column *restrict from;		/* assigned by db */
	const struct Column *restrict until;	/* assigned by db */
};

struct Database;

/* Table tasks:					ARG
 *	build columns, blocks	X COL_COUNT	COL_SPEC
 *	write blocks to file	X BLK_COUNT	Table
 *	*/

struct Table {
	struct FileHandle file;
	struct LengthLock total;		/* total table length */
	char *contents;				/* table file start */
	struct TblSpec *spec;			/* from raw input */
	struct ColumnInterval columns;		/* slice assigned by db */
	struct RowBlockInterval row_blocks;	/* slice assigned by db */
	struct HandlerClosure fail_cl;		/* cleanup self, then db */
	struct Database *parent;
};

struct TableInterval {
	struct Table *restrict from;		/* assigned by main */
	const struct Table *restrict until;	/* assigned by main */
};

struct Generator;

struct Database {
	struct FileHandle loader;
	struct DirHandle dir;
	struct LengthLock total;		/* total database length */
	char *contents;				/* table files and loader */
	struct String name;			/* raw input */
	struct DbSpec *spec;			/* from raw input */
	struct TableInterval tables;
	struct HandlerClosure fail_cl;		/* cleanup self, then main */
	struct Generator *parent;
};

struct DatabaseInterval {
	struct Database *restrict from;		/* assigned by main */
	const struct Database *restrict until;	/* assigned by main */
};

struct Counter {
	Mutex processing;	/* condition lock */
	ThreadCond done;	/* broadcasted once 'pointers' are set */
	bool ready;	/* flipped true once 'pointers' are set */
	char *digits;		/* "1", "2", "3", ..., "$(upto)" */
	char **pointers;	/* digit pointers */
	size_t upto;		/* final and max stringified number */
	size_t size_digits;	/* sizeof("1", "2", ... "$(upto)") */
	unsigned int mag_upto;	/* ⌊ log₁₀(upto) ⌋ */
	struct HandlerClosure fail_cl;	/* cleanup self, then main */
	struct Generator *parent;
};

struct Generator {
	struct ThreadPool pool;			/* all child threads */
	struct ThreadLog log;
	struct Counter counter;			/* shared by all */
	struct LengthLock total;		/* total file length */
	struct DatabaseInterval databases;
	struct DbSpecInterval *db_specs;	/* from raw input */
	char *contents;				/* buffer for all files */
};

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define COLUMN_FAILURE_MESSAGE_1					\
"\n" ANSI_UNDERLINE "COLUMN " ANSI_BRIGHT
#define COLUMN_FAILURE_MESSAGE_2					\
ANSI_NORMAL " EXITING ON FAILURE" ANSI_NO_UNDERLINE "\n"

#define TABLE_FAILURE_MESSAGE_1						\
"\n" ANSI_UNDERLINE "TABLE " ANSI_BRIGHT
#define TABLE_FAILURE_MESSAGE_2						\
ANSI_NORMAL " EXITING ON FAILURE" ANSI_NO_UNDERLINE "\n"

#define DATABASE_FAILURE_MESSAGE_1					\
"\n" ANSI_UNDERLINE "DATABASE " ANSI_BRIGHT
#define DATABASE_FAILURE_MESSAGE_2					\
ANSI_NORMAL " EXITING ON FAILURE" ANSI_NO_UNDERLINE "\n"

#define COUNTER_FAILURE_MESSAGE						\
"\n" ANSI_UNDERLINE "COUNTER EXITING ON FAILURE" ANSI_NO_UNDERLINE "\n"

#define GENERATOR_FAILURE_MESSAGE					\
"\n" ANSI_UNDERLINE "GENERATOR EXITING ON FAILURE" ANSI_NO_UNDERLINE "\n"

/* Rowspan Operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
rowspan_init(struct Rowspan *const restrict rowspan,
	     struct RowBlock *const restrict parent)
{
	rowspan->parent = parent;
}

/* RowspanInterval Operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
rowspan_interval_init(struct RowspanInterval *const restrict interval,
		      struct Rowspan *const restrict from,
		      const struct Rowspan *const restrict until)
{
	interval->from  = from;
	interval->until = until;
}

/* RowBlock Operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
row_block_init(struct RowBlock *const restrict row_block,
	       struct Rowspan *restrict rowspan,
	       const struct Rowspan *const restrict rowspans_until,
	       const size_t row_count)
{
	length_lock_init(&row_block->total,
			 0lu);

	rowspan_interval_init(&row_block->rowspans,
			      rowspan,
			      rowspans_until);

	do {
		rowspan_init(rowspan,
			     row_block);
		++rowspan;
	} while (rowspan < rowspans_until);


	row_block->row_count = row_count;
}


/* RowBlockInterval Operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
row_block_interval_init(struct RowBlockInterval *const restrict interval,
			struct RowBlock *const restrict from,
			const struct RowBlock *const restrict until)
{
	interval->from  = from;
	interval->until = until;
}


/* Column Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
column_exit_on_failure(void *arg,
		       const char *restrict faliure)
__attribute__((noreturn));

inline void
column_init(struct Column *const restrict column,
	    const struct ColSpec *const restrict spec,
	    struct Rowspan *const restrict rowspans_from,
	    const struct Rowspan *const restrict rowspans_until,
	    struct Table *const restrict parent)
{
	column->spec = spec;

	column->contents = NULL; /* no-op in free on early exit */

	rowspan_interval_init(&column->rowspans,
			      rowspans_from,
			      rowspans_until);

	handler_closure_init(&column->fail_cl,
			     &column_exit_on_failure,
			     column);

	column->parent = parent;
}

/* ColumnInterval Operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
column_interval_init(struct ColumnInterval *const restrict interval,
		     struct Column *const restrict from,
		     const struct Column *const restrict until)
{
	interval->from  = from;
	interval->until = until;
}


/* Table Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
table_exit_on_failure(void *arg,
		      const char *restrict faliure)
__attribute__((noreturn));

inline void
table_init(struct Table *const restrict table,
	   struct Database *const restrict parent,
	   struct Column *const restrict columns_from,
	   const struct Column *const restrict columns_until,
	   struct RowBlock *const restrict rowblocks_from,
	   const struct RowBlock *const restrict rowblocks_until,
	   char *const restrict table_name_bytes,
	   const size_t table_name_length)
{
	table->parent = parent;

	length_lock_init(&table->total,
			 0lu);

	column_interval_init(&table->columns,
			     columns_from,
			     columns_until);

	row_block_interval_init(&table->row_blocks,
				row_blocks_from,
				row_blocks_until);

	string_init(&table->name,
		    table_name_bytes,
		    table_name_length);

	handler_closure_init(&table->fail_cl,
			     &table_exit_on_failure,
			     table);
}


/* TableInterval Operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
table_interval_init(struct TableInterval *const restrict interval,
		    struct Table *const restrict from,
		    const struct Table *const restrict until)
{
	interval->from	= from;
	interval->until = until;
}


/* Database Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
database_exit_on_failure(void *arg,
			 const char *restrict faliure)
__attribute__((noreturn));

inline void
database_init(struct Database *const restrict database,
	      struct Generator *const restrict parent,
	      struct Table *const restrict tables_from,
	      const struct Table *const restrict tables_until,
	      char *const restrict database_name_bytes,
	      const size_t database_name_length)
{
	database->parent = parent;

	length_lock_init(&database->total,
			 0lu);

	table_interval_init(&database->tables,
			    tables_from,
			    tables_until);

	string_init(&database->name,
		    database_name_bytes,
		    database_name_length);

	handler_closure_init(&database->fail_cl,
			     &database_exit_on_failure,
			     database);
}


/* Counter Operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
counter_init(struct Counter *const restrict counter,
	     struct Generator *const restrict parent,
	     const size_t upto)
{
	mutex_init(&counter->processing);
	thread_cond_init(&counter->done);

	counter->ready = false;
	counter->upto  = upto;

	handler_closure_init(&counter->fail_cl,
			     &counter_exit_on_failure,
			     counter);
}

void
counter_exit_on_failure(void *arg,
			const char *restrict failure)
__attribute__((noreturn));


/* Generator Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
generator_exit_on_failure(void *arg,
			  const char *restrict failure)
__attribute__((noreturn));


#endif /* ifndef MYSQL_SEED_GENERATE_GENERATOR_H_ */
