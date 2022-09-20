#include "cradle.h"
#include "hashtable.h"

#define STACKSIZ	3

char look;
uint32_t data[5];
uint32_t addr[5];

static uint32_t stack[STACKSIZ];
static uint32_t *sp = stack;
uint32_t pop()
{
	if (sp < stack)
		panic("Stack Underflow");
	return *--sp;
}
void push(uint32_t val)
{
	if (sp >= stack + STACKSIZ)
		panic("Stack Overflow");
	*sp++ = val;
}

// for debugging purposes
void printstack()
{
	for (int i = 0; i < STACKSIZ; i++)
		printf("%d\t", stack[i]);
	printf("\n");
}

// new char from input stream
void nextchar()
{
	look = getchar();
}

// report error
void error(const char *s)
{
	printf("Error: %s\n", s);
}

// report error and halt
void panic(const char *s)
{
	error(s);
	exit(1);
}

// report what was expected and halt
void expected(const char *s)
{
	char e[1024];
	sprintf(e, "%s Expected", s);
	panic(e);
}

// match specific input char
void match(char c)
{
	if (look == c)
		nextchar();
	else {
		char s[1024];
		sprintf(s, "'%c'", c);
		expected(s);
	}
}

// get an identifier
char getname()
{
	if (!isalpha(look))
		expected("Name");
	// TODO: is toupper needed?
	// char r = toupper(look);
	char r = look;
	nextchar();
	return r;
}

// get a number
char getnum()
{
	if (!isdigit(look))
		expected("Integer");
	char r = look;
	nextchar();
	return r;
}

// parse and execute a math factor
void factor()
// <factor> ::= <number> | (<expression>) | <variable>
{
	if (look == '(') {
		match('(');
		expression();
		match(')');
	}
	else if (isalpha(look)) {
		char varname[2] = {getname(), '\0'};
		struct entry *ep = lookup(varname);
		if (ep == NULL) {
			printf("var '%s' not found\n", varname);
			return;
		}
		// data[0] = ((uint32_t (*)()) lookup(varname)->content)();
		data[0] = *((int *) lookup(varname)->content);
	}
	else
		data[0] = getnum() - '0'; // EXEC
}

// recognize and execute a multiply
void multiply()
{
	match('*');
	factor();
	data[0] *= pop(); // EXEC
}

// recognize and execute a divide
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

// parse and execute a math term
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
			expected("Mulop");
		}
	}
}

// recognize and execute an add
void add()
{
	match('+');
	term();
	data[0] += pop(); // EXEC
}

// recognize and execute a subtract
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

// parse and execute a math expression
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
			expected("Addop");
		}
	}
}

// initialize
void init()
{
	nextchar();
}
