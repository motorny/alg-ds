#pragma once
#include <stdio.h>
#include <stdlib.h>

#define FILE_NOT_FOUND 1
#define NOT_ENOUGHT_MEMORY NULL

typedef enum check_t {
  NOTFACED = 0,
  FACED = 1
} check_t;

typedef struct word_t{
  char* word;
  int size;
  struct word_t* next;
}word_t;

#ifdef __cplusplus
extern "C" {
#endif

  word_t* Initialize(FILE* fp);
  word_t* SortWords(word_t* first);
  void PrintWords(word_t* first);
  void MemoryFree(word_t* first);

#ifdef __cplusplus
}
#endif
