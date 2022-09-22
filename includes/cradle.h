#include <stdint.h>

extern char look;
extern uint32_t data[5];
extern uint32_t addr[5];

// declare needed lib functions
int getchar();
int toupper(int);
int isalpha(int);
int isdigit(int);

// initialize program
void init();
