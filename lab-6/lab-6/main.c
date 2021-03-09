#include "treap.h"


int main() {

	node* root = NULL;

	char* command = (char*)malloc(MAX_INPUT_LENGTH * sizeof(char));
	int val;
	if (!command) {
		perror("not enough memory");
		exit(1);
	}
	while (fgets(command, MAX_INPUT_LENGTH, stdin)) {
		val = strtol(command + 2, NULL, 10);
		if (command[0] == 'a')
			insert(val, get_count(root), &root);
		else if (command[0] == 'r') {
			bool deleted = false;
			del_val(val, &root, &deleted);
		}
		else if (command[0] == 'f') {
			bool contains = false;
			check(val, root, &contains);
			if (contains)
				printf("yes\n");
			else
				printf("no\n");
		}

	}



	free_tree(root);
	free(command);
	return 0;
}







