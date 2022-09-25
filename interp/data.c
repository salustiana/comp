#include "data.h"
#include "message.h"
#include "token.h"

char *strdup(const char *s)
{
	size_t size = sizeof(char) * (strlen(s) + 1);
	char *t = malloc(size);
	if (t)
		memcpy(t, s, size);
	return t;
}

static struct ventry *vartab[HASHSIZE];
static struct fentry *functab[HASHSIZE];

/* hash function */
uint32_t hash(const char *s)
{
	uint32_t hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/*
 * the install and lookup functions use only the
 * first two members of the ventry and fentry structs
 * (next and name) so as to be reusable for any "entry"
 * type struct.
 * this is accomplished by casting to (struct entry)
 * when using these functions, to only acknowledge the
 * next and name members of the struct.
 * recasting to (struct ventry/fentry) is then performed
 * by the savevar/savefunc and getvar/getfunc functions.
 */
struct entry *lookup(const char *n, struct entry *table[])
{
	struct entry *ep;
	for (ep = table[hash(n)]; ep != NULL; ep = ep->next)
		if (strcmp(n, ep->name) == 0)
			return ep;
	return NULL;
}

/*
 * install a new entry of the given size in table
 * return its address
 */
struct entry *install(const char *n, size_t size, struct entry *table[])
{
	struct entry *ep = lookup(n, table);
	if (ep)
		return ep;
	if ((ep = malloc(size)) == NULL || (ep->name = strdup(n)) == NULL) {
		char e[TOKENLEN];
		sprintf(e, "could not allocate memory for %s", n);
		panic(e);
	}
	uint32_t hashval = hash(n);
	ep->next = table[hashval];
	table[hashval] = ep;
	return ep;
}

void savevar(const char *n, uint32_t val)
{
	struct ventry *ep = (struct ventry *) install(n,
			sizeof(struct ventry), (struct entry **) vartab);
	ep->val = val;
}

void savefunc(const char *n, uint32_t (*func)())
{
	struct fentry *ep = (struct fentry *) install(n,
			sizeof(struct fentry), (struct entry **) functab);
	ep->func = func;
}

uint32_t *getvar(const char *n)
{
	struct ventry *ep = ((struct ventry *) lookup(n, (struct entry **) vartab));
	if (ep == NULL) {
		char e[TOKENLEN];
		sprintf(e, "undeclared variable: %s", n);
		panic(e);
	}

	return &ep->val;
}

uint32_t (*getfunc(const char *n))()
{
	struct fentry *ep = ((struct fentry *) lookup(n, (struct entry **) functab));
	if (ep == NULL) {
		char e[TOKENLEN];
		sprintf(e, "undeclared function: %s", n);
		panic(e);
	}

	return ep->func;
}
