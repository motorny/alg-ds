#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NOT_ENOUGH_MEMORY 2
#define EMPTY_QUEUE -1
#define INCORRECT_SIZE 1

typedef struct Queue
{
  struct Queue* ptrToNext, * ptrToPrev;
  int value;
}QUEUE;

int gMatrixSize = 0;
int** gM = NULL;
QUEUE* gQueue = NULL;

int addElementInQueue(int value)
{
  if (!gQueue)
  {
    gQueue = (QUEUE*)malloc(sizeof(QUEUE));

    if (!gQueue)
      return NOT_ENOUGH_MEMORY;

    gQueue->ptrToNext = gQueue->ptrToPrev = gQueue;
    gQueue->value = value;
    return 0;
  }
  QUEUE* node = (QUEUE*)malloc(sizeof(QUEUE));
  if (!node)
    return NOT_ENOUGH_MEMORY;

  node->value = value;
  node->ptrToPrev = gQueue->ptrToPrev;
  node->ptrToNext = gQueue;
  gQueue->ptrToPrev->ptrToNext = node;
  gQueue->ptrToPrev = node;
  gQueue = node;

  return 0;
}

int popElement()
{
  if (!gQueue)
    return EMPTY_QUEUE;
  int a;
  if (gQueue->ptrToNext == gQueue)
  {
    a = gQueue->value;
    free(gQueue);
    gQueue = NULL;
    return a;
  }

  QUEUE* node = gQueue->ptrToPrev;
  node->ptrToPrev->ptrToNext = node->ptrToNext;
  node->ptrToNext->ptrToPrev = node->ptrToPrev;
  a = node->value;
  free(node);
  return a;
}

int readMatrix()
{
  int c, l = 0;
  char strn[10000];

  scanf("%i", &gMatrixSize);

  if (gMatrixSize < 1)
    return INCORRECT_SIZE;

  gM = (int**)malloc(sizeof(int*) * gMatrixSize);
  if (!gM)
    return NOT_ENOUGH_MEMORY;

  for (int i = 0; i < gMatrixSize; i++)
  {
    gM[i] = (int*)calloc(sizeof(int) * gMatrixSize, sizeof(int));
    if (!gM)
      return NOT_ENOUGH_MEMORY;
  }
  int n = 1, k = 1;

  while (k < gMatrixSize)
  {
    k *= 10;
    n++;
  }

  char* str = (char*)malloc(sizeof(char) * (n + 1));
  if (!str)
    return NOT_ENOUGH_MEMORY;

  int  index = 0, mIndexI = 0, mIndexJ = 0, IindexRead = 0;
  while ((c = fgetc(stdin)) != EOF)
  {
    if (!isspace(c))
    {
      str[index] = (char)c;
      index++;
    }
    else
    {
      str[index] = 0;
      index = 0;
      if (IindexRead)
        mIndexJ = atoi(str);
      else
      {
        mIndexI = mIndexJ = atoi(str);
        IindexRead = 1;
      }
      gM[mIndexI][mIndexJ] = gM[mIndexJ][mIndexI] = 1;

      if (c == '\n'||c=='\r')
        IindexRead = 0;
    }
  }
  return 0;
}

int* graphTraversal()
{
  int* usedNodes = (int*)calloc(sizeof(int) * gMatrixSize, sizeof(int));
  int* toPrint = (int*)malloc(sizeof(int) * gMatrixSize);
  int printIndex = 0;
  int number;

  addElementInQueue(0);

  while (gQueue)
  {
    number = popElement();
    if (!usedNodes[number])
    {
      for (int i = 0; i < gMatrixSize; i++)
        if (i != number && gM[number][i])
          addElementInQueue(i);
      toPrint[printIndex] = number;
      usedNodes[number] = 1;
      printIndex++;
    }

    if(!gQueue&&printIndex!=gMatrixSize)
      for(int i = 0;i<gMatrixSize;i++)
        if (!usedNodes[i])
        {
          addElementInQueue(i);
          break;
        }
  }
  return toPrint;
}

int main()
{
  readMatrix();

  int* a = graphTraversal();

  for (int i = 0; i < gMatrixSize; i++)
  {
    printf("%i", a[i]);
    if (i < gMatrixSize-1)
      printf(" ");
  }
  printf("\n");

  return 0;
  
}
