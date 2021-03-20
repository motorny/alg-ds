#include "AA_tree.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#pragma warning(disable:4996)

void InterfaceAAtree(aatree_t** tree) {
	char buff[1000];
	char sym = 0;
	char command = 0;
	int num = 0;
	int i = 0;
	sym = getchar();
	while (sym != EOF) {
		command = sym;
		sym = getchar();
		while (isspace(sym))
			sym = getchar();
		while (isdigit(sym)) {
			buff[i] = sym;
			i++;
			sym = getchar();
		}
		buff[i] = '\0';
		num = atoi(buff);
		i = 0;

		switch (command) {
		case 'a':
		{
			Insert(tree, num);
			break;
		}
		case 'f':
		{
			if (FindNode(*tree, num) == TRUE)
				printf("yes\n");
			else
				printf("no\n");
			break;
		}
		case 'r':
		{
			DeleteNode(tree, num);
			break;
		}
		}
		if (sym == '\n')
			sym = getchar();
	}
}

int main(void) {
	aatree_t* tree = NULL;
	InterfaceAAtree(&tree);
	FreeTree(tree);
	return 0;
}