#include <stdio.h>
#include <stdlib.h>
#include "2_3_tree.h"
#pragma warning (disable:4996)




int main() {

	char command;
	int key;
	node* root = NULL;

	while ((command = getchar()) != EOF) {
		scanf("%i", &key);
		ParseCommand(command, key, &root);
		PrintLinearly(root);
	}
	FreeTree(root);
	return 0;
}