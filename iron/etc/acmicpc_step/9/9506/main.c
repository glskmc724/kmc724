#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_LEN 128
#define OUTPUT_DEL_OFFSET 3

int main(void)
{
	int n;
	int rst;
	int idx;
	int sum;
	int len;
	char str[MAX_BUFFER_LEN];
	char tmp[MAX_BUFFER_LEN];

	while (1)
	{
		scanf("%d", &n);

		if (n == -1)
		{
			break;
		}

		sum = 0;
		rst = -1;
		sprintf(str, "%d = ", n);
		for (int i = 0; i < n - 1; i++)
		{
			idx = i + 1;
			rst = n % idx;
			if (rst == 0)
			{
				sprintf(tmp, "%d + ", idx);
				strcat(str, tmp);
				sum += idx;
			}
		}

		if (sum == n)
		{
			len = strlen(str);
			str[len - OUTPUT_DEL_OFFSET] = 0;
			printf("%s\n", str);
		}
		else
		{
			printf("%d is NOT perfect.\n", n);
		}
	}

}