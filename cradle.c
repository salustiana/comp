#include "message.h"
#include "cradle.h"
#include "data.h"
#include "token.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

enum {
	SECT_BSS,
	SECT_TEXT,
};

char look;
int section = -1;
uint32_t line = 1;
uint32_t line_char;
char *file_name = "stdin";

/* plain output */
void emit(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

/* enter data section */
void bss_sect()
{
	if (section != SECT_BSS) {
		emit("\t.section .bss\n");
		section = SECT_BSS;
	}
}

/* enter text section */
void text_sect()
{
	if (section != SECT_TEXT) {
		emit("\t.section .text\n");
		section = SECT_TEXT;
	}
}

/* output an indented line in the text section */
void emit_text_ln(const char *fmt, ...)
{
	text_sect();
	putchar('\t');

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	putchar('\n');
}

/* produce an exit syscall */
void emit_exit(const char *fmt, ...)
{
	putchar('\t');

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	putchar('\n');

	text_sect();
	emit_text_ln("movl $1, "REG_A);
	emit_text_ln("int $0x80");
}

/* create new static var in bss section */
void new_static(const char *varname)
{
	bss_sect();
	emit("\t.lcomm %s, 4\n", varname);
}

/* new char from input stream */
void next_char()
{
	// TODO: skipping whitespace in this function
	// causes getnum() to accept broken numbers: 12 2 = 122
	while ((look = getchar()) == ' ' || look == '\t')
		line_char++;
	if (look == '\n') {
		line++;
		line_char = 0;
	}
	else {
		line_char++;
	}
}

/* match specific input char */
void match(char c)
{
	if (look == c)
		next_char();
	else
		expected("%c", c);
}

/*
 * get an identifier
 * the returned string must be freed
 */
char *get_name()
{
	if (!isalpha(look))
		expected("name");

	char name[TOKENLEN];
	int i = 0;
	while (isalnum(look)) {
		name[i] = look;
		next_char();
		i++;
	}
	name[i] = '\0';

	return strdup(name);
}

/* get a number */
uint32_t get_num()
{
	if (!isdigit(look))
		expected("integer");

	char num[TOKENLEN];
	int i = 0;
	while (isdigit(look)) {
		num[i] = look;
		next_char();
		i++;
	}
	num[i] = '\0';
	// TODO: atoi returns smaller type than uint32_t
	return atoi(num);
}
