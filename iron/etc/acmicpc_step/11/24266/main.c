#include <stdio.h>

int main(void)
{
	int n;
	long long int tmp;
	long long int res;

	scanf("%d", &n);
	
	tmp = (long long int)n;
	res = tmp * tmp * tmp;

	printf("%lld\n", res);
	printf("3");
}