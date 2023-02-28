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
}

TEST(list, push)
{
	struct list_t *list = list_create();

	ASSERT_EQ(list_size(list), 0);

	char s1[] = "abs";

	list_push_back(list, s1);

	ASSERT_EQ(list_size(list), 1);
	ASSERT_EQ(strcmp(list_end(list), "abs"), 0);
	ASSERT_EQ(strcmp(list_begin(list), "abs"), 0);

	char s2[] = "12345";

	list_push_back(list, s2);
	ASSERT_EQ(list_size(list), 2);
	ASSERT_EQ(strcmp(list_end(list), "12345"), 0);
	ASSERT_EQ(strcmp(list_begin(list), "abs"), 0);
}
