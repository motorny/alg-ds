#ifndef LIST_H_INCLUDED__
#define LIST_H_INCLUDED__

#pragma once

#define ERROR_MORE_COLUMNS_THEN_EXPECTED - 2
#define ERROR_WITH_COLUMNS - 1
#define OK 1

//define list and its functions 
typedef struct List {
  char* data;
  struct List* next;
} List_t;

List_t* Add2List(List_t* head, char* word);

int Table2List(FILE* table, List_t* buckets[], int n);

int CreateBucketMerge(List_t* buckets1[], List_t* buckets2[], List_t* bucketsMerge[], int n);

void List2Table(List_t* buckets[], FILE* table, int n);

#endif