#ifndef ALG_DS_23TREE_H
#define ALG_DS_23TREE_H

typedef struct Node {
    struct Node* left, * middle, * right; // children

    int lval, rval; // values in the node

    struct Node* lsib, * rsib;

    int max_child;
} Node_t;

#define EMPTY (-1)

void freeNode(Node_t* node);

void freeTree(Node_t* root);

Node_t* newNode(int val);

Node_t* insertTerminate(Node_t* root, int val);

Node_t* insertNode(Node_t* root, int val);

Node_t* deleteTerminal(Node_t* root, int val);

Node_t* deleteNode(Node_t* root, int val);

Node_t* _deleteNode(Node_t* root, int val);

Node_t* findNode(Node_t* root, int val);

void printTree(Node_t* root);


#endif //ALG_DS_23TREE_H
