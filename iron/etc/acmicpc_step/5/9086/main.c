#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_STR 1000

int main(void)
{
	int cnt;

	scanf("%d", &cnt);

	for (int i = 0; i < cnt; i++)
	{
		char* str = (char*)malloc(sizeof(char) * MAX_NUM_STR);
		int len;

		scanf("%s", str);
		len = strlen(str);

		printf("%c%c\n", str[0], str[len - 1]);
	}
}