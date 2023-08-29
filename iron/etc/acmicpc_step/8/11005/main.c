#include <stdio.h>

#define NUM_ARR 36
#define MAX_BUFFER_LEN 128

int main(void)
{
	int N, B;
	char arr[NUM_ARR] = { '0', '1', '2', '3', '4', '5', '6', '7','8', '9',
							'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
							'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
							'U', 'V', 'W', 'X', 'Y', 'Z' };
	char res[MAX_BUFFER_LEN];
	int idx;

	scanf("%d %d", &N, &B);
	idx = 0;

	while (N > 1)
	{
		res[idx++] = arr[N % B];
		N = N / B;
	}

	if (N == 1)
	{
		res[idx++] = arr[1];
	}

	for (int i = 0; i < idx; i++)
	{
		printf("%c", res[idx - i - 1]);
	}
}