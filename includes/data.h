#include <stdint.h>

#define HASHSIZE	101

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

char *strdup(const char *s);

void save_var(const char *n, uint32_t val);

void save_func(const char *n, uint32_t (*func)());

uint32_t *get_var(const char *n);

uint32_t (*get_func(const char *n))();
