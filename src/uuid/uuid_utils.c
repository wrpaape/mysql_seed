#include "uuid/uuid_utils.h"

#define UUID_UTILS_START_FAILURE_HEADER					\
FAILURE_HEADER_WRAP("uuid_utils_start", ":")	"\n"


/* global constants
 * ────────────────────────────────────────────────────────────────────────── */
struct UUIDState uuid_state;

/* constructors, destructors
 * ────────────────────────────────────────────────────────────────────────── */
void
uuid_utils_start_failure(const char *restrict failure)
{
	char buffer[256];

	char *restrict ptr;

	ptr = put_string_size(&buffer[0],
			      UUID_UTILS_START_FAILURE_HEADER,
			      sizeof(UUID_UTILS_START_FAILURE_HEADER) - 1lu);

	ptr = put_string(ptr,
			 failure);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);

	exit(EXIT_FAILURE);
	__builtin_unreachable();
}

void
uuid_utils_start(void)
{
	uint8_t node[MAC_ADDRESS_LENGTH];

	const char *restrict failure;

	if (uuid_mac_address(&node[0],
			     &failure)) {
		mutex_init(&uuid_state.lock);

		uuid_state.clk_seq = (uint16_t) random_uint();

		return;
	}

	uuid_utils_start_failure(failure);
	__builtin_unreachable();
}

extern inline uint64_t
uuid_time_now(const struct HandlerClosure *const restrict fail_cl);

extern inline bool
uuid_mac_address(uint8_t *const restrict mac_address,
		 const char *restrict *const restrict failure);

extern inline void
uuid_init(struct UUID *const restrict uuid,
	  const struct HandlerClosure *const restrict fail_cl);
