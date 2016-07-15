#ifndef MYSQL_SEED_GENERATE_LOADER_H_
#define MYSQL_SEED_GENERATE_LOADER_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h"	/* Specs, string, file utils */

#define TAB_TOKEN "<TAB>"
#define PUT_TAB_TOKEN(PTR) PUT_STRING_WIDTH(PTR, TAB_TOKEN, 5)


#define TABLE_HEADER_LINE_COUNT "18"

#define TABLE_HEADER_1							\
  " 1) "	/* database/<db_name>/<tbl_name>.tsv */

#define TABLE_HEADER_2							\
"\n 2)"									\
"\n 3) contains tab-separated seed data for table:"			\
"\n 4)"									\
"\n 5) \t"	/* <tbl_name> */

#define TABLE_HEADER_3							\
"\n 6)"									\
"\n 7) in MySQL database:"						\
"\n 8)"									\
"\n 9) \t"	/* <db_name> */

#define TABLE_HEADER_4							\
"\n10)"									\
"\n11)"									\
"\n12) Row definition adheres to the syntax:"				\
"\n13)"									\
"\n14) "	/* <col_name_1><TAB><col_name_2><TAB> ... <col_name_N> */

#define TABLE_HEADER_5							\
	"<NEWLINE>"							\
"\n15)"									\
"\n16) ╔═══════════════════════════════════════════════╗"		\
"\n17) ║ LINES 1 THROUGH " TABLE_HEADER_LINE_COUNT " ARE IGNORED BY LOADER! ║" \
"\n18) ╚═══════════════════════════════════════════════╝\n"

#define LOADER_FILE_LI							\
"\n# \t- "
#define PUT_LOADER_FILE_LI(PTR)						\
PUT_STRING_WIDTH(PTR, LOADER_FILE_LI, 6)

/* loader header template (4 segments) */
#define LOADER_HEADER_1							\
"# " /* loader_filepath */
#define PUT_LOADER_HEADER_1(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_HEADER_1, 2)

#define LOADER_HEADER_2							\
"\n#"
"\n# seeds MySQL database " /* <db_name> */
#define PUT_LOADER_HEADER_2(PTR)					\
PTR = put_string_size(PTR,						\
		      LOADER_HEADER_2,					\
		      sizeof(LOADER_HEADER_2) - 1lu)

#define LOADER_HEADER_3							\
" according to the tabular data files:"					\
"\n#"									\
LOADER_FILE_LI
#define PUT_LOADER_HEADER_3(PTR)					\
PTR = put_string_size(PTR,						\
		      LOADER_HEADER_3,					\
		      sizeof(LOADER_HEADER_3) - 1lu)


#define LOADER_HEADER_4							\
"\n"									\
"\nUSE " /* <db_name> */
#define PUT_LOADER_HEADER_4(PTR)					\
PUT_STRING_WIDTH(PTR, LOADER_HEADER_4, 6)

#define LOADER_HEADER_5							\
			 ";"						\
"\n"
#define PUT_LOADER_HEADER_5(PTR)					\
PUT_STRING_WIDTH(LOADER_HEADER_5, 2)

#define LOADER_HEADER_BASE_SIZE_MAX					\
(sizeof(LOADER_HEADER_1 LOADER_HEADER_2 LOADER_HEADER_3			\
	LOADER_HEADER_4 LOADER_HEADER_5)				\
 + LOADER_FILEPATH_SIZE_MAX + (DB_NAME_NN_SIZE_MAX * 2lu) - 1lu)



/* load table template (2 segments) */
#define LOADER_LOAD_TABLE_1						\
"\n"
"\nLOAD DATA INFILE '" /* <table_filepath n> */
#define PUT_LOADER_LOAD_TABLE_1(PTR)					\
PTR = put_string_size(PTR,						\
		      LOADER_LOAD_TABLE_1,				\
		      sizeof(LOADER_LOAD_TABLE_1) - 1lu)

#define LOADER_LOAD_TABLE_2						\
"\n\tIGNORE INTO TABLE " /* <tbl_name> */
#define PUT_LOADER_LOAD_TABLE_2(PTR)					\
PTR = put_string_size(PTR,						\
		      LOADER_LOAD_TABLE_2,				\
		      sizeof(LOADER_LOAD_TABLE_2) - 1lu)

#define LOADER_LOAD_TABLE_3						\
"\n\tFIELDS TERMINATED BY '\\t'"					\
"\n\t       ENCLOSED BY   ''"						\
"\n\t       ESCAPED BY    '\\'"						\
"\n\tLINES  STARTING BY   ''"						\
"\n\t       TERMINATED BY '\'"						\
"\n\tIGNORE " TABLE_HEADER_LINE_COUNT " LINES;"
#define PUT_LOADER_LOAD_TABLE_3(PTR)					\
PTR = put_string_size(PTR,						\
		      LOADER_LOAD_TABLE_3,				\
		      sizeof(LOADER_LOAD_TABLE_3) - 1lu)

#define LOADER_LOAD_TABLE_BASE_SIZE					\
(sizeof(LOADER_LOAD_TABLE_1 LOADER_LOAD_TABLE_2 LOADER_LOAD_TABLE_3)	\
 - 1lu)


inline size_t
loader_estimate_size(const unsigned int tbl_count)
{
	return LOADER_HEADER_BASE_SIZE_MAX
	     + (tbl_count * ((TABLE_FILEPATH_SIZE_MAX * 2lu)
			     + LOADER_LAOD_TABLE_BASE_SIZE
			     + TBL_NAME_NN_SIZE_MAX));
}

inline char *
loader_put_header(char *restrict ptr,
		  const struct Database *const restrict database)
{
	PUT_LOADER_HEADER_1(ptr);

	ptr = put_string_size(ptr,
			      &database->loader.path.buffer[0],
			      database->loader.path.length);

	PUT_LOADER_HEADER_2(ptr);

	ptr = put_string_size(ptr,
			      database->spec->name.bytes,
			      database->spec->name.length);

	PUT_LOADER_HEADER_3(ptr);

	const struct Table *const restrict until = database->tables.until;
	const struct Table *restrict from	 = database->tables.from;

	while (1) {
		ptr = put_string_size(ptr,
				      &from->file.path.buffer[0],
				      from->file.path.length);

		++from;

		if (from == until)
			break;

		PUT_LOADER_FILE_LI(ptr);
	}

	PUT_LOADER_HEADER_4(ptr);

	ptr = put_string_size(ptr,
			      database->spec->name.bytes,
			      database->spec->name.length);

	PUT_LOADER_HEADER_5(ptr);

	return ptr;
}

inline char *
loader_put_body(char *restrict ptr,
		const struct Database *const restrict database)
{
	const struct Table *const restrict until = database->tables.until;
	const struct Table *restrict from	 = database->tables.from;


	do {
		PUT_LOADER_LOAD_TABLE_1(ptr);

		ptr = put_string_size(ptr,
				      &from->file.path.buffer[0],
				      from->file.path.length);

		PUT_LOADER_LOAD_TABLE_2(ptr);

		ptr = put_string_size(ptr,
				      from->spec->name.bytes,
				      from->spec->name.length);

		PUT_LOADER_LOAD_TABLE_3(ptr);

		++from;
	} while (from < until);

	return ptr;
}

/* worker task entry point
 * ────────────────────────────────────────────────────────────────────────── */
void
loader_build(void *arg);



#endif /* ifndef MYSQL_SEED_GENERATE_LOADER_H_ */
