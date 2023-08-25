#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 100

int main(void)
{
	char str[MAX_STR_LEN];
	int len;

	scanf("%s", str);

	len = strlen(str);

	printf("%d", len);
}