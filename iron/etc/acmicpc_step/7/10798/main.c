#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LINE 5
#define MAX_BUFFER_LEN 128

typedef struct
{
	int len;
	char str[MAX_BUFFER_LEN];
} word;

int main(void)
{
	word* words;
	int max;
	int j;

	j = 0;
	max = 0;
	words = (word*)calloc(NUM_LINE, sizeof(word));

	for (int i = 0; i < NUM_LINE; i++)
	{
		scanf("%s", words[i].str);
		words[i].len = strlen(words[i].str);
		if (max < words[i].len)
		{
			max = words[i].len;
		}
	}

	while (j < max)
	{
		for (int i = 0; i < NUM_LINE; i++)
		{
			if (j < words[i].len)
			{
				printf("%c", words[i].str[j]);
			}
		}
		j = j + 1;
	}
}