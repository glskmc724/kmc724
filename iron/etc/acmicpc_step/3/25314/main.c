#include <stdio.h>

int main(void)
{
	int input;
	int res;

	scanf("%d", &input);
	res = input / 4;
	for (int i = 0; i < res; i++)
	{
		printf("long ");
	}
	printf("int");
	return 0;
}