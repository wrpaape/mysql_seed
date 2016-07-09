#ifndef MYSQL_SEED_GENERATE_GENERATE_LOADER_H_
#define MYSQL_SEED_GENERATE_GENERATE_LOADER_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */

#define TABLE_HEADER_LINE_COUNT "15"

#define TABLE_HEADER
  " 1) database" PATH_DELIM "<db_name>" PATH_DELIM "<tbl_name>.tsv"
"\n 2)"
"\n 3) contains tab-separated seed data for table:"
"\n 4)"
"\n 5) \t<tbl_name>"
"\n 6)"
"\n 7) in MySQL database:"
"\n 8)"
"\n 9) \t<db_name>"
"\n10)"
"\n11) ╔═══════════════════════════════════════════════╗"
"\n12) ║ LINES 1 THROUGH " TABLE_HEADER_LINE_COUNT " ARE IGNORED BY LOADER! ║"
"\n13) ╚═══════════════════════════════════════════════╝"
"\n14)"
"\n15) <TAB>"

/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */

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
"\n\tIGNORE " TABLE_HEADER_LINE_COUNT " LINES"




#endif /* ifndef MYSQL_SEED_GENERATE_GENERATE_LOADER_H_ */
