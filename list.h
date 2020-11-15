#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_DATE_SYMB 11
#define MAX_NAME_SYMB 40
#define END_OF_LIST NULL

typedef struct Node {
	char date[MAX_DATE_SYMB];
	char name[MAX_NAME_SYMB];
	unsigned int hours;

	struct Node* pPrev;
}Node;

Node* readEntry(Node*,FILE*); //returns head pointer
Node* findPlace(Node* pHead, Node* pItem);
Node* findLastNode(Node* pHead);
void printMoreN(Node* pHead, const int N);
void freeMem(Node* pHead);