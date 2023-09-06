#include <stdio.h>

int main(void)
{
	int a;
	int b;
	int c;
	int max;
	int sum;

	while (1)
	{
		max = 0;
		sum = 0;

		scanf("%d %d %d", &a, &b, &c);

		if (max < a)
		{
			max = a;
			sum = b + c;
		}
		
		if (max < b)
		{
			max = b;
			sum = a + c;
		}

		if (max < c)
		{
			max = c;
			sum = a + b;
		}

		if (a == 0 && b == 0 && c == 0)
		{
			break;
		}
		else
		{
			if (max >= sum)
			{
				printf("Invalid\n", max, sum);
				continue;
			}

			if (a == b && a == c && b == c)
			{
				printf("Equilateral");
			}
			else
			{
				if (a == b || a == c || b == c)
				{
					printf("Isosceles");
				}
				else
				{
					printf("Scalene");
				}
			}
			printf("\n");
		}
	}
}