#ifndef MYSQL_SEED_MYSQL_SEED_H_
#define MYSQL_SEED_MYSQL_SEED_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_generate.h"	/* generate mode */
#include "mysql_seed_execute.h"		/* execute mode */
#include "mysql_seed_remove.h"		/* remove mode */
#include "mysql_seed_help.h"		/* help mode */

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define FAILURE_NO_MODE_FLAG						\
PARSE_FAILURE_MESSAGE("MODE not specified") MORE_INFO_MESSAGE

#define FAILURE_INVALID_MODE_FLAG_HEADER				\
PARSE_FAILURE_HEADER("invalid MODE flag")

/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
inline void
print_no_mode_flag(void)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_NO_MODE_FLAG,
		     sizeof(FAILURE_NO_MODE_FLAG) - 1lu);
}

inline void
print_invalid_mode_flag(char *const restrict arg)
{
	char buffer[ARG_INSPECT_BUFFER_SIZE];

	char *restrict ptr
	= put_string_size(&buffer[0],
			  FAILURE_INVALID_MODE_FLAG_HEADER,
			  sizeof(FAILURE_INVALID_MODE_FLAG_HEADER) - 1lu);

	ptr = put_string_inspect(ptr,
				 arg,
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      MORE_INFO_MESSAGE,
			      sizeof(MORE_INFO_MESSAGE) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}

/* parse stdin args
 *─────────────────────────────────────────────────────────────────────────── */
inline int
mode_dispatch(char *const *const restrict from,
	      const unsigned int rem_argc)
{
	char *const restrict flag = *from;

	if (*flag != '-')
		goto INVALID_MODE_FLAG;

	const char *const restrict arg = flag + 1l;
	const char *const restrict rem = arg + 1l;


	/* parse short mode flag */
	switch (*arg) {
	case '-':
		break;	/* parse long mode flag */

	case 'g':
		if (*rem == '\0')
			return generate_dispatch(from + 1l,
						 rem_argc);
		goto INVALID_MODE_FLAG;


	case 'h':
		if (*rem == '\0')
			return help_dispatch(from + 1l,
					     rem_argc);
		goto INVALID_MODE_FLAG;


	case 'e':
		if (*rem == '\0')
			return execute_dispatch(from + 1l,
						rem_argc);
		goto INVALID_MODE_FLAG;

	case 'r':
		if (*rem == '\0')
			return remove_dispatch(from + 1l,
					       rem_argc);

	default:
		goto INVALID_MODE_FLAG;
	}

	/* parse long mode flag */
	switch (*rem) {
	case 'g':
		if (strings_equal("enerate", rem + 1l))
			return generate_dispatch(from + 1l,
						 rem_argc);
		break;

	case 'h':
		if (strings_equal("elp", rem + 1l))
			return help_dispatch(from + 1l,
					     rem_argc);
		break;

	case 'e':
		if (strings_equal("xecute", rem + 1l))
			return execute_dispatch(from + 1l,
						rem_argc);
		break;

	case 'r':
		if (strings_equal("emove", rem + 1l))
			return remove_dispatch(from + 1l,
					       rem_argc);

	default:
		break;
	}

INVALID_MODE_FLAG:
	print_invalid_mode_flag(flag);
	return EXIT_FAILURE;
}
#endif	/* MYSQL_SEED_MYSQL_SEED_H_ */
