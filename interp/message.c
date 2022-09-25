#include "message.h"
#include "token.h"

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
	char e[TOKENLEN];
	sprintf(e, "%s Expected", s);
	panic(e);
}
