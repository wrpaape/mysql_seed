#include "mysql_seed_help.h"

extern inline void
exit_help_usage(void);

extern inline void
exit_help_generate(void);

extern inline void
exit_help_load(void);

/* print help message, return success status
 *─────────────────────────────────────────────────────────────────────────── */
inline int
print_help_usage(void)
{
	const char *restrict failure;

	if (write_report(STDOUT_FILENO,
			 HELP_USAGE_MESSAGE,
			 sizeof(HELP_USAGE_MESSAGE),
			 &failure))
		return EXIT_SUCCESS;

	write_muffle(STDERR_FILENO,
		     failure,
		     string_size(failure));

	return EXIT_FAILURE;
}

inline int
print_help_generate(void)
{
	const char *restrict failure;

	if (write_report(STDOUT_FILENO,
			 HELP_GENERATE_MESSAGE,
			 sizeof(HELP_GENERATE_MESSAGE),
			 &failure))
		return EXIT_SUCCESS;

	write_muffle(STDERR_FILENO,
		     failure,
		     string_size(failure));

	return EXIT_FAILURE;
}

inline int
print_help_load(void)
{
	const char *restrict failure;

	if (write_report(STDOUT_FILENO,
			 HELP_GENERATE_MESSAGE,
			 sizeof(HELP_GENERATE_MESSAGE),
			 &failure))
		return EXIT_SUCCESS;

	write_muffle(STDERR_FILENO,
		     failure,
		     string_size(failure));

	return EXIT_FAILURE;
}


/* dispatch help mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
help_dispatch(char *const restrict *const restrict arg_ptr,
	      char *const restrict *const restrict until_ptr);
