#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef char* str; // string || ptr to first letter
typedef str* strPtr; // strPtr == ptr to first string

strPtr ParseString(char* string, char* separator, int ElemCount);

int StrCpyN(char* destination, char* origin, int N); // copy first N chars
char* FindSubstr(char* substr, char* origin);
int IsSubstrHere(char* substr, char* origin); 
int strlen(char* str); // length of string 
void FillPtrStr(strPtr ptr, char* content, int count);
