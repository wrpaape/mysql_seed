#ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_
#define MYSQL_SEED_MYSQL_SEED_GENERATE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h" /* file/exit/string/parallelization utils */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define GD_FAILURE_NO_DB_SPEC    PARSE_FAILURE_MESSAGE("no DB_SPEC")

#define GD_FAILURE_DB_SPEC_SHORT PARSE_FAILURE_MESSAGE("DB_SPEC too short")

#define GD_ERROR_DB_SPEC_SHORT   PARSE_ERROR_MESSAGE("DB_SPEC too short")

#define GD_FAILURE_MALLOC	 MALLOC_FAILURE_MESSAGE("generate_dispatch")

#define GD_FAILURE_PARSE	 PARSE_FAILURE_MESSAGE("no valid DB_SPEC")

/* parsing DB_SPEC */
#define FAILURE_NO_DB_SPEC						\
PARSE_FAILURE_MESSAGE("no DB_SPEC provided") MORE_INFO_MESSAGE

#define FAILURE_DB_SPEC_SHORT						\
PARSE_FAILURE_MESSAGE("DB_SPEC too short, need at least "		\
		      DB_SPEC_LENGTH_MIN_STRING " arguments to "	\
		      "describe a database in generate mode") MORE_INFO_MESSAGE

/* parsing DB_NAME */
#define ERROR_INVALID_DB_NAME_HEADER					\
PARSE_ERROR_HEADER("invalid DB_NAME")

#define ERROR_INVALID_DB_NAME_EMPTY					\
PARSE_ERROR_HEADER("invalid DB_NAME (empty), ignoring DB_SPEC")

#define ERROR_INVALID_DB_NAME_REASON_LONG				\
"\n" ERROR_WRAP("reason: exceeded MySql maximum of "
		DB_NAME_LENGTH_MAX_STRING " non-null UTF-8 codepoints,"
		" ignoring DB_SPEC:") "\n"

#define ERROR_INVALID_DB_NAME_REASON_INVALID				\
"\n" ERROR_WRAP("reason: includes one or more invalid UTF-8 codepoints"	\
		", ignoring DB_SPEC:") "\n"

/* parsing COL_NAME */
#define ERROR_INVALID_COL_NAME_HEADER					\
PARSE_ERROR_HEADER("invalid COL_NAME")

#define ERROR_INVALID_COL_NAME_EMPTY					\
PARSE_ERROR_HEADER("invalid COL_NAME (empty), ignoring DB_SPEC")

#define ERROR_INVALID_COL_NAME_REASON_LONG				\
"\n" ERROR_WRAP("reason: exceeded MySql maximum of "			\
		COL_NAME_LENGTH_MAX_STRING " non-null UTF-8 codepoints"	\
		", ignoring DB_SPEC:") "\n"

#define ERROR_INVALID_COL_NAME_REASON_INVALID				\
"\n" ERROR_WRAP("reason: includes one or more invalid UTF-8 codepoints"	\
		", ignoring DB_SPEC:") "\n"


/* parsing ROW_COUNT */
#define ERROR_INVALID_ROW_COUNT_HEADER					\
PARSE_ERROR_HEADER("invalid ROW_COUNT")

#define ERROR_INVALID_ROW_COUNT_REASON_INVALID				\
"\n" ERROR_WRAP("reason: not a number ≥ 1 or overflows implementation-"	\
		"defined uintmax_t, ignoring DB_SPEC:") "\n"


/* parsing COL_TYPE */
#define ERROR_INVALID_COL_TYPE_HEADER					\
PARSE_ERROR_HEADER("invalid COL_TYPE")

#define ERROR_INVALID_COL_TYPE_REASON_INVALID				\
"\n" ERROR_WRAP("reason: not supported, ignoring DB_SPEC:") "\n"


/* parsing COL_TYPE_Q */
#define ERROR_INVALID_COL_TYPE_Q_HEADER					\
PARSE_ERROR_HEADER("invalid COL_TYPE_Q")

#define ERROR_INVALID_COL_TYPE_Q_REASON_INVALID				\
"\n" ERROR_WRAP("reason: not supported, ignoring DB_SPEC:") "\n"

