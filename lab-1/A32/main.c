#pragma warning (disable: 4996)

#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif

#include<stdio.h>
#include<stdlib.h>
#include <crtdbg.h>
#include<assert.h>
#include <Windows.h>
#include <locale.h>
#include "list.h"

#define N 10// how many columns can be in table

int main(void) {
  setlocale(LC_ALL, "RUS");//for work with russian exel

  //exel tables
  FILE* table1, * table2, * tableMerge;

  //massive of lists
  List_t* buckets1[N] = {NULL};
  List_t* buckets2[N] = {NULL};
  List_t* bucketsMerge[2 * N] = {NULL};;

  //open exel files for reading and merging
  table1 = fopen("table1.csv", "r");
  assert(table1 != NULL);
  table2 = fopen("table2.csv", "r");
  assert(table2 != NULL);
  tableMerge = fopen("tableMerge.csv", "w");
  assert(tableMerge != NULL);

  if (Table2List(table1, buckets1, N) == 0 || Table2List(table2, buckets2, N) == 0) {
    fprintf(tableMerge, "To many columns\n");
    return 0;
  }
  if (CreateBucketMerge(buckets1, buckets2, bucketsMerge, N) == 0) {
    fprintf(tableMerge, "Tables need to have same columns\n");
    return 0;
  }
  List2Table(bucketsMerge, tableMerge, N);

  //closing tables
  fclose(table1);
  fclose(table2);
  fclose(tableMerge);

  _CrtDumpMemoryLeaks();
  return 0;
}