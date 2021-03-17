#include<stdio.h>
#include<stdlib.h>
#include"treap.h"
#include"tree.h"
#pragma warning(disable:4996)

int main(void) {
  Treap* Tree = NULL;
  GetTreeFromConsole(&Tree);
  DestroyTree(&Tree);
  return 0;
}
