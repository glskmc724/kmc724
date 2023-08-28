#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

int check(char* str)
{
	int left;
	int right;

	left = 0;
	right = strlen(str) - 1;
	
	while (1)
	{
		if (left > right)
		{
			break;
		}
		else
		{
			if (str[left++] != str[right--])
			{
				return 0;
			}
		}
	}
	return 1;
}

int main(void)
{
	char* str;
	int left;
	int right;

	str = (char*)calloc(MAX_STR_LEN, sizeof(char));

	scanf("%s", str);
	printf("%d", check(str));
}