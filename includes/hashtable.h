#include <stddef.h>
#include <stdint.h>

#define HASHSIZE	101

void *malloc(unsigned long);
int strcmp(const char *, const char *);
char *strdup(const char *);


struct entry {
	struct entry	*next;
	char		*name;
	void		*content;
};

struct entry *lookup(char *n);

// install new entry, overwriting if exists
// return NULL if no space is left
struct entry *install(char *n, void *content);
