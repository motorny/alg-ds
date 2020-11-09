#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#pragma warning(disable: 4996)

void FreeList(adjList_t* list) {
  vertex_t* curElement = list->begin;
  while (curElement != NULL) {
    list->begin = list->begin->vertex;
    free(curElement);
    curElement = list->begin;
  }
}

int ReadAdjList(adjList_t adjLists[], int length) {
  int i, number;
  char ch;
  //Цикл считывания списка смежности
  for (i = 0; i < length; i++){
    scanf("%d%c", &number, &ch);
    while (ch == ' ') {
      scanf("%d%c", &number, &ch);
      //Запись в текущий список
      if (!adjLists[i].begin) {
        adjLists[i].begin = (vertex_t*)malloc(sizeof(vertex_t));
        if (adjLists[i].begin == NULL) {
          for (i = 0; i < length; i++) {
            FreeList(&adjLists[i]);
          }
          return 1;
        }
        adjLists[i].end = adjLists[i].begin;
      }
      else {
        adjLists[i].end->vertex = (vertex_t*)malloc(sizeof(vertex_t));
        if (adjLists[i].end->vertex == NULL) {
          for (i = 0; i < length; i++) {
            FreeList(&adjLists[i]);
          }
          return 1;
        }
        adjLists[i].end = adjLists[i].end->vertex;
      }
      adjLists[i].end->number = number;
      adjLists[i].end->vertex = NULL;

      //Запись в соответсвующий список для обспечения полноты списка
      if (i < number) {
        if (!adjLists[number].begin) {
          adjLists[number].begin = (vertex_t*)malloc(sizeof(vertex_t));
          if (adjLists[number].begin == NULL) {
            for (i = 0; i < length; i++) {
              FreeList(&adjLists[i]);
            }
            return 1;
          }
          adjLists[number].end = adjLists[number].begin;
        }
        else {
          adjLists[number].end->vertex = (vertex_t*)malloc(sizeof(vertex_t));
          if (adjLists[number].end->vertex == NULL) {
            for (i = 0; i < length; i++) {
              FreeList(&adjLists[i]);
            }
            return 1;
          }
          adjLists[number].end = adjLists[number].end->vertex;
        }
        adjLists[number].end->number = i;
        adjLists[number].end->vertex = NULL;
      }
    }
  }
  return 0;
}

int* DFS(adjList_t adjLists[], int length, int* lengthDFS) {
  int* dfs = (int*)malloc(sizeof(int) * length);
  struct {
    int* elements;
    int  topOfStack;
  } stack;
  int i = 0, j;
 vertex_t* curVertex;

  stack.elements = (int*)malloc(sizeof(int) * length);
  if (!dfs || !stack.elements) {
    free(dfs);
    free(stack.elements);
    return 0;
  }
  dfs[0] = 0;
  *lengthDFS = 1;
  stack.elements[0] = 0;
  stack.topOfStack = 0;

  while (stack.topOfStack != -1){
    curVertex = adjLists[i].begin;
    for (j = 0; j < *lengthDFS; j++) {
      if (curVertex != NULL && curVertex->number == dfs[j]) {
        curVertex = curVertex->vertex;
        j = 0;
      }
    }
    if (curVertex == NULL) {
      i = stack.elements[stack.topOfStack - 1];
      stack.topOfStack--;
    }
    else {
      stack.topOfStack++;
      stack.elements[stack.topOfStack] = curVertex->number;
      (*lengthDFS)++;
      dfs[*lengthDFS - 1] = curVertex->number;
      i = curVertex->number;
    }
  }

  return dfs;
}

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
  for (i = 0; i < n; i++){
    adjLists[i].begin = NULL;
    adjLists[i].end = NULL;
  }
  //Чтение списка смежности
  error = ReadAdjList(adjLists, n);
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
  for (i = 0; i < lengthDFS; i++){
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