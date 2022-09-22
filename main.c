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
	init();
	expression();
	printf("%d\n", data[0]);
}
