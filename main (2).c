#include "aatree.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

void Process(Node** tree)
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
			insert(tree, data);
			break;
		}
		case 'r':
		{
			removeNode(tree, data);
			break;
		}
		case 'f':
		{
			if (findNode(*tree, data))
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
}

int main()
{
	Node* tree = NULL;
	Process(&tree);
	treeFree(tree);
	return 0;
}