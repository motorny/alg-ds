#pragma once
#ifndef AATREE_H
#define AATREE_H

#define FAIL -1
#define SUCCESS 1
#define Min(a,b) (((a) < (b)) ? (a) : (b)) 

typedef enum
{
	False,
	True
} Bool;

typedef struct NODE
{
	int data;
	int level;
	struct NODE* l;
	struct NODE* r;
} Node;
int insert(Node** head, const int elem);
void Print(Node** head);
int findNode(Node* head, const int elem);
void removeNode(Node** head, int elem);
void treeFree(Node* head);
#endif //AATREE_H 