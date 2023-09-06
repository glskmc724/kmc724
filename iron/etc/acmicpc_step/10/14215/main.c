#include <stdio.h>

int main(void)
{
	int a;
	int b;
	int c;
	int max = 0;
	int mid = 0;
	int min = 0;
	int sum = 0;
	int res = 0;

	scanf("%d %d %d", &a, &b, &c);

	if (max < a)
	{
		max = a;
		sum = b + c;

		if (b < c)
		{
			mid = c;
			min = b;
		}
		else
		{
			mid = b;
			min = c;
		}
	}

	if (max < b)
	{
		max = b;
		sum = a + c;

		if (a < c)
		{
			mid = c;
			min = a;
		}
		else
		{
			mid = a;
			min = c;
		}
	}

	if (max < c)
	{
		max = c;
		sum = a + b;

		if (a < b)
		{
			mid = b;
			min = a;
		}
		else
		{
			mid = a;
			min = b;
		}
	}

	if (max >= sum)
	{
		res = max - sum;
		sum = sum + (max - res - 1);
	}
	else
	{
		sum = sum + max;
	}
	printf("%d", sum);
}