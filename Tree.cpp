#include <stdio.h>
#include <malloc.h>
#include "Node.hpp"
#pragma warning (disable:4996)

int main() {
	char input;
	int number;
	Node_t* node = NULL;

	input = (char)getchar();
	while (input != EOF) {
		scanf("%d", &number);
		switch (input) {
		case 'a':
		{
			node = Insert(node, number);
			break;
		}
		case 'f':
		{
			Node_t* searched = Search(node, number);
			if (!searched)
				puts("no");
			else {
				puts("yes");
				node = Splay(searched);
			}
			break;
		}
		case 'r':
		{
			node = Delete(node, number);
			break;
		}
		default:
			break;
		}
		input = (char)getchar();
		if (input == '\r' || input == '\n')
			input = (char)getchar();
	}
	FreeTree(node);
	return 0;
}