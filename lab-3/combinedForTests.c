#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#pragma warning (disable:4996)

typedef enum {
  ERROR = -1,
  OK,
  EMPTY, 
  DONE, 
  NOT_DONE
}ERR_STATUS;

typedef struct {
  int* arr;
  int headP;
  int tailP;
  int size;
}queue_t;

typedef enum {
  WHITE = 5,
  GRAY,
  BLACK
}COLOR_STATUS;


typedef struct {
  int vertexVal;
  COLOR_STATUS color;
  int* brothers;
  int numOfBros;
  int pathLen;
}node_t;

ERR_STATUS CreateQueue(queue_t* queue, int size) {
  if (size <= 0)
    return ERROR;

  queue->arr = (int*)malloc(size * sizeof(int));
  if (queue->arr == NULL)
    return EMPTY;

  queue->headP = 0;
  queue->tailP = 0;
  queue->size = size;

  return OK;
}

ERR_STATUS Enqueue(queue_t* queue, int elem) {
  if (queue == NULL || queue->arr == NULL || queue->tailP >= queue->size)
    return ERROR;

  queue->arr[queue->tailP] = elem;
  queue->tailP++;

  return OK;
}


ERR_STATUS Dequeue(queue_t* queue, int* elem) {
  if (queue == NULL || queue->arr == NULL)
    return ERROR;

  if (queue->headP >= queue->tailP)
    return EMPTY;

  *elem = queue->arr[queue->headP];
  queue->headP++;
  
  return OK;
}


ERR_STATUS DeleteQueue(queue_t* queue) {
  if (queue == NULL || queue->arr == NULL)
    return ERROR;

  free(queue->arr);
  queue->headP = 0;
  queue->tailP = 0;
  queue->size = 0;

  return OK;
}

node_t* CreateAdjList(int numOfVertex) {
  node_t* adjList;
  int i, j;

  adjList = (node_t*)malloc(numOfVertex * sizeof(node_t));
  if (adjList == NULL)
    return NULL;

  for (i = 0; i < numOfVertex; ++i) {
    adjList[i].brothers = (int*)malloc(numOfVertex * sizeof(int));
    if (adjList[i].brothers == NULL) {
      for (j = 0; j < i; ++j)
        free(adjList[j].brothers);

      free(adjList);
      return NULL;
    }

    adjList[i].color = WHITE;
    adjList[i].pathLen = 0;
    adjList[i].numOfBros = 0;
  }

  return adjList;
}


void DeleteAdjList(node_t* adjList, int numOfVertex){
  int i;

  for (i = 0; i < numOfVertex; ++i)
    free(adjList[i].brothers);

  free(adjList);
  return;
}

void FillAdjList(node_t* adjList, int numOfVertex) {
  char dummy;
  int vertex;
  int bro;
  int i;

  for (i = 0; i < numOfVertex; ++i) {
    scanf("%i%c", &vertex, &dummy);
    adjList[i].vertexVal = vertex;

    while (dummy != '\n' && dummy != '\r') {
      scanf("%i", &bro);

      adjList[i].brothers[adjList[i].numOfBros] = bro;
      adjList[i].numOfBros++;
      adjList[bro].brothers[adjList[bro].numOfBros] = vertex;
      adjList[bro].numOfBros++;

      scanf("%c", &dummy);
    }
  }

  return;
}

ERR_STATUS BFS(node_t* adjList, int numOfVertex) {
  int curVerVal;
  int beg = 0;
  int size;
  int tmp;
  node_t* curBro;
  queue_t queue;
  ERR_STATUS tmpStat = OK;
  ERR_STATUS flag = NOT_DONE;
  int i;

  adjList[beg].color = GRAY;
  if (CreateQueue(&queue, numOfVertex) == ERROR)
    return ERROR;

  if (Enqueue(&queue, adjList[beg].vertexVal) == ERROR) {
    DeleteQueue(&queue);
    return ERROR;
  }
  tmpStat = Dequeue(&queue, &curVerVal);

  while (flag != DONE) {
    while (tmpStat != EMPTY) {
      if (tmpStat == ERROR) {
        DeleteQueue(&queue);
        return ERROR;
      }
      size = adjList[curVerVal].numOfBros;

      for (i = 0; i < size; ++i) {
        tmp = adjList[curVerVal].brothers[i];
        curBro = &adjList[tmp];

        if (curBro->color == WHITE) {
          curBro->color = GRAY;
          curBro->pathLen = adjList[curVerVal].pathLen++;

          if (Enqueue(&queue, curBro->vertexVal) == ERROR) {
            DeleteQueue(&queue);
            return ERROR;
          }
        }
      }
      adjList[curVerVal].color = BLACK;
      printf("%i ", adjList[curVerVal].vertexVal);

      tmpStat = Dequeue(&queue, &curVerVal);
    }

    //Checking
    for (i = 0; i < numOfVertex; ++i) {
      if (adjList[i].color == WHITE) {
        beg = i;
        flag = NOT_DONE;
        break;
      }
      flag = DONE;
    }
  }
  DeleteQueue(&queue);
  return OK;
}


int main() {
  int numOfVertex;
  node_t* adjList;

  scanf("%i", &numOfVertex);

  adjList = CreateAdjList(numOfVertex);
  if (adjList == NULL)
    return ERROR; 
  
  FillAdjList(adjList, numOfVertex);
  
  if (BFS(adjList, numOfVertex) == ERROR)
    return ERROR; 

  DeleteAdjList(adjList, numOfVertex);
  return OK;
}