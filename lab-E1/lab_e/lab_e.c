#include "bintree.h"

#pragma warning (disable:4996)

ERR_STATUS Process(btree_t** tree) {
	int key;
	char oper = getchar();
	while (oper != EOF) {
		scanf("%i", &key);

		switch (oper) {
		case 'a':
			*tree = BtreeInsertMod(*tree, key);
			break;

		case 'r':
			*tree = BtreeDelete(*tree, key);
			break;

		case 'f':
			if (BtreeSearchMod(*tree, key) == OK)
				printf("yes\n");
			else
				printf("no\n");
			break;

		default:
			printf("Incorrect input\n");
			//BtreeFree(*tree);
			return OK;

		}
		oper = getchar();
		if (oper == '\r')
			oper = getchar();
		if (oper == '\n')
			oper = getchar();
	}
	return OK;
}


int main() {
	btree_t* tree = NULL;

	if (Process(&tree) == ERROR)
		return ERROR;

	PrintTreeBad(tree, 0);
	BtreeSubHeightDif(tree);
	BtreeInorderWalk(tree);
	printf("\n");
	BtreeInorderWalkSubNods(tree);
	printf("\n");
	printf("%i", BtreeHeight(tree));

	if (tree != NULL)
		BtreeFree(tree);

	return OK;
}