#include "message.h"
#include "cradle.h"
#include "data.h"
#include "token.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

char look;

/* new char from input stream */
void nextchar()
{
	// TODO: skipping whitespace in this function
	// causes getnum() to accept broken numbers: 12 2 = 122
	while ((look = getchar()) == ' ' || look == '\t')
		;
}

/* match specific input char */
void match(char c)
{
	if (look == c)
		nextchar();
	else
		expected("%c", c);
}

/*
 * get an identifier
 * the returned string must be freed
 */
char *getname()
{
	if (!isalpha(look))
		expected("name");

	char name[TOKENLEN];
	int i = 0;
	while (isalnum(look)) {
		name[i] = look;
		nextchar();
		i++;
	}
	name[i] = '\0';

	return strdup(name);
}

/* get a number */
uint32_t getnum()
{
	if (!isdigit(look))
		expected("integer");

	char num[TOKENLEN];
	int i = 0;
	while (isdigit(look)) {
		num[i] = look;
		nextchar();
		i++;
	}
	num[i] = '\0';
	// TODO: atoi returns smaller type than uint32_t
	return atoi(num);
}
