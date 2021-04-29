#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 12 
#define DELETED 0
#define NOT_DELETED 1
#define DEFAULT_ADD_VAL 0

typedef struct Node {
	int val;
	int prior;
	int count;
	struct Node* left;
	struct Node* right;
} Node;



Node* InitNode(int val);
int GetCount(Node* p);
void UpdateCount(Node* p);
Node* Merge(Node* l, Node* r);
void Split(int key, Node* root, Node** l, Node** r, int add);
void Insert(int val, int pos, Node** root);
void Print(Node* root);
int Delete(int pos, Node** root);
void Check(int val, Node* root, bool* contains);

void Find(int val, Node* root, Node** result);
void DeleteVal(int val, Node** root, bool* deleted);
void DeleteTree(Node* root);