#include "tree23.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

node* workingWithTree(node* tree)
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
		data = atoi(number);
		index = 0;
		switch (operation)
		{
		case 'a':
		{
			insert(&tree, data);
			break;
		}
		case 'r':
		{
			tree = delKey(tree, data);
			break;
		}
		case 'f':
		{
			if (find(tree, data))
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

	return tree;
}

int main()
{
	node* tree = NULL;
	tree = workingWithTree(tree);
	return 0;
}
