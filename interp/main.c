#include "cradle.h"

// TODO: remove
#include "data.h"
extern void expression();
int printf(const char *, ...);

uint32_t ret_88()
{
	return 88;
}

int main()
{
	savevar("x", 8);
	savefunc("f", ret_88);
	init();
}
