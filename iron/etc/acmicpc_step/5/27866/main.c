#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LEN 1000

int main(void)
{
	char* str;
	int idx;

	str = (char*)malloc(sizeof(char) * MAX_STR_LEN);

	scanf("%s", str);
	scanf("%d", &idx);
	idx -= 1;

	printf("%c", str[idx]);

	return 0;
}