#include <stdio.h>
#include "23Tree.h"
#pragma warning (disable:4996)

int main(void) {
	Tree23* tree = NULL;
	int command, key;

	command = getchar();
	while (command != EOF) {
		scanf("%d", &key);
		switch (command) {
		case 'a':
			tree = InsertNumber(tree, key);
			break;
		case 'f':
			if (FindNumber(tree, key))
				printf("yes\n");
			else
				printf("no\n");
			break;
		case 'r':
			tree = DeleteNumber(tree, key);
			break;
		default:
			Destroy_Tree(tree);
			return 0;
		}
		command = getchar();
		if (command == '\n')
			command = getchar();
	}
	Destroy_Tree(tree);
	return 0;
}