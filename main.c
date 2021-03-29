#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node{
 int num;
 struct node* next;
 int isVisited;
} adjList_t;

adjList_t* InitGraph( int size) { 
  int i;
  adjList_t* adjList = NULL;
  if (size < 0) {
    return NULL;
  }
  adjList = (adjList_t*)malloc((size) * sizeof(adjList_t));
  if (adjList == NULL) {
    return NULL;
  }
  else {
    for (i = 0; i < size; i++) {
        adjList[i].num = i;
        adjList[i].next = NULL;
        adjList[i].isVisited = FALSE;

    }
    return adjList;
  }
}

int FillGraph(adjList_t* arr, int a, int b) {
  adjList_t *newB, *tmp;
  //vertexes add in ascending order in adjList
    //add rib a-b
  newB = (adjList_t*)malloc(sizeof(adjList_t));
  if (newB == NULL) {
    return 0;
  }
  tmp = &arr[a];
  if (tmp->next != NULL) {
    while (tmp) {
      if (tmp->next == NULL) {
        break;
      }
      if (tmp->next->num < b) {
        tmp = tmp->next;
      }
      else
        break;
    }
  }
  //add in list
  newB->next = tmp->next;
  tmp->next = newB;
  newB->num = b;

  //add rib b-a
  newB = (adjList_t*)malloc(sizeof(adjList_t));
  if (newB == NULL) {
    return 0;
  }
  tmp = &arr[b];
  if (tmp->next != NULL) {
    while (tmp) {
      if (tmp->next == NULL) {
        break;
      }
      if (tmp->next->num < a) {
        tmp = tmp->next;
      }
      else
        break;
    }
  }
  //add in list
  newB->next = tmp->next;
  tmp->next = newB;
  newB->num = a;

  return 1;
}

void FreeGraph(adjList_t* arr,int size) {
  int i;
  adjList_t* freeP;
  adjList_t* tmp = arr;
  //free list for each element of array
  for (i = 0; i < size; i++) {
    tmp = arr[i].next;
    while (tmp) {
      freeP = tmp;
      tmp = tmp->next;
      free(freeP);
    }
  }
  //free array
  free(arr);
}

int BFS(adjList_t* graph, int startVertex, int *visited, int* queue) {
  int countVertex = 0, countV = 0, endQ = 0;
  int i, cur;
  adjList_t*tmp;

  //add startVertex in queue
  queue[endQ] = graph[startVertex].num;
  endQ++;
  
  while (endQ != 0) {
    //take 1st elem in queue and add to visited
    cur = queue[0];
    visited[countV] = queue[0];
    graph[queue[0]].isVisited = TRUE;
    countV++;
      //queue shift
    for (i = 0; i < endQ-1; i++) {
      queue[i] = queue[i + 1];
    }
    endQ--;
      //add unvisited vertices which are adjacent with cur
    tmp = graph[cur].next;
    while (tmp) {
      //if ver is unvisited
      if (graph[tmp->num].isVisited == FALSE) {
        //add to queue
        queue[endQ] = tmp->num;
        graph[tmp->num].isVisited = TRUE;
        endQ++;
      }
      tmp = tmp->next;
    }
  }
  return countV;
}

//interface for tokens
/*
int main() {
  int size = 0, a, b, index = 0;
  int isInita = 0, isInitb = 0;
  int i;
  char str[100];
  int c;
  adjList_t* arr;

  while ((c = (char)getchar()) != '\n') {
    str[index++] = c;
  }
  str[index] = '\0';
  size = atoi(str);
  index = 0;
  arr = InitGraph(size);

  while ((c = (char)getchar()) != EOF) {
      str[index++] = c;
    if (c == ' ') {
      a = atoi(str);
      index = 0;
      isInita = TRUE;
    }

    if (c == '\n') {
      b = atoi(str);
      index = 0;
      isInitb = TRUE;
    }

    if (isInita && isInitb) {
      FillGraph(arr, a, b);
      isInita = FALSE;
      isInitb = FALSE;
    }
  }

  int* visited = (int*)malloc(size * sizeof(int));
  int* queue = (int*)malloc(size * sizeof(int));
  if (visited && queue) {
   int countV = BFS(arr, 0, visited, queue, size);
    for (i = 0; i < countV; i++) {
    printf("%i ", visited[i]);
  }
    free(visited);
    free(queue);
  }

  FreeGraph(arr, size);
  return 0;
}
*/
