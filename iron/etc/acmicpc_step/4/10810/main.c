#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int N;
	int M;
	int* baskets;
	int i, j, k;

	scanf("%d %d", &N, &M);

	baskets = (int*)calloc(N, sizeof(int));

	for (int cnt = 0; cnt < M; cnt++)
	{
		scanf("%d %d %d", &i, &j, &k);

		for (int idx = i - 1; idx < j; idx++)
		{
			baskets[idx] = k;
		}
	}

	for (int idx = 0; idx < N; idx++)
	{
		printf("%d ", baskets[idx]);
	}
	return 0;
}