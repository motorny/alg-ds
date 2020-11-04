#include "graph.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#pragma warning (disable: 4996)

#define TRUE 1
#define FALSE 0

data_t* ReadData(int* numOfVertex, int* numOfEdges) {
  int i = 0;
  data_t* data;
  int f = 2;
  int maxSize = 100;
  scanf("%i", numOfVertex);
  data = malloc(maxSize * sizeof(data_t));
  while (f > 1) {
    f = scanf("%i %i", &data[i].a, &data[i].b);
    ++i;
    if (i == maxSize) {
      maxSize += 100;
      data = realloc(data, maxSize * sizeof(data_t));
    }
  }
  *numOfEdges = i;
  return data;
}

int Compare(const int* num1, const int* num2) {
  if (*num1 > * num2)
    return 1;
  else if (*num1 < *num2)
    return -1;
  else
    return 0;
}

void PrintVertexes(int* out, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    printf("%i ", out[i]);
  }
}

void BFS(data_t* data, int numOfVertex, int numOfEdges) {
  int i;
  int cur;
  int* isUsed = malloc(sizeof(int) * numOfVertex);
  int* out = malloc(sizeof(int) * numOfVertex);
  int numOfOut = 0;
  int nextVertex;
  memset(isUsed, FALSE, sizeof(int) * numOfVertex);
  queue_t* queue = CreateQueue();
  QueuePush(queue, 0);
  isUsed[0] = TRUE;
  printf("0 ");
  while (!QueueIsEmpty(queue)) {
    cur = QueuePop(queue);
    numOfOut = 0;
    for (i = 0; i < numOfEdges; ++i) {
      if (data[i].a == cur && !isUsed[data[i].b]) {
        nextVertex = data[i].b;
      }
      else if (data[i].b == cur && !isUsed[data[i].a]) {
        nextVertex = data[i].a;
      }
      else
        continue;
      isUsed[nextVertex] = TRUE;
      QueuePush(queue, nextVertex);
      out[numOfOut] = nextVertex;
      ++numOfOut;
    }
    qsort(out, numOfOut, sizeof(int), &Compare);
    PrintVertexes(out, numOfOut);
  }
  RemoveQueue(queue);
}
