#include "message.h"

/* report error */
void error(const char *s)
{
	printf("Error: %s\n", s);
}

/* report error and halt */
void panic(const char *s)
{
	error(s);
	exit(1);
}

/* report what was expected and halt */
void expected(const char *s)
{
	char e[1024];
	sprintf(e, "%s Expected", s);
	panic(e);
}
