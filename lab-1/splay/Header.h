#pragma once
typedef enum {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
}way_t;

typedef struct node_t {
    int key;
    struct node_t* left;
    struct node_t* parent;
    struct node_t* right;
} node_t;

node_t* futher(node_t* tree);

node_t* grandfuther(node_t* tree);

node_t* Rotateleft(node_t* tree);

node_t* Rotateright(node_t* tree);

node_t* splay(node_t* tree);

node_t* Findnode(node_t* tree, int num);

void Add(node_t** tree, int num);

void Delete(node_t** tree, node_t* vertex);

