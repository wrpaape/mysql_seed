# mysql_seed

## Overview
`mysql_seed` is a command-line utility for generating large quantities of high quality tabular data intended to provision MySQL database servers. A single invokation can create multiple databases worth of data written to `.csv` files accompanied by `.mysql` scripts that will handle schema creation and data loading.


## Prerequisites
- gcc >= 2.5
- GNU Make
- mysql
- ruby >= 1.9 (Unity test scripts), not needed if `DEVELOPMENT_MODE != T` 


## Building
Invoking `make` at the project root will create the main executable binary, `bin/mysql_seed`, along with executable unit tests for most modules in the `test` directory.


## Usage

### `mysql_seed <MODE> [SPECS]`



## `MODE`s

### `help`
`mysql_seed <-h, --help> [MODE]`  
prints operation details for mode `MODE` or general usage if not specified

**examples**  
`mysql_seed --help`  
will print help concerning general usage

`mysql_seed -h generate`  
will print help concerning `generate` mode

`mysql_seed --help e`  
will print help concerning `execute` mode



### `generate`

`mysql_seed <-g, --generate> <DB_SPEC_1> [DB_SPEC_2] ... [DB_SPEC_N]`  
generates seed files for `N` databases according to their `DB_SPEC` specification

**examples**  
```
mysql_seed --generate --database foo_forum --table users 5000 --column id --unsigned-integer --unique \
                                                              --column username --string \
                                                              --column password --string --hash 128 \
                                                              --column age --unsigned-integer --random --range 18 99 \
                                                              --column created_at --timestamp --unique \
                                           --table threads 50000 --column id --unsigned-integer --unique \
                                                                 --column user_id --unsigned-integer --unique --group 5000 --even \
                                                                 --column title --string --unique "Some Interesting Topic Number " \
                                                                 --column score --integer --random --range -100 1000 \
                                                                 --column created_at --timestamp --unique \
                                           --table posts 500000 --column id --unsigned-integer --unique \
                                                                --column user_id --unsigned-integer --unique --group 5000 --linear \
                                                                --column thread_id --unsigned-integer --random --range 1 50000 \
                                                                --column content --string --fixed "This is a post." \
                                                                --column score --integer --random --range -10 100 \
                                                                --column created_at --timestamp --unique
```
will generate the following files in the `database` directory:
```
.
└── foo_forum
    ├── load_foo_forum.mysql
    ├── posts.csv
    ├── threads.csv
    └── users.csv
```

The following example uses short flags and creates multiple database directories.
```
mysql_seed -g -d classics -t sports_drama 999999 -c id -u \
                                                 -c title -s -u "Rocky " \
                                                 -c director -s -nf \
                                                 -c tomatometer -u -r -u 100 \
                                                 -c duration -u -r -r 60 180 \
              -d foo_shop -t products 100 -c id -u \
                                          -c name -s -u "Product" \
                                          -c description -s -u "this is a description for Product" \
                                          -c price -u -r -r 100 10000 \
                          -t clients 10000 -c id -u \
                                           -c first_name -s -n1 \
                                           -c last_name -s -nl \
                                           -c business -s -u "BazBiz" -g 1000 -l \
                                           -c email -s -f "bar@example.com" \
                                           -c phone -u -r -r 1000000000 9999999999 \
                          -t orders 1000000 -c id -u \
                                            -c client_id -u -g 10000 \
                                            -c product_id -u -r -r 1 100 \
                                            -c UUID -s -uu \
                                            -c quantity -u -r -r 1 1000 \
                                            -c delivered -u -r -u 1 \
                                            -c created_at -ts \
              -d ynot_db -t ads 100000 -c id -u \
                                       -c name -s -u "Popup Number " \
                                       -c click_count -u -r \
                                       -c created_at -ts \
                         -t referrals 1000000 -c id -u \
                                              -c ad_id -u -r -r 1 100000 \
                                              -c created_at -ts
```
will generate the following files in the `database` directory:
```
.
├── classics
│   ├── load_classics.mysql
│   └── sports_drama.csv
├── foo_shop
│   ├── clients.csv
│   ├── load_foo_shop.mysql
│   ├── orders.csv
│   └── products.csv
└── ynot_db
    ├── ads.csv
    ├── load_ynot_db.mysql
    └── referrals.csv
```

