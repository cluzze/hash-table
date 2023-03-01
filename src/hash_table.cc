#include "hash_table.h"

#define ALPH_CARDINALITY 31

struct htab_node_data_t
{
	char *key;
	struct list_node_t *node;
}

struct htab_node_t
{
	struct htab_node_t *next;
	struct list_node_data_t data;
}

struct htab_t
{
	struct htab_node_t **htab_nodes;
	struct list_t *list;
	int size;
}

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

int get_hash(const char *key, int mod) // only lower case letters
{
	int len = 0, hash = 0, acc = 0;
	int i = 0;

	len = strlen(key);
	acc = 1;

	for (i = 0; i < len; i++)
	{
		hash += mod_mult(key[i] - 'a' + 1, acc, mod);

		if (hash >= mod)
			hash %= mod;

		acc = mod_mult(acc, ALPH_CARDINALITY, mod);
	}

	return hash;
}

struct htab_t *htab_create(int size)
{
	struct htab_t *htab = (struct htab_t*)calloc(1, sizeof(struct htab));

	htab->size = size;
	htab->htab_nodes = (struct htab_node_t**)calloc(htab->size, sizeof(struct htab_node_t*));
	htab->list = list_create();

	return htab;
}

struct list_node_t *htab_find(struct htab_t *htab, const char * key)
{
	
}






