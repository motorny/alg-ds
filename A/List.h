#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node_t;

Node_t* newNode(int data);

Node_t* insert(Node_t* last, int data);

Node_t* pop(Node_t* last);

void freeList(Node_t* last);

#endif // LIST_H