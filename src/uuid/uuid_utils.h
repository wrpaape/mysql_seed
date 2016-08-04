#ifndef MYSQL_SEED_UUID_UUID_UTILS_H_
#define MYSQL_SEED_UUID_UUID_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* thread, time utils */
#include "system/file_utils.h"		/* getaddrinfo */

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

#define LENGTH_MAC_ADDRESS 6lu
struct MACAddressBuffer {
	uint8_t octets[LENGTH_MAC_ADDRESS];
};

#define SET_MAC_ADDRESS(PTR, MAC)					\
*((struct MACAddressBuffer *const restrict) PTR)			\
= *((const struct MACAddressBuffer *const restrict) MAC)


#define MAIN_INTERFACE_NAME "en0"


/* 100-nanosecond intervals elapsed from October 15, 1582 to January 1, 1970 */
#define GREGORIAN_REFORM_EPOCH_DIFF 122192928000000000lu

#define UUID_VERSION 1

#define UUID_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("uuid_mac_address")

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
	int mib_name[6u];
	struct ifconf configuration;
	size_t size_required;
	int interface_index;

	thread_protect_open();

	interface_name_to_index_handle_cl(&interface_index,
					  MAIN_INTERFACE_NAME,
					  fail_cl);

	thread_protect_close();

	mib_name[0] = CTL_NET;
	mib_name[1] = PF_ROUTE;
	mib_name[2] = 0;
	mib_name[3] = PF_LINK;
	mib_name[4] = NET_RT_IFLIST;
	mib_name[5] = interface_index;

	sysctl_handle_cl(&mib_name[0],
			 6u,
			 NULL,
			 &size_required,
			 NULL,
			 0,
			 fail_cl);

	configuration.ifc_buf = NULL;

	thread_try_ensure_open(&free,
			       configuration.ifc_buf);

	configuration.ifc_buf = malloc(size_required);

	if (configuration.ifc_buf == NULL) {
		handler_closure_call(fail_cl,
				     UUID_MALLOC_FAILURE);
		__builtin_unreachable();
	}

	sysctl_handle_cl(&mib_name[0],
			 6u,
			 configuration.ifc_buf,
			 &size_required,
			 NULL,
			 0,
			 fail_cl);

	const struct if_msghdr *const restrict header
	= (const struct if_msghdr *const restrict) configuration.ifc_buf;

	const struct sockaddr_dl *const restrict address
	= (const struct sockaddr_dl *const restrict) (header + 1l);

	SET_MAC_ADDRESS(mac_address,
			LLADDR(address));

	thread_try_ensure_close();
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
