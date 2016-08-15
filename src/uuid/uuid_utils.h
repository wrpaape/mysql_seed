#ifndef MYSQL_SEED_UUID_UUID_UTILS_H_
#define MYSQL_SEED_UUID_UUID_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* thread, time utils */
#include "system/file_utils.h"		/* system calls for retrieveing MAC */
#include "random/random.h"		/* psuedo-random number generator */
#include "string/string_utils.h"	/* string utils */


/* macro constants
 * ────────────────────────────────────────────────────────────────────────── */
#define MAC_ADDRESS_LENGTH 6lu

/* XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX\0 */
#define UUID_STRING_SIZE 37lu

/* 01234
 * -XXXX-XXXXXXXXXXXX\0 */
#define CLK_SEQ_NODE_SIZE   19lu
#define CLK_SEQ_LAST_OFFSET 4l

/* 100-nanosecond intervals elapsed from October 15, 1582 to January 1, 1970 */
#define GREGORIAN_REFORM_EPOCH_DIFF 122192928000000000lu

#define UUID_VERSION 1

/* error message
 * ────────────────────────────────────────────────────────────────────────── */
#define UUID_MALLOC_FAILURE						\
MALLOC_FAILURE_MESSAGE("uuid_mac_address")

#ifdef WIN32
#	define UUID_GET_PROCESS_HEAP_FAILURE				\
	FAILURE_REASON("uuid_mac_address", "GetProcessHeap failure")

#	define UUID_HEAP_ALLOC_FAILURE					\
	FAILURE_REASON("uuid_mac_address", "HeapAlloc failure")

#	define UUID_HEAP_FREE_FAILURE					\
	FAILURE_REASON("uuid_mac_address", "HeapFree failure")
#else
#	define MAIN_INTERFACE_NAME "en0"
#endif /* ifdef WIN32 */


/* typedefs, structs
 * ────────────────────────────────────────────────────────────────────────── */
struct UUID {
	uint32_t time_low;
	uint16_t time_mid;
	uint16_t time_hi_and_version;
	uint8_t clk_seq_hi_res;
	uint8_t clk_seq_low;
	uint8_t node[MAC_ADDRESS_LENGTH];
};

struct UUIDState {
	Mutex lock;
	char clk_seq_node[CLK_SEQ_NODE_SIZE];
	char *restrict clk_seq_last;
};

struct UUIDStringBuffer {
	char bytes[UUID_STRING_SIZE];
};

#define SET_UUID_STRING(PTR, UUID_STRING)				\
*((struct UUIDStringBuffer *const restrict) PTR)			\
= *((const struct UUIDStringBuffer *const restrict) UUID_STRING)

#define PUT_UUID_STRING(PTR, UUID_STRING)				\
({*((struct UUIDStringBuffer *const restrict) PTR)			\
= *((const struct UUIDStringBuffer *const restrict) UUID_STRING);	\
PTR += UUID_STRING_SIZE;})

struct ClkSeqNodeBuffer {
	char bytes[CLK_SEQ_NODE_SIZE];
};

#define SET_CLK_SEQ_NODE(PTR, CLK_SEQ_NODE)				\
*((struct ClkSeqNodeBuffer *const restrict) PTR)			\
= *((const struct ClkSeqNodeBuffer *const restrict) CLK_SEQ_NODE)

struct MACAddressBuffer {
	uint8_t octets[MAC_ADDRESS_LENGTH];
};

#define SET_MAC_ADDRESS(PTR, MAC)					\
*((struct MACAddressBuffer *const restrict) PTR)			\
= *((const struct MACAddressBuffer *const restrict) MAC)




/* global constants
 * ────────────────────────────────────────────────────────────────────────── */
extern struct UUIDState uuid_state;

