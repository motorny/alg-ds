#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "firstlab.h"


int main(void) {
  elem_t* head;
  int i, a, b = 5, c;
  int arr[15];
  head = CreateHead();

  /*for (i = 1; i <= 15; i++) {
    arr[i-1] = i;
    printf("%i ", arr[i-1]);
  }
  for (i = 0; i < 15; i++) {
    AddElement(head, arr[i]);
  }*/
  AddElement(head, 1);
  DeleteElement(head, 1);
  c = GetElementNum(head, 1);
  printf("%i\n", c);
  
  return 0;
}