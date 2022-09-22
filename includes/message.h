int printf(const char *, ...);
int sprintf(char *, const char *, ...);
void exit(int);

/* report error */
void error(const char *s);

/* report error and halt */
void panic(const char *s);

/* report what was expected and halt */
void expected(const char *s);
