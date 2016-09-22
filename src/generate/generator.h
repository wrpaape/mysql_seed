#ifndef MYSQL_SEED_GENERATE_GENERATOR_H_
#define MYSQL_SEED_GENERATE_GENERATOR_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h"		/* file/exit/string/thread utils */
#include "thread/thread_pool.h"		/* ThreadPool */
#include "memory/memory_copy_array.h"	/* memory_copy */
#include "random/random_generator.h"	/* number generator closures */
#include "generate/group.h"		/* group partitioner */


/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
/* minimum valid spec lengths
 *
 * -c COL_NAME COL_TYPE */
#define COL_SPEC_LENGTH_MIN	   3lu
#define COL_SPEC_LENGTH_MIN_STRING "3"

/* -t TBL_NAME ROW_COUNT COL_SPEC */
#define TBL_SPEC_LENGTH_MIN	   6lu
#define TBL_SPEC_LENGTH_MIN_STRING "6"

/* -d DB_NAME TBL_SPEC */
#define DB_SPEC_LENGTH_MIN	  8lu
#define DB_SPEC_LENGTH_MIN_STRING "8"
#define DB_SPEC_MINIMAL							\
INPUT_WRAP("-d DB_NAME -t TBL_NAME ROW_COUNT -c COL_NAME COL_TYPE")

/* Counter limits */
#if (SIZE_MAX < UINT32_MAX)
#	define UPTO_MAX				9999lu
#	define UPTO_MAX_STRING			"9999"
#	define MAG_UPTO_MAX			3u
#	define SIZE_UPTO_MAX_STR		5u
#	define  LARGE_UPTO_MAX			0
#	define BASE_STRING_LENGTH_MAX		251lu
#	define BASE_STRING_LENGTH_MAX_STRING	"251"
#else
#	define UPTO_MAX				99999999lu
#	define UPTO_MAX_STRING			"99999999"
#	define MAG_UPTO_MAX			7u
#	define SIZE_UPTO_MAX_STR		9u
#	define LARGE_UPTO_MAX			1
#	define BASE_STRING_LENGTH_MAX		247lu
#	define BASE_STRING_LENGTH_MAX_STRING	"247"
#endif /* if (SIZE_MAX < UINT32_MAX) */

#define FLOAT_PRECISION_DEFAULT	6u
#define FLOAT_PRECISION_MAX	15u

#define FIXED_STRING_LENGTH_MAX		255lu
#define FIXED_STRING_LENGTH_MAX_STRING	"255"

#define COUNT_GENERATOR_WORKERS 4lu

/* file templates
 *─────────────────────────────────────────────────────────────────────────── */
#define TABLE_HEADER_LINE_COUNT "17"


/* /1* table file *1/ */
/* #define TAB_TOKEN "<TAB>" */
/* #define TAB_TOKEN_LENGTH 5lu */
/* #define PUT_TAB_TOKEN(PTR)						\ */
/* PUT_STRING_WIDTH(PTR, TAB_TOKEN, 5) */

#define TABLE_HEADER_1							\
  " 1) "	/* database/<db_name>/<tbl_name>.csv */
#define PUT_TABLE_HEADER_1(PTR)						\
PUT_STRING_WIDTH(PTR, TABLE_HEADER_1, 4)

#define TABLE_HEADER_2							\
"\n 2)"									\
"\n 3) contains " FIELD_DELIM_WORD "-separated seed data for table:"	\
"\n 4)"									\
"\n 5) \t"	/* <tbl_name> */
#define PUT_TABLE_HEADER_2(PTR)						\
PTR = put_string_size(ptr,						\
		      TABLE_HEADER_2,					\
		      sizeof(TABLE_HEADER_2) - 1lu)

#define TABLE_HEADER_3							\
"\n 6)"									\
"\n 7) in MySQL database:"						\
"\n 8)"									\
"\n 9) \t"	/* <db_name> */
#define PUT_TABLE_HEADER_3(PTR)						\
PTR = put_string_size(ptr,						\
		      TABLE_HEADER_3,					\
		      sizeof(TABLE_HEADER_3) - 1lu)

