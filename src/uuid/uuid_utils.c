#include "uuid/uuid_utils.h"

/* global constants
 * ────────────────────────────────────────────────────────────────────────── */
struct UUIDState uuid_state;

extern inline void
uuid_state_init_clk_seq_node(char *restrict clk_seq_node,
			     const uint8_t *restrict node);

extern inline void
uuid_state_increment_clk_seq(char *restrict ptr);

extern inline uint64_t
uuid_time_now(const struct HandlerClosure *const restrict fail_cl);

extern inline bool
uuid_mac_address(uint8_t *const restrict mac_address,
		 const char *restrict *const restrict failure);

extern inline char *
put_uuid_time(char *restrict ptr,
	      const uint64_t uuid_time);

extern inline void
uuid_string_increment_time(char *restrict ptr);

extern inline void
set_uuid_clk_seq_node(char *restrict ptr,
		      const struct HandlerClosure *const restrict fail_cl);

extern inline void
uuid_string_init(char *restrict ptr,
		 const struct HandlerClosure *const restrict fail_cl);

/* constructors, destructors
 * ────────────────────────────────────────────────────────────────────────── */
extern inline bool
uuid_utils_constructor(const char *restrict *const restrict failure);
