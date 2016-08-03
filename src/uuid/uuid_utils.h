#ifndef MYSQL_SEED_UUID_UUID_UTILS_H_
#define MYSQL_SEED_UUID_UUID_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "time/time_utils.h"		/* timespec_now, stdint */
#include "system/system_utils.h"	/* getaddrinfo */

/* typedefs, structs
 * ────────────────────────────────────────────────────────────────────────── */
struct UUID {
	uint32_t time_low;
	uint16_t time_mid;
	uint16_t time_hi_and_version;
	uint8_t clk_seq_hi_res;
	uint8_t clk_seq_low;
	uint8_t node[6];
};

/* 100-nanosecond intervals elapsed from October 15, 1582 to January 1, 1970 */
#define GREGORIAN_REFORM_EPOCH_DIFF 122192928000000000lu

#define UUID_VERSION 1


inline uint64_t
uuid_time_now(const struct HandlerClosure *const restrict fail_cl)
{
	struct timespec now;

	timespec_now_handle_cl(&now,
			       fail_cl);

	return (now.tv_sec * 10000000lu)
	     + (now.tv_nsec / 100lu)
	     + GREGORIAN_REFORM_EPOCH_DIFF;
}

inline void
uuid_mac_address(uint8_t *const restrict mac_address,
		 const struct HandlerClosure *const restrict fail_cl)
{
	struct addrinfo hints = {
		.ai_family   = AF_UNSPEC,		/* AF_INET, AF_INET6 */
		.ai_socktype = 0,			/* any socket type */
		.ai_protocol = 0,			/* any protocol */
		.ai_flags    = AI_ALL | AI_V4MAPPED	/* IPv6, IPv4 */
	};

	struct addrinfo *result;
	struct addrinfo *ptr;

	getaddrinfo_handle_cl("localhost",
			      NULL,
			      &hints,
			      &result,
			      fail_cl);

	bool found = false;

	uint8_t mac[6] = { 0 };

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		*((Width6 *) &mac[0]) = *((Width6 *) &ptr->ai_addr->sa_data[0]);

		printf("%02X:%02X:02%X:%02X:%02X:%02X\n",
		       mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	}

	freeaddrinfo(result);
}


inline void
uuid_init(struct UUID *const restrict uuid,
	  const struct HandlerClosure *const restrict fail_cl)
{
	const uint64_t now = uuid_time_now(fail_cl);

	uuid->time_low = (uint32_t) now;

	uuid->time_mid = (uint16_t) (now >> 32);

	uuid->time_hi_and_version = (uint16_t) ((now >> 48)
						| (UUID_VERSION << 12));
}



#endif /* ifndef MYSQL_SEED_UUID_UUID_UTILS_H_ */
