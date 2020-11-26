#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LabA.h"

void AddList(list_t* start, list_t* NEW) {
  NEW->prev = start->prev;
  start->prev = NEW;
}

int ReadList(list_t* start) {
  char q[] = { 48 };
  list_t* NEW = (list_t*)calloc(1, sizeof(list_t));

  scanf("%s", &NEW->str);
  AddList(start, NEW);

  if (strcmp(NEW->str, q) == 0) {
    start->prev = NEW->prev;
    free(NEW);
    return 0;
  }
  else
    ReadList(start);
}

list_t* SortTwo(list_t* elem) {

  if (strcmp(elem->str, elem->prev->str) <= 0) {
    if (elem->prev->prev != NULL)
      elem->prev = SortTwo(elem->prev);
    return elem;
  }
  else {
    count++;
    list_t tmp;
    list_t* first;
    first = elem->prev;
    tmp.prev = elem->prev->prev;
    elem->prev->prev = elem;
    elem->prev = tmp.prev;
    if (first->prev->prev != NULL)
      first->prev = SortTwo(first->prev);
    return first;
  }
}

int SortList(list_t* start) {
  count = 0;
  start->prev = SortTwo(start->prev);
  if (count == 0)
    return 0;
  else
    SortList(start);
}

void PrintList(list_t* el) {
  printf("%s\n", el->str);
  if (el->prev != NULL)
    PrintList(el->prev);
}