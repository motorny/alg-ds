#include "bintree.h"
//#include <iostream>

#pragma warning (disable:4996)

ERR_STATUS Process(sbtree_t** tree) {
	int l, r;
	int num;
	char oper = getchar();
	while (oper != EOF) {
		scanf("%i %i", &l, &r);

		switch (oper) {
		case 'a':
			*tree = SBtreeInsertMod(*tree, l, r);
			break;

		case 'r':
			*tree = SBtreeDelete(*tree, l, r);
			break;

		case 'f':
			if (SBtreeSearchMod(*tree, l, r) == OK)
				printf("yes\n");
			else
				printf("no\n");
			break;

		case 'i':
			if (SBTreeInsectSecMod(*tree, l, r, &num) == OK)
				printf("yes %i\n", num);
			else
				printf("no \n");
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
	sbtree_t* tree = NULL;

	if (Process(&tree) == ERROR)
		return ERROR;

	PrintTreeBad(tree, 0);
	SBtreeInorderWalk(tree);
	printf("\n");
	SBtreeInorderWalkR(tree);
	
	if (tree != NULL)
		SBtreeFree(&tree);

	return OK;
}