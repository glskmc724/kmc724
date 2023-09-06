#include <stdio.h>

int main(void)
{
	int a1;
	int a0;
	int c;
	int n0;
	int fn;
	int gn;
	int cgn;

	scanf("%d %d", &a1, &a0);
	scanf("%d", &c);
	scanf("%d", &n0);

	fn = a1 * n0 + a0;
	gn = n0;
	cgn = gn * c;
	
	if ((fn <= cgn) && ((c - a1) >= 0))
	{
		printf("1");
	}
	else
	{
		printf("0");
	}
}