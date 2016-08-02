#ifndef MYSQL_SEED_TIME_UUID_UTILS_H_
#define MYSQL_SEED_TIME_UUID_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "utils/types/octet.h"
#include "stdint.h"

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



#endif /* ifndef MYSQL_SEED_TIME_UUID_UTILS_H_ */
