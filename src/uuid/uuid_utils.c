#include "uuid/uuid_utils.h"

extern inline uint64_t
uuid_time_now(const struct HandlerClosure *const restrict fail_cl);

extern inline void
uuid_mac_address(uint8_t *const restrict mac_address,
		 const struct HandlerClosure *const restrict fail_cl);

extern inline void
uuid_init(struct UUID *const restrict uuid,
	  const struct HandlerClosure *const restrict fail_cl);
