#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>

struct list_node_t;

struct list_t;

struct list_t *list_create();

int list_size(const struct list_t *list);

struct list_node_t *list_begin(const struct list_t *list);

struct list_node_t *list_end(const struct list_t *list);

int list_node_get_data(const struct list_node_t *list_node);

int list_empty(const struct list_t *list);

void list_push_back(struct list_t *list, int data);

void list_destroy(struct list_t *list);

void list_print(const struct list_t *list, FILE *fd);

#endif