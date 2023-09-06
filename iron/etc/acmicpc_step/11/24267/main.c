#include <stdio.h>

int main(void)
{
	int n;
	long long int tmp;
	long long int res;
	
	scanf("%d", &n);
	tmp = (long long int)n;

	res = (tmp * (tmp - 1) * (tmp - 2)) / 6;

	printf("%lld\n", res);
	printf("3");
} 