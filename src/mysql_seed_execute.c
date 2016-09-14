#include "mysql_seed_execute.h"

/* print errors
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
execute_failure_no_exec_spec(void);
extern inline void
execute_failure_short_exec_spec(void);
extern inline void
execute_expected_db_flag(const char *const restrict invalid);
extern inline void
execute_invalid_db_name_empty(void);
extern inline void
execute_invalid_db_name_invalid(const char *const restrict db_name);
extern inline void
execute_invalid_db_name_long(const char *const restrict db_name);
extern inline void
execute_password_already_set(void);
extern inline void
execute_user_already_set(const char *const restrict user);

/* parsing DB_NAME
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
execute_parse_db_name(struct String *const restrict db_name,
		      char *const restrict arg);

extern inline bool
execute_db_flag_match(char *const restrict arg);


/* read MySQL password
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
read_mysql_password(char *const restrict buffer,
		    const size_t size_max,
		    const char *restrict *const restrict failure);


/* dispatch load mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
execute_dispatch(char *const restrict *restrict from,
		 const unsigned int rem_argc);
