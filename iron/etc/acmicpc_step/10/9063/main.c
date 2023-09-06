#include <stdio.h>
#include <limits.h>

int main(void)
{
	int N;
	int x;
	int y;
	int max_x = -INT_MAX;
	int max_y = -INT_MAX;
	int min_x = INT_MAX;
	int min_y = INT_MAX;
	int width;
	int height;
	int area;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &x, &y);


		if (max_x < x)
		{
			max_x = x;
		}

		if (max_y < y)
		{
			max_y = y;
		}

		if (min_x > x)
		{
			min_x = x;
		}

		if (min_y > y)
		{
			min_y = y;
		}
	}

	width = max_x - min_x;
	height = max_y - min_y;
	area = width * height;

	printf("%d", area);
}