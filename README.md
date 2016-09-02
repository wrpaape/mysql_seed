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



##`MODE`s
###`help`
`mysql_seed <-h, --help> [MODE]`  
prints operation details for mode `MODE` or general usage if not specified

**examples**  
`mysql_seed --help`  
will print help concerning general usage

`mysql_seed -h generate`  
will print help concerning `generate` mode

`mysql_seed --help e`  
will print help concerning `execute` mode



###`generate`
`mysql_seed <-g, --generate> <DB_SPEC_1> [DB_SPEC_2] ... [DB_SPEC_N]`  
generates seed files for `N` databases according to their `DB_SPEC` specification

**examples**  


###`execute`
`mysql_seed <-e, --execute> <DB_NAME> [MYSQL_ARGS]`  



###`remove`
`mysql_seed <-r, --remove> <-a, --all | DB_NAME_1> [DB_NAME_2] ... [DB_NAME_N]`  




##`SPEC`s

###`DB_SPEC`
`<-d, --database> <DB_NAME> <TBL_SPEC_1> [TBL_SPEC_2] ... [TBL_SPEC_N]`  
indicates that the tables described by `TBL_SPEC`s `1` through `N` belong to the MySQL database named `DB_NAME`


###`TBL_SPEC`
`<-t, --table> <TBL_NAME> <ROW_COUNT> <COL_SPEC_1> [COL_SPEC_2] ... [COL_SPEC_N]`  
specifies a database table with name `TBL_NAME` having `ROW_COUNT` rows and `N` columns populated according to their respective `COL_SPEC`s"


###`COL_SPEC`
`<-c, --column> <COL_NAME> <COL_TYPE> [COL_TYPE_Q] [GRP_SPEC]`  
specifies a database column with name `COL_NAME` and data type `COL_TYPE`. A column type qualifier, `COL_TYPE_Q`,  may be provided to fine-tune data generation for a given type. For all non-fixed data specifications a group specification, `GRP_SPEC`, may be appended to partition a column into groups.


###`GRP_SPEC`
`<-g, --group> <GRP_COUNT> [<-e, --even> | <-l, --linear>]`  


###Notation
- &lt;MANDATORY&gt;
- [OPTIONAL]
- THIS AND THAT | OR THESE
- HOMOGENOUS INPUT ... SEQUENCE
- -shrtflg, --equivalent-long-flag


##Supported Data Types

###String (VARCHAR, CHAR)

####`<-s, --string>`  

