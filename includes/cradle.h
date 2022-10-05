#include <stdint.h>

#define REG_A	"%%eax"
#define REG_B	"%%ebx"
#define REG_C	"%%ecx"
#define REG_D	"%%edx"
#define REG_SP	"%%esp"

extern char look;
extern uint32_t line;
extern uint32_t line_char;
extern char *file_name;

/* output an indented line in the text section */
void emit_text_ln(const char *fmt, ...);

/* plain output */
void emit(const char *fmt, ...);

/* produce an exit syscall */
void emit_exit(const char *fmt, ...);

/* create new static var in bss section */
void new_static(const char *varname);

/* new char from input stream */
void next_char();

/* match specific input char */
void match(char c);

/*
 * get an identifier
 * the returned string must be freed
 */
char *get_name();

/* get a number */
int32_t get_num();
