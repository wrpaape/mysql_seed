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

struct Block;

struct Rowspan {
	struct Block *parent;	/* get row_count, update total block length */
	char *cell;		/* points to first cell */
};

struct RowspanInterval {
	struct Rowspan *restrict start_ptr;
	const struct Rowspan *restrict until_ptr;
};

struct Block {
	struct RowspanInterval rowspans;	/* X COL_COUNT */
	size_t row_count;			/* either div or mod */
	struct LengthLock total;		/* total block string length */
	char *file_contents;			/* points to file contents */
};


struct BlockInterval {
	struct Block *restrict start_ptr;
	const struct Block *restrict until_ptr;
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
	struct Column *restrict start_ptr;		/* assigned by db */
	const struct Column *restrict until_ptr;	/* assigned by db */
};


/* Table tasks:					ARG
 *	build counter		X 1		upto
 *	build columns, blocks	X COL_COUNT	COL_SPEC
 *	write blocks to file	X BLK_COUNT	Table
 *	*/
struct Table {
	struct LengthLock total;		/* total table length */
	struct ColumnInterval columns;		/* slice assigned by db */
	struct BlockInterval blocks;		/* slice assigned by db */
	struct CallbackNode cleanup;		/* cleanup self, then db */
	struct CountString counter;		/* ensure 1st task */
	struct FileHandle file;
};

struct TableInterval {
	struct Table *restrict start_ptr;		/* assigned by main */
	const struct Table *restrict until_ptr;		/* assigned by main */
};


struct Database {
	struct TableInterval tables;
	struct CallbackNode cleanup;		/* cleanup self, then main */
	struct DirHandle dir;
	struct FileHandle loader;
};






#endif /* ifndef MYSQL_SEED_GENERATE_GENERATE_DATABASE_H_ */