inline void
uuid_state_init_clk_seq_node(char *restrict clk_seq_node,
			     const uint8_t *restrict node)
{

	const urint_t random = random_uint();

	*clk_seq_node = '-';
	++clk_seq_node;

	/* put clk_seq_hi */
	clk_seq_node = put_octet_hex_lower(clk_seq_node,
					   (uint8_t) random);

	/* put clk_seq_low */
	clk_seq_node = put_octet_hex_lower(clk_seq_node,
					   (uint8_t) (random >> 8));

	*clk_seq_node = '-';
	++clk_seq_node;

	/* put node */
	clk_seq_node = put_octet_hex_lower(clk_seq_node,
					   *node);
	++node;
	clk_seq_node = put_octet_hex_lower(clk_seq_node,
					   *node);
	++node;
	clk_seq_node = put_octet_hex_lower(clk_seq_node,
					   *node);
	++node;
	clk_seq_node = put_octet_hex_lower(clk_seq_node,
					   *node);
	++node;
	clk_seq_node = put_octet_hex_lower(clk_seq_node,
					   *node);
	++node;
	clk_seq_node = put_octet_hex_lower(clk_seq_node,
					   *node);

	*clk_seq_node = '\0';
}

inline void
uuid_state_increment_clk_seq(char *restrict ptr)
{
	switch (*ptr) {
	case '0': *ptr = '1'; return;
	case '1': *ptr = '2'; return;
	case '2': *ptr = '3'; return;
	case '3': *ptr = '4'; return;
	case '4': *ptr = '5'; return;
	case '5': *ptr = '6'; return;
	case '6': *ptr = '7'; return;
	case '7': *ptr = '8'; return;
	case '8': *ptr = '9'; return;
	case '9': *ptr = 'a'; return;
	case 'a': *ptr = 'b'; return;
	case 'b': *ptr = 'c'; return;
	case 'c': *ptr = 'd'; return;
	case 'd': *ptr = 'e'; return;
	case 'e': *ptr = 'f'; return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10", 2); return;
	case '1': SET_STRING_WIDTH(ptr, "20", 2); return;
	case '2': SET_STRING_WIDTH(ptr, "30", 2); return;
	case '3': SET_STRING_WIDTH(ptr, "40", 2); return;
	case '4': SET_STRING_WIDTH(ptr, "50", 2); return;
	case '5': SET_STRING_WIDTH(ptr, "60", 2); return;
	case '6': SET_STRING_WIDTH(ptr, "70", 2); return;
	case '7': SET_STRING_WIDTH(ptr, "80", 2); return;
	case '8': SET_STRING_WIDTH(ptr, "90", 2); return;
	case '9': SET_STRING_WIDTH(ptr, "a0", 2); return;
	case 'a': SET_STRING_WIDTH(ptr, "b0", 2); return;
	case 'b': SET_STRING_WIDTH(ptr, "c0", 2); return;
	case 'c': SET_STRING_WIDTH(ptr, "d0", 2); return;
	case 'd': SET_STRING_WIDTH(ptr, "e0", 2); return;
	case 'e': SET_STRING_WIDTH(ptr, "f0", 2); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "100", 3); return;
	case '1': SET_STRING_WIDTH(ptr, "200", 3); return;
	case '2': SET_STRING_WIDTH(ptr, "300", 3); return;
	case '3': SET_STRING_WIDTH(ptr, "400", 3); return;
	case '4': SET_STRING_WIDTH(ptr, "500", 3); return;
	case '5': SET_STRING_WIDTH(ptr, "600", 3); return;
	case '6': SET_STRING_WIDTH(ptr, "700", 3); return;
	case '7': SET_STRING_WIDTH(ptr, "800", 3); return;
	case '8': SET_STRING_WIDTH(ptr, "900", 3); return;
	case '9': SET_STRING_WIDTH(ptr, "a00", 3); return;
	case 'a': SET_STRING_WIDTH(ptr, "b00", 3); return;
	case 'b': SET_STRING_WIDTH(ptr, "c00", 3); return;
	case 'c': SET_STRING_WIDTH(ptr, "d00", 3); return;
	case 'd': SET_STRING_WIDTH(ptr, "e00", 3); return;
	case 'e': SET_STRING_WIDTH(ptr, "f00", 3); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1000", 4); return;
	case '1': SET_STRING_WIDTH(ptr, "2000", 4); return;
	case '2': SET_STRING_WIDTH(ptr, "3000", 4); return;
	case '3': SET_STRING_WIDTH(ptr, "4000", 4); return;
	case '4': SET_STRING_WIDTH(ptr, "5000", 4); return;
	case '5': SET_STRING_WIDTH(ptr, "6000", 4); return;
	case '6': SET_STRING_WIDTH(ptr, "7000", 4); return;
	case '7': SET_STRING_WIDTH(ptr, "8000", 4); return;
	case '8': SET_STRING_WIDTH(ptr, "9000", 4); return;
	case '9': SET_STRING_WIDTH(ptr, "a000", 4); return;
	case 'a': SET_STRING_WIDTH(ptr, "b000", 4); return;
	case 'b': SET_STRING_WIDTH(ptr, "c000", 4); return;
	case 'c': SET_STRING_WIDTH(ptr, "d000", 4); return;
	case 'd': SET_STRING_WIDTH(ptr, "e000", 4); return;
	case 'e': SET_STRING_WIDTH(ptr, "f000", 4); return;
	default:  SET_STRING_WIDTH(ptr, "0000", 4);
	}
}

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
uuid_mac_address(uint8_t *const restrict mac_address,
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

inline char *
put_uuid_time(char *restrict ptr,
	      const uint64_t uuid_time)
{
	/* put time_low */
	ptr = put_octet_hex_lower(ptr,
				  (uint8_t) (uuid_time >> 24));

	ptr = put_octet_hex_lower(ptr,
				  (uint8_t) (uuid_time >> 16));

	ptr = put_octet_hex_lower(ptr,
				  (uint8_t) (uuid_time >>  8));

	ptr = put_octet_hex_lower(ptr,
				  (uint8_t) uuid_time);

	*ptr = '-';
	++ptr;

	/* put time_mid */
	ptr = put_octet_hex_lower(ptr,
				  (uint8_t) (uuid_time >> 40));

	ptr = put_octet_hex_lower(ptr,
				  (uint8_t) (uuid_time >> 32));


	*ptr = '-';
	++ptr;

	/* put time_hi_and_version */
	ptr = put_octet_hex_lower(ptr,
				  (uint8_t) ((UUID_VERSION << 4)
					     | ((uuid_time >> 56) & 0xF)));

	return put_octet_hex_lower(ptr,
				   (uint8_t) (uuid_time >> 48));
}

inline void
uuid_string_increment_time(char *restrict ptr)
{
	switch (*ptr) {
	case '0': *ptr = '1'; return;
	case '1': *ptr = '2'; return;
	case '2': *ptr = '3'; return;
	case '3': *ptr = '4'; return;
	case '4': *ptr = '5'; return;
	case '5': *ptr = '6'; return;
	case '6': *ptr = '7'; return;
	case '7': *ptr = '8'; return;
	case '8': *ptr = '9'; return;
	case '9': *ptr = 'a'; return;
	case 'a': *ptr = 'b'; return;
	case 'b': *ptr = 'c'; return;
	case 'c': *ptr = 'd'; return;
	case 'd': *ptr = 'e'; return;
	case 'e': *ptr = 'f'; return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10", 2); return;
	case '1': SET_STRING_WIDTH(ptr, "20", 2); return;
	case '2': SET_STRING_WIDTH(ptr, "30", 2); return;
	case '3': SET_STRING_WIDTH(ptr, "40", 2); return;
	case '4': SET_STRING_WIDTH(ptr, "50", 2); return;
	case '5': SET_STRING_WIDTH(ptr, "60", 2); return;
	case '6': SET_STRING_WIDTH(ptr, "70", 2); return;
	case '7': SET_STRING_WIDTH(ptr, "80", 2); return;
	case '8': SET_STRING_WIDTH(ptr, "90", 2); return;
	case '9': SET_STRING_WIDTH(ptr, "a0", 2); return;
	case 'a': SET_STRING_WIDTH(ptr, "b0", 2); return;
	case 'b': SET_STRING_WIDTH(ptr, "c0", 2); return;
	case 'c': SET_STRING_WIDTH(ptr, "d0", 2); return;
	case 'd': SET_STRING_WIDTH(ptr, "e0", 2); return;
	case 'e': SET_STRING_WIDTH(ptr, "f0", 2); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "100", 3); return;
	case '1': SET_STRING_WIDTH(ptr, "200", 3); return;
	case '2': SET_STRING_WIDTH(ptr, "300", 3); return;
	case '3': SET_STRING_WIDTH(ptr, "400", 3); return;
	case '4': SET_STRING_WIDTH(ptr, "500", 3); return;
	case '5': SET_STRING_WIDTH(ptr, "600", 3); return;
	case '6': SET_STRING_WIDTH(ptr, "700", 3); return;
	case '7': SET_STRING_WIDTH(ptr, "800", 3); return;
	case '8': SET_STRING_WIDTH(ptr, "900", 3); return;
	case '9': SET_STRING_WIDTH(ptr, "a00", 3); return;
	case 'a': SET_STRING_WIDTH(ptr, "b00", 3); return;
	case 'b': SET_STRING_WIDTH(ptr, "c00", 3); return;
	case 'c': SET_STRING_WIDTH(ptr, "d00", 3); return;
	case 'd': SET_STRING_WIDTH(ptr, "e00", 3); return;
	case 'e': SET_STRING_WIDTH(ptr, "f00", 3); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1000", 4); return;
	case '1': SET_STRING_WIDTH(ptr, "2000", 4); return;
	case '2': SET_STRING_WIDTH(ptr, "3000", 4); return;
	case '3': SET_STRING_WIDTH(ptr, "4000", 4); return;
	case '4': SET_STRING_WIDTH(ptr, "5000", 4); return;
	case '5': SET_STRING_WIDTH(ptr, "6000", 4); return;
	case '6': SET_STRING_WIDTH(ptr, "7000", 4); return;
	case '7': SET_STRING_WIDTH(ptr, "8000", 4); return;
	case '8': SET_STRING_WIDTH(ptr, "9000", 4); return;
	case '9': SET_STRING_WIDTH(ptr, "a000", 4); return;
	case 'a': SET_STRING_WIDTH(ptr, "b000", 4); return;
	case 'b': SET_STRING_WIDTH(ptr, "c000", 4); return;
	case 'c': SET_STRING_WIDTH(ptr, "d000", 4); return;
	case 'd': SET_STRING_WIDTH(ptr, "e000", 4); return;
	case 'e': SET_STRING_WIDTH(ptr, "f000", 4); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10000", 5); return;
	case '1': SET_STRING_WIDTH(ptr, "20000", 5); return;
	case '2': SET_STRING_WIDTH(ptr, "30000", 5); return;
	case '3': SET_STRING_WIDTH(ptr, "40000", 5); return;
	case '4': SET_STRING_WIDTH(ptr, "50000", 5); return;
	case '5': SET_STRING_WIDTH(ptr, "60000", 5); return;
	case '6': SET_STRING_WIDTH(ptr, "70000", 5); return;
	case '7': SET_STRING_WIDTH(ptr, "80000", 5); return;
	case '8': SET_STRING_WIDTH(ptr, "90000", 5); return;
	case '9': SET_STRING_WIDTH(ptr, "a0000", 5); return;
	case 'a': SET_STRING_WIDTH(ptr, "b0000", 5); return;
	case 'b': SET_STRING_WIDTH(ptr, "c0000", 5); return;
	case 'c': SET_STRING_WIDTH(ptr, "d0000", 5); return;
	case 'd': SET_STRING_WIDTH(ptr, "e0000", 5); return;
	case 'e': SET_STRING_WIDTH(ptr, "f0000", 5); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "100000", 6); return;
	case '1': SET_STRING_WIDTH(ptr, "200000", 6); return;
	case '2': SET_STRING_WIDTH(ptr, "300000", 6); return;
	case '3': SET_STRING_WIDTH(ptr, "400000", 6); return;
	case '4': SET_STRING_WIDTH(ptr, "500000", 6); return;
	case '5': SET_STRING_WIDTH(ptr, "600000", 6); return;
	case '6': SET_STRING_WIDTH(ptr, "700000", 6); return;
	case '7': SET_STRING_WIDTH(ptr, "800000", 6); return;
	case '8': SET_STRING_WIDTH(ptr, "900000", 6); return;
	case '9': SET_STRING_WIDTH(ptr, "a00000", 6); return;
	case 'a': SET_STRING_WIDTH(ptr, "b00000", 6); return;
	case 'b': SET_STRING_WIDTH(ptr, "c00000", 6); return;
	case 'c': SET_STRING_WIDTH(ptr, "d00000", 6); return;
	case 'd': SET_STRING_WIDTH(ptr, "e00000", 6); return;
	case 'e': SET_STRING_WIDTH(ptr, "f00000", 6); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1000000", 7); return;
	case '1': SET_STRING_WIDTH(ptr, "2000000", 7); return;
	case '2': SET_STRING_WIDTH(ptr, "3000000", 7); return;
	case '3': SET_STRING_WIDTH(ptr, "4000000", 7); return;
	case '4': SET_STRING_WIDTH(ptr, "5000000", 7); return;
	case '5': SET_STRING_WIDTH(ptr, "6000000", 7); return;
	case '6': SET_STRING_WIDTH(ptr, "7000000", 7); return;
	case '7': SET_STRING_WIDTH(ptr, "8000000", 7); return;
	case '8': SET_STRING_WIDTH(ptr, "9000000", 7); return;
	case '9': SET_STRING_WIDTH(ptr, "a000000", 7); return;
	case 'a': SET_STRING_WIDTH(ptr, "b000000", 7); return;
	case 'b': SET_STRING_WIDTH(ptr, "c000000", 7); return;
	case 'c': SET_STRING_WIDTH(ptr, "d000000", 7); return;
	case 'd': SET_STRING_WIDTH(ptr, "e000000", 7); return;
	case 'e': SET_STRING_WIDTH(ptr, "f000000", 7); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10000000", 8); return;
	case '1': SET_STRING_WIDTH(ptr, "20000000", 8); return;
	case '2': SET_STRING_WIDTH(ptr, "30000000", 8); return;
	case '3': SET_STRING_WIDTH(ptr, "40000000", 8); return;
	case '4': SET_STRING_WIDTH(ptr, "50000000", 8); return;
	case '5': SET_STRING_WIDTH(ptr, "60000000", 8); return;
	case '6': SET_STRING_WIDTH(ptr, "70000000", 8); return;
	case '7': SET_STRING_WIDTH(ptr, "80000000", 8); return;
	case '8': SET_STRING_WIDTH(ptr, "90000000", 8); return;
	case '9': SET_STRING_WIDTH(ptr, "a0000000", 8); return;
	case 'a': SET_STRING_WIDTH(ptr, "b0000000", 8); return;
	case 'b': SET_STRING_WIDTH(ptr, "c0000000", 8); return;
	case 'c': SET_STRING_WIDTH(ptr, "d0000000", 8); return;
	case 'd': SET_STRING_WIDTH(ptr, "e0000000", 8); return;
	case 'e': SET_STRING_WIDTH(ptr, "f0000000", 8); return;
	default:  SET_STRING_WIDTH(ptr, "00000000", 8);
	}

	/* carry overflow to time_mid */
	ptr += 12l;

	switch (*ptr) {
	case '0': *ptr = '1'; return;
	case '1': *ptr = '2'; return;
	case '2': *ptr = '3'; return;
	case '3': *ptr = '4'; return;
	case '4': *ptr = '5'; return;
	case '5': *ptr = '6'; return;
	case '6': *ptr = '7'; return;
	case '7': *ptr = '8'; return;
	case '8': *ptr = '9'; return;
	case '9': *ptr = 'a'; return;
	case 'a': *ptr = 'b'; return;
	case 'b': *ptr = 'c'; return;
	case 'c': *ptr = 'd'; return;
	case 'd': *ptr = 'e'; return;
	case 'e': *ptr = 'f'; return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10", 2); return;
	case '1': SET_STRING_WIDTH(ptr, "20", 2); return;
	case '2': SET_STRING_WIDTH(ptr, "30", 2); return;
	case '3': SET_STRING_WIDTH(ptr, "40", 2); return;
	case '4': SET_STRING_WIDTH(ptr, "50", 2); return;
	case '5': SET_STRING_WIDTH(ptr, "60", 2); return;
	case '6': SET_STRING_WIDTH(ptr, "70", 2); return;
	case '7': SET_STRING_WIDTH(ptr, "80", 2); return;
	case '8': SET_STRING_WIDTH(ptr, "90", 2); return;
	case '9': SET_STRING_WIDTH(ptr, "a0", 2); return;
	case 'a': SET_STRING_WIDTH(ptr, "b0", 2); return;
	case 'b': SET_STRING_WIDTH(ptr, "c0", 2); return;
	case 'c': SET_STRING_WIDTH(ptr, "d0", 2); return;
	case 'd': SET_STRING_WIDTH(ptr, "e0", 2); return;
	case 'e': SET_STRING_WIDTH(ptr, "f0", 2); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "100", 3); return;
	case '1': SET_STRING_WIDTH(ptr, "200", 3); return;
	case '2': SET_STRING_WIDTH(ptr, "300", 3); return;
	case '3': SET_STRING_WIDTH(ptr, "400", 3); return;
	case '4': SET_STRING_WIDTH(ptr, "500", 3); return;
	case '5': SET_STRING_WIDTH(ptr, "600", 3); return;
	case '6': SET_STRING_WIDTH(ptr, "700", 3); return;
	case '7': SET_STRING_WIDTH(ptr, "800", 3); return;
	case '8': SET_STRING_WIDTH(ptr, "900", 3); return;
	case '9': SET_STRING_WIDTH(ptr, "a00", 3); return;
	case 'a': SET_STRING_WIDTH(ptr, "b00", 3); return;
	case 'b': SET_STRING_WIDTH(ptr, "c00", 3); return;
	case 'c': SET_STRING_WIDTH(ptr, "d00", 3); return;
	case 'd': SET_STRING_WIDTH(ptr, "e00", 3); return;
	case 'e': SET_STRING_WIDTH(ptr, "f00", 3); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1000", 4); return;
	case '1': SET_STRING_WIDTH(ptr, "2000", 4); return;
	case '2': SET_STRING_WIDTH(ptr, "3000", 4); return;
	case '3': SET_STRING_WIDTH(ptr, "4000", 4); return;
	case '4': SET_STRING_WIDTH(ptr, "5000", 4); return;
	case '5': SET_STRING_WIDTH(ptr, "6000", 4); return;
	case '6': SET_STRING_WIDTH(ptr, "7000", 4); return;
	case '7': SET_STRING_WIDTH(ptr, "8000", 4); return;
	case '8': SET_STRING_WIDTH(ptr, "9000", 4); return;
	case '9': SET_STRING_WIDTH(ptr, "a000", 4); return;
	case 'a': SET_STRING_WIDTH(ptr, "b000", 4); return;
	case 'b': SET_STRING_WIDTH(ptr, "c000", 4); return;
	case 'c': SET_STRING_WIDTH(ptr, "d000", 4); return;
	case 'd': SET_STRING_WIDTH(ptr, "e000", 4); return;
	case 'e': SET_STRING_WIDTH(ptr, "f000", 4); return;
	default:  SET_STRING_WIDTH(ptr, "0000", 4);
	}

	/* carry overflow to time_high_and_version */
	ptr += 8l;

	switch (*ptr) {
	case '0': *ptr = '1'; return;
	case '1': *ptr = '2'; return;
	case '2': *ptr = '3'; return;
	case '3': *ptr = '4'; return;
	case '4': *ptr = '5'; return;
	case '5': *ptr = '6'; return;
	case '6': *ptr = '7'; return;
	case '7': *ptr = '8'; return;
	case '8': *ptr = '9'; return;
	case '9': *ptr = 'a'; return;
	case 'a': *ptr = 'b'; return;
	case 'b': *ptr = 'c'; return;
	case 'c': *ptr = 'd'; return;
	case 'd': *ptr = 'e'; return;
	case 'e': *ptr = 'f'; return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10", 2); return;
	case '1': SET_STRING_WIDTH(ptr, "20", 2); return;
	case '2': SET_STRING_WIDTH(ptr, "30", 2); return;
	case '3': SET_STRING_WIDTH(ptr, "40", 2); return;
	case '4': SET_STRING_WIDTH(ptr, "50", 2); return;
	case '5': SET_STRING_WIDTH(ptr, "60", 2); return;
	case '6': SET_STRING_WIDTH(ptr, "70", 2); return;
	case '7': SET_STRING_WIDTH(ptr, "80", 2); return;
	case '8': SET_STRING_WIDTH(ptr, "90", 2); return;
	case '9': SET_STRING_WIDTH(ptr, "a0", 2); return;
	case 'a': SET_STRING_WIDTH(ptr, "b0", 2); return;
	case 'b': SET_STRING_WIDTH(ptr, "c0", 2); return;
	case 'c': SET_STRING_WIDTH(ptr, "d0", 2); return;
	case 'd': SET_STRING_WIDTH(ptr, "e0", 2); return;
	case 'e': SET_STRING_WIDTH(ptr, "f0", 2); return;
	default: --ptr;
	}

	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "100", 3); return;
	case '1': SET_STRING_WIDTH(ptr, "200", 3); return;
	case '2': SET_STRING_WIDTH(ptr, "300", 3); return;
	case '3': SET_STRING_WIDTH(ptr, "400", 3); return;
	case '4': SET_STRING_WIDTH(ptr, "500", 3); return;
	case '5': SET_STRING_WIDTH(ptr, "600", 3); return;
	case '6': SET_STRING_WIDTH(ptr, "700", 3); return;
	case '7': SET_STRING_WIDTH(ptr, "800", 3); return;
	case '8': SET_STRING_WIDTH(ptr, "900", 3); return;
	case '9': SET_STRING_WIDTH(ptr, "a00", 3); return;
	case 'a': SET_STRING_WIDTH(ptr, "b00", 3); return;
	case 'b': SET_STRING_WIDTH(ptr, "c00", 3); return;
	case 'c': SET_STRING_WIDTH(ptr, "d00", 3); return;
	case 'd': SET_STRING_WIDTH(ptr, "e00", 3); return;
	case 'e': SET_STRING_WIDTH(ptr, "f00", 3); return;
	default:  SET_STRING_WIDTH(ptr, "000", 3); /* leave version untouched */
	}
}

