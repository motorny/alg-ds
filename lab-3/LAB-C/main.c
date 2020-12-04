#include <stdio.h>
#include <stdlib.h>
#include "DFC.h"
#pragma warning(disable: 4996)

int main(void) {
  adjList_t* adjLists;
  int n, i, lengthDFS;
  int error;
  int* dfs;
  //vertex_t* vertex;
  //Выделение памяти под список смежностей
  scanf("%d", &n);
  adjLists = (adjList_t*)malloc(sizeof(adjList_t) * n);
  if (adjLists == NULL) {
    return 1;
  }
  for (i = 0; i < n; i++) {
    adjLists[i].begin = NULL;
    adjLists[i].end = NULL;
  }
  //Чтение списка смежности
  error = ReadAdjList(adjLists, n, stdin);
  if (error == 1) {
    free(adjLists);
    return 1;
  }
  //Вывод прочтённого списка (для теста)
  /*printf("\n\n");
  for (i = 0; i < n; i++) {
    vertex = adjLists[i].begin;
    while (vertex != NULL){
      printf("%d ", vertex->number);
      vertex = vertex->vertex;
    }
    printf("\n");
  }*/

  //Обход
  dfs = DFS(adjLists, n, &lengthDFS);
  for (i = 0; i < lengthDFS; i++) {
    printf("%d ", dfs[i]);
  }
  //Освобождение памяти
  for (i = 0; i < n; i++) {
    FreeList(&adjLists[i]);
  }
  free(adjLists);
  return 0;
}

/*11
0 1 2
1 3 4
2 7
3
4 5 6
5
6
7 8 9
8 10
9
10


4
0 1 2 3
1 2 3
2 3
3*/