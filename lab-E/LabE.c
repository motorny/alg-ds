#include<stdio.h>
#include<stdbool.h>
#include"Tree.h"


int main(void) {
	NODE* root = NULL;
	ConsoleTree(&root);
	printTreePostOrder(root);
	printf("\n");
	WriteInDataMinLeavesHeight(root);
	printTreePostOrder(root);
	return 0;
}