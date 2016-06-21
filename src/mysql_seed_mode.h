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
	const char *field_name;
	const char *base_value;	/* optional */
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
	const char *name;
	struct SeedTableSpec *seed_tables;
	unsigned int table_count;
};

struct SeedCreateSpec {
	const char *filename;
	struct SeedDatabaseSpec *seed_databases;
	unsigned int database_count;
};


/* seed_run
 * ────────────────────────────────────────────────────────────────────────── */
struct SeedRunSpec {
	const char *filename;
	const char *user;
	const char *password;
};


/* seed_exit
 * ────────────────────────────────────────────────────────────────────────── */
struct SeedExitSpec {
	int status;
	FILE *stream;
	const char *format;
	va_list ap;
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
typespec void SeedModeHandler(const union SeedModeSpec *const restrict spec);


/* 'SeedModeHandler' dispatch function
 *─────────────────────────────────────────────────────────────────────────── */
struct SeedMode {
	SeedModeHandler *handle;
	union SeedModeSpec spec;
};


/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_MODE_H_ */
