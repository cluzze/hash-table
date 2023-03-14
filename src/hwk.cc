#include "hash_table.h"
#include "list.h"

#include <stdlib.h>
#include <string.h>

int main()
{
	int i;
	int res;
	int n, text_len, ans_len;
	char *text, *ans;
	char *word;
	struct htab_t *htab;
	struct list_node_t *list_node;

	scanf("%d%d", &n, &text_len);

	text = (char*)calloc(text_len + 1, sizeof(char));

	scanf("\n");
	for (i = 0; i < text_len; i++)
	{
		scanf("%c", &text[i]);
	}

	scanf("%d", &ans_len);

	ans = (char*)calloc(ans_len + 1, sizeof(char));

	scanf("\n");
	for (i = 0; i < ans_len; i++)
	{
		scanf("%c", &ans[i]);
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

		printf("%d ", res);

		word = strtok(NULL, " ");
		i++;
	}

	free(text);
	free(ans);
	htab_free(htab);

}