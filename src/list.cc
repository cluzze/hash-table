#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

struct list_node_t
{
	struct list_node_t *next;
	struct list_node_t *prev;
	int data;
};

struct list_t
{
	struct list_node_t *begin;
	struct list_node_t *end;
	unsigned int size;
};

struct list_t *list_create()
{
	struct list_t *list;

	list = (struct list_t*)calloc(1, sizeof(struct list_t));

	return list;
}

void list_destroy(struct list_t *list)
{
	struct list_node_t *node;

	while (list->begin != NULL)
	{
		node = list->begin->next;
		free(list->begin);
		list->begin = node;
	}

	free(list);

	return;
}

int list_size(const struct list_t *list)
{
	return list->size;
}

int list_empty(const struct list_t *list)
{
	return list->size == 0;
}

void list_push_back(struct list_t *list, int data)
{
	struct list_node_t *new_node;

	new_node = (struct list_node_t*)calloc(1, sizeof(struct list_node_t));

	new_node->data = data;

	if (list_empty(list))
	{
		list->begin = new_node;
		list->end = new_node;
		list->size++;

		return;
	}

	list->end->next = new_node;
	new_node->prev = list->end;
	list->end = new_node;
	list->size++;

	return;
}

void list_print(const struct list_t *list, FILE *fd)
{
	unsigned int i;
	struct list_node_t *node = list->begin;
	
	for (i = 0; i < list->size; i++, node = node->next)
	{
		fprintf(fd, "node №%d: %d\n", i, node->data);
	}

	return;
}

struct list_node_t *list_begin(const struct list_t *list)
{
	return list->begin;
}

struct list_node_t *list_end(const struct list_t *list)
{
	return list->end;
}

int list_node_get_data(const struct list_node_t *list_node)
{
	return list_node->data;
}