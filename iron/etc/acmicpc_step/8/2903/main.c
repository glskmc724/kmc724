#include <stdio.h>
#include <math.h>

#define INIT_NUM 4

int main(void)
{
	int N;
	int init = INIT_NUM;
	int sum = sqrt(init);
	int sqr = 1;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		sum = sum + sqr;
		sqr = sqr * 2;
	}

	printf("%d", sum * sum);
}