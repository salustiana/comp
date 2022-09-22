#include <stddef.h>
#include <stdint.h>

#define HASHSIZE	101

void *malloc(unsigned long);
int strcmp(const char *, const char *);
char *strdup(const char *);

struct entry {
	struct entry	*next;
	char		*name;
};

struct ventry {
	struct ventry	*next;
	char		*name;
	uint32_t	val;
};

struct fentry {
	struct fentry	*next;
	char		*name;
	uint32_t	(*func)();
};

void savevar(const char *n, uint32_t val);

void savefunc(const char *n, uint32_t (*func)());

uint32_t *getvar(const char *n);

uint32_t (*getfunc(const char *n))();
