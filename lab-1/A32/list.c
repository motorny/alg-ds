#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

//initialize first node
static void InitBucket(List_t** head) {
  *head = (List_t*)malloc(sizeof(List_t));
  assert(*head != NULL);
}

List_t* Add2List(List_t* head, char* word) {
  List_t* cur = head;
  if (head == NULL) {//initialization
    InitBucket(&head);
    head->data = word;
    head->next = NULL;
  }
  else {//add new element
    while (cur->next != NULL)
      cur = cur->next;
    cur->next = (List_t*)malloc(sizeof(List_t));
    assert(cur->next != NULL);
    if (cur->next) {
      cur->next->data = word;
      cur->next->next = NULL;
    }
  }
  return head;
}

static void DestroyNode(List_t* buckets[], int column) {
  List_t* cur;
  cur = buckets[column];
  buckets[column] = buckets[column]->next;
  free(cur->data);
  free(cur);
}

static int FindColumns(List_t* buckets1[], List_t* buckets2[], int* L, int* R, int n) {
  int column1 = 0, column2;
  while (buckets1[column1] != NULL && column1 < n) {
    column2 = 0;
    while (buckets2[column2] != NULL && column2 < n) {
      if (strcmp(buckets1[column1]->data, buckets2[column2]->data) == 0) {//if names of the columns are the same 
        *L = column1;
        *R = column2;
        return 1;
      }
      else
        column2++;
    }
    column1++;
  }
  return 0;
}

static List_t* Copy2List(List_t* buckets, List_t* bucketsMerge) {
  char* buf = (char*)malloc(21 * sizeof(char*));
  assert(buf != NULL);
  strcpy(buf, buckets->data);
  return Add2List(bucketsMerge, buf);
}

int Table2List(FILE* table, List_t* buckets[], int n) {//transform exel file to list 
  int column = 0, count = 0;
  char* word = (char*)malloc(21 * sizeof(char*));
  char str;
  while ((str = (char)fgetc(table)) != (EOF)) {
    if (column >= n)
      return 0;
    switch (str) {
      case ';'://if next column
        if(word)
          word[count] = '\0';
        buckets[column] = Add2List(buckets[column], word);
        word = (char*)malloc(21 * sizeof(char*));
        column++;
        count = 0;
        break;
      case '\n'://if next line
        if (word)
          word[count] = '\0';
        buckets[column] = Add2List(buckets[column], word);
        word = (char*)malloc(21 * sizeof(char*));
        column = 0;
        count = 0;
        break;
      default://if we read text
        if (word)
          word[count++] = str;
        break;
    }
  }
  free(word);
  return 1;
}

int CreateBucketMerge(List_t* buckets1[], List_t* buckets2[], List_t* bucketsMerge[], int n) {

  List_t* cur;
  int leftColumn, rightColumn;

  if (FindColumns(buckets1, buckets2, &leftColumn, &rightColumn, n) == 0)
    return 0;

  //for start  add to bucketMerge names of columns exept the same
  int columnTables = 0, columnMerge = 0;
  for (columnTables = 0; columnTables < n && buckets1[columnTables] != NULL; columnTables++) {
    bucketsMerge[columnMerge] = Copy2List(buckets1[columnTables], bucketsMerge[columnMerge]);
    DestroyNode(buckets1, columnTables);
    columnMerge++;
  }
  for (columnTables = 0; columnTables < n && buckets2[columnTables] != NULL; columnTables++) {
    if (columnTables != rightColumn)  //same columns
      bucketsMerge[columnMerge] = Copy2List(buckets2[columnTables], bucketsMerge[columnMerge]);
    DestroyNode(buckets2, columnTables);
    columnMerge++;
  }

  //merge buckets1 and buckets2
  while (buckets1[leftColumn] != NULL && buckets2[rightColumn] != NULL) {
    if (atoi(buckets1[leftColumn]->data) < atoi(buckets2[rightColumn]->data))
      buckets1[leftColumn] = buckets1[leftColumn]->next;
    else
      if (atoi(buckets1[leftColumn]->data) == atoi(buckets2[rightColumn]->data)) {
        columnMerge = 0;
        for (columnTables = 0; columnTables < n && buckets1[columnTables] != NULL; columnTables++) {
          bucketsMerge[columnMerge] = Copy2List(buckets1[columnTables], bucketsMerge[columnMerge]);
          DestroyNode(buckets1, columnTables);
          columnMerge++;
        }
        for (columnTables = 0; columnTables < n && buckets2[columnTables] != NULL; columnTables++) {
          if (columnTables != rightColumn)//same columns
            bucketsMerge[columnMerge] = Copy2List(buckets2[columnTables], bucketsMerge[columnMerge]);
          columnMerge++;
        }
      }
      else
        if (atoi(buckets1[leftColumn]->data) > atoi(buckets2[rightColumn]->data))
          for (columnTables = 0; columnTables < n && buckets2[columnTables] != NULL; columnTables++)
            DestroyNode(buckets2, columnTables);
  }
  for (columnTables = 0; columnTables < n; columnTables++) {
    if (buckets2[columnTables] == NULL)
      break;
    cur = buckets2[columnTables];
    if (cur != NULL)
      free(cur->data);
    free(cur);
  }
  return 1;
}

void List2Table(List_t* buckets[], FILE* table, int n) {
  while (1) {
    for (int column = 0; column < 2 * n && buckets[column] != NULL; column++) {
      List_t* cur = buckets[column];
      fprintf(table, "%s;", cur->data);
      DestroyNode(buckets, column);
    }
    fprintf(table, "\n");
    if (buckets[0] == NULL)
      break;
  }
}