inline void
set_uuid_clk_seq_node(char *restrict ptr,
		      const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&uuid_state.lock);

	mutex_lock_handle_cl(&uuid_state.lock,
			     fail_cl);

	SET_CLK_SEQ_NODE(ptr,
			 &uuid_state.clk_seq_node[0]);

	uuid_state_increment_clk_seq(uuid_state.clk_seq_last);

	mutex_unlock_handle_cl(&uuid_state.lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}

inline void
uuid_string_init(char *restrict ptr,
		 const struct HandlerClosure *const restrict fail_cl)
{
	ptr = put_uuid_time(ptr,
			    uuid_time_now(fail_cl));

	set_uuid_clk_seq_node(ptr,
			      fail_cl);
}


/* constructors, destructors
 * ────────────────────────────────────────────────────────────────────────── */
inline bool
uuid_utils_constructor(const char *restrict *const restrict failure)
{
	uint8_t node[MAC_ADDRESS_LENGTH];

	const bool success = random_constructor(failure)
			  && uuid_mac_address(&node[0],
					      failure);

	if (success) {
		mutex_init(&uuid_state.lock);

		uuid_state_init_clk_seq_node(&uuid_state.clk_seq_node[0],
					     &node[0]);

		uuid_state.clk_seq_last = &uuid_state.clk_seq_node[0]
					+ CLK_SEQ_LAST_OFFSET;
	}

	return success;
}


#endif /* ifndef MYSQL_SEED_UUID_UUID_UTILS_H_ */
