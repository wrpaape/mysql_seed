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
struct CallbackNode {
	const struct HandlerClosure *parent;	/* cleanup parent */
	struct HandlerClosure self;		/* cleanup self */
};

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
	struct RowspanInterval rowspans;	/* X COL_COUNT */
	size_t row_count;			/* either div or mod */
	struct LengthLock total;		/* total block string length */
	char *file_contents;			/* points to file contents */
};


struct RowBlockInterval {
	struct RowBlock *restrict from;
	const struct RowBlock *restrict until;
};

struct Table;

struct Column {
	struct Table *table;			/* length, counter, cleanup */
	struct CountString *counter;		/* access to counter */
	struct RowspanInterval rowspans;	/* X BLK_COUNT */
	struct HandlerClosure fail_cl;		/* cleanup self, then table */
	struct String name;			/* assigned by table */
};

struct ColumnInterval {
	struct Column *restrict from;		/* assigned by db */
	const struct Column *restrict until;	/* assigned by db */
};


/* Table tasks:					ARG
 *	build counter		X 1		upto
 *	build columns, blocks	X COL_COUNT	COL_SPEC
 *	write blocks to file	X BLK_COUNT	Table
 *	*/
struct Table {
	struct LengthLock total;		/* total table length */
	struct ColumnInterval columns;		/* slice assigned by db */
	struct RowBlockInterval row_blocks;	/* slice assigned by db */
	struct CallbackNode cleanup;		/* cleanup self, then db */
	struct CountString counter;		/* ensure 1st task */
	struct FileHandle file;
};

struct TableInterval {
	struct Table *restrict from;		/* assigned by main */
	const struct Table *restrict until;		/* assigned by main */
};


struct Database {
	struct TableInterval tables;
	struct CallbackNode cleanup;		/* cleanup self, then main */
	struct DirHandle dir;
	struct FileHandle loader;
};


/* RowBlock Operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
rowspan_init(struct Rowspan *const restrict rowspan,
	     struct RowBlock *const restrict parent)
{
	rowspan->parent = parent;
}

inline void
rowspan_interval_init(struct RowspanInterval *const restrict interval,
		      struct Rowspan *const restrict from,
		      const struct Rowspan *const restrict until)
{
	interval->from  = from;
	interval->until = until;
}

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

inline void
row_block_interval_init(struct RowBlockInterval *const restrict interval,
			struct RowBlock *const restrict from,
			const struct RowBlock *const restrict until)
{
	interval->from  = from;
	interval->until = until;
}


inline void
column_init(struct Column *const restrict column,
	    struct Table *const restrict table,
	    struct CountString *const restrict counter,
	    struct Rowspan *const restrict rowspans_from,
	    const struct Rowspan *const restrict rowspans_until,
	    char *const restrict column_name_bytes,
	    const size_t column_name_length)
{
	column->table	= table;
	column->counter = counter;

	rowspan_interval_init(&column->rowspans,
			      rowspans_from,
			      rowspans_until);

	column->name.bytes  = column_name_bytes;
	column->name.length = column_name_length;
}




#endif /* ifndef MYSQL_SEED_GENERATE_GENERATE_DATABASE_H_ */
