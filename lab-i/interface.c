#include "b_tree.h"
#pragma warning (disable:4996)

int Read(int* data) {
	int tmp = 0;
	char ch = (char)getchar();

	if (ch == EOF)
		return 0;

	tmp = scanf("%i", data);
	tmp = getchar();

	switch (ch) {
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
	int num, var;
	Btree_t tree;

	InitBtree(&tree);
	var = Read(&num);
	while (var) {
		switch (var) {
		case 1:
			AddToBtree(&tree, num);
			break;
		case 2:
			if (FindInBtree(&tree, num) != NULL)
				printf("yes\n");
			else
				printf("no\n");
			break;
		default:
			DeleteFromBtree(&tree, num);
			break;
		}

		var = Read(&num);
	}

	DestroyBtree(&tree);
	return 0;
}