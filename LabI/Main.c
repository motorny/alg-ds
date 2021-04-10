#include <stdio.h>
#include "Tree.h"

#pragma warning (disable: 4996)

void ConsoleTree() {
	char com = ' ';
	int key;
	tree_t* t = CreateTree();

	while (true) {
		com = getchar();
		if (com == EOF) {
			break;
		}
		scanf("%d", &key);
		getchar();
		switch (com) {
		case 'a':
			InsertTree(t, key);
			break;
		case 'f':
			if (SearchTree(t, key)) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
			break;
		case 'r':
			DeleteTree(t, key);
			break;
		}
	}

	FreeTree(t);
}

int main() {
	ConsoleTree();
	return 0;
}