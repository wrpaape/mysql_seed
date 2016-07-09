#ifndef MYSQL_SEED_GENERATE_GENERATE_DATABASE_H_
#define MYSQL_SEED_GENERATE_GENERATE_DATABASE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */

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