#define TABLE_HEADER_4							\
"\n10)"									\
"\n11) Row definition adheres to the syntax:"				\
"\n12)"									\
"\n13) "	/* <col_name_1><TAB><col_name_2><TAB> ... <col_name_N> */
#define PUT_TABLE_HEADER_4(PTR)						\
PTR = put_string_size(ptr,						\
		      TABLE_HEADER_4,					\
		      sizeof(TABLE_HEADER_4) - 1lu)

#define TABLE_HEADER_5							\
	"<NEWLINE>"							\
"\n14)"									\
"\n15) ╔═══════════════════════════════════════════╗"			\
"\n16) ║ LINES 1 THROUGH " TABLE_HEADER_LINE_COUNT " ARE IGNORED BY LOADER! ║" \
"\n17) ╚═══════════════════════════════════════════╝"
#define PUT_TABLE_HEADER_5(PTR)						\
PTR = put_string_size(ptr,						\
		      TABLE_HEADER_5,					\
		      sizeof(TABLE_HEADER_5) - 1lu)

#define TABLE_HEADER_BASE_SIZE						\
(sizeof(TABLE_HEADER_1 TABLE_HEADER_2 TABLE_HEADER_3 TABLE_HEADER_4	\
	TABLE_HEADER_5) - 1lu)


/* loader file */
#define LOADER_TABLE_LI							\
"\n# \t- "
#define PUT_LOADER_TABLE_LI(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_TABLE_LI, 6)

/* loader header template (4 segments) */
#define LOADER_HEADER_1							\
"# " /* loader_filepath */
#define PUT_LOADER_HEADER_1(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_HEADER_1, 2)

#define LOADER_HEADER_2							\
"\n#"									\
"\n# seeds MySQL database " /* <db_name> */
#define PUT_LOADER_HEADER_2(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_HEADER_2, 26)

#define LOADER_HEADER_3							\
" according to the tabular data files:"					\
"\n#"									\
LOADER_TABLE_LI
#define PUT_LOADER_HEADER_3(PTR)					\
PTR = put_string_size(PTR,						\
		      LOADER_HEADER_3,					\
		      sizeof(LOADER_HEADER_3) - 1lu)


#define LOADER_HEADER_4							\
"\n"									\
"\nCREATE DATABASE " /* <db_name> */
#define PUT_LOADER_HEADER_4(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_HEADER_4, 18)

#define LOADER_HEADER_5							\
				     ";"				\
"\n"									\
"\nUSE " /* <db_name> */
#define PUT_LOADER_HEADER_5(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_HEADER_5, 7)

#define LOADER_HEADER_6							\
			 ";"
#define PUT_LOADER_HEADER_6(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_HEADER_6, 1)



#define LOADER_HEADER_BASE_SIZE_MAX					\
(sizeof(LOADER_HEADER_1 LOADER_HEADER_2 LOADER_HEADER_3			\
	LOADER_HEADER_4 LOADER_HEADER_5 LOADER_HEADER_6)		\
 + LOADER_FILEPATH_SIZE_MAX + (DB_NAME_NN_SIZE_MAX * 2lu) - 1lu)


/* create table template (col_count segments) */
#define LOADER_CREATE_TABLE_1						\
"\n"									\
"\nCREATE TABLE " /* <tbl_name> */
#define PUT_LOADER_CREATE_TABLE_1(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_CREATE_TABLE_1, 15)

#define LOADER_CREATE_TABLE_2						\
" (\n\t"
#define PUT_LOADER_CREATE_TABLE_2(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_CREATE_TABLE_2, 4)