The `*.csv` files contain the tabular data, and the `load_*.mysql` scripts contains MySQL statements that `CREATE` a database along with its specified tables and load the `.csv` data accordingly.



### `execute`

`mysql_seed <-e, --execute> [CRED_SPEC] <DB_NAME_1> [DB_NAME_2] ... [DB_NAME_N]`  
loads one or more generated databases into a local MySQL server

**examples**  
```
mysql_seed --execute --user root --password foo_forum
```
will, after requesting a password, connect to MySQL as `root` and run the provisioning script `database/foo_forum/load_foo_forum.mysql` generated in the first `generate` mode example.

```
mysql_seed -e -ptastyham classics foo_shop ynot_db
```
will connect to MySQL as the default user with password `tastyham` and create the databases `classics`, `foo_shop`, and `ynot_db` and provision them with the data generated in the second `generate` mode example.



### `remove`

`mysql_seed <-r, --remove> <-a, --all | DB_NAME_1> [DB_NAME_2] ... [DB_NAME_N]`  
deletes generated database directories. If `<-a, --all>` is specified, all files residing in the top-level `database` directory are deleted. Otherwise only those directories specified by name after `<-r, --remove>` will be deleted along with their contents.


**examples**  
After running the `generate` mode examples, the `database` directory would look like this:
```
.
├── classics
│   ├── load_classics.mysql
│   └── sports_drama.csv
├── foo_forum
│   ├── load_foo_forum.mysql
│   ├── posts.csv
│   ├── threads.csv
│   └── users.csv
├── foo_shop
│   ├── clients.csv
│   ├── load_foo_shop.mysql
│   ├── orders.csv
│   └── products.csv
└── ynot_db
    ├── ads.csv
    ├── load_ynot_db.mysql
    └── referrals.csv
```

Invoking `mysql_seed` like this:
```
mysql_seed --remove classics ynot_db`
```
will clear out the `classics` and `ynot_db` subdirectories:
```
.
├── foo_forum
│   ├── load_foo_forum.mysql
│   ├── posts.csv
│   ├── threads.csv
│   └── users.csv
└── foo_shop
    ├── clients.csv
    ├── load_foo_shop.mysql
    ├── orders.csv
    └── products.csv
