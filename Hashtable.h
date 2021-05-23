#pragma once
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define FREE 2
#define NOTFREE 4
#define DELETED 3
#define SIZE 10000

#define TRUE 1
#define FALSE 0

typedef struct {
	char* str;
	int status;
} Hashtable;

Hashtable* CreateHashT();

int Add(Hashtable* table, char* str);

int Delete(Hashtable* table, char* str);

int Find(Hashtable* table, char* str);