#define LOADER_CREATE_TABLE_FIELD_DELIM					\
",\n\t"
#define PUT_LOADER_CREATE_TABLE_FIELD_DELIM(PTR)			\
PUT_STRING_WIDTH(PTR, LOADER_CREATE_TABLE_FIELD_DELIM, 3)

#define LOADER_CREATE_TABLE_BASE_SIZE					\
(sizeof(LOADER_CREATE_TABLE_1 LOADER_CREATE_TABLE_2) - 1lu)

/* load table template (2 segments) */
#define LOADER_LOAD_TABLE_1						\
"\n);"									\
"\n"									\
"\nLOAD DATA INFILE '" ABSPATH_PFX /* <table_filepath n> */
#define PUT_LOADER_LOAD_TABLE_1(PTR)					\
PTR = put_string_size(PTR,						\
		      LOADER_LOAD_TABLE_1,				\
		      sizeof(LOADER_LOAD_TABLE_1) - 1lu)

#define LOADER_LOAD_TABLE_2						\
"'\n\tIGNORE INTO TABLE " /* <tbl_name> */
#define PUT_LOADER_LOAD_TABLE_2(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_LOAD_TABLE_2, 21)

#define LOADER_LOAD_TABLE_3						\
"\n\tFIELDS TERMINATED BY '" FIELD_DELIM_STRING "'"			\
"\n\t       ENCLOSED BY   ''"						\
"\n\t       ESCAPED BY    '\\\\'"					\
"\n\tLINES  STARTING BY   ''"						\
"\n\t       TERMINATED BY '\\n'"					\
"\n\tIGNORE " TABLE_HEADER_LINE_COUNT " LINES;"
#define PUT_LOADER_LOAD_TABLE_3(PTR)					\
PTR = put_string_size(PTR,						\
		      LOADER_LOAD_TABLE_3,				\
		      sizeof(LOADER_LOAD_TABLE_3) - 1lu)

#define LOADER_LOAD_TABLE_BASE_SIZE					\
(sizeof(LOADER_LOAD_TABLE_1 LOADER_LOAD_TABLE_2 LOADER_LOAD_TABLE_3)	\
 - 1lu)


/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */
/* GENERATOR COMPONENT SPECS
 * ──────────────────────────────────────────────────────────────────────────
 * ────────────────────────────────────────────────────────────────────────── */
/* -c username --string --unique tastyham		→ tastyham1
 *							  tastyham2
 *			   				  ...
 *			   				  tastyham<ROW_COUNT> */
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
	union StringLengthScale scale;
	struct StringBuilder fixed;
	struct StringBuilder base;
};

/* -c temperature --integer-unsigned --range 500 200000	→ 580
 *							  100000
 *							  (random in 500..200000)
 *			   				  ...  */
struct UIntegerRange {
	uintmax_t min;
	uintmax_t max;
};

union UIntegerScale {
	struct UIntegerRange range;
	uintmax_t from;
	uintmax_t upto;
};

union UIntegerGenerator {
	struct BoundOffsetUGeneratorClosure range;
	struct BoundOffsetUGeneratorClosure from;
	struct BoundUGeneratorClosure upto;
	UGenerator *unbound;
};

struct UIntegerRandSpec {
	union UIntegerGenerator gen;
	unsigned int width_max;
};

union UIntegerQualifier {
	union UIntegerScale scale;
	struct UIntegerRandSpec rand_spec;
	struct StubBuilder fixed;
};

/* -c temperature --integer --range -100 100		→ 45
 *							  100
 *							  (random in -100..100)
 *			   				  ...  */
struct IntegerRange {
	intmax_t min;
	intmax_t max;
};

union IntegerScale {
	struct IntegerRange range;
	intmax_t from;
	intmax_t upto;
};

union IntegerGenerator {
	struct BoundOffsetIGeneratorClosure range;
	struct BoundOffsetIGeneratorClosure from;
	struct BoundIGeneratorClosure upto;
	IGenerator *unbound;
};

struct IntegerRandSpec {
	union IntegerGenerator gen;
	unsigned int width_max;
};

