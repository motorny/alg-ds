#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define WASNOT 0
#define WAS 1
#define NOTICE 2
typedef struct {
  int count;
  int* nodes;
  int visit;
}node;
void Readlist(node* list, int n) {
  int i, numberNode, numberNextNode;
  char space;
  for (i = 0; i < n; i++) {
    scanf("%i%c", &numberNode, &space);
    while (space != '\n' && space != '\r' && space !='EOF') {
      scanf("%i%c", &numberNextNode, &space); 
      list[numberNode].nodes[list[numberNode].count++] = numberNextNode;
      list[numberNextNode].nodes[list[numberNextNode].count++] = numberNode;
    }
  }
}
DFSa(node* list, int n, int number) {
  int i;
  list[number].visit = NOTICE;
  printf("%i ", number);
  for (i = 0; i < list[number].count;i++) {
    if (list[list[number].nodes[i]].visit != NOTICE) {
      DFSa(list, n, list[number].nodes[i]);
    }
  }
}
int main(void) {
  node* list;
  int n, i;
  scanf("%i", &n);
  list = (node*)malloc(sizeof(node) * n);
  for (i = 0; i < n; i++) {
    list[i].count = 0;
    list[i].nodes = (int*)malloc(sizeof(int) * n);
    list[i].visit = WASNOT;
  }
  Readlist(list, n);
  DFSa(list, n,0);
  return 0;
}   