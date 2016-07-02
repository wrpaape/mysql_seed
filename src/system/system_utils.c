#include "system_utils.h"

extern inline bool
get_winsize_report(struct winsize *const restrict window,
		   const int filedes,
		   const char *restrict *const restrict failure)
