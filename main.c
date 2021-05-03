#include "avl.h"

int main(void)  {
	int num = 0;
	int founder = 0;
	node_t* tree=NULL;
	char c = getchar();
	while (c != EOF) {
		scanf("%d", &num);
		if (c == 'a') {
			tree = AddNode(tree, num);
		}
		else if (c == 'r') {
			tree = RemoveNode(tree, num);
		}
		else if (c == 'f') {
			founder = FindNode(tree, num);
			if (founder == 1)
				printf("yes\n");
			else
				printf("no\n");
		}
		else {
			return 0;
		}
		c = getchar();
		if (c == '\r')
			c = getchar();
		if (c == '\n')
			c = getchar();
	}
	return 0;
}