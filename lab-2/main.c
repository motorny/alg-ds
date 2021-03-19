#include <stdio.h>
#include <stdlib.h>
#include "AA-tree.h"
#pragma warning(disable:4996)

enum mode_t {
	ADD,
	DELETE,
	FIND,
	PRINT,
	ERROR = -1
};

int ReadAction(FILE* fp, int* key) {
	char c, n;
	int check;
	check = fscanf(fp, "%c", &c);
	if (check == -1)
		return ERROR;

	fscanf(fp, " %d", key);
	fscanf(fp, "%c", &n); //it's for \n

	switch (c) {
	case 'a':
		return ADD;
	case 'r':
		return DELETE;
	case 'f':
		return FIND;
	case 'p':
		return PRINT;
	default:
		return ERROR;
	}
}

int main(void) {
	int mode = 0, num = 0;
	tree_t* tree = NULL;

	mode = ReadAction(stdin, &num);
	if (mode == ERROR)
		return -1;

	do {
		switch (mode) {
		case ADD:
			tree = Add(tree, num);
			break;
		case DELETE:
			Del(&tree, num);
			break;
		case FIND:
			if (Find(tree, num) != NULL)
				printf("yes\n");
			else
				printf("no\n");
			break;
		case PRINT:
			PrintTree(tree);
			break;
		default:
			break;
		}
		mode = ReadAction(stdin, &num);

	} while (mode != ERROR);

	DestroyTree(tree);

	return 0;
}
