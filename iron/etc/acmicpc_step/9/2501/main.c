#include <stdio.h>

int main(void)
{
	int N;
	int K;
	int rst;
	int cnt;

	scanf("%d %d", &N, &K);
	cnt = 1;

	for (int i = 0; i < N; i++)
	{
		if ((rst = N % (i + 1)) == 0)
		{
			if (cnt == K)
			{
				//printf("%d/%d=%d...%d", N, i + 1, N / (i + 1), N % (i + 1));
				printf("%d\n", i + 1);
			}
			cnt += 1;
		}
	}

	if (cnt <= K)
	{
		printf("0");
	}
}