union IntegerQualifier {
	union IntegerScale scale;
	struct IntegerRandSpec rand_spec;
	struct StubBuilder fixed;
};


/* -c temperature --float --range 1 500.25		→ 300.2334
 *							  1.0000000
 *							  (random in 1..500.25)
 *			   				  ...  */
struct FloatRange {
	long double min;
	long double max;
};

union FloatScale {
	struct FloatRange range;
	long double from;
	long double upto;
};

struct FloatQualifier {
	union FloatScale scale;
	unsigned int precision;
	struct StubBuilder fixed;
};

union TypeQualifier {
	union StringQualifier string;
	union IntegerQualifier integer;
	union UIntegerQualifier u_integer;
	struct FloatQualifier float_pt;
};

struct GrpSpec {
	size_t count;
	GroupPartitioner *partition;
};

struct ColSpec {
	struct String name;
	struct PutLabelClosure type;
	union TypeQualifier type_q;
	struct GrpSpec grp_spec;
	Procedure *build;
};

struct ColSpecInterval {
	struct ColSpec *restrict from;
	const struct ColSpec *restrict until;
};

struct TblSpec {
	struct String name;
	size_t row_count;
	struct ColSpecInterval col_specs;	/* contiguous interval */
	struct TblSpec *next;
};

struct DbSpec {
	struct String name;
	struct TblSpec *tbl_specs;		/* linked list */
	struct DbSpec *next;
};



/* GENERATOR COMPONENTS
 * ──────────────────────────────────────────────────────────────────────────
 * ────────────────────────────────────────────────────────────────────────── */
struct RowBlock;

struct Rowspan {
	char *cell;			/* points to first cell */
	bool separate;			/* is indepenedent column (not JOIN) */
	struct RowBlock *parent;	/* get row_count, update block length */
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
	struct Rowspan *restrict rowspans_from;	/* X BLK_COUNT, col_count gap */
	char *contents;
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
	const struct TblSpec *spec;		/* from raw input */
	struct ColumnInterval columns;		/* slice assigned by db */
	struct RowBlockInterval row_blocks;	/* slice assigned by db */
	struct HandlerClosure fail_cl;		/* cleanup self, then db */
	struct Database *parent;
	const struct Rowspan *restrict rowspans_until;
	unsigned int col_count;
};

struct TableInterval {
	struct Table *restrict from;		/* assigned by main */
	const struct Table *restrict until;	/* assigned by main */
};

struct Counter {
	Mutex processing;	/* condition lock */
	ThreadCond done;	/* broadcasted once 'pointers' are set */
	bool ready;		/* flipped true once 'pointers' are set */
	char *digits;		/* "1", "2", "3", ..., "$(upto)" */
	char **pointers;	/* digit pointers */
	size_t upto;		/* final and max stringified number */
	size_t size_digits;	/* sizeof("1", "2", ... "$(upto)") */
	unsigned int mag_upto;	/* ⌊ log₁₀(upto) ⌋ */
	struct HandlerClosure fail_cl;	/* cleanup self, then main */
	struct Generator *parent;
};

struct Generator;

struct Database {
	struct FileHandle loader;
	struct Dirpath dirpath;
	const struct DbSpec *spec;		/* raw input */
	struct TableInterval tables;
	struct HandlerClosure fail_cl;		/* cleanup self, then main */
	struct Generator *parent;
};

struct DatabaseInterval {
	struct Database *restrict from;		/* assigned by main */
	const struct Database *restrict until;	/* assigned by main */
};


struct GeneratorTaskList {
	struct TaskStore counter_columns_loaders;
	struct TaskStore table_headers;
	struct TaskStore table_contents;
	struct TaskStore table_files;
};

