#ifndef MYSQL_SEED_GENERATE_GENERATE_LOADER_H_
#define MYSQL_SEED_GENERATE_GENERATE_LOADER_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */

#define TABLE_HEADER_LINE_COUNT "18"

#define TAB_TOKEN "<TAB>"

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
"\n17) ║ LINES 1 THROUGH " TABLE_HEADER_LINE_COUNT " ARE IGNORED BY LOADER! ║"	\
"\n18) ╚═══════════════════════════════════════════════╝\n"

/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */


#define
" 1) "	/* database/<db_name>/load_<tbl_name>.tsv */
"# database" PATH_DELIM "<db_name>" PATH_DELIM "load_<db_name>.mysql"
"\n#"
"\n# seeds MySQL database <db_name> according to the tabular data files:"
"\n#"
"\n# \t- "


"\nUSE <db_name>;"
"\n"
"\nLOAD DATA INFILE 'database" PATH_DELIM "<db_name>" PATH_DELIM "<tbl_name>.tsv'"
"\n\tIGNORE INTO TABLE <tbl_name>"
"\n\tFIELDS TERMINATED BY '\\t'"
"\n\t       ENCLOSED BY   ''"
"\n\t       ESCAPED BY    '\\'"
"\n\tLINES  STARTING BY   ''"
"\n\t       TERMINATED BY '\'"
"\n\tIGNORE " TABLE_HEADER_LINE_COUNT " LINES;"




#endif /* ifndef MYSQL_SEED_GENERATE_GENERATE_LOADER_H_ */
