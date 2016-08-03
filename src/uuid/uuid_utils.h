#ifndef MYSQL_SEED_UUID_UUID_UTILS_H_
#define MYSQL_SEED_UUID_UUID_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "time/time_utils.h"	/* timespec_now, stdint */

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
uuid_time_now(void)
{
	struct timespec now;

	timespec_now_muffle(&now);

	return (now.tv_sec * 10000000lu)
	     + (now.tv_nsec / 100lu)
	     + GREGORIAN_REFORM_EPOCH_DIFF;
}


inline void
uuid_init(struct UUID *const restrict uuid)
{
	const uint64_t now = uuid_time_now();

	uuid->time_low = (uint32_t) now;

	uuid->time_mid = (uint16_t) (now >> 32);

	uuid->time_hi_and_version = (uint16_t) ((now >> 48)
						| (UUID_VERSION << 12));
}



#endif /* ifndef MYSQL_SEED_UUID_UUID_UTILS_H_ */
