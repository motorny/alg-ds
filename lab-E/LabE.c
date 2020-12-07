#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Tree.h"


int main(void) {
	NODE* root = NULL;
	ConsoleTree(&root);
	printTreePreOrder(root, "root", 0);
	printf("\n");
	WriteInDataMinLeavesHeight(root);
	printTreePostOrder(root);
	return 0;
}