#include "mysql_seed.h"

/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
print_no_mode_flag(void);

extern inline void
print_invalid_mode_flag(char *const restrict arg);


/* parse stdin args
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
mode_dispatch(char *const *const restrict from,
	      const int rem_argc);


/* main entry point
 *─────────────────────────────────────────────────────────────────────────── */
int
main(int argc,
     char **argv)
{
	if (argc < 2) {
		print_no_mode_flag();
		return EXIT_FAILURE;
	}

	return mode_dispatch(argv + 1l,
			     argc - 2);
}
