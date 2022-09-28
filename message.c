#include "cradle.h"
#include "message.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

/* output an indented line */
void emitln(const char *fmt, ...)
{
	putchar('\t');

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	putchar('\n');
}

/* produce an exit syscall */
void emitexit(const char *fmt, ...)
{
	putchar('\t');

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	putchar('\n');

	emitln("movl $1, "REG_A);
	emitln("int $0x80");
}

/* report error */
void error(const char *fmt, ...)
{
	fprintf(stderr, "error: ");

	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fprintf(stderr, "\n");
}

/* report error and halt */
void panic(const char *fmt, ...)
{
	fprintf(stderr, "error: ");

	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fprintf(stderr, "\n");
	exit(1);
}

/* report what was expected and halt */
void expected(const char *fmt, ...)
{
	fprintf(stderr, "error: expected ");

	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fprintf(stderr, "\n");
	exit(1);
}
