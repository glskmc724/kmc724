#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_LEN 16
#define MAX_NUM_LOG 1000000

typedef struct
{
	int idx;
	int commute;
	char name[MAX_BUFFER_LEN];
} employee;

static employee* employees;

int compare(const void* a, const void* b)
{
	int hash_a;
	int hash_b;
	employee employee_a;
	employee employee_b;

	hash_a = (*(int*)a);
	hash_b = (*(int*)b);

	employee_a = employees[hash_a];
	employee_b = employees[hash_b];

	//printf("strcmp(%s, %s)=%d\n", employee_b.name, employee_a.name, strcmp(employee_b.name, employee_a.name));

	return strcmp(employee_b.name, employee_a.name);
}

unsigned int cyclic_shift(char* str, int len)
{
	unsigned int h = 0;
	for (int i = 0; i < len; i++)
	{
		h = (h << 5) | (h >> 27);
		h += (unsigned int)str[i];
	}
	return h;
}

int main(void)
{
	int n;
	char name[MAX_BUFFER_LEN];
	char commute[MAX_BUFFER_LEN];
	int len;
	int hash;
	int cnt;
	int* hash_arr;

	employees = (employee*)calloc(MAX_NUM_LOG, sizeof(employee));
	hash_arr = (int*)calloc(MAX_NUM_LOG, sizeof(int));
	cnt = 0;

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%s %s", name, commute);

		if (strcmp(commute, "enter") == 0)
		{
			len = strlen(name);
			hash = (cyclic_shift(name, len)) % MAX_NUM_LOG;
			strcpy(employees[hash].name, name);
			employees[hash].commute = 1;
			if (employees[hash].idx == 0)
			{
				hash_arr[cnt++] = hash;
				employees[hash].idx = cnt;
			}
		}
		else if (strcmp(commute, "leave") == 0)
		{
			len = strlen(name);
			hash = (cyclic_shift(name, len)) % MAX_NUM_LOG;
			employees[hash].commute = 0;
		}
	}

	//quick_sort(hash_arr, 0, cnt - 1);
	qsort(hash_arr, cnt, sizeof(int), compare);

	for (int i = 0; i < cnt; i++)
	{
		hash = hash_arr[i];
		if (employees[hash].commute == 1)
		{
			printf("%s\n", employees[hash].name);
		}
	}
}