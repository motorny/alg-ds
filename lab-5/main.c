#include "intervalTree.h"

int main(void) {
	tree_t* tree = NULL;

	while (1) {
		int left = 0;
		int right = 0;
		char function = getchar();
		if (function == EOF || function == '\n')
			break;

		scanf("%d %d", &left, &right);

		//choosing operator
		if (function == 'a')
			AddByLeftBorder(&tree, left, right);

		else if (function == 'r')
			DeleteByBorders(FindByBorders(tree, left, right));

		else if (function == 'f') {
			if (FindByBorders(tree, left, right))
				printf("yes\n");
			else
				printf("no\n");
		}

		else if (function == 'i') {
			answer_t* answer = (answer_t*)malloc(sizeof(answer_t));
			answer->segments = (segment_t*)malloc(sizeof(segment_t));
			answer->count = 0;
			if (SearchIntersecting(tree, left, right, answer)) {
				PrintAnswer(answer);
			}
			else
				printf("no\n");
			FreeAnswer(answer);
		}

		function = getchar(); //get "\n" at the end of str
	}

	PrintTree(tree);

	DestroyTree(tree);

	return 0;
}