```

To clear all files and directories under `database` in one go, the shorthand
```
mysql_seed -r -a`
```
or
```
mysql_seed -r --all`
```
is provided for convenience.

**warning**  
`remove` mode behaves similarly to `rm -rf` in that **everything** residing in the target directory(ies) is deleted indiscriminately, not just those files produced by a `generate` invokation.



## `SPEC`s

### `DB_SPEC`

`<-d, --database> <DB_NAME> <TBL_SPEC_1> [TBL_SPEC_2] ... [TBL_SPEC_N]`  
indicates that the tables described by `TBL_SPEC`s `1` through `N` belong to the MySQL database named `DB_NAME`


### `TBL_SPEC`

`<-t, --table> <TBL_NAME> <ROW_COUNT> <COL_SPEC_1> [COL_SPEC_2] ... [COL_SPEC_N]`  
specifies a database table with name `TBL_NAME` having `ROW_COUNT` rows and `N` columns populated according to their respective `COL_SPEC`s"


### `COL_SPEC`

`<-c, --column> <COL_NAME> <COL_TYPE> [COL_TYPE_Q] [GRP_SPEC]`  
specifies a database column with name `COL_NAME` and data type `COL_TYPE`. A column type qualifier, `COL_TYPE_Q`,  may be provided to fine-tune data generation for a given type. For all non-fixed data specifications a group specification, `GRP_SPEC`, may be appended to partition a column into groups.


### `GRP_SPEC`

`<-g, --group> <GRP_COUNT> [<-e, --even> | <-l, --linear>]`  
splits a database column of `ROW_COUNT` entries into `GRP_COUNT` groups having equal values. An even partition type, `<-e, --even>`, specifies that entries should be split evenly into groups of the same size (±1 if `ROW_COUNT` % `GRP_COUNT` != 0). A linear partition type, `<-l, --linear>`, generates `GRP_COUNT` groups of steadily increasing size. Omitting a partition type defaults to `<-e, --even>` behavior.


### `CRED_SPEC`

`<USER_SPEC> | <PWD_SPEC> | <USER_SPEC> <PWD_SPEC> | <PWD_SPEC> <USER_SPEC>`  
specifies MySQL credentials for accessing a local server


### `USER_SPEC`

`<-u, --user> <USER> | <-uUSER, --user=USER>`  
specifies MySQL user for target server


### `PWD_SPEC`

`<-p, --password> | <-pPASSWORD, --password=PASSWORD>`  
specifies MySQL password for target server. If `PASSWORD` is not specified (standalone `<-p, --password>` flag), you will be prompted to enter it before proceeding.


### Notation
- &lt;MANDATORY&gt;
- [OPTIONAL]
- THIS AND THAT | OR THESE
- HOMOGENOUS INPUT ... SEQUENCE
- -shrtflg, --equivalent-long-flag


## Supported Data Types

### Integer (TINYINT, SMALLINT, MEDIUMINT, INT, BIGINT)

#### `<-i, --integer>`

| Qualifier      | `COL_TYPE_Q`                                       | description                                              | example entries                            | MySQL type declaration                                               |
| -------------- | -------------------------------------------------- | -------------------------------------------------------- | :----------------------------------------: | -------------------------------------------------------------------- |
| None (Default) | N/A                                                | ascending integers (starting from "1")                   | 1<br/>2<br/>...<br/>*ROW_COUNT*            | **TINYINT** - **INT** (depends on *ROWCOUNT*)                        |
| Fixed          | `<-f, --fixed> <FIXED_INT>`                        | all entries set to *FIXED_INT*, **GRP_SPEC not allowed** | -1234567<br/>-1234567<br/>...<br/>-1234567 | **TINYINT** - **BIGINT** (depends on *FIXED_INT*)                    |
| Unique         | `<-u, --unique>`                                   | ascending integers (starting from "1")                   | 1<br/>2<br/>...<br/>*ROW_COUNT*            | **TINYINT** - **INT** (depends on *ROWCOUNT*)                        |
| Random Default | `<-r, --random>`                                   | random 32 bit integers                                   | -99123112<br/>1012233332<br/>...<br/>-5992 | **INT**                                                              |
| Random From    | `<-r, --random> <-f, --from> <MIN_INT>`            | random 32 or 64 bit integers ≥ *MIN_INT*                 | 1337<br/>*MIN_INT*<br/>...<br/>-223121232  | **INT** or **BIGINT** (depends on *MIN_INT*)                         |
| Random Upto    | `<-r, --random> <-u, --upto> <MAX_INT>`            | random 32 or 64 bit integers ≤ *MAX_INT*                 | *MAX_INT*<br/>-123123123<br/>...<br/>12313 | **INT** or **BIGINT** (depends on *MAX_INT*)                         |
| Random Range   | `<-r, --random> <-r, --range> <MIN_INT> <MAX_INT>` | random 32 or 64 bit integers ≤ *MIN_INT* and ≥ *MAX_INT* | 412221<br/>*MAX_INT*<br/>...<br/>*MIN_INT* | **INT** or **BIGINT** (depends on larger of *MIN_INT* and *MAX_INT*) |


### Unsigned Integer (TINYINT UNSIGNED, SMALLINT UNSIGNED, MEDIUMINT UNSIGNED, INT UNSIGNED, BIGINT UNSIGNED)

#### `<-u, --unsigned-integer>`

| Qualifier      | `COL_TYPE_Q`                                         | description                                                         | example entries                              | MySQL type declaration                                               |
| -------------- | ---------------------------------------------------- | ------------------------------------------------------------------- | :------------------------------------------: | -------------------------------------------------------------------- |
| None (Default) | N/A                                                  | ascending integers (starting from "1")                              | 1<br/>2<br/>...<br/>*ROW_COUNT*              | **TINYINT UNSIGNED** - **INT UNSIGNED** (depends on *ROWCOUNT*)      |
| Fixed          | `<-f, --fixed> <FIXED_UINT>`                         | all entries set to *FIXED_UINT*, **GRP_SPEC not allowed**           | 1234567<br/>1234567<br/>...<br/>1234567      | **TINYINT UNSIGNED** - **BIGINT UNSIGNED** (depends on *FIXED_UINT*) |
| Unique         | `<-u, --unique>`                                     | ascending integers (starting from "1")                              | 1<br/>2<br/>...<br/>*ROW_COUNT*              | **TINYINT UNSIGNED** - **INT UNSIGNED** (depends on *ROWCOUNT*)      |
| Random Default | `<-r, --random>`                                     | random 32 bit unsigned integers                                     | 99123112<br/>321123123<br/>...<br/>5992      | **INT UNSIGNED**                                                     |
| Random From    | `<-r, --random> <-f, --from> <MIN_UINT>`             | random 32 or 64 bit unsigned integers ≥ *MIN_UINT*                  | 1337<br/>*MIN_UINT*<br/>...<br/>223121232    | **INT UNSIGNED** or **BIGINT UNSIGNED** (depends on *MIN_UINT*)      |
| Random Upto    | `<-r, --random> <-u, --upto> <MAX_UINT>`             | random 32 or 64 bit unsigned integers ≤ *MAX_UINT*                  | *MAX_UINT*<br/>123123123<br/>...<br/>12313   | **INT UNSIGNED** or **BIGINT UNSIGNED** (depends on *MAX_UINT*)      |
| Random Range   | `<-r, --random> <-r, --range> <MIN_UINT> <MAX_UINT>` | random 32 or 64 bit unsigned integers ≤ *MIN_UINT* and ≥ *MAX_UINT* | 412221<br/>*MAX_UINT*<br/>...<br/>*MIN_UINT* | **INT UNSIGNED** or **BIGINT UNSIGNED** (depends on *MAX_UINT*)      |


### Datetime (DATETIME)

#### `<-dt, --datetime>`

| Qualifier      | `COL_TYPE_Q`     | description                                                              | example entries                                                             | MySQL type declaration |
| -------------- | ---------------- | ------------------------------------------------------------------------ | :-------------------------------------------------------------------------: | ---------------------- |
| None (Default) | N/A              | ascending UTC datetimes (starting from current datetime, 1 second apart) | 2016-09-02 18:08:25<br/>2016-09-02 18:08:26<br/>...<br/>2016-09-02 18:10:01 | **DATETIME**           |
| Fixed          | `<-f, --fixed>`  | all entries set to current UTC datetime, **GRP_SPEC not allowed**        | 2016-09-02 18:08:25<br/>2016-09-02 18:08:25<br/>...<br/>2016-09-02 18:09:25 | **DATETIME**           |
| Unique         | `<-u, --unique>` | ascending UTC datetimes (starting from current datetime, 1 second apart) | 2016-09-02 18:08:25<br/>2016-09-02 18:08:26<br/>...<br/>2016-09-02 18:10:01 | **DATETIME**           |


### Timestamp (TIMESTAMP)

#### `<-ts, --timestamp>`

| Qualifier      | `COL_TYPE_Q`     | description                                                                | example entries                                                             | MySQL type declaration |
| -------------- | ---------------- | -------------------------------------------------------------------------- | :-------------------------------------------------------------------------: | ---------------------- |
| None (Default) | N/A              | ascending UTC timestamps (starting from current timestamp, 1 second apart) | 2016-09-02 18:08:25<br/>2016-09-02 18:08:26<br/>...<br/>2016-09-02 18:10:01 | **TIMESTAMP**          |
| Fixed          | `<-f, --fixed>`  | all entries set to current UTC timestamp, **GRP_SPEC not allowed**         | 2016-09-02 18:08:25<br/>2016-09-02 18:08:25<br/>...<br/>2016-09-02 18:09:25 | **TIMESTAMP**          |
| Unique         | `<-u, --unique>` | ascending UTC timestamps (starting from current timestamp, 1 second apart) | 2016-09-02 18:08:25<br/>2016-09-02 18:08:26<br/>...<br/>2016-09-02 18:10:01 | **TIMESTAMP**          |


### String (VARCHAR, CHAR)

#### `<-s, --string>`  

| Qualifier      | `COL_TYPE_Q`                   | description                                                              | example entries                                         | MySQL type declaration                            |
| -------------- | ------------------------------ | ------------------------------------------------------------------------ | :-----------------------------------------------------: | ------------------------------------------------- |
| None (Default) | N/A                            | *COL_NAME* concatenated with an ascending integer (starting from "1")    | username1<br/>username2<br/>...<br/>username*ROW_COUNT* | **CHAR(***length(COL_NAME)***)**                  |
| Fixed          | `<-f, --fixed> <FIXED_STRING>` | all entries set to *FIXED_STRING*, **GRP_SPEC not allowed**              | foo bar<br/>foo bar<br/>...<br/>foo bar                 | **CHAR(***length(FIXED_STRING)***)**              |
| Unique         | `<-u, --unique> <BASE_STRING>` | *BASE_STRING* concatenated with an ascending integer (starting from "1") | foo1<br/>foo2<br/>...<br/>foo*ROW_COUNT*                | **VARCHAR(***length(BASE_STRING*ROW_COUNT*)***)** |
| Hash           | `<-h, --hash> <HASH_LENGTH>`   | shuffled strings of hexadecimal digits having length *HASH_LENGTH*       | af100<br/>92dd1<br/>...<br/>1d2ba                       | **CHAR(***HASH_LENGTH***)**                       |
| UUID           | `<-uu, --uuid>`              | Universally Unique Idenfiers (version 1) | 866d0c36-3a20-11b2-fb9d-d0a637edde91<br/>866d0c37-3a20-11b2-fb9d-d0a637edde91<br/>...<br/>d71dd15d-3a20-11b2-fb9d-d0a637edde91 | **CHAR(36)** |
| First Names    | `<-n1, --names-first>`         | random sample of American first names                                    | Robert<br/>Alice<br/>...<br/>Joseph                     | **VARCHAR(***FIRST_NAME_LENGTH_MAX***)**          |
| Last Names     | `<-nl, --names-last>`          | random sample of American last names                                     | Smith<br/>Johnson<br/>...<br/>Garcia                    | **VARCHAR(***LAST_NAME_LENGTH_MAX***)**           |
| Full Names     | `<-nf, --names-full>`          | <*FIRST_NAME*> [*INITIAL* &# 124; *FIRST_NAME*] <*LAST_NAME*>             | Amy Cruz<br/>Susan E Bell<br/>...<br/>Bob Joe Cook      | **VARCHAR(***FULL_NAME_LENGTH_MAX***)**           |
| Join           | `<-j, --join> <JOIN_1> [+ JOIN_2] ... [+ JOIN_N]` | `+`-delimited *JOIN*s are expanded and then concatenated into a single string column (see below for more details) | Hello, my name is John, I am 28 years old, and I'm with group # 1!<br/>Hello, my name is Samantha, I am 38 years old, and I'm with group # 1!<br/>...<br/>Hello, my name is Aaron, I am 17 years old, and I'm with group #*GRP_COUNT*! | **CHAR(***Σlength(JOIN_i)***)** or **VARCHAR(***Σlength(JOIN_i)***)** (depends on variability of *JOIN*s and total length) |


### Join Strings (VARCHAR, CHAR)

#### `<-s, --string> <-j, --join> <JOIN_1> [+ JOIN_2] ... [+ JOIN_N]` where

#### `JOIN := <COL_TYPE> [COL_TYPE_Q] [GRP_SPEC] | <FIXED_STRING>`  

A Join String `COL_SPEC` will expand its `+`-delimited list of `JOIN` statements and then concatenate the result into a single string column. If `JOIN` starts with a `-`, it will be parsed identically to the latter portion of an independent 'COL_SPEC' (`<COL_TYPE> [COL_TYPE_Q] [GRP_SPEC]`), otherwise it will be interpreted as filler string (`<FIXED_STRING`). If a `<FIXED_STRING>` starting with a `-` is desired, an explicit Fixed String `JOIN` statement (`<-s, --string> <-f, --fixed> <FIXED_STRING>`) can be used to ensure correct interpretation. That being said, all `<COL_TYPE> [COL_TYPE_Q] [GRP_SPEC]` compositions supported in individual `COL_SPEC`s (**except** nested Join String declarations) can be expressed in a `JOIN`. MySQL typing for `CREATE` statements of a Join String column will be set to either `CHAR` or `VARCHAR` depending on whether or not the column's total length is constant and no more than `CHAR`-maximum of 255 UTF8 code points.

**example**  
The `COL_SPEC`
```
--column xml --string --join "<message id='" \
                           + --string --hash 16 \
                           + "' from='user" \
                           + --integer \
                           + "@example.com/resource' to='chatroom" \
                           + --integer --group 3 --linear \
                           + "@conference.example.com' type='groupchat'><body>Hello chatroom" \
                           + --integer --group 3 --linear \
                           + " from user" \
                           + --integer \
                           + "\!</body></message>"
