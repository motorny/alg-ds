#include "tree.h"

int main(void) {
	char command;
	int key;
	node_t* root = NULL;

	while ((command = getchar()) != EOF) {
		scanf("%i", &key);
		MainFunc(command, key, &root);
	}
	FreeTree(root);
	return 0;
}