/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct GeneratorCounter {
	unsigned int databases;
	unsigned int tables;
	unsigned int columns;
};

struct DatabaseCounter {
	unsigned int tables;
	unsigned int columns;
};


/* Generator/DatbaseCounter operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
generator_counter_reset(struct GeneratorCounter *const restrict gen_counter)
{
	gen_counter->databases = 0u;
	gen_counter->tables	 = 0u;
	gen_counter->columns	 = 0u;
}

inline void
database_counter_reset(struct DatabaseCounter *const restrict db_counter)
{
	db_counter->tables  = 0u;
	db_counter->columns = 0u;
}

inline void
generator_counter_increment(struct GeneratorCounter *const restrict gen_counter,
			    struct DatabaseCounter *const restrict db_counter)
{
	gen_counter->databases += 1u;
	gen_counter->tables    += db_counter->tables;
	gen_counter->columns   += db_counter->columns;
}


/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
inline void
print_no_db_spec(void)
{
	write_muffle(STDERR_FILENO,
		     GD_FAILURE_NO_DB_SPEC,
		     sizeof(GD_FAILURE_NO_DB_SPEC) - 1lu);
}

inline void
print_invalid_db_spec(char *const restrict *const restrict from,
		      char *restrict *const restrict until,
		      const char *const restrict reason,
		      const size_t length_reason)
{
	char buffer[ARGV_INSPECT_BUFFER_SIZE];

	const char *const restrict *const restrict until_max = from
							     + ARGC_INSPECT_MAX;
	if (until > until_max)
		until = until_max;

	char *restrict
	ptr = put_string_size(&buffer[0],
			      PARSE_ERROR_INSPECT_1,
			      sizeof(PARSE_ERROR_INSPECT_1) - 1lu);

	ptr = put_inspect_args(ptr,
			       from,
			       until);

	ptr = put_string_size(ptr,
			      reason,
			      length_reason);


	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

inline void
print_generate_dispatch_malloc_failure(void)
{
	write_muffle(STDERR_FILENO,
		     GD_FAILURE_MALLOC
		     sizeof(GD_FAILURE_MALLOC) - 1lu);
}

inline void
print_generate_dispatch_parse_failure(void)
{
	write_muffle(STDERR_FILENO,
		     GD_FAILURE_PARSE
		     sizeof(GD_FAILURE_PARSE) - 1lu);

}

/* dispatch generate mode according to 'from'
 *─────────────────────────────────────────────────────────────────────────── */
inline void
generate_scan_specs(struct GeneratorCounter *const restrict gen_counter,
		    struct DbSpec *restrict spec_buffer,
		    int *const restrict exit_status,
		    char *const restrict *restrict from,
		    const char *const restrict *const restrict until)
{

	struct DatabaseCounter db_counter = {
		.tables	   = 0lu,
		.columns   = 0lu
	};

	char *const restrict *const restrict last_valid_db_spec
	= until - DB_SPEC_LENGTH_MIN;

	struct DbSpec *restrict db_spec;
	struct TblSpec *restrict tbl_spec;
	struct ColSpec *restrict col_spec;

	while (1) {
		from = flag_match_next(from,
				       until,
				       'd',
				       "database");

		if (from > last_valid_db_spec)
			return;


		++from;

		/* parse DB_NAME */

		utf8_string_size_length_status




		generator_counter_increment(gen_counter,
					    &db_counter);

		spec_buffer = next_spec_buffer;

		database_counter_reset(&db_counter);
	}
}


