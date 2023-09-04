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

typedef struct
{
	struct node* next;
	employee entry;
} node;

typedef struct
{
	int hash;
	employee employee;
} hashmap;

static employee* employees;
static node* list;

node* insert(node* n, char* name, int idx)
{
	node* new = (node*)calloc(1, sizeof(node));

	while (n->next != NULL)
	{
		n = n->next;
	}

	new->next = NULL;
	strcpy(new->entry.name, name);
	new->entry.commute = 1;
	new->entry.idx = idx;
	n->next = new;

	return new;
}

void delete(node* n, char* name)
{
	while (n != NULL)
	{
		if (strcmp(n->entry.name, name) == 0)
		{
			n->entry.commute = 0;
			return;
		}
		else
		{
			n = n->next;
		}
	}
}

node* find(node* n, char* name)
{
	while (n != NULL)
	{
		if (strcmp(n->entry.name, name) == 0)
		{
			return n;
		}
		else
		{
			n = n->next;
		}
	}
	return 0;
}

int compare(const void* a, const void* b)
{
	hashmap* hash_a;
	hashmap* hash_b;

	hash_a = (hashmap*)a;
	hash_b = (hashmap*)b;

	//printf("%s %s\n", hash_a->employee.name, hash_b->employee.name);

	return strcmp(hash_b->employee.name, hash_a->employee.name);
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
	hashmap* map;
	node* pnode;

	//employees = (employee*)calloc(MAX_NUM_LOG, sizeof(employee));
	list = (node*)calloc(MAX_NUM_LOG, sizeof(node));
	map = (int*)calloc(MAX_NUM_LOG, sizeof(hashmap));
	cnt = 0;

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%s %s", name, commute);

		if (strcmp(commute, "enter") == 0)
		{
			len = strlen(name);
			hash = (cyclic_shift(name, len)) % MAX_NUM_LOG + 1;

			pnode = find(&list[hash], name);

			if (pnode != NULL)
			{
				pnode->entry.commute = 1;
			}
			else
			{
				map[cnt].hash = hash;
				pnode = insert(&list[hash], name, cnt + 1);
				map[cnt++].employee = pnode->entry;
			}

		}
		else if (strcmp(commute, "leave") == 0)
		{
			len = strlen(name);
			hash = (cyclic_shift(name, len)) % MAX_NUM_LOG + 1;
			
			delete(&list[hash], name);
		}
	}

	qsort(map, cnt, sizeof(hashmap), compare);

	for (int i = 0; i < cnt; i++)
	{
		hash = map[i].hash;

		if (list[hash].next != NULL)
		{
			pnode = find(&list[hash], map[i].employee.name);
			if (pnode->entry.commute == 1)
			{
				printf("%s\n", pnode->entry.name);
			}
		}
	}
}