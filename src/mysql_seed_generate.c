#include "mysql_seed_generate.h"

/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
print_no_database_flag(void);

extern inline int
print_invalid_database_flag(char *const restrict flag);


/* DBPoolGrid operations (call only from main thread)
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
db_pool_grid_destroy(struct DBPoolGrid *restrict db_pool_grid);
extern inline void
db_pool_grid_shutdown_failure(struct DBPoolGrid *restrict db_pool_grid,
			      const char *const restrict failure);
extern inline void
db_pool_grid_shutdown_success(struct DBPoolGrid *restrict db_pool_grid);
void
db_pool_grid_exit_on_failure(void *arg,
			     const char *const restrict failure)
{
	struct DBPoolGrid *const restrict db_pool_grid
	= (struct DBPoolGrid *const restrict) arg;

	/* shutdown all pools and self destruct */
	db_pool_grid_shutdown_failure(db_pool_grid,
				      failure);
	/* destroy pool grid */
	db_pool_grid_destroy(db_pool_grid);

	/* dump failure message to stderr and exit */
	exit_failure_print_message(failure);
	__builtin_unreachable();
}
extern inline void
db_pool_grid_init(struct DBPoolGrid *const restrict db_pool_grid,
		  struct ThreadPool *const restrict *const restrict pools,
		  const size_t count_pools)
extern inline struct DBPoolGrid *
db_pool_grid_create(const size_t count_db_specs);
extern inline int
db_pool_grid_process(struct DBPoolGrid *const restrict db_pool_grid,
		     char *restrict *const restrict db_spec,
		     char *restrict *const restrict next_db_spec,
		     char *const restrict *const restrict until_ptr);

/* dispatch generate mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
process_db_specs(char *restrict *const restrict db_spec,
		 char *const restrict *const restrict until_ptr)
extern inline int
generate_dispatch(char *const restrict *const restrict arg_ptr,
		  char *const restrict *const restrict until_ptr);
