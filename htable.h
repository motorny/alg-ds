#pragma once

#define K 1
typedef struct htable {
	char* str;
	int status;
}htable;
#define FREE 0
#define DELETED 2
#define NOTFREE 1

#define SUCCESS 1
#define FAIL -1

htable* hInit(int hSize);
int hFunc(char* str, int size);
int hAdd(htable* h, char elem[], int hSize);
int hFind(htable* h, char elem[], int hSize);
int hDelete(htable* h, char elem[], int hSize);
void tableDelete(htable* h, int hSize);