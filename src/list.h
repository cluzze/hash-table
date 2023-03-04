#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include "hash_table.h"

struct list_node_t;

struct list_t;

struct list_t *list_create();

int list_size(const struct list_t *list);

struct list_node_t *list_begin(const struct list_t *list);

struct list_node_t *list_end(const struct list_t *list);

int list_empty(const struct list_t *list);

struct list_node_t *list_push_back(struct list_t *list, const char *key, int vaue);

void list_erase(struct list_t *list, struct list_node_t *node);

void list_free(struct list_t *list);

void list_print(const struct list_t *list, FILE *fd);

int list_node_get_value(struct list_node_t *list_node);

int *list_node_get_value_ptr(struct list_node_t *list_node);

const char *list_node_get_key(struct list_node_t *list_node);

const char **list_node_get_key_ptr(struct list_node_t *list_node);

void list_for_each(struct list_t *list, struct htab_t *htab);

#endif