/* output an indented line */
void emitln(const char *fmt, ...);

/* produce an exit syscall */
void emitexit(const char *fmt, ...);

/* report error */
void error(const char *fmt, ...);

/* report error and halt */
void panic(const char *fmt, ...);

/* report what was expected and halt */
void expected(const char *fmt, ...);
