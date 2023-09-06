#include <stdio.h>

int main(void)
{
	int a;
	int b;
	int c;
	int sum;

	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);

	sum = a + b + c;

	if (a == 60 && b == 60 && c == 60)
	{
		printf("Equilateral");
	}
	else
	{
		if (sum == 180)
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
		else
		{
			printf("Error");
		}
	}
}