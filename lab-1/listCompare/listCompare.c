#include <stdio.h>
#include <stdlib.h>
#include "..\list.h"
#include "..\skipList.h"
#include <Windows.h>
#include <crtdbg.h>
#pragma warning(disable:4996)

int main(void) {
  int maxRandKey, skipListHight, repeatCount, insertCount, findCount, deleteCount;
  int i, j;
  list* List;
  skipList* sList;
  LARGE_INTEGER freq;
  LARGE_INTEGER startTime;
  LARGE_INTEGER endTime;
  double skipList_time;
  double list_time;
  printf("maxRandKey:\n");
  scanf("%i", &maxRandKey);
  if (maxRandKey == 0) {
    maxRandKey = 1000;
  }
  printf("skipListHight:\n");
  scanf("%i", &skipListHight);
  if (skipListHight == 0) {
    skipListHight = 8;
  }
  printf("repeatCount:\n");
  scanf("%i", &repeatCount);
  if (repeatCount == 0) {
    repeatCount = 100;
  }
  printf("insertCount:\n");
  scanf("%i", &insertCount);
  if (insertCount == 0) {
    insertCount = 50000;
  }
  printf("findCount:\n");
  scanf("%i", &findCount);
  if (findCount == 0) {
    findCount = 50000;
  }
  printf("deleteCount:\n");
  scanf("%i", &deleteCount);
  if (deleteCount == 0) {
    deleteCount = 50000;
  }
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&startTime);
  for (j = 0; j < repeatCount; j++)
  {
    sList = skipList_Get(skipListHight);
    for (i = 0; i < insertCount; i++) {
      skipList_Add(sList, NULL, rand() % maxRandKey);
    }
    for (i = 0; i < findCount; i++) {
      skipList_Find(sList, rand() % maxRandKey);
    }
    for (i = 0; i < deleteCount; i++) {
      skipList_DeleteByKey(sList, rand() % maxRandKey);
    }
    skipList_Free(sList);
  }
  QueryPerformanceCounter(&endTime);
  skipList_time = (endTime.QuadPart - startTime.QuadPart) / ((double)freq.QuadPart) / repeatCount;
  printf("%lf\n", skipList_time);

  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&startTime);
  List = list_Get();
  for (i = 0; i < insertCount; i++) {
    list_Add(List, NULL, rand() % maxRandKey);
  }
  for (i = 0; i < findCount; i++) {
    list_Find(List, rand() % maxRandKey);
  }
  for (i = 0; i < deleteCount; i++) {
    list_DeleteByKey(List, rand() % maxRandKey);
  }
  list_Free(List);

  QueryPerformanceCounter(&endTime);
  list_time = (endTime.QuadPart - startTime.QuadPart) / ((double)freq.QuadPart);
  printf("%lf\n", list_time);
}