```
will generate a column of XMPP groupchat stanzas distributed linearly across 3 separate multi-user chat rooms. `xml VARCHAR(151)` will be added to the `CREATE TABLE` statement in the `load_<DB_NAME>.mysql` script, and, for a table of 24 rows, the column data will look similar to this:
```
<message id='f2af7519924f4459' from='user1@example.com/resource' to='chatroom1@conference.example.com' type='groupchat'><body>Hello chatroom1 from user1!</body></message>
<message id='ceb87434c96755f4' from='user2@example.com/resource' to='chatroom1@conference.example.com' type='groupchat'><body>Hello chatroom1 from user2!</body></message>
<message id='8920c40acc278049' from='user3@example.com/resource' to='chatroom1@conference.example.com' type='groupchat'><body>Hello chatroom1 from user3!</body></message>
<message id='0f41b039caf09da9' from='user4@example.com/resource' to='chatroom1@conference.example.com' type='groupchat'><body>Hello chatroom1 from user4!</body></message>
<message id='d3498737688ed8df' from='user5@example.com/resource' to='chatroom2@conference.example.com' type='groupchat'><body>Hello chatroom2 from user5!</body></message>
<message id='403fdeab7d3fdb82' from='user6@example.com/resource' to='chatroom2@conference.example.com' type='groupchat'><body>Hello chatroom2 from user6!</body></message>
<message id='fd1f7964abc0b2f7' from='user7@example.com/resource' to='chatroom2@conference.example.com' type='groupchat'><body>Hello chatroom2 from user7!</body></message>
<message id='4bf157116c461d18' from='user8@example.com/resource' to='chatroom2@conference.example.com' type='groupchat'><body>Hello chatroom2 from user8!</body></message>
<message id='d1fcf9b4da6032aa' from='user9@example.com/resource' to='chatroom2@conference.example.com' type='groupchat'><body>Hello chatroom2 from user9!</body></message>
<message id='a1a9df2ffa571fa0' from='user10@example.com/resource' to='chatroom2@conference.example.com' type='groupchat'><body>Hello chatroom2 from user10!</body></message>
<message id='64843bc230f8cf53' from='user11@example.com/resource' to='chatroom2@conference.example.com' type='groupchat'><body>Hello chatroom2 from user11!</body></message>
<message id='f52021bab5e8980e' from='user12@example.com/resource' to='chatroom2@conference.example.com' type='groupchat'><body>Hello chatroom2 from user12!</body></message>
<message id='fe78a4a581d7cc63' from='user13@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user13!</body></message>
<message id='3ac48b42e6f0ddcd' from='user14@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user14!</body></message>
<message id='9a877befba3d7f75' from='user15@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user15!</body></message>
<message id='d975a0fbac388533' from='user16@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user16!</body></message>
<message id='5a9e72ca58afd490' from='user17@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user17!</body></message>
<message id='b04ecbe8cab311cb' from='user18@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user18!</body></message>
<message id='9be7bcebd66e243a' from='user19@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user19!</body></message>
<message id='92ca989a6b8836b5' from='user20@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user20!</body></message>
<message id='43bb18e9f57bf4d4' from='user21@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user21!</body></message>
<message id='a3c52edb08074669' from='user22@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user22!</body></message>
<message id='6f0479812ad3c4db' from='user23@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user23!</body></message>
<message id='25082191e6aa3be5' from='user24@example.com/resource' to='chatroom3@conference.example.com' type='groupchat'><body>Hello chatroom3 from user24!</body></message>
```


## Features
- builds on OS X and Linux systems (Windows in progress)
- robust thread pool implementation built with POSIX threads (pthread) API
- graceful error handling
  - recoverable errors are caught and reported
  - system call failures are logged and reported after cleanup
  - any generated files are deleted, and all dynamically allocated memory is freed on fatal errors before program termination


## Goals

### Short Term
- Windows Compatibility
- `verbose` flag for `execute` mode to toggle on/off blocking and error reports from MySQL process
- local timezone timestamps (instead of UTC)

### Long Term
- logarithmic group partitioning
- support for floating point types (FLOAT, DOUBLE)
