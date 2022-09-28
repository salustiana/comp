#include "cradle.h"
#include "message.h"
#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* parse and translate an identifier */
void ident()
{
	char *name = getname();
	if (look == '(') {
		match('(');
		match(')');
		emitln("call %s", name);
	}
	else
		emitln("movl %s, "REG_A, name);
	free(name);
}

/* parse and translate a math factor */
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
		emitln("movl $%d, "REG_A, getnum());
}

/* recognize and translate a multiply */
void multiply()
{
	match('*');
	factor();
	emitln("popl "REG_B);
	emitln("imul "REG_B", "REG_A);
}

/* recognize and translate a divide */
void divide()
{
	match('/');
	factor();
	emitln("movl "REG_A", "REG_B);
	emitln("popl "REG_A);
	emitln("idivl "REG_B);
}

/* parse and translate a math term */
void term()
// <term> ::= <factor> [<mulop> <factor>]*
{
	factor();
	while (look == '*' || look == '/') {
		emitln("pushl "REG_A);
		switch (look) {
		case '*':
			multiply();
			break;
		case '/':
			divide();
			break;
		default:
			// this check is superfluous
			expected("mulop");
		}
	}
}

/* recognize and translate an add */
void add()
{
	match('+');
	term();
	emitln("popl "REG_B);
	emitln("addl "REG_B", "REG_A);
}

/* recognize and translate a subtract */
void subtract()
{
	match('-');
	term();
	emitln("popl "REG_B);
	emitln("subl "REG_B", "REG_A);
	emitln("negl "REG_A);
}

int isaddop(char c)
{
	return (c == '+' || c == '-');
}

/* parse and translate a math expression */
void expression()
// <expression> ::= [<addop>]* <term> [<addop> <term>]*
{
	// TODO: this handling of - and + at the beggining is temporary
	// add a 0 infront if first char in expression is - or +
	if (isaddop(look))
		emitln("movl $0, "REG_A);
	else
		term();
	
	while (isaddop(look)) {
		emitln("pushl "REG_A);
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

/* parse and translate an assignment */
/* TODO
void assignment()
// <ident>=<expression>
{
	char *name = getname();
	match('=');
	expression();
	savevar(name, data[0]);
	free(name);
}
*/

/* initialize */
void init()
{
	emitln(".section .text");
	emitln(".globl _start");
	printf("_start:\n");
	nextchar();
	while (look != EOF) {
		expression();
		match('\n');
	}
	emitexit("movl "REG_A", "REG_B);
}
