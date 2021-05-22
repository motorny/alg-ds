#include "BplsTree.h"

int main(void) {
	tree_t* root = CreateTree();

	while (1) {
		int key = 0;
		char function = getchar();
		if (function == EOF || function == '\n')
			break;

		scanf("%d", &key);

		//choosing operator
		if (function == 'a')
            InsertKey(&root, key);
		else if (function == 'r')
            DeleteByKey(root, key);
		else if (function == 'f') {
			if (FindByKey(root, key))
				printf("yes\n");
			else
				printf("no\n");
		}
		function = getchar(); //get "\n" at the end of str
	}

    DestroyTree(root);
	return 0;
}