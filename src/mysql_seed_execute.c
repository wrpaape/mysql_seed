#include "mysql_seed_execute.h"

/* print errors
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
execute_failure_no_exec_spec(void);
extern inline void
execute_failure_short_exec_spec(void);
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
extern inline void
execute_no_db_names(void);
extern inline void
execute_no_user_or_db_names(void);
extern inline void
execute_no_valid_db_names(void);

/* parsing MySQL credentials
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
read_mysql_password(struct MysqlPassword *const restrict password);
extern inline char *const restrict *restrict
execute_parse_user(const char *restrict *const restrict user,
		   char *const restrict *restrict from,
		   char *const restrict *restrict until);
extern inline char *const restrict *restrict
execute_parse_pwd(struct MysqlPassword *const restrict password,
		  char *const restrict *restrict from,
		  char *const restrict *restrict until);
extern inline char *const restrict *restrict
execute_parse_pwd_short_first(struct MysqlCredentials *const restrict creds,
			      const char *restrict rem_flag,
			      char *const restrict *restrict from,
			      char *const restrict *restrict until);
extern inline char *const restrict *restrict
execute_parse_pwd_long_first(struct MysqlCredentials *const restrict creds,
			     const char *restrict rem_flag,
			     char *const restrict *restrict from,
			     char *const restrict *restrict until);
extern inline char *const restrict *restrict
execute_parse_user_short_first(struct MysqlCredentials *const restrict creds,
			       const char *restrict rem_flag,
			       char *const restrict *restrict from,
			       char *const restrict *restrict until);
extern inline char *const restrict *restrict
execute_parse_user_long_first(struct MysqlCredentials *const restrict creds,
			      const char *restrict rem_flag,
			      char *const restrict *restrict from,
			      char *const restrict *restrict until);

extern inline char *const restrict *restrict
execute_parse_credentials(struct MysqlCredentials *const restrict credentials,
			  char *const restrict *restrict from,
			  char *const restrict *restrict until);

/* parsing DB_NAME
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
execute_parse_db_name(struct String *const restrict db_name,
		      char *const restrict arg);

extern inline struct String *
execute_parse_db_names_recover(struct String *restrict db_names,
			       char *const restrict *restrict from,
			       char *const restrict *restrict until);

extern inline struct String *
execute_parse_db_names(struct String *restrict db_names,
		       char *const restrict *restrict from,
		       char *const restrict *restrict until,
		       int *const restrict exit_status);



/* dispatch load mode according to 'arg_ptr'
 *─────────────────────────────────────────────────────────────────────────── */
extern inline int
execute_dispatch(char *const restrict *restrict from,
		 const unsigned int rem_argc);
