#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void gen_test(FILE* out, int size)
{
	int i = 0, j = 0, len = 0;
	char c = 0;
	fprintf(out, "%d\n", size);
	for (i = 0; i < size; i++)
	{
		len = 1 + rand() % 5;
		for (j = 0; j < len; j++)
		{
			c = 'a' + rand() % 10;
			fprintf(out, "%c", c);
		}
		fprintf(out, "\n");
	}
}

int main()
{
	FILE *input = NULL;
	int sizes[7] = {100, 1000, 3000, 5000, 10000, 20000, 100000};
	int i = 0;
	char files[][17] ={ "tests/input1.txt",
						"tests/input2.txt",
						"tests/input3.txt",
						"tests/input4.txt",
						"tests/input5.txt",
						"tests/input6.txt",
						"tests/input7.txt",
					};

	for (i = 0; i < 7; i++)
	{
		input = fopen(files[i], "w");
		gen_test(input, sizes[i]);
	}
	
	gen_test(input, 100);

}