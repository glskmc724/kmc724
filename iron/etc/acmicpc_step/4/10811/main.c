#include <stdio.h>
#include <stdlib.h>

void reverse(int* arr, int n, int m);

int main(void)
{
	int N;
	int M;
	int* baskets;
	int i, j;

	scanf("%d %d", &N, &M);

	baskets = (int*)calloc(N, sizeof(int));

	for (int idx = 0; idx < N; idx++)
	{
		baskets[idx] = idx + 1;
	}

	for (int cnt = 0; cnt < M; cnt++)
	{
		scanf("%d %d", &i, &j);
		reverse(baskets, i, j);
	}

	for (int idx = 0; idx < N; idx++)
	{
		printf("%d ", baskets[idx]);
	}

	return 0;
}

void reverse(int* arr, int n, int m)
{
	int tmp;
	int left;
	int right;

	left = n - 1;
	right = m - 1;

	while (left < right)
	{
		tmp = arr[left];
		arr[left] = arr[right];
		arr[right] = tmp;

		left += 1;
		right -= 1;
	}
}