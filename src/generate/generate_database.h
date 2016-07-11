#ifndef MYSQL_SEED_GENERATE_GENERATE_DATABASE_H_
#define MYSQL_SEED_GENERATE_GENERATE_DATABASE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h" /* file/exit/string/parallelization utils */


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

/* COL_SPEC COMPONENTS
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
	size_t from;
	size_t upto;
	size_t fixed;
	struct StringLengthRange range;
};

union StringQualifier {
	const char *base;
	union StringLengthScale length_scale;
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
	uintmax_t from;
	uintmax_t upto;
	uintmax_t fixed;
	struct IntegerUnsignedRange range;
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
	intmax_t from;
	intmax_t upto;
	intmax_t fixed;
	struct IntegerSignedRange range;
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
	unsigned int precision;
	union FloatScale scale;
};

union TypeQualifier {
	union StringQualifier string;
	union IntegerQualifier integer;
	union FloatQualifier flt_pt;
};

struct ColSpec {
	Procedure *build;
	union TypeQualifier type;
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
	char *contents;				/* table file block */
	struct RowspanInterval rowspans;	/* X COL_COUNT */
	size_t row_count;			/* either div or mod */
	struct LengthLock total;		/* total block string length */
};


struct RowBlockInterval {
	struct RowBlock *restrict from;
	const struct RowBlock *restrict until;
};

struct Table;

struct Column {
	struct Table *parent;			/* length, cleanup */
	struct CountString *counter;		/* access to shared counter */
	struct RowspanInterval rowspans;	/* X BLK_COUNT */
	struct String name;			/* raw input */
	struct ColSpec spec;			/* raw input */
	struct HandlerClosure fail_cl;		/* cleanup self, then table */
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
	char *contents;				/* table file */
	struct Database *parent;
	struct LengthLock total;		/* total table length */
	struct ColumnInterval columns;		/* slice assigned by db */
	struct RowBlockInterval row_blocks;	/* slice assigned by db */
	struct String name;			/* raw input */
	struct HandlerClosure fail_cl;		/* cleanup self, then db */
	struct FileHandle file;
};

struct TableInterval {
	struct Table *restrict from;		/* assigned by main */
	const struct Table *restrict until;	/* assigned by main */
};

struct Generator;

struct Database {
	char *contents;				/* table files and loader */
	struct Generator *parent;
	struct LengthLock total;		/* total database length */
	struct TableInterval tables;
	struct String name;			/* raw input */
	struct HandlerClosure fail_cl;		/* cleanup self, then main */
	struct DirHandle dir;
	struct FileHandle loader;
};

struct DatabaseInterval {
	struct Database *restrict from;		/* assigned by main */
	const struct Database *restrict until;	/* assigned by main */
};

struct Generator {
	char *contents;				/* buffer for all files */
	struct LengthLock total;		/* total file length */
	struct DatabaseInterval databases;
	struct CountString counter;		/* ensure 1st task */
	struct ThreadPool pool;			/* all child threads */
	struct ThreadLog log;
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

#define GENERATOR_FAILURE_MESSAGE_1					\
"\n" ANSI_UNDERLINE "GENERATOR " ANSI_BRIGHT
#define GENERATOR_FAILURE_MESSAGE_2					\
ANSI_NORMAL " EXITING ON FAILURE" ANSI_NO_UNDERLINE "\n"

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
	       struct Rowspan *const restrict rowspans_from,
	       const struct Rowspan *const restrict rowspans_until,
	       const size_t row_count)
{
	rowspan_init(rowspans_from,
		     row_block);

	rowspan_interval_init(&row_block->rowspans,
			      rowspans_from,
			      rowspans_until);

	row_block->row_count = row_count;

	length_lock_init(&row_block->total,
			 0lu);
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
	    struct Table *const restrict parent,
	    struct CountString *const restrict counter,
	    struct Rowspan *const restrict rowspans_from,
	    const struct Rowspan *const restrict rowspans_until,
	    char *const restrict column_name_bytes,
	    const size_t column_name_length)
{
	column->parent	= parent;
	column->counter = counter;

	rowspan_interval_init(&column->rowspans,
			      rowspans_from,
			      rowspans_until);

	string_init(&column->name,
		    column_name_bytes,
		    column_name_length);

	handler_closure_init(&column->fail_cl,
			     &column_exit_on_failure,
			     column);
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



#endif /* ifndef MYSQL_SEED_GENERATE_GENERATE_DATABASE_H_ */
