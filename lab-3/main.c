#include "pre_order.h"

int main(void){
  int size = 0;
  int *matrix = NULL, *result = NULL, *state = NULL;
  int index = 0;
  int i = 0;


  if (GraphInit(&matrix, &size) != SUCCESS){
    if (matrix != NULL)
      free(matrix);
    return 0;
  }

  state = (int*)malloc(sizeof(int) * size);
  if (state == NULL) {
    if (matrix != NULL)
      free(matrix);
    return 0;
  }
  memset(state, NOT_FACED, size * (sizeof(int)));

  result = (int*)malloc(sizeof(int) * size);
  if (result == NULL) {
    if (matrix != NULL)
      free(matrix);
    return 0;
  }
   
  if ((matrix) && (state) && (size > 0))
    if(DepthFirstSearch(1, size, matrix, state, 0, &result) == SUCCESS)
      for (i = 0; i < size; i++)
        printf("%d ", result[i]);

  free(matrix);
  free(state);
  free(result);
  return 0;
}
