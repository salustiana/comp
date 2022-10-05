#include "cradle.h"
#include "message.h"
#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* parse and translate an identifier */
void ident()
{
	char *name = get_name();
	if (look == '(') {
		match('(');
		match(')');
		emit_text_ln("call %s", name);
	}
	else
		emit_text_ln("movl %s, "REG_A, name);
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
		emit_text_ln("movl $%d, "REG_A, get_num());
}

/* recognize and translate a multiply */
void multiply()
{
	match('*');
	factor();
	emit_text_ln("popl "REG_B);
	emit_text_ln("imull "REG_B", "REG_A);
}

/* recognize and translate a divide */
void divide()
{
	match('/');
	factor();
	emit_text_ln("movl "REG_A", "REG_B);
	emit_text_ln("popl "REG_A);
	emit_text_ln("idivl "REG_B);
}

/* parse and translate a math term */
void term()
// <term> ::= <factor> [<mulop> <factor>]*
{
	factor();
	while (look == '*' || look == '/') {
		emit_text_ln("pushl "REG_A);
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
	emit_text_ln("popl "REG_B);
	emit_text_ln("addl "REG_B", "REG_A);
}

/* recognize and translate a subtract */
void subtract()
{
	match('-');
	term();
	emit_text_ln("popl "REG_B);
	emit_text_ln("subl "REG_B", "REG_A);
	emit_text_ln("negl "REG_A);
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
		emit_text_ln("movl $0, "REG_A);
	else
		term();
	
	while (isaddop(look)) {
		emit_text_ln("pushl "REG_A);
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
void assignment()
// <ident>=<expression>
{
	char *name = get_name();
	match('=');
	expression();
	new_static(name);
	emit_text_ln("movl "REG_A", %s", name);
	free(name);
}

/* initialize */
void init()
{
	emit_text_ln(".globl _start");
	emit("_start:\n");
	next_char();
	while (look != EOF) {
		expression();
		match('\n');
	}
	emit_exit("movl "REG_A", "REG_B);
}
