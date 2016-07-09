#ifndef MYSQL_SEED_GENERATE_GENERATE_TABLE_H_
#define MYSQL_SEED_GENERATE_GENERATE_TABLE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */

/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */

struct Table {
	int database_root;
	struct ThreadPool *database_pool;
	const char *name;
	size_t row_count;
	struct CountString *count_string;
};






#endif /* ifndef MYSQL_SEED_GENERATE_GENERATE_TABLE_H_ */
