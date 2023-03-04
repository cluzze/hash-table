#include "hash_table.h"
#include "list.h"

#include <string.h>
#include <stdlib.h>

#define ALPH_CARDINALITY 31

struct htab_node_t
{
	struct htab_node_t *next;
	struct list_node_t *node;
};

struct htab_t
{
	struct htab_node_t **htab_nodes;
	struct list_t *list;
	int size;
};

struct htab_node_t *htab_find_node(const struct htab_t *htab, const char * key);

void free_nodes(struct htab_t *htab);

long long mod_mult(long long a, long long b, long long mod)
{
	long long sum = 0;

	while (b)
	{
		if (b & 1)
		{
			sum = (sum + a) % mod;
		}

		a = (a << 1) % mod;
		b =  b >> 1;
	}

	return sum;
}

int get_hash(const char *key, int mod)
{
	int len = 0, hash = 0, acc = 0;
	int i = 0;

	len = strlen(key);
	acc = 1;

	for (i = 0; i < len; i++)
	{
		hash += mod_mult(key[i], acc, mod);

		if (hash >= mod)
			hash %= mod;

		acc = mod_mult(acc, ALPH_CARDINALITY, mod);
	}

	return hash;
}

struct htab_t *htab_create(int size)
{
	struct htab_t *htab = (struct htab_t*)calloc(1, sizeof(struct htab_t));

	htab->size = size;
	htab->htab_nodes = (struct htab_node_t**)calloc(htab->size, sizeof(struct htab_node_t*));
	htab->list = list_create();

	return htab;
}

struct htab_node_t *htab_find_node(const struct htab_t *htab, const char * key, struct htab_node_t **erase)
{
	int hash = 0;
	struct htab_node_t *htab_node = NULL;

	hash = get_hash(key, htab->size);

	htab_node = htab->htab_nodes[hash];

	while (htab_node && strcmp(list_node_get_key(htab_node->node), key))
	{
		if (erase)
			*erase = htab_node;

		htab_node = htab_node->next;
	}

	return htab_node;
}

struct list_node_t *htab_find(const struct htab_t *htab, const char *key)
{
	struct htab_node_t *htab_node = NULL;

	htab_node = htab_find_node(htab, key, NULL);

	if (!htab_node)
		return NULL;

	return htab_node->node;
}

void htab_insert_list_node(struct htab_t *htab, struct list_node_t *list_node)
{
	int hash = 0;
	struct htab_node_t *htab_node = NULL;
	
	hash = get_hash(list_node_get_key(list_node), htab->size);
	htab_node = (struct htab_node_t*)calloc(1, sizeof(struct htab_node_t));
	htab_node->node = list_node;
	htab_node->next = htab->htab_nodes[hash];
	htab->htab_nodes[hash] = htab_node;
}

void htab_insert(struct htab_t *htab, const char *key, int value)
{
	struct list_node_t *list_node = NULL;

	list_node = htab_find(htab, key);

	if (list_node)
	{
		*list_node_get_value_ptr(list_node) = value;
		return;
	}

	list_node = list_push_back(htab->list, key, value);

	htab_insert_list_node(htab, list_node);

	return;
}

int htab_size(const struct htab_t *htab)
{
	return list_size(htab->list);
}

void htab_erase(struct htab_t *htab, const char *key)
{
	int hash = 0;
	struct htab_node_t *htab_node = NULL;
	struct htab_node_t *prev = NULL;

	htab_node = htab_find_node(htab, key, &prev);

	if (!htab_node)
		return;

	list_erase(htab->list, htab_node->node);

	if (!prev)
	{
		hash = get_hash(key, htab->size);
		htab->htab_nodes[hash] = htab_node->next;
		free(htab_node);
		return;
	}

	prev->next = htab_node->next;
	free(htab_node);
}

void htab_rehash(struct htab_t *htab, int size)
{
	free_nodes(htab);

	htab->size = size;

	htab->htab_nodes = (struct htab_node_t**)calloc(htab->size, sizeof(struct htab_node_t*));

	list_for_each(htab->list, htab);

	return;
}

void htab_print(const struct htab_t *htab, FILE *fd)
{
	int i = 0;
	struct htab_node_t *htab_node = NULL;
	
	fprintf(fd, "htab size: %d\n", htab_size(htab));
	fprintf(fd, "list:\n");
	list_print(htab->list, fd);
	fprintf(fd, "htab nodes:\n");
	for (i = 0; i < htab->size; i++)
	{
		fprintf(fd, "%d: ", i);
		htab_node = htab->htab_nodes[i];

		while (htab_node)
		{
			fprintf(fd, "<key = %s; value = %d>, ", list_node_get_key(htab_node->node),
													list_node_get_value(htab_node->node));
			htab_node = htab_node->next;
		}
		fprintf(fd, "\n");
	}
	fprintf(fd, "\n");
}

void free_nodes(struct htab_t *htab)
{
	int i = 0;
	struct htab_node_t *htab_node = NULL;
	struct htab_node_t *next = NULL;
	

	for (i = 0; i < htab->size; i++)
	{
		htab_node = htab->htab_nodes[i];

		while (htab_node)
		{
			next = htab_node->next;
			free(htab_node);
			htab_node = next;
		}
	}
	free(htab->htab_nodes);
}

void htab_free(struct htab_t *htab)
{
	free_nodes(htab);
	list_free(htab->list);
	free(htab);
}






