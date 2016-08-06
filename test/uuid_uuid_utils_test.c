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

void test_uuid_utils_start(void)
{
	puts(&uuid_state.clk_seq_node[0]);

	TEST_ASSERT_EQUAL_PTR(&uuid_state.clk_seq_node[CLK_SEQ_LAST_OFFSET],
			      uuid_state.clk_seq_last);
}

void test_uuid_mac_address(void)
{
	const char *restrict failure;

	uint8_t mac_address[MAC_ADDRESS_LENGTH];

	TEST_ASSERT_TRUE(uuid_mac_address(&mac_address[0],
					  &failure));

	printf("%02X:%02X:%02X:%02X:%02X:%02X\n",
	       mac_address[0],
	       mac_address[1],
	       mac_address[2],
	       mac_address[3],
	       mac_address[4],
	       mac_address[5]);
}