struct Generator {
	struct ThreadPool pool;			/* all child threads */
	struct Worker workers[COUNT_GENERATOR_WORKERS];
	struct GeneratorTaskList build;
	struct Counter counter;			/* shared by all */
	struct ThreadLog log;
	struct DatabaseInterval databases;
	const struct DbSpec *db_specs;		/* from raw input */
	struct HandlerClosure fail_cl;		/* cleanup self, then main */
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


/* init Generator FileHandle, Dirpath
 *─────────────────────────────────────────────────────────────────────────── */
inline void
database_dirpath_init(struct Dirpath *const restrict dirpath,
		      const struct String *const restrict db_name)
{
	SET_STRING_WIDTH(&dirpath->buffer[0],
			 DB_DIRPATH_PFX,
			 DB_DIRPATH_PFX_NN_WIDTH);

	memory_copy(&dirpath->buffer[DB_DIRPATH_PFX_LENGTH],
		    db_name->bytes,
		    db_name->length + 1lu);

	dirpath->length = DB_DIRPATH_PFX_LENGTH
			+ db_name->length;
}

inline void
table_file_init(struct FileHandle *const restrict file,
		const struct String *const restrict tbl_name,
		const struct Dirpath *const restrict db_dirpath)
{
	char *restrict ptr;

	ptr = put_string_size(&file->name.buffer[0],
			      tbl_name->bytes,
			      tbl_name->length);

	SET_STRING_WIDTH(ptr,
			 TABLE_FILENAME_SFX,
			 TABLE_FILENAME_SFX_WIDTH);

	file->name.length = tbl_name->length
			  + TABLE_FILENAME_SFX_LENGTH;

	const size_t filename_size = file->name.length + 1lu;

	file->path.length = db_dirpath->length + filename_size;


	ptr = put_string_size(&file->path.buffer[0],
			      &db_dirpath->buffer[0],
			      db_dirpath->length);

	PUT_PATH_DELIM(ptr);

	memory_copy(ptr,
		    &file->name.buffer[0],
		    filename_size);
}

inline void
loader_file_init(struct FileHandle *const restrict file,
		 const struct String *const restrict db_name,
		 const struct Dirpath *const restrict db_dirpath)
{
	char *restrict ptr;

	SET_STRING_WIDTH(&file->name.buffer[0],
			 LOADER_FILENAME_PFX,
			 LOADER_FILENAME_PFX_NN_WIDTH);

	ptr = put_string_size(&file->name.buffer[LOADER_FILENAME_PFX_NN_SIZE],
			      db_name->bytes,
			      db_name->length);

	SET_STRING_WIDTH(ptr,
			 LOADER_FILENAME_SFX,
			 LOADER_FILENAME_SFX_WIDTH);

	file->name.length = LOADER_FILENAME_PFX_LENGTH
			  + db_name->length
			  + LOADER_FILENAME_SFX_LENGTH;

	const size_t filename_size = file->name.length + 1lu;

	file->path.length = db_dirpath->length + filename_size;

	ptr = put_string_size(&file->path.buffer[0],
			      &db_dirpath->buffer[0],
			      db_dirpath->length);

	PUT_PATH_DELIM(ptr);

	memory_copy(ptr,
		    &file->name.buffer[0],
		    filename_size);
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
	    struct Table *const restrict parent)
{
	column->spec = spec;

	column->rowspans_from = rowspans_from;

	column->contents = NULL; /* no-op if freed before allocation */

	handler_closure_init(&column->fail_cl,
			     &column_exit_on_failure,
			     column);

	column->parent = parent;
}


/* Table Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
table_exit_on_failure(void *arg,
		      const char *restrict faliure)
__attribute__((noreturn));


/* Database Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
database_exit_on_failure(void *arg,
			 const char *restrict faliure)
__attribute__((noreturn));


/* Generator Operations
 *─────────────────────────────────────────────────────────────────────────── */
void
generator_exit_on_failure(void *arg,
			  const char *restrict failure)
__attribute__((noreturn));

#endif /* ifndef MYSQL_SEED_GENERATE_GENERATOR_H_ */
