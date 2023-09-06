#include <stdio.h>

int main(void)
{
	int n;
	double res;

	scanf("%d", &n);

	// 4, 8, 12, 16, 20
	res = (double)n * 4;

	printf("%.lf", res);

}