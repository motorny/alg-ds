#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#pragma warning (disable:4996)

enum {
	ADD = 1,
	FIND = 2,
	DELETE = 3,
};


int GetInput(int* key) {
	char sym = (char)getchar();
	int id = 0;
	if (sym == EOF)
		return 0;
	id = scanf("%i", key);
	id = getchar();

	switch (sym) {
	case 'a':
		return 1;
	case 'f':
		return 2;
	case 'r':
		return 3;
	default:
		return 0;
	}
}

int main(void) {
	int key = 0;
	node_t* tree = NULL;

	//Run1(tree, &key);


	int command = 0;
	command = GetInput(&key);
	while (command) {
		switch (command) {
		case 1:
			AddToTree(&tree, (key));
			break;
		case 2:
			if (FindInTree(tree, (key)) != NULL)
				printf("yes\n");
			else
				printf("no\n");
			break;
		default:
			DeleteFromTree(&tree, (key));
			break;
		}

		command = GetInput(&key);
	}

	PrintLevels(tree, 1, "root");
	printf("\n");
	PrintTree(tree, 1);
	printf("\n");
	PrintNodes(tree);

	DestroyTree(&tree);
	return 0;
}