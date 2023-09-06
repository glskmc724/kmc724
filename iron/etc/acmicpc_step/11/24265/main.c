#include <stdio.h>

int main(void)
{
	int n;
	double tmp;
	double res;

	scanf("%d", &n);

	tmp = (double)n;
	res = (tmp - 1) * (tmp - 1) - ((tmp - 2) * (tmp - 1) / 2);
	
	printf("%.lf\n", res);
	printf("2");
}