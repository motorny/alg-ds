#include "btree.h"

int main() {
	char command;
	int value;
	BTREE* tree = NULL;

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
			if (Search(tree, value) == FAIL)
				puts("no");
			else if (Search(tree, value) == SUCCESS)
				puts("yes");
			break;
		}
		case 'r':
		{
			Delete(tree, value);
			break;
		}
		default:
			break;
		}
		command = (char)getchar();
		if (command == '\r' || command == '\n')
			command = (char)getchar();
	}

	Print(tree, 0);
	Clear(tree);
	return 0;
}