#ifndef MYSQL_SEED_MYSQL_SEED_INPUT_H_
#define MYSQL_SEED_MYSQL_SEED_INPUT_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "system/exit_utils.h"	/* exit, file, string utils */

/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define FLAG_LENGTH_MAX (sizeof("--generate") * 2lu)
#define INVALID_FLAG_BUFFER_SIZE

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define MORE_INFO_MESSAGE "\n\nmysql_seed -h for more info\n"

#define INVALID_SPEC_HEADER(SPEC)					\
ERROR_WRAP("error - invalid " SPEC ": ")

#define INVALID_FLAG_HEADER(FLAG)					\
ERROR_WRAP("error - invalid " FLAG " flag: ")

#define NO_FLAG_MESSAGE(FLAG)						\
ERROR_WRAP("error - no " FLAG " flag specified") MORE_INFO_MESSAGE


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct String {
	const char *bytes;
	size_t size;
};

#define FAIL_SWITCH_ERRNO_FAILURE	0lu
#define FAIL_SWITCH_FAILURE_POINTER	failure


#define FAIL_SWITCH_FAILURE_ROUTINE	utf8_string_size_length
inline bool
string_init_utf8_length_report(struct String *const restrict string,
			       const char *const restrict bytes,
			       const size_t length,
			       const char *restrict *const restrict failure)
{
	string->size = utf8_string_size_length(bytes,
					       length);

	if (string->size > 0lu) {
		string->bytes = bytes;
		return true;
	}

	switch(errno) {
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "'bytes' contains byte sequence(s) that are "
				 "not valid UTF-8 code points")
	FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
				 "'bytes' exceeds maximum UTF-8 code point "
				 "length 'length'")
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

#undef FAIL_SWITCH_ERRNO_FAILURE
#undef FAIL_SWITCH_FAILURE_POINTER
#undef FAIL_SWITCH_FAILURE_ROUTINE

#endif	/* MYSQL_SEED_MYSQL_SEED_INPUT_H_ */
