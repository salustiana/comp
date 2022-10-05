#include <stdint.h>

#define HASHSIZE	101

struct entry {
	struct entry	*next;
	char		*name;
};

struct ventry {
	struct ventry	*next;
	char		*name;
	int32_t	val;
};

struct fentry {
	struct fentry	*next;
	char		*name;
	int32_t	(*func)();
};

char *strdup(const char *s);

void save_var(const char *n, int32_t val);

void save_func(const char *n, int32_t (*func)());

int32_t *get_var(const char *n);

int32_t (*get_func(const char *n))();