inline int
generate_dispatch(char *restrict *const restrict arg,
		  const int rem_argc)
{
	if (rem_argc < DB_SPEC_LENGTH_MIN) {

		if (rem_argc == 0lu)
			print_no_db_spec()
		else
			print_invalid_db_spec(arg,
					      arg + rem_argc,
					      GD_FAILURE_DB_SPEC_SHORT,
					      sizeof(GD_FAILURE_DB_SPEC_SHORT)
					      - 1lu);

		return EXIT_FAILURE;
	}
	/* calculate max required size for all components + their specs
	 *
	 *
	 * minimal valid (i.e. most memory dense) input for GENERATE MODE:
	 *
	 *                      ARGV - 9 args
	 * ┌──────────────────────────────────────────────────────┐
	 * │                     DB_SPEC - 8 args                 │
	 * │  ┌───────────────────────────────────────────────────┐
	 * │  │                        TBL_SPEC - 6 args          │
	 * │  │          ┌────────────────────────────────────────┐
	 * │  │          │                      COL_SPEC - 3 args │
	 * │  │          │                     ┌──────────────────┐
	 * │  │          │                     │                  │
	 * -g -d DB_NAME -t TBL_NAME ROW_COUNT -c COL_NAME COL_TYPE
	 *
	 * generates 1 database with 1 table with 1 column
	 *
	 *
	 * extreme valid cases (mac = argc - 1 for leading mode flag)
	 *
	 * (a) DB_SPEC count maximized, need memory for:
	 *                                      always 1 or 0
	 *	DbSpec  X DB_CNT  = mac / 8    ┌─────────────┐
	 *	TblSpec X TBL_CNT = DB_CNT  +  ((mac % 8) / 6)
	 *	ColSpec X COL_CNT = TBL_CNT + (((mac % 8) % 6) / 3)
	 *	                              └───────────────────┘
	 *	with                                always 0
	 *
	 *	((mac % 8) % 6) % 3
	 *
	 *	args leftover for storage-free COL_TYPE_Qs
	 *
	 *
	 * (b) TBL_SPEC count maximized, need memory for:
	 *
	 *	DbSpec  X DB_CNT  = 1
	 *	TblSpec X TBL_CNT = (mac - 2) / 6
	 *	ColSpec X COL_CNT = TBL_CNT + (((mac - 2) % 6) / 3)
	 *	                              └───────────────────┘
	 *	with                               always 1 or 0
	 *
	 *	((mac - 2) % 6) % 3
	 *
	 *	args leftover for COL_TYPE_Qs
	 *
	 *
	 * (c) COL_SPEC count maximized, need memory for:
	 *
	 *	DbSpec	X DB_CNT =  1
	 *	TblSpec	X TBL_CNT = 1
	 *	ColSpec	X COL_CNT = (margc - 5) / 3
	 *
	 *	with
	 *
	 *	(margc - 5) % 3
	 *
	 *	args leftover for COL_TYPE_Qs
	 *
	 *
	 *						overhead
	 * struct DbSpec {
	 *	struct String name;			1 pointer + 1 size_t
	 *	struct TblSpecInterval tbl_specs;	2 pointers
	 * };						────────────────
	 *						3 pointers + 1 size_t
	 *
	 * struct TblSpec {
	 *	struct String name;			1 pointer + 1 size_t
	 *	size_t row_count			1 size_t
	 *	struct ColSpecInterval col_specs;	2 pointers
	 * };						────────────────
	 *						3 pointers + 2 size_t
	 * struct ColSpec {
	 *	struct String name;			1 pointer + 1 size_t
	 *	union TypeQualifier			2 ldbls + 1 uint (max)
	 *	Procedure *create;			1 pointer
	 * };						────────────────
	 *						2 pointer + 1 size_t
	 *						+ 2 lbls + 1 uint
	 * worst case for allocing specs is (c) */

	struct DbSpec *const restrict
	spec_alloc = malloc(sizeof(struct DbSpec)
			    + sizeof(struct TblSpec)
			    + (sizeof(struct ColSpec) * ((rem_argc - 6) / 3)));

	if (spec_alloc == NULL) {
		print_generate_dispatch_malloc_failure();

		return EXIT_FAILURE;
	}

	struct GeneratorCounter gen_counter = {
		.databases = 0lu;
		.tables	   = 0lu;
		.columns   = 0lu;
	};

	int exit_status = EXIT_SUCCESS;

	generate_scan_specs(&gen_counter,
			    spec_alloc,
			    &exit_status,
			    arg,
			    &arg[rem_argc]);

	if (gen_counter.databases == 0u) {
	    print_generate_dispatch_parse_failure();

	    free(spec_alloc);

	    return EXIT_FAILURE;
	}


	free(spec_alloc);

	return exit_status;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_GENERATE_H_ */
