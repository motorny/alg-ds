#include <stdio.h>
#include "lab_h.h"

#pragma warning(disable : 4996)

int main(void) {
	node_t* tree = NULL;
	WhatToDo(tree);
	DestroyTree(tree);
}