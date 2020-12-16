#include <stdio.h>
#include <stdlib.h>

#include "treeofintervals.h"
#pragma warning(disable: 4996)

int main() {
	node_t* tree = NULL;
	ManageTreeOfIntervals(&tree); //to find intersections use operator 'i'
	PrintTree(tree, 1);
	DestroyTree(&tree);
	return 0;
}