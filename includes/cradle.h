#include <stdint.h>

extern char look;
extern uint32_t data[5];
extern uint32_t addr[5];

// declare needed lib functions
int getchar();
int toupper(int);
int printf(const char *, ...);
int sprintf(char *, const char *, ...);
void exit(int);

// new char from input stream
void nextchar();

// report error
void error(const char *s);

// report error and halt
void panic(const char *s);

// report what was expected and halt
void expected(const char *s);

// match specific input char
void match(char c);

// recognize an alpha character
int isalpha(int c);

// recognize a decimal digit
int isdigit(int c);

// get an identifier
char getname();

// get a number
char getnum();

// parse and translate a math expression
void expression();

// initialize
void init();
