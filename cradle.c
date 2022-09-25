#include "message.h"
#include "cradle.h"
#include "data.h"
#include "token.h"

#define STACKSIZ	3

char look;
uint32_t data[5];
uint32_t addr[5];

static uint32_t stack[STACKSIZ];
static uint32_t *sp = stack;
uint32_t pop()
{
	if (sp < stack)
		panic("stack underflow");
	return *--sp;
}
void push(uint32_t val)
{
	if (sp >= stack + STACKSIZ)
		panic("stack overflow");
	*sp++ = val;
}

/* for debugging purposes */
void printstack()
{
	for (int i = 0; i < STACKSIZ; i++)
		printf("%d\t", stack[i]);
	printf("\n");
}

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
	else {
		char s[TOKENLEN];
		if (c == '\n')
			sprintf(s, "'\\n'");
		else
			sprintf(s, "'%c'", c);
		expected(s);
	}
}

/* get an identifier */
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

void ident()
{
	char *name = getname();
	if (look == '(') {
		match('(');
		match(')');
		data[0] = getfunc(name)();
	}
	else {
		uint32_t *vp = getvar(name);
		if (vp == NULL) {
			printf("var '%s' not found\n", name);
			return;
		}
		data[0] = *vp;
	}
	free(name);
}

/* parse and execute a math factor */
void factor()
// <factor> ::= <number> | (<expression>) | <variable> | <function()>
{
	void expression();
	// (<expression>)
	if (look == '(') {
		match('(');
		expression();
		match(')');
	}
	// <variable> | <function()>
	else if (isalpha(look))
		ident();
	// <number>
	else
		data[0] = getnum(); // EXEC
}

/* recognize and execute a multiply */
void multiply()
{
	match('*');
	factor();
	data[0] *= pop(); // EXEC
}

/* recognize and execute a divide */
void divide()
{
	match('/');
	factor();
	data[1] = pop(); // EXEC
	data[0] = data[1]/data[0]; // EXEC
	/* optimization:
	data[0] = pop()/data[0]; // EXEC
	*/
}

/* parse and execute a math term */
void term()
// <term> ::= <factor> [<mulop> <factor>]*
{
	factor();
	while (look == '*' || look == '/') {
		push(data[0]);
		switch (look) {
		case '*':
			multiply();
			break;
		case '/':
			divide();
			break;
		default:
			expected("mulop");
		}
	}
}

/* recognize and execute an add */
void add()
{
	match('+');
	term();
	data[0] += pop(); // EXEC
}

/* recognize and execute a subtract */
void subtract()
{
	match('-');
	term();
	data[0] -= pop(); // EXEC
	data[0] = -data[0]; // EXEC
}

int isaddop(char c)
{
	return (c == '+' || c == '-');
}

/* parse and execute a math expression */
void expression()
// <expression> ::= [<addop>]* <term> [<addop> <term>]*
{
	// TODO: this handling of - and + at the beggining is temporary
	// add a 0 infront if first char in expression is - or +
	if (isaddop(look))
		data[0] = 0;
	else
		term();
	// term();
	
	while (isaddop(look)) {
		push(data[0]); // EXEC
		switch (look) {
		case '+':
			add();
			break;
		case '-':
			subtract();
			break;
		default:
			expected("addop");
		}
	}
}

/* parse and execute an assignment */
void assignment()
// <ident>=<expression>
{
	char *name = getname();
	match('=');
	expression();
	savevar(name, data[0]);
	free(name);
}

/* initialize */
void init()
{
	printf(">>> ");
	nextchar();
	while (look != EOF) {
		expression();
		printf("%d\n", data[0]);
		printf(">>> ");
		match('\n');
	}
	putchar('\n');
}
