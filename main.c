#include "cradle.h"

// TODO: remove
#include "hashtable.h"

uint32_t ret_88()
{
	return 88;
}

int main()
{
	install("x", ret_88);
	init();
	expression();
	printf("%d\n", data[0]);
}
