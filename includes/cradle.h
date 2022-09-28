#include <stdint.h>

#define REG_A	"%%eax"
#define REG_B	"%%ebx"
#define REG_C	"%%ecx"
#define REG_D	"%%edx"
#define REG_SP	"%%esp"

extern char look;

/* new char from input stream */
void nextchar();

/* match specific input char */
void match(char c);

/*
 * get an identifier
 * the returned string must be freed
 */
char *getname();

/* get a number */
uint32_t getnum();
