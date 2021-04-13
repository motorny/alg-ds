#pragma once

#define OK 1
#define m 2 // degree of tree
#define NOT_FOUND -1
#define ERR -2

typedef enum {
    FALSE,
    TRUE,
} flag_t;



typedef struct node_t {
    int key[2 * m - 1];
    int n;  //number of node keys
    flag_t Isleaf;
    struct node_t* kids[2 * m];
} node_t;

typedef struct tree_t {
    struct node_t* root;
}tree_t;

//

node_t* InitNewNode();
flag_t FindKey(node_t* tree, int key);
int Split(node_t* node, int index);
void Nonfull_Insert(tree_t* tree, int k);
node_t* Insert(node_t* root, int key);
int Positiontodelete(int key, int* keys, int n);
int Remove(node_t* tree, int key);
void DeleteKey(int key);
void Print(tree_t* tree, int h);
