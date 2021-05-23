#pragma once

typedef struct Node {
	int key;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
} Node_t;

Node_t *Splay(Node_t *&);

Node_t *Insert(Node_t *, int);

Node_t *Search(Node_t *, int);

Node_t *Delete(Node_t *, int);

void FreeTree(Node_t *);

void Left(Node_t &);

void Right(Node_t &);
