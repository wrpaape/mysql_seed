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

struct Table {

};

struct TableInfo {

	struct Table *tables;
	const struct Table *until_ptr;

};

struct Loader {
	int file_descriptor;
}

struct Database {
	int directory_descriptor;
	const char *name;
	struct ThreadPool *pool;
	struct TableInfo;
};






#endif /* ifndef MYSQL_SEED_GENERATE_GENERATE_DATABASE_H_ */
