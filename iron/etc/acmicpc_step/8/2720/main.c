#include <stdio.h>

typedef struct
{
	int q;
	int d;
	int n;
	int p;
} cent;

cent calculate(int C)
{
	cent c;

	c.q = C / 25;
	c.d = (C % 25) / 10;
	c.n = (C % 25 % 10) / 5;
	c.p = C % 25 % 10 % 5;

	return c;
}

int main(void)
{
	int T;
	cent c;

	scanf("%d", &T);

	for (int i = 0; i < T; i++)
	{
		int C;

		scanf("%d", &C);
		c = calculate(C);
		printf("%d %d %d %d\n", c.q, c.d, c.n, c.p);
	}
}