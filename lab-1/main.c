#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int compare(const data_t* a, const data_t* b) {
  if (a->temperature > b->temperature)
    return 1;
  else if (a->temperature < b->temperature)
    return -1;
  else {
    if (a->date.year > b->date.year)
      return 1;
    else if (a->date.year < b->date.year)
      return -1;
    else {
      if (a->date.month > b->date.month)
        return 1;
      else if (a->date.month < b->date.month)
        return -1;
      else {
        if (a->date.day > b->date.day)
          return 1;
        else if (a->date.day < b->date.day)
          return -1;
        else
          return 0;
      }
    }
  }
}

void ReadData(char* path, list_t* list) {
  data_t data;
  FILE* f;
  char buffer[20];
  char* tmp;
  fopen_s(&f, path, "r");
  while (!feof(f)) {
    fgets(buffer, 20, f);
    data.date.day = strtol(buffer, &tmp, 10);
    data.date.month = strtol(tmp + 1, &tmp, 10);
    data.date.year = strtol(tmp + 1, &tmp, 10);
    data.temperature = strtod(tmp + 1, NULL);
    AddToList(list, &data, &compare);
  }
}

void PrintNegList(list_t* list) {
  node_t* p = list->head;
  while (p != NULL) {
    if (p->data.temperature < 0)
      printf("Date: %i.%i.%i Temperature: %lf\n", p->data.date.day, p->data.date.month, p->data.date.year, p->data.temperature);
    p = p->next;
  }
  printf("\n");
}

void PrintAllList(list_t* list) {
  node_t* p = list->head;
  while (p != NULL) {
    printf("Date: %i.%i.%i Temperature: %lf\n", p->data.date.day, p->data.date.month, p->data.date.year, p->data.temperature);
    p = p->next;
  }
  printf("\n");
}

int IsInList(list_t* list, double num) {
  node_t* p = list->head;
  while (p != NULL) {
    if (p->data.temperature == num)
      return 1;
    p = p->next;
  }
  return 0;
}

int main() {
  double num;
  list_t* lst = CreateList();

  // Task 1
  ReadData("data.txt", lst);
  printf("All list:\n");
  PrintAllList(lst);

  // Task 2
  printf("With negative temperature:\n");
  PrintNegList(lst);


  // Task 3
  printf("Check number:\n");
  scanf("%lf", &num);
  IsInList(lst, num) ? printf("%lf is in the list\n", num) : printf("%lf is not in the list\n", num);

  DeleteList(lst);

  return 0;
}