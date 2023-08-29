#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 256

int ascii_to_int(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return ch - '0';
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		return ch - 'A' + 10;
	}
	else
	{
		return -1;
	}
}

int main(void)
{
	char N[MAX_STR_LEN];
	int B;
	int len;
	int sum;
	int sqr;

	scanf("%s %d", N, &B);
	len = strlen(N);
	sum = 0;

	for (int i = 0; i < len; i++)
	{
		sqr = 1;
		for (int j = 0; j < len - i - 1; j++)
		{
			sqr = sqr * B;
		}
		sum = sum + (ascii_to_int(N[i]) * sqr);
		//printf("%d %d\r\n", sum, sqr);
	}
	printf("%d", sum);
}