#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define SIZE 40
#pragma warning (disable:4996)

//id-sorting
typedef struct {
  int id;
  char name[40];
} line_t;

//list
typedef struct elem_t {
  line_t* line;
  struct elem_t* next;
} elem_t;

//pointer to first elem == pointer to table
typedef struct {
  elem_t* head;
}table_t;

char* FileReading(FILE* filename);
void Print(table_t* table);
table_t* BuildTable(FILE* filename);
table_t* MergeTable(table_t* A, table_t* B);
void DestroyTable(table_t* table);
#endif