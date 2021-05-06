#include "Hash.h"

HashTable* workingWithHashTable(HashTable* table)
{
	char c, operation, number[1024];
	int index = 0, data;

	c = getchar();
	while (c != EOF)
	{
		operation = c;
		c = getchar();
		while (isspace(c))
		{
			c = getchar();
		}
		while (isdigit(c))
		{
			number[index++] = c;
			c = getchar();
		}
		number[index] = '\0';
		index = 0;
		switch (operation)
		{
		case 'a':
		{
			add(table, number);
			break;
		}
		case 'r':
		{
			del(table, number);
			break;
		}
		case 'f':
		{
			if (find(table, number) == 0)
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
			break;
		}
		}
		if (c == '\n')
		{
			c = getchar();
		}
	}

	return table;
}

int main()
{
	HashTable* table = createHashTable(10000);
	table = workingWithHashTable(table);
	return 0;
}