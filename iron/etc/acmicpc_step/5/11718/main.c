#include <stdio.h>

#define MAX_NUM_STR 100
#define MAX_STR_LEN 128

int main(void)
{
	for (int cnt = 0; cnt < MAX_NUM_STR; cnt++)
	{
		char msg[MAX_STR_LEN];
		char ch;

		for (int idx = 0; idx < MAX_STR_LEN; idx++)
		{
			ch = getchar();
			if (ch == '\n')
			{
				msg[idx] = 0;
				break;
			}
			else if (ch == EOF)
			{
				return 0;
			}
			else
			{
				msg[idx] = ch;
			}
		}
		if (cnt + 1 == MAX_NUM_STR)
		{
			printf("%s", msg);
		}
		else
		{
			printf("%s\n", msg);
		}
	}
	return 0;
}