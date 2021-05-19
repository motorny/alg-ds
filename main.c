#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	char command;
	int val;
	BTREE* tree = NULL;

	command = (char)getchar();

	while (command != EOF) {
		scanf_s("%d", &val);
		switch (command) {
		case 'a':
		{
			Insert(&tree, val);
			break;
		}
		case 'f':
		{
			if (Search(tree, val) == NOTFOUND)
				printf("no\n");
			else if (Search(tree, val) == FOUND)
				printf("yes\n");
			break;
		}
		case 'r':
		{
			DestroyTree(tree, val);
			break;
		}
		default:
			break;
		}
		command = (char)getchar();
		if (command == '\r' || command == '\n')
			command = (char)getchar();
	}

//	PrintTree(tree, 0);
	Clear(tree);
	return 0;
}