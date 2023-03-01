#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include "list.h"

struct htab_node_t;

struct htab_t;

struct htab_t *htab_create(int size);

#endif