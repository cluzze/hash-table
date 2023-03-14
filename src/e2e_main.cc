#include "list.h"
#include "hash_table.h"

#include <stdlib.h>
#include <string.h>

#include "gtest/gtest.h"

int solve(int *exp, FILE *inp)
{
	int i;
	int res;
	int n, text_len, ans_len;
	char *text, *ans;
	char *word;
	struct htab_t *htab;
	struct list_node_t *list_node;

	fscanf(inp, "%d%d", &n, &text_len);

	text = (char*)calloc(text_len + 1, sizeof(char));

	fscanf(inp, "\n");
	for (i = 0; i < text_len; i++)
	{
		fscanf(inp, "%c", &text[i]);
	}

	fscanf(inp, "%d", &ans_len);

	ans = (char*)calloc(ans_len + 1, sizeof(char));

	fscanf(inp, "\n");
	for (i = 0; i < ans_len; i++)
	{
		fscanf(inp, "%c", &ans[i]);
	}

	htab = htab_create(10007);

	word = strtok(text, " ");
	while (word)
	{
		htab_insert(htab, word, 1);
		word = strtok(NULL, " ");
	}

	word = strtok(ans, " ");

	i = 0;

	while (word)
	{
		list_node = htab_find(htab, word);
		if (list_node)
			res = list_node_get_value(list_node);
		else
			res = 0;

		if (res != exp[i])
			return 0;

		word = strtok(NULL, " ");
		i++;
	}

	//htab_print(htab, stdout);
	free(text);
	free(ans);
	htab_free(htab);

	return 1;
}

int main()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}

TEST(e2e, e2e)
{
	int ans[8][34] = {{0, 3, 3},
					{1, 2, 3},
					{1, 1, 2, 0, 2},
					{1, 0, 3, 3, 2, 1, 3, 2},
					{4, 4, 4, 2, 2, 1, 2, 2, 4, 1, 5, 3, 0, 0, 2, 2, 1},
					{3, 0, 1, 1, 5, 1, 2, 3, 4, 1, 2, 0, 2, 5, 2, 1, 4, 1, 2, 4, 4, 3, 1, 3, 0, 5, 2, 1, 0, 3, 1, 4, 3, 4},
					{11, 6, 6, 11, 11, 7, 13, 6, 10, 10, 15},
					{11, 12, 15, 11, 9, 13, 8, 14, 15, 11, 9}};

	char input[8][19] = {"tests/test1.txt",
						 "tests/test2.txt",
						 "tests/test3.txt",
						 "tests/test4.txt",
						 "tests/test5.txt",
						 "tests/test6.txt",
						 "tests/test7.txt",
						 "tests/test8.txt",
						};

	for (int i = 0; i < 8; i++)
	{
		FILE* inp = fopen(input[i], "r");
		ASSERT_EQ(solve(ans[i], inp), 1);
		fclose(inp);
	}
}