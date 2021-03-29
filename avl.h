#ifndef AVL_TREE
#define AVL_TREE

typedef struct node {
  int key;
  unsigned int height;
  struct node* right;
  struct node* left;
} node_t;

int GetBalanceFactor(node_t* p);

void FixHeight(node_t* p);

unsigned int Height(node_t* p);

node_t* RotateRight(node_t* p);

node_t* RotateLeft(node_t* q);

node_t* Balance(node_t* p);

node_t* AddVertex(node_t* p, int k);

node_t* FindMin(node_t* p);

node_t* RemoveMin(node_t* p);

node_t* DeleteVertex(node_t* p, int k);

node_t* FindVertex(node_t* p, int k);

#endif