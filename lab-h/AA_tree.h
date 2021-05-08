#pragma once


typedef struct aatree_t {
	int data;
	int level;
	struct aatree_t* right;
	struct aatree_t* left;
}aatree_t;

typedef enum {
	FALSE,
	TRUE,
}bool_t;

typedef enum {
	NO_ERRORS,
	NO_MEMORY_ALLOCATED,
}error_t;

int Insert(aatree_t** head, const int elemToInsert);

int FindNode(aatree_t* head, const int elemToFind);

void DeleteNode(aatree_t** head, int elemToDelete);

void FreeTree(aatree_t* head);

void PrintTree(aatree_t** head);