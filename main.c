#include<stdio.h>
#include<stdlib.h>
#include"E1.h"
int main(void) {
  tree_t* tree = NULL;
  tree = readString(tree);
  printTree(tree, 1);
  freeTree(tree);
}