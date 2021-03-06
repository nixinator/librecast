#include "test.h"
#include <librecast/net.h>
#include "../src/log.h"

int main()
{
	test_name("lc_msg_set() / lc_msg_get()");
	LOG_LEVEL = 127;
	char data[] = "life, the universe and everything";
	size_t len = strlen(data);
	int op = LC_OP_PING;
	int *getint;
	void *ptr;

	lc_message_t msg;
	lc_msg_init(&msg);

	test_assert(lc_msg_set(NULL, LC_ATTR_DATA, NULL) == LC_ERROR_INVALID_PARAMS,
			"lc_msg_set(): msg == NULL");
	test_assert(lc_msg_set(&msg, 9999, NULL) == LC_ERROR_MSG_ATTR_UNKNOWN,
			"lc_msg_set(): invalid attr");
	test_assert(lc_msg_set(&msg, LC_ATTR_LEN, &len) == 0,
			"lc_msg_set(): set LC_ATTR_LEN");

	test_assert(len == strlen(data), "len unmodified by lc_msg_set()");

	test_assert(lc_msg_set(&msg, LC_ATTR_OPCODE, &op) == 0,
			"lc_msg_set(): set opcode");
	test_assert(lc_msg_set(&msg, LC_ATTR_DATA, NULL) == 0,
			"lc_msg_set(): set NULL data");
	test_assert(lc_msg_set(&msg, LC_ATTR_DATA, &data) == 0,
			"lc_msg_set(): set data");

	test_assert(lc_msg_get(NULL, LC_ATTR_DATA, &ptr) == LC_ERROR_INVALID_PARAMS,
			"lc_msg_get(): msg == NULL");
	test_assert(lc_msg_get(&msg, 9999, &ptr) == LC_ERROR_MSG_ATTR_UNKNOWN,
			"lc_msg_get(): invalid attr");
	test_assert(lc_msg_get(&msg, LC_ATTR_DATA, NULL) == LC_ERROR_INVALID_PARAMS,
			"lc_msg_get(): NULL value ptr");
	test_assert(lc_msg_get(&msg, LC_ATTR_DATA, &ptr) == 0,
			"lc_msg_get(): get data value");
	test_expect(data, (char *)ptr);

	test_assert(len == strlen(data), "len unmodified by lc_msg_set() wilma found a bug");

	test_assert(lc_msg_get(&msg, LC_ATTR_OPCODE, (void **)&getint) == 0,
			"lc_msg_get(): get opcode value");
	logmsg(LOG_DEBUG, "getint (opcode) == %i", *getint);

	test_assert(len == strlen(data), "len unmodified by lc_msg_set() barney found a bug");

	test_assert(op == *getint, "lc_msg_get(): check opcode");


	test_assert(lc_msg_get(&msg, LC_ATTR_LEN, (void **)&getint) == 0,
			"lc_msg_get(): get length");
	logmsg(LOG_DEBUG, "getint (len) == %i", *getint);
	test_assert(len == strlen(data), "len unmodified by lc_msg_set() fred found a bug");
	test_log("%i == %i", len, *getint);
	test_assert(len == *getint, "lc_msg_get(): check length");


	return fails;
}
