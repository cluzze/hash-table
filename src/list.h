#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>

struct list_t;

struct list_t *list_create();

int list_size(const struct list_t *list);

char *list_begin(const struct list_t *list);

char *list_end(const struct list_t *list);

int list_empty(const struct list_t *list);

void list_push_back(struct list_t *list, const char* data);

void list_destroy(struct list_t *list);

void list_print(const struct list_t *list, FILE *fd);

#endif