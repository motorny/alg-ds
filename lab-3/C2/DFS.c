#include "DFS.h"

static void getStrBeforeSlashN(char* str, char**newStr, char** newEnd) {
  int i = 0;

  while (*str != '\n' && *str != 0 && i < 99) {
    (*newStr)[i++] = *str;
    str++;
  }
  if (*str == '\n' && i < 99) {
    (*newStr)[i++] = '\n';
    str++;
  }
  *newEnd = str;
  (*newStr)[i] = 0;

  return;
}

static int isNumber(char c) {
  if (c >= '0' && c <= '9')
    return TRUE;
  return FALSE;
}

int ReadGraphInfo(int* graphSize, int** graphMatrix) {
  int i, firstNode, secondNode;
  char str[100],
    * strPtr, * endNum;
  FILE* F = stdin;

  fgets(str, 100, F);
  strPtr = str;
  *graphSize = (int)strtod(strPtr, &endNum);
  if (*graphSize <= 0)
    return FALSE;

  *graphMatrix = (int*)malloc((*graphSize) * (*graphSize) * sizeof(int));
  if (*graphMatrix == NULL)
    return FALSE;
  memset(*graphMatrix, 0, (*graphSize) * (*graphSize) * sizeof(int));

  if (*graphSize == 1)
    return TRUE;

  do {
    i = 0;
    fgets(str, 100, F);

    if (str[0] != '\0') {
      strPtr = str;

      while (isspace(*strPtr))
        strPtr++;
      if (feof(F))
        return TRUE;
      if (isNumber(*strPtr) == 0)
        return FALSE;
      firstNode = (int)strtod(strPtr, &endNum);
      strPtr = endNum;

      while (isspace(*strPtr))
        strPtr++;
      if (isNumber(*strPtr) == 0)
        return FALSE;
      secondNode = (int)strtod(strPtr, &endNum);
      strPtr = endNum;

      (*graphMatrix)[firstNode + (*graphSize) * secondNode] =
        (*graphMatrix)[secondNode + (*graphSize) * firstNode] = 1;

      while (isspace(*strPtr))
        strPtr++;
      if (feof(F))
        return TRUE;
    }
  } while (TRUE);
}

int ParseStrLikeSTDIN(char* str, int* graphSize, int** graphMatrix) {
  int i, firstNode, secondNode;
  char * strPtr, * endNum;

  while (isspace(*str))
    str++;
  if (*str == '*')
    return FALSE;
  strPtr = (char*)malloc(250);
  getStrBeforeSlashN(str, &strPtr, &endNum);
  str = endNum;

  *graphSize = (int)strtod(strPtr, &endNum);
  
  if (*graphSize <= 0)
    return FALSE;

  *graphMatrix = (int*)malloc((*graphSize) * (*graphSize) * sizeof(int));
  if (*graphMatrix == NULL)
    return FALSE;
  memset(*graphMatrix, 0, (*graphSize) * (*graphSize) * sizeof(int));

  if (*graphSize == 1)
    return TRUE;

  do {
    i = 0;
    getStrBeforeSlashN(str, &strPtr, &endNum);
    str = endNum;

    if (strPtr[0] != '\0') {
      while (isspace(*strPtr))
        strPtr++;
      if (*strPtr == '*')
        return TRUE;
      
      if (isNumber(*strPtr) == 0)
        return FALSE;
      firstNode = (int)strtod(strPtr, &endNum);
      strPtr = endNum;

      while (isspace(*strPtr))
        strPtr++;
      if (isNumber(*strPtr) == 0)
        return FALSE;
      secondNode = (int)strtod(strPtr, &endNum);
      strPtr = endNum;

      (*graphMatrix)[firstNode + (*graphSize) * secondNode] =
        (*graphMatrix)[secondNode + (*graphSize) * firstNode] = 1;

      while (isspace(*strPtr))
        strPtr++;
      if (*strPtr == '*')
        return TRUE;
    }
  } while (TRUE);

  return TRUE;
}

void PrintMatrix(int graphSize, int* graphMatrix) {
  if (graphMatrix == NULL || graphSize < 1)
    return;

  for (int i = 0; i < graphSize; i++) {
    for (int j = 0; j < graphSize; j++)
      printf("%i ", graphMatrix[i * graphSize + j]);
    printf("\n");
  }
}

int DFS(int graphSize, int* graphMatrix, int* wasInTheseNodes, int currentNode, int** answer) {
  int nextNode;
  static int answerPos = 0;

  if (graphMatrix == NULL || graphSize < 1 || wasInTheseNodes == NULL || currentNode < 0 || currentNode >= graphSize)
    return FALSE;
  
  if (wasInTheseNodes[currentNode] != 1) {
    (*answer)[answerPos++] = currentNode;
    wasInTheseNodes[currentNode] = 1;
  }
  for (nextNode = 0; nextNode < graphSize; nextNode++) {
    if (wasInTheseNodes[nextNode] == 0 && graphMatrix[currentNode * graphSize + nextNode] == 1 && currentNode != nextNode)
      DFS(graphSize, graphMatrix, wasInTheseNodes, nextNode, answer);
  }
  return TRUE;
}

void PrintDFS(int* answer, int size) {
  for (int i = 0; i < size; i++)
    printf("%i ", answer[i]);
}

void FreeDFSPointers(int* answer, int* graphMatrix, int* wasTheseNodes) {
  free(answer);
  free(graphMatrix);
  free(wasTheseNodes);
}