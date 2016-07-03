#include "system_utils.h"

extern inline bool
get_winsize_status(struct winsize *const restrict window,
		   const int file_descriptor);
extern inline void
get_winsize_muffle(struct winsize *const restrict window,
		   const int file_descriptor);
extern inline bool
get_winsize_report(struct winsize *const restrict window,
		   const int file_descriptor,
		   const char *restrict *const restrict failure);
extern inline void
get_winsize_handle(struct winsize *const restrict window,
		   const int file_descriptor,
		   Handler *const handle,
		   void *arg);
extern inline void
get_winsize_handle_cl(struct winsize *const restrict window,
		      const int file_descriptor,
		      const struct HandlerClosure *const restrict fail_cl);
