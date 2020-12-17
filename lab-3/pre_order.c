#include "pre_order.h"

bool_t GraphInit(int** matrix, int* size){
  char sym = 0;
  char input[MAX_SIZE];
  int i = 0, dot1 = 0, dot2 = 0;

  sym = getchar();
  if(sym == EOF)
    return FAIL;

  while(sym != '\n'){
    if (sym == EOF)
      return SUCCESS;
    input[i] = sym;
    i++;
    sym = getchar();
  }
  input[i] = '\0';

  *size = atoi(input);

  if(*size < 1)
    return FAIL;

  *matrix = (int*)malloc(sizeof(int) * (*size) * (*size));
  if(*matrix == NULL)
    return FAIL;

  for (i = 0; i < ((*size) * (*size)); i++)
    (*matrix)[i] = 0;

  if (*size == 1)
    return SUCCESS;

  sym = getchar();
  for (i = 0; sym != EOF;){
    if(sym == ' '){
      input[i] = '\0';
      dot1 = atoi(input);
      i = 0;
    }
    else if(sym == '\n'){
      input[i] = '\0';
      dot2 = atoi(input);
      i = 0;
      (*matrix)[dot1 + (*size) * dot2] = 1;
      (*matrix)[dot1 * (*size) + dot2] = 1;
    }
    else{
      input[i] = sym;
      i++;
    }
    sym = getchar();
  }
  return SUCCESS;
}

int DepthFirstSearch(int ifFirstCycle, int size, int* matrix, int* dotState, int currDot, int** result) {

  int nextDot;
  static int i = 0;

  if ((currDot < 0) || (currDot >= size))
    return FAIL;

  if (ifFirstCycle == 1){
    i = 0;
    memset(dotState, FACED, size * (sizeof(int)));
  }

  if (dotState[currDot] != NOT_FACED){
    (*result)[i++] = currDot;
    dotState[currDot] = NOT_FACED;
  }

  for (nextDot = 0; nextDot < size; nextDot++){
    if ((dotState[nextDot] == FACED) && (matrix[currDot * size + nextDot] == 1) && (currDot != nextDot)) {
      DepthFirstSearch(0, size, matrix, dotState, nextDot, result);
    }
  }

  return SUCCESS;
}