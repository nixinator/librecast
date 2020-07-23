#include "test.h"

int main()
{
	result("lc_channel_new() / lc_channel_free()");

	lc_ctx_t *lctx;
	lc_channel_t *chan;

	lctx = lc_ctx_new();
	chan = lc_channel_new(lctx, "example.com");

	lc_channel_free(chan);
	lc_ctx_free(lctx);

	return 0;
}