#pragma once

typedef int T;

typedef enum { 
    BLACK, RED 
} nodeColor;

typedef struct Node_ {
    struct Node_* left;
    struct Node_* right;
    struct Node_* parent;
    nodeColor color;
    T data;
} Node;

#define ERROR_ALLOC NULL
#define NIL &forLeaves          
static Node forLeaves = { NIL, NIL, 0, BLACK, 0 };

Node* insert(T data, Node** root);

Node* findNode(T data, Node* root);

void deleteD(T data, Node** root);
