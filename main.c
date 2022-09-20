#include "cradle.h"

// TODO: remove
#include "hashtable.h"

uint32_t ret_88()
{
	return 88;
}
int a = 8;

int main()
{
	install("x", &a);
	init();
	expression();
	printf("%d\n", data[0]);
}
