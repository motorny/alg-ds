#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 50

typedef struct MyList
{
  struct MyList* ptrToNext;
  char word[MAX_WORD_SIZE];
  int keyDigit;
}LST;

#define NOT_ENOUGH_MEMORY       1
#define NULLPTR_STRING_ON_INPUT 2
#define MATCH_OF_KEY_NUMBERS    3 
#define FILE_CANNOT_BE_OPENED   4
