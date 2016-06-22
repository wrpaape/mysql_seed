#ifndef MYSQL_SEED_MYSQL_SEED_MODE_H_
#define MYSQL_SEED_MYSQL_SEED_MODE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdio.h> /* FILE */


/* MODE SPECS
 * ══════════════════════════════════════════════════════════════════════════ */

/* seed_create
 * ────────────────────────────────────────────────────────────────────────── */
struct FieldSpec {
	const char *restrict field_name;
	const char *restrict base_value;	/* optional */
};

struct TableSpec {
	const char *table_name;
	struct FieldSpec *fields;
	unsigned int field_count;
};

struct SeedTableSpec {
	struct TableSpec table;
	unsigned int seed_count;
};

struct SeedDatabaseSpec {
	const char *restrict name;
	struct SeedTableSpec *restrict seed_tables;
	unsigned int table_count;
};

struct SeedCreateSpec {
	const char *restrict filename;
	struct SeedDatabaseSpec *seed_databases;
	unsigned int database_count;
};


/* seed_run
 * ────────────────────────────────────────────────────────────────────────── */
struct SeedRunSpec {
	const char *restrict filename;
	const char *restrict user;
	const char *restrict password;
};


/* seed_exit
 * ────────────────────────────────────────────────────────────────────────── */
struct SeedExitSpec {
	int status;
	FILE *restrict stream;
	const char *restrict message;
};


/* input for 'SeedModeHandler' dispatch functions
 * ────────────────────────────────────────────────────────────────────────── */
union SeedModeSpec {
	struct SeedCreateSpec create;
	struct SeedRunSpec run;
	struct SeedExitSpec exit;
};


/* mode procedure dispatch
 * ────────────────────────────────────────────────────────────────────────── */
typedef void SeedModeHandler(const union SeedModeSpec *const restrict spec);


/* 'SeedModeHandler' dispatch function
 *─────────────────────────────────────────────────────────────────────────── */
struct SeedMode {
	SeedModeHandler *handle;
	union SeedModeSpec spec;
};


/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_MODE_H_ */