| Qualifier      | `COL_TYPE_Q`                   | description                                                              | example entries                                         | MySQL type declaration                            |
| -------------- | ------------------------------ | ------------------------------------------------------------------------ | :-----------------------------------------------------: | ------------------------------------------------- |
| None (Default) | N/A                            | *COL_NAME* concatenated with an ascending integer (starting from "1")    | username1<br/>username2<br/>...<br/>username*ROW_COUNT* | **CHAR(***length(COL_NAME)***)**                  |
| Fixed          | `<-f, --fixed> <FIXED_STRING>` | all entries set to *FIXED_STRING*, **GRP_SPEC not allowed**              | foo bar<br/>foo bar<br/>...<br/>foo bar                 | **CHAR(***length(FIXED_STRING)***)**              |
| Unique         | `<-u, --unique> <BASE_STRING>` | *BASE_STRING* concatenated with an ascending integer (starting from "1") | foo1<br/>foo2<br/>...<br/>foo*ROW_COUNT*                | **VARCHAR(***length(BASE_STRING*ROW_COUNT*)***)** |
| Hash           | `<-h, --hash> <HASH_LENGTH>`   | shuffled strings of hexadecimal digits having length *HASH_LENGTH*       | af100<br/>92dd1<br/>...<br/>1d2ba                       | **CHAR(***HASH_LENGTH***)**                       |
| UUID           | `<-uu, --uuid>`              | Universally Unique Idenfiers (version 1) | 866d0c36-3a20-11b2-fb9d-d0a637edde91<br/>866d0c37-3a20-11b2-fb9d-d0a637edde91<br/>...<br/>d71dd15d-3a20-11b2-fb9d-d0a637edde91 | **CHAR(36)** |
| First Names    | `<-n1, --names-first>`         | random sample of American first names                                    | Robert<br/>Alice<br/>...<br/>Joseph                     | **VARCHAR(***FIRST_NAME_LENGTH_MAX***)**          |
| Last Names     | `<-nl, --names-last>`          | random sample of American last names                                     | Smith<br/>Johnson<br/>...<br/>Garcia                    | **VARCHAR(***LAST_NAME_LENGTH_MAX***)**           |
| Full Names     | `<-nf, --names-full>`          | <*first_name*> [*initial* &#124; *first_name*] <*last_name*>             | Amy Cruz<br/>Sue E Bell<br/>...<br/>Bob Joe Cook        | **VARCHAR(***FULL_NAME_LENGTH_MAX***)**           |


###Integer (TINYINT, SMALLINT, MEDIUMINT, INT, BIGINT)

####`<-i, --integer>`

| Qualifier      | `COL_TYPE_Q`                                       | description                                              | example entries                            | MySQL type declaration                                               |
| -------------- | -------------------------------------------------- | -------------------------------------------------------- | :----------------------------------------: | -------------------------------------------------------------------- |
| None (Default) | N/A                                                | ascending integers (starting from "1")                   | 1<br/>2<br/>...<br/>*ROW_COUNT*            | **TINYINT** - **INT** (depends on *ROWCOUNT*)                        |
| Fixed          | `<-f, --fixed> <FIXED_INT>`                        | all entries set to *FIXED_INT*, **GRP_SPEC not allowed** | -1234567<br/>-1234567<br/>...<br/>-1234567 | **TINYINT** - **BIGINT** (depends on *FIXED_INT*)                    |
| Unique         | `<-u, --unique>`                                   | ascending integers (starting from "1")                   | 1<br/>2<br/>...<br/>*ROW_COUNT*            | **TINYINT** - **INT** (depends on *ROWCOUNT*)                        |
| Random Default | `<-r, --random>`                                   | random 32 bit integers                                   | -99123112<br/>1012233332<br/>...<br/>-5992 | **INT**                                                              |
| Random From    | `<-r, --random> <-f, --from> <MIN_INT>`            | random 32 or 64 bit integers ≥ *MIN_INT*                 | 1337<br/>*MIN_INT*<br/>...<br/>-223121232  | **INT** or **BIGINT** (depends on *MIN_INT*)                         |
| Random Upto    | `<-r, --random> <-u, --upto> <MAX_INT>`            | random 32 or 64 bit integers ≤ *MAX_INT*                 | *MAX_INT*<br/>-123123123<br/>...<br/>12313 | **INT** or **BIGINT** (depends on *MAX_INT*)                         |
| Random Range   | `<-r, --random> <-r, --range> <MIN_INT> <MAX_INT>` | random 32 or 64 bit integers ≤ *MIN_INT* and ≥ *MAX_INT* | 412221<br/>*MAX_INT*<br/>...<br/>*MIN_INT* | **INT** or **BIGINT** (depends on larger of *MIN_INT* and *MAX_INT*) |


###Unsigned Integer (TINYINT UNSIGNED, SMALLINT UNSIGNED, MEDIUMINT UNSIGNED, INT UNSIGNED, BIGINT UNSIGNED)

####`<-u, --unsigned-integer>`

| Qualifier      | `COL_TYPE_Q`                                         | description                                                         | example entries                              | MySQL type declaration                                               |
| -------------- | ---------------------------------------------------- | ------------------------------------------------------------------- | :------------------------------------------: | -------------------------------------------------------------------- |
| None (Default) | N/A                                                  | ascending integers (starting from "1")                              | 1<br/>2<br/>...<br/>*ROW_COUNT*              | **TINYINT UNSIGNED** - **INT UNSIGNED** (depends on *ROWCOUNT*)      |
| Fixed          | `<-f, --fixed> <FIXED_UINT>`                         | all entries set to *FIXED_UINT*, **GRP_SPEC not allowed**           | 1234567<br/>1234567<br/>...<br/>1234567      | **TINYINT UNSIGNED** - **BIGINT UNSIGNED** (depends on *FIXED_UINT*) |
| Unique         | `<-u, --unique>`                                     | ascending integers (starting from "1")                              | 1<br/>2<br/>...<br/>*ROW_COUNT*              | **TINYINT UNSIGNED** - **INT UNSIGNED** (depends on *ROWCOUNT*)      |
| Random Default | `<-r, --random>`                                     | random 32 bit unsigned integers                                     | 99123112<br/>321123123<br/>...<br/>5992      | **INT UNSIGNED**                                                     |
| Random From    | `<-r, --random> <-f, --from> <MIN_UINT>`             | random 32 or 64 bit unsigned integers ≥ *MIN_UINT*                  | 1337<br/>*MIN_UINT*<br/>...<br/>223121232    | **INT UNSIGNED** or **BIGINT UNSIGNED** (depends on *MIN_UINT*)      |
| Random Upto    | `<-r, --random> <-u, --upto> <MAX_UINT>`             | random 32 or 64 bit unsigned integers ≤ *MAX_UINT*                  | *MAX_UINT*<br/>123123123<br/>...<br/>12313   | **INT UNSIGNED** or **BIGINT UNSIGNED** (depends on *MAX_UINT*)      |
| Random Range   | `<-r, --random> <-r, --range> <MIN_UINT> <MAX_UINT>` | random 32 or 64 bit unsigned integers ≤ *MIN_UINT* and ≥ *MAX_UINT* | 412221<br/>*MAX_UINT*<br/>...<br/>*MIN_UINT* | **INT UNSIGNED** or **BIGINT UNSIGNED** (depends on *MAX_UINT*)      |


###Datetime (DATETIME)

####`<-dt, --datetime>`

| Qualifier      | `COL_TYPE_Q`     | description                                                              | example entries                                                             | MySQL type declaration |
| -------------- | ---------------- | ------------------------------------------------------------------------ | :-------------------------------------------------------------------------: | ---------------------- |
| None (Default) | N/A              | ascending UTC datetimes (starting from current datetime, 1 second apart) | 2016-09-02 18:08:25<br/>2016-09-02 18:08:26<br/>...<br/>2016-09-02 18:10:01 | **DATETIME**           |
| Fixed          | `<-f, --fixed>`  | all entries set to current UTC datetime, **GRP_SPEC not allowed**        | 2016-09-02 18:08:25<br/>2016-09-02 18:08:25<br/>...<br/>2016-09-02 18:09:25 | **DATETIME**           |
| Unique         | `<-u, --unique>` | ascending UTC datetimes (starting from current datetime, 1 second apart) | 2016-09-02 18:08:25<br/>2016-09-02 18:08:26<br/>...<br/>2016-09-02 18:10:01 | **DATETIME**           |


###Timestamp (TIMESTAMP)

####`<-ts, --timestamp>`
| Qualifier      | `COL_TYPE_Q`     | description                                                                | example entries                                                             | MySQL type declaration |
| -------------- | ---------------- | -------------------------------------------------------------------------- | :-------------------------------------------------------------------------: | ---------------------- |
| None (Default) | N/A              | ascending UTC timestamps (starting from current timestamp, 1 second apart) | 2016-09-02 18:08:25<br/>2016-09-02 18:08:26<br/>...<br/>2016-09-02 18:10:01 | **TIMESTAMP**          |
| Fixed          | `<-f, --fixed>`  | all entries set to current UTC timestamp, **GRP_SPEC not allowed**         | 2016-09-02 18:08:25<br/>2016-09-02 18:08:25<br/>...<br/>2016-09-02 18:09:25 | **TIMESTAMP**          |
| Unique         | `<-u, --unique>` | ascending UTC timestamps (starting from current timestamp, 1 second apart) | 2016-09-02 18:08:25<br/>2016-09-02 18:08:26<br/>...<br/>2016-09-02 18:10:01 | **TIMESTAMP**          |


##Features
- robust thread pool implementation build with POSIX threads (pthread) API
- graceful error handling
  - recoverable errors are caught and reported
  - system call failures are logged and reported after cleanup
  - any generated files are deleted, and all dynamically allocated memory is freed on fatal errors before program termination


##Goals

###Short Term
- local timezone timestamps (instead of UTC)
- Linux Compatibility
- Windows Compatibility

###Long Term
- support for floating point types (FLOAT, DOUBLE)
- composable string types (i.e. printf-style formatting)
