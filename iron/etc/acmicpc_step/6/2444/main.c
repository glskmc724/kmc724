#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int cnt;
	int max;
	int mid;
	int num;
	int tmp;
	int** arr;

	scanf("%d", &cnt);

	max = cnt * 2 - 1;
	arr = (int**)calloc(max, sizeof(int*));

	for (int i = 0; i < max; i++)
	{
		arr[i] = (int*)calloc(max, sizeof(int));
	}

	mid = num = cnt - 1;
	for (int i = 0; i < max; i++)
	{
		tmp = num;
		for (int j = 0; j < max; j++)
		{
			if (j == mid)
			{
				arr[i][j] = 1;
			}
			else if (j < mid)
			{
				if (tmp != 0)
				{
					arr[i][j] = -1;
					tmp = tmp - 1;
				}
				else
				{
					arr[i][j] = 1;
				}
			}
			else
			{
				if (tmp < cnt - num - 1)
				{
					arr[i][j] = 1;
				}
				else
				{
					arr[i][j] = 0;
				}
				tmp += 1;
			}
		}
		if (i < mid)
		{
			num = num - 1;
		}
		else
		{
			num = num + 1;
		}
	}

	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			if (arr[i][j] == 1)
			{
				printf("*");
			}
			else if (arr[i][j] == -1)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}
