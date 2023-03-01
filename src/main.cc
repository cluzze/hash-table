#include "list.h"

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

	list_destroy(list);
}

TEST(list, push)
{
	struct list_t *list = list_create();

	ASSERT_EQ(list_size(list), 0);

	list_push_back(list, 1);

	ASSERT_EQ(list_size(list), 1);
	ASSERT_EQ(list_node_get_data(list_end(list)) == 1, 1);
	ASSERT_EQ(list_node_get_data(list_begin(list)) == 1, 1);

	list_push_back(list, 2);
	ASSERT_EQ(list_size(list), 2);
	ASSERT_EQ(list_node_get_data(list_end(list)) == 2, 1);
	ASSERT_EQ(list_node_get_data(list_begin(list)) == 1, 1);

	list_destroy(list);
}
