#mysql_seed

##Overview
`mysql_seed` is a command-line utility for generating large quantities of high quality tabular data intended to provision MySQL database servers. A single invokation can create multiple databases worth of data written to `.csv` files accompanied by `.mysql` scripts that will handle schema creation and data loading.

##Prerequisites
- gcc >= 2.5
- GNU Make

##Building
Invoking `make` at the project root will create the main executable binary, `bin/mysql_seed`, along with executable unit tests for all tested modules in the `test` directory.

##Usage
###`mysql_seed <MODE> [SPECS]`


###MODES

####help
- command

`mysql_seed <-h, --help> [MODE]`


- description

prints operation details for mode `MODE` or general usage if not specified

- examples

`mysql_seed --help`

`mysql_seed -h generate`

`mysql_seed --help e`



####generate
- command
`mysql_seed <-g, --generate> <DB_SPEC_1> [DB_SPEC_2] ... [DB_SPEC_N]`
- description
generates seed files for N databases according to their `DB_SPEC` specification
- examples


####execute
- command
`mysql_seed <-e, --execute> <DB_NAME> [MYSQL_ARGS]`


####remove
- command
`mysql_seed <-r, --remove> <-a, --all | DB_NAME_1> [DB_NAME_2] ... [DB_NAME_N]`


###SPECS

####`DB_SPEC`
- form

`<-d, --database> <DB_NAME> <TBL_SPEC_1> [TBL_SPEC_2] ... [TBL_SPEC_N]`
- description
  indicates that the tables described by `TBL_SPEC`s `1` through `N` belong to the MySQL database named `DB_NAME`

####`TBL_SPEC`
- form
  `<-t, --table> <TBL_NAME> <ROW_COUNT> <COL_SPEC_1> [COL_SPEC_2] ... [COL_SPEC_N]`
- description
  specifies a database table with name `TBL_NAME` having `ROW_COUNT` rows and `N` columns populated according to their respective `COL_SPEC`s"


####`COL_SPEC`
- form
  `<-c, --column> <COL_NAME> <COL_TYPE> [COL_TYPE_Q] [RAND_SPEC] [GRP_SPEC]`
- description
  specifies a database column with name `COL_NAME` and data type `COL_TYPE`. A column type qualifier, `COL_TYPE_Q`,  may be provided to fine-tune data generation for a given type. For some `COL_TYPE`-`COL_TYPE_Q` combinations a `RAND_SPEC` may be provided to define limits on random data generation.  For all non-fixed data types a group specification, `GRP_SPEC`, may be appended to partition a column into groups.

####`RAND_SPEC`
- form
  `<-r, --random> [<-f, --from> <MIN_TYPE> | <-u, --upto> <MAX_(TYPE)> | <-r, --range> <MIN_(TYPE)> <MAX_(TYPE)>]`
- description

####`GRP_SPEC`
- form
  `<-g, --group> <GRP_COUNT> [<-e, --even> | <-l, --linear>]`
- description



###Notation
- <MANDATORY>
- [OPTIONAL]
- THIS AND THAT | OR THESE
- HOMOGENOUS INPUT ... SEQUENCE
- `-shrtflg, --equivalent-long-flag`
