#include "hashtable.h"

static struct entry *hashtab[HASHSIZE];

// hash function
uint32_t hash(char *s)
{
	uint32_t hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

struct entry *lookup(char *n)
{
	struct entry *ep;
	for (ep = hashtab[hash(n)]; ep != NULL; ep = ep->next)
		if (strcmp(n, ep->name) == 0)
			return ep;
	return NULL;
}

// install new entry, overwriting if exists
// return NULL if no space is left
struct entry *install(char *n, void *content)
{
	struct entry *ep = lookup(n);
	if (ep) {
		ep->content = content;
		return ep;
	}
	if ((ep = malloc(sizeof(struct entry))) == NULL
			|| (ep->name = strdup(n)) == NULL)
		return NULL;
	uint32_t hashval = hash(n);
	ep->next = hashtab[hashval];
	ep->content = content;
	hashtab[hashval] = ep;
	return ep;
}
