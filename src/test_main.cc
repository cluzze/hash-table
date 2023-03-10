#include "list.h"
#include "hash_table.h"

#include "gtest/gtest.h"
#include <string.h>

int main()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}

TEST(list, create)
{
	struct list_t *list = list_create();

	ASSERT_EQ(list == NULL, 0);

	list_free(list);
}

TEST(list, push)
{
	struct list_t *list = list_create();

	ASSERT_EQ(list_size(list), 0);

	list_push_back(list, "asdq", 1);

	ASSERT_EQ(list_size(list), 1);
	ASSERT_EQ(list_node_get_value(list_end(list)) == 1, 1);
	ASSERT_EQ(list_node_get_value(list_begin(list)) == 1, 1);

	list_push_back(list, "87654321", 2);
	ASSERT_EQ(list_size(list), 2);
	ASSERT_EQ(list_node_get_value(list_end(list)) == 2, 1);
	ASSERT_EQ(list_node_get_value(list_begin(list)) == 1, 1);

	list_free(list);
}


TEST(hash_table, create)
{
	struct htab_t *htab = htab_create(5);
	ASSERT_EQ(htab == NULL, 0);

	htab_free(htab);
}

TEST(hash_table, insert)
{
	struct htab_t *htab = htab_create(20);

	char s[5][6] = {"sdsad", "12345", "asdfg", "qwert", "09876"};

	for (int i = 0; i < 5; i++)
	{
		htab_insert(htab, s[i], i);
	}

	ASSERT_EQ(htab_size(htab) == 5, 1);

	char ss[6] = "sdsad";

	htab_insert(htab, ss, 17);

	ASSERT_EQ(htab_size(htab) == 5, 1);
	htab_free(htab);
}


TEST(hash_table, find)
{
	int i = 0;
	struct htab_t *htab = htab_create(5);
	struct list_node_t *node = NULL;

	char s[5][6] = {"sdsad", "12345", "asdfg", "qwert", "09876"};

	for (int i = 0; i < 5; i++)
	{
		htab_insert(htab, s[i], i);
	}

	for (i = 0; i < 5; i++)
	{
		node = htab_find(htab, s[i]);
		ASSERT_EQ(node != NULL, 1);
	}

	htab_free(htab);
}

TEST(hash_table, erase)
{
	struct htab_t *htab = htab_create(20);
	struct list_node_t *node = NULL;

	char s[5][6] = {"sdsad", "12345", "asdfg", "qwert", "09876"};
	
	for (int i = 0; i < 5; i++)
	{
		htab_insert(htab, s[i], i);
	}

	htab_erase(htab, "sdsad");
	htab_erase(htab, "12345");

	node = htab_find(htab, "sdsad");
	ASSERT_EQ(node == NULL, 1);

	node = htab_find(htab, "12345");
	ASSERT_EQ(node == NULL, 1);

	htab_free(htab);
}

TEST(hash_table, rehash)
{
	int i = 0;
	struct htab_t *htab = htab_create(4);
	struct list_node_t *node = NULL;

	char s[5][6] = {"sdsad", "12345", "asdfg", "qwert", "09876"};
	
	for (i = 0; i < 5; i++)
	{
		htab_insert(htab, s[i], i);
	}

	htab_rehash(htab, 20);

	for (i = 0; i < 5; i++)
	{
		node = htab_find(htab, s[i]);
		ASSERT_EQ(node != NULL, 1);
	}

	htab_free(htab);
}