#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int N;
	int M;
	int* baskets;
	int i, j;
	int tmp;

	scanf("%d %d", &N, &M);

	baskets = (int*)calloc(N, sizeof(int));

	for (int idx = 0; idx < N; idx++)
	{
		baskets[idx] = idx + 1;
	}

	for (int cnt = 0; cnt < M; cnt++)
	{
		scanf("%d %d", &i, &j);

		i = i - 1;
		j = j - 1;

		tmp = baskets[i];
		baskets[i] = baskets[j];
		baskets[j] = tmp;
	}

	for (int idx = 0; idx < N; idx++)
	{
		printf("%d ", baskets[idx]);
	}
	return 0;
}