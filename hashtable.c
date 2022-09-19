#include "hashtable.h"

static struct fentry *hashtab[HASHSIZE];

// hash function
uint32_t hash(char *s)
{
	uint32_t hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

struct fentry *lookup(char *n)
{
	struct fentry *ep;
	for (ep = hashtab[hash(n)]; ep != NULL; ep = ep->next)
		if (strcmp(n, ep->name) == 0)
			return ep;
	return NULL;
}

// install new func entry, overwriting if exists
// return NULL if no space is left
struct fentry *install(char *n, uint32_t (*func)())
{
	struct fentry *ep = lookup(n);
	if (ep) {
		ep->func = func;
		return ep;
	}
	if ((ep = malloc(sizeof(struct fentry))) == NULL
			|| (ep->name = strdup(n)) == NULL)
		return NULL;
	uint32_t hashval = hash(n);
	ep->next = hashtab[hashval];
	ep->func = func;
	hashtab[hashval] = ep;
	return ep;
}
