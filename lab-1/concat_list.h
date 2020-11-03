#pragma once
#ifndef CONCAT_LIST_H
#define CONCAT_LIST_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
	NO_ERRORS, //0
	NO_MEMORY_ERROR,
	EMPTY_LIST_ERROR,
	END_OF_STREAM,
}error_t;

typedef char elem_t;

typedef struct node_t {
	elem_t* data;
	struct node_t* next;
}node_t;

typedef struct {
	node_t* head;
	node_t* tail;
} list_t;

void Push(char* string, list_t* list, error_t* err);

char* ReadStr(FILE* stream, error_t* err);

void CreateList(list_t* list, int* len, error_t* err);

void DestoyList(list_t* list, error_t* err);

char* Concat(list_t* list, int* len, error_t* err);

void PrintError(error_t* err);

#endif



