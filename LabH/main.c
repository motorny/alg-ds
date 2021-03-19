#pragma warning (disable : 4996)

#include "tree.h"

int main() {
	char command;
	int value;
	SPLAYTREE* tree = NULL;

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
			SPLAYTREE* searched = Search(tree, value);
			if (!searched)
				puts("no");
			else {
				puts("yes");
				tree = Splay(searched);
			}
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
	Clear(tree);
	return 0;
}