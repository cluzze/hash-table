#include "list.h"
#include "hash_table.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int n, text_len, ans_len;
	char *text, *ans;

	scanf("%d %d", &n, &text_len);

	text = (char*)calloc(text_len + 1, sizeof(char));
	for (i = 0; i < text_len; i++)
	{
		scanf("%c", &text[i]);
	}

	scanf("%d", &ans_len);

	ans = (char*)calloc(ans_len + 1, sizeof(char));
	for (i = 0; i < ans_len; i++)
	{
		scanf("%c", &ans[i]);
	}

	printf("%s\n%s\n", text, ans);
}