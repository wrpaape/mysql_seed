#ifndef MYSQL_SEED_UUID_UUID_UTILS_H_
#define MYSQL_SEED_UUID_UUID_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* thread, time utils */
#include "system/file_utils.h"	/* system calls for retrieveing MAC */
#include "random/random.h"		/* psuedo-random number generator */
#include "string/string_utils.h"	/* string utils */


/* macro constants
 * ────────────────────────────────────────────────────────────────────────── */
#define LENGTH_MAC_ADDRESS 6lu

/* 100-nanosecond intervals elapsed from October 15, 1582 to January 1, 1970 */
#define GREGORIAN_REFORM_EPOCH_DIFF 122192928000000000lu

#define UUID_VERSION 1

#ifdef WIN32
#	define UUID_GET_PROCESS_HEAP_FAILURE				\
	FAILURE_REASON("uuid_mac_address", "GetProcessHeap failure")

#	define UUID_HEAP_ALLOC_FAILURE					\
	FAILURE_REASON("uuid_mac_address", "HeapAlloc failure")

#	define UUID_HEAP_FREE_FAILURE					\
	FAILURE_REASON("uuid_mac_address", "HeapFree failure")
#else
#	define MAIN_INTERFACE_NAME "en0"
#endif /* ifdef WIN32 *?

/* typedefs, structs
 * ────────────────────────────────────────────────────────────────────────── */
struct UUID {
	uint32_t time_low;
	uint16_t time_mid;
	uint16_t time_hi_and_version;
	uint8_t clk_seq_hi_res;
	uint8_t clk_seq_low;
	uint8_t node[LENGTH_MAC_ADDRESS];
};

struct UUIDState {
	Mutex lock;
	uint16_t clk_seq;
	uint8_t node[LENGTH_MAC_ADDRESS];
};


struct MACAddressBuffer {
	uint8_t octets[LENGTH_MAC_ADDRESS];
};

#define SET_MAC_ADDRESS(PTR, MAC)					\
*((struct MACAddressBuffer *const restrict) PTR)			\
= *((const struct MACAddressBuffer *const restrict) MAC)

#define UUID_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("uuid_mac_address")


/* global constants
 * ────────────────────────────────────────────────────────────────────────── */
extern struct UUIDState uuid_state;


/* constructors, destructors
 * ────────────────────────────────────────────────────────────────────────── */
void
uuid_utils_start_failure(const char *restrict failure)
__attribute__((noreturn));

void
uuid_utils_start(void)
__attribute__((constructor (103)));

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

inline bool
uuid_state_init_mac_address(uint8_t *const restrict mac_address,
			    const char *restrict *const restrict failure)
{

#ifdef WIN32
	ULONG size_required;

	if (!size_adapters_addresses_report(0,
					    0,
					    NULL,
					    &size_required,
					    failure))
		return false;

	const WINAPI heap = GetProcessHeap();

	if (heap == NULL) {
		*failure = UUID_GET_PROCESS_HEAP_FAILURE;
		return false;
	}

	const PIP_ADAPTER_ADDRESSES adapter_addresses
	= HeapAlloc(heap,
		    0,
		    size_required):

	if (adapter_addresses == NULL) {
		*failure = UUID_HEAP_ALLOC_FAILURE;
		return false;
	}

	if (!get_adapters_addresses_report(0,
					   0,
					   NULL,
					   adapter_addresses,
					   &size_required,
					   failure)) {
		(void) HeapFree(heap,
				0,
				adapter_addresses);
		return false;
	}

	SET_MAC_ADDRESS(mac_address,
			adapter_addresses->Address);

	const bool free_success = HeapFree(heap,
					   0,
					   adapter_addresses);

	if (!free_success)
		*failure = UUID_HEAP_FREE_FAILURE;

	return free_success;

#else
	struct ifconf configuration;
	size_t size_required;
	int interface_index;

	if (!interface_name_to_index_report(&interface_index,
					    MAIN_INTERFACE_NAME,
					    failure))
		return false;

	int mib_name[6u] = {
		[0u] = CTL_NET,
		[1u] = PF_ROUTE,
		[2u] = 0,
		[3u] = PF_LINK,
		[4u] = NET_RT_IFLIST,
		[5u] = interface_index
	};

	if (!sysctl_report(&mib_name[0],
			   6u,
			   NULL,
			   &size_required,
			   NULL,
			   0,
			   failure))
		return false;

	configuration.ifc_buf = malloc(size_required);

	if (configuration.ifc_buf == NULL) {
		*failure = UUID_MALLOC_FAILURE;
		return false;
	}

	if (!sysctl_report(&mib_name[0],
			   6u,
			   configuration.ifc_buf,
			   &size_required,
			   NULL,
			   0,
			   failure)) {
		free(configuration.ifc_buf);
		return false;
	}

	const struct if_msghdr *const restrict header
	= (const struct if_msghdr *const restrict) configuration.ifc_buf;

	const struct sockaddr_dl *const restrict address
	= (const struct sockaddr_dl *const restrict) (header + 1l);

	SET_MAC_ADDRESS(mac_address,
			LLADDR(address));

	free(configuration.ifc_buf);

	return true;
#endif /* ifdef WIN32 */
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
