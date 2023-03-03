#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include "list.h"

struct htab_node_t;

struct htab_t;

struct htab_t *htab_create(int size);

struct list_node_t *htab_find(const struct htab_t *htab, const char * key);

void htab_insert(struct htab_t *htab, const char *key, int new_value);

int htab_size(const struct htab_t *htab);

void htab_erase(struct htab_t *htab, const char *key);

void htab_resize(struct htab_t *htab, int size);

void htab_print(const struct htab_t *htab, FILE *fd);

void htab_free(struct htab_t *htab);

#endif