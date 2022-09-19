#include <stddef.h>
#include <stdint.h>

#define HASHSIZE	101

void *malloc(unsigned long);
int strcmp(const char *, const char *);
char *strdup(const char *);


struct fentry {
	struct fentry	*next;
	char		*name;
	uint32_t	(*func)();
};

struct fentry *lookup(char *n);

// install new func entry, overwriting if exists
// return NULL if no space is left
struct fentry *install(char *n, uint32_t (*func)());
