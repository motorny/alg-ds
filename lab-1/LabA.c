#include "Header.h"

char* FileReading(FILE* filename) {
  char arr[SIZE];
  if (fgets(arr, SIZE, filename))
    return arr;
  else
    return NULL;
}

//Printing List
void Print(table_t* table) {

  if (table == NULL)
    return;

  elem_t* elem = table->head;
  while (elem != NULL) {
    printf("%i | %s \n", elem->line->id, elem->line->name);
    elem = elem->next;
  }
  printf("\n\n");
}

//Building table
table_t* BuildTable(FILE* filename) {

  if (!filename)
    return NULL;
  int IsRead = 0; //bool, shows have we read from file or not
  int i = 0, num = 0, k = 0, j = 0;
  char* arr = NULL;
  table_t* NewTable = (table_t*)malloc(sizeof(table_t));
  elem_t* elem = (elem_t*)malloc(sizeof(elem_t)), * help = elem, * prev = NULL;
  line_t* line = (line_t*)malloc(sizeof(line_t));
  elem->next = NULL;
  elem->line = line;
  NewTable->head = elem;

  while ((arr = FileReading(filename)) != NULL) {

    //putting data to strings
    for (j = 0; j < 40; ++j)
      elem->line->name[j] = arr[j];

    IsRead = 1; //at least 1 string was read
    i = 0;
    elem->line->id = 0;
    //pushing number
    while (elem->line->name[i] >= '0' && elem->line->name[i] <= '9') {
      elem->line->id = elem->line->id * 10 + (int)(elem->line->name[i] - '0');
      i++;
    }
    for (k = 0; k < 30; ++k) {
      elem->line->name[k] = elem->line->name[k + (i + 1)];
      if (elem->line->name[k + i] == '\n') {
        elem->line->name[k-1] = '\0';
        break;
      }
    }
    prev = elem;
    elem = (elem_t*)malloc(sizeof(elem_t));
    line = (line_t*)malloc(sizeof(line_t));
    help->next = elem;
    help = elem;
    elem->line = line;
  }

  //if something was read
  if (IsRead) {
    //one realloc was not necessary
    free(elem);
    free(line);

    if (prev)
      prev->next = NULL;

    return NewTable;
  }
  else {
    free(elem);
    free(line);
    free(NewTable);
    return NULL;

  }
}

//Merging two sorted tables
table_t* MergeTable(table_t* A, table_t* B) {

  if (A == NULL || B == NULL)
    return NULL;
  
  table_t* NewTable = (table_t*)malloc(sizeof(table_t));
  elem_t* help = NULL, *prevA = NULL, *prevB = NULL;
  int k=0; //bool, shows by which list we are moving on
  

  NewTable->head = (A->head->line->id <= B->head->line->id ? A->head : B->head);
  help = NewTable->head;

  if (NewTable->head == A->head)
    k = 0; //head on A, so going on A
  else
    k = 1; //going on B

  prevA = A->head;
  prevB = B->head;

  while (A->head != NULL && B->head != NULL) {

    // k=0 - going on A
    // k=1 - going on B

    //A less than B
    if (A->head->line->id <= B->head->line->id) {
      
      if (k == 0) {
        prevA = A->head;
        A->head = A->head->next;
      }

      else if(k==1) {
        prevB->next = A->head;
        prevA = A->head;
        A->head = A->head->next;
        k = 0;
      }

    }

    //A bigger than B
    else {

      if (k==1) {
        prevB = B->head;
        B->head = B->head->next;
      }

      else if (k == 0) {
        prevA->next = B->head;
        prevB = B->head;
        B->head = B->head->next;
        k = 1;
      }


    }

  }

  if (A->head == NULL)
    prevA->next = B->head;

  else
    prevB->next= A->head;

  free(A);
  A = NULL;
  free(B);
  B = NULL;
  return NewTable;
}

void DestroyTable(table_t* table) {
  if (table == NULL)
    return;

  elem_t* ptr = table->head, *ptr1 = NULL;

  do {
    ptr1 = ptr->next;
    free(ptr->line);
    free(ptr);
    ptr = ptr1;

  } while (ptr1 != NULL);
  free(table);
}

