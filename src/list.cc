#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

struct list_node_t
{
	struct list_node_t *next;
	struct list_node_t *prev;
	const char *key;
	int value;
};

struct list_t
{
	struct list_node_t *begin;
	struct list_node_t *end;
	int size;
};

struct list_t *list_create()
{
	struct list_t *list = NULL;

	list = (struct list_t*)calloc(1, sizeof(struct list_t));

	return list;
}

void list_free(struct list_t *list)
{
	struct list_node_t *node = NULL;

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

struct list_node_t *list_push_back(struct list_t *list, const char *key, int value)
{
	struct list_node_t *new_node = NULL;

	new_node = (struct list_node_t*)calloc(1, sizeof(struct list_node_t));

	new_node->key = key;
	new_node->value = value;

	if (list_empty(list))
	{
		list->begin = new_node;
		list->end = new_node;
		list->size++;

		return list->end;
	}

	list->end->next = new_node;
	new_node->prev = list->end;
	list->end = new_node;
	list->size++;

	return list->end;
}

void list_erase(struct list_t *list, struct list_node_t *node)
{
	if (list->size == 1)
	{
		free(node);
		list->begin = NULL;
		list->end = NULL;
		list->size--;
		return;
	}

	if (node == list->begin)
	{
		list->begin = node->next;
		node->next->prev = NULL;
		list->size--;
		free(node);
		return;
	}

	if (node == list->end)
	{
		list->end = node->prev;
		node->prev->next = NULL;
		list->size--;
		free(node);
		return;
	}

	node->next->prev = node->prev;
	node->prev->next = node->next;
	list->size--;
	free(node);
	return;
}

void list_print(const struct list_t *list, FILE *fd)
{
	int i = 0;
	struct list_node_t *node = list->begin;
	
	for (i = 0; i < list->size; i++, node = node->next)
	{
		fprintf(fd, "node %d: <key - %s, value - %d>\n", i, node->key, node->value);
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

int list_node_get_value(struct list_node_t *list_node)
{
	if (!list_node)
		return 0;
	return list_node->value;
}

int *list_node_get_value_ptr(struct list_node_t *list_node)
{
	if (!list_node)
		return NULL;
	return &list_node->value;
}

const char *list_node_get_key(struct list_node_t *list_node)
{
	if (!list_node)
		return NULL;
	return list_node->key;
}

const char **list_node_get_key_ptr(struct list_node_t *list_node)
{
	if (!list_node)
		return NULL;
	return &list_node->key;
}

void list_for_each(struct list_t *list, struct htab_t *htab)
{
	int i = 0;
	struct list_node_t *list_node = list->begin;

	for (i = 0; i < list->size; i++, list_node = list_node->next)
	{
		htab_insert_list_node(htab, list_node);
	}

	return;
}







