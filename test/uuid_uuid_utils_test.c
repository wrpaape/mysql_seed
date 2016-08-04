#include "unity.h"
#include "uuid/uuid_utils.h"
#include <stdlib.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void
handle_uuid_mac_address_failure(void *arg,
				const char *restrict failure)
__attribute__((noreturn));

void handle_uuid_mac_address_failure(void *arg,
				     const char *restrict failure)
{
	puts(failure);
	TEST_FAIL();
	exit(1);
}

void test_uuid_mac_address(void)
{
	const struct HandlerClosure fail_cl = {
		.handle = &handle_uuid_mac_address_failure,
		.arg	= NULL
	};

	uint8_t mac_address[LENGTH_MAC_ADDRESS];

	uuid_mac_address(&mac_address[0],
			 &fail_cl);

	printf("%02X:%02X:%02X:%02X:%02X:%02X\n",
	       mac_address[0],
	       mac_address[1],
	       mac_address[2],
	       mac_address[3],
	       mac_address[4],
	       mac_address[5]);
}
