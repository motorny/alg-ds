#pragma warning (disable : 4996)

#include "tree.h"

int main() {
	char command;
	int value;
	TREE_NODE* tree = NULL;

	command = (char)getchar();
	while (command != EOF) {
		scanf("%d", &value);
		switch (command) {
		case 'a':
		{
			Insert(&tree, value);
			break;
		}
		case 'f': 
		{
			if (Search(tree, value) == NO_ELEMENT)
				puts("no");
			else if (Search(tree, value) == FOUND_ELEMENT) 
				puts("yes");
			break;
		}
		case 'r':
		{
			Delete(&tree, value);
			break;
		}
		default:
			break;
		}
		command = (char)getchar();
		if (command == '\r' || command == '\n')
			command = (char)getchar();
	}

	NormalPrint(tree, 0, "root");
	printf("\n");
	SpecialPrint(tree);
	printf("\n");
	PrintAsTree(tree, 0);
	Clear(tree);
	return 0;
}