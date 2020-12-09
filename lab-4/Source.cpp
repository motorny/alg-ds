#include<stdio.h>
#include<stdlib.h>
#include"mytree.h"
#pragma warning(disable:4996)

int main(void) {
	Node* root = NULL;
	GetTreeFromConsole(&root);
	MinHeightLeaves(root);
	PrintTree(root, "tr", 1);
	DestroyTree(&root);
	return 0;
}