#include "system/exit_utils.h"

void
exit_failure_dump_buffer(const void *const restrict buffer,
			 const size_t size)
{
	write_muffle(STDERR_FILENO,
		     buffer,
		     size);
	exit(EXIT_FAILURE);
}
void
exit_success_dump_buffer(const void *const restrict buffer,
			 const size_t size)
{
	const char *restrict failure;

	if (write_report(STDOUT_FILENO,
			 buffer,
			 size,
			 &failure))
		exit(EXIT_SUCCESS);

	exit_failure_print_message(failure);
	__builtin_unreachable();
}

extern inline void
exit_success_print_message(const char *const restrict message);
extern inline void
exit_failure_print_message(const char *const restrict message);

/* push 'exit_action' to the top of the callback stack to be executed on exit */
extern inline bool
exit_action_push_status(Action *const exit_action);
extern inline void
exit_action_push_muffle(Action *const exit_action);
extern inline bool
exit_action_push_report(Action *const exit_action,
			const char *restrict *const restrict failure);
extern inline void
exit_action_push_handle(Action *const exit_action,
			Handler *const handle,
			void *arg);
extern inline void
exit_action_push_handle_cl(Action *const exit_action,
			   const struct HandlerClosure *const restrict fail_cl);
