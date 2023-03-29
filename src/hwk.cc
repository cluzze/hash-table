#include "hash_table.h"
#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

char** read_strings(FILE* input, char **text, int n)
{
	size_t size = 0;
	int i = 0;

	text = (char**)calloc(n, sizeof(char*));

	for (i = 0; i < n; i++)
	{
		getline(&text[i], &size, input);
		size = strlen(text[i]);
		if (text[i][size - 1] == '\n')
			text[i][size - 1] = '\0';
	}
	return text;
}

char *make_res(char *ans, const char *a, const char *b, const char *c, const char *d)
{
	strcat(ans, a);
	strcat(ans, " ");
	strcat(ans, b);
	strcat(ans, " ");
	strcat(ans, c);
	strcat(ans, " ");
	strcat(ans, d);
	return ans;
}

int solve(struct htab_t *htab, struct htab_t *ans, char **strings, int n)
{
	int i = 0, j = 0, k = 0;
	char *a = NULL, *d = NULL;
	char *c = NULL, *b = NULL;
	struct list_node_t *find1 = NULL, *find2 = NULL;
	int value1 = 0, value2 = 0;
	int alen = 0;
	int ans_len = 0;
	char *str = NULL;
	int res = 0;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			a = strings[i];
			d = strings[j];
			alen = strlen(a);

			find1 = htab_find(htab, a);
			find2 = htab_find(htab, d);

			value1 = list_node_get_value(find1);
			value2 = list_node_get_value(find2);

			if (value1 >= 2 && value2 >= 2)
			{
				if (strcmp(a, d) == 0 && value1 < 4)
				{
					continue;
				}
				ans_len = 4 + 2 * (alen + strlen(d));
				str = (char*)calloc(ans_len, sizeof(char));
				str = make_res(str, a, d, a, d);
				if (!htab_find(ans, str))
				{
					htab_insert(ans, str, 1);
					res++;
				}
				else
				{
					free(str);
				}
			}

			for (k = 0; k < alen; k++)
			{
				if (strncmp(a + k, d, alen - k) == 0) // a + b = c + d === c + d = a + b
				{
					b = d + alen - k;
					c = (char*)calloc(alen - k + 2, sizeof(char));
					strncpy(c, a, k);
					c[k] = '\0';
					if (htab_find(htab, c) && htab_find(htab, b))
					{
						ans_len = 4 + alen + strlen(b) + strlen(c) + strlen(d);
						str = (char*)calloc(ans_len, sizeof(char));
						str = make_res(str, a, b, c, d);
						
						if (!htab_find(ans, str))
						{
							htab_insert(ans, str, 1);
							res++;
						}
						else
						{
							free(str);
						}
					}
					free(c);
				}
			}
		}
	}
	return res;
}

int main()
{
	struct htab_t *htab = NULL;
	struct htab_t *ans = NULL;
	FILE *input = NULL;
	int size = 0;
	char **strings = NULL;
	int i = 0, k = 0;
	int res = 0;
	char files[][17] ={ "tests/input1.txt",
						"tests/input2.txt",
						"tests/input3.txt",
						"tests/input4.txt",
						"tests/input5.txt",
						"tests/input6.txt",
						"tests/input7.txt",
					};

	clock_t start, end;
	double cpu_time_used;

	for (k = 0; k < 7; k++)
	{
		input = fopen(files[k], "r");
		
		if (fscanf(input, "%d\n", &size) != 1)
			return -1;

		strings = read_strings(input, strings, size);

		fclose(input);
		htab = htab_create(100000);
		ans = htab_create(100000);

		for (i = 0; i < size; i++)
		{
			htab_insert(htab, strings[i], 1);
		}

		start = clock();
		res = solve(htab, ans, strings, size);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

		printf("test: %s, res: %d, time used: %f\n", files[k], res, cpu_time_used);

	#ifdef DUMP 
		htab_print(ans, stdout);
	#endif

		for (i = 0; i < size; i++)
		{
			free(strings[i]);
		}

		free(strings);
		htab_free_keys(ans);
		htab_free(htab);
		htab_free(ans);
	}
}