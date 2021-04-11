#ifndef TREE23_H
#define TREE23_H

#define MEMORY_ALLOCATED_ERROR -1;
#define SUCCESS 0

typedef enum
{
	FALSE,
	TRUE
} BOOL;

typedef struct node node;

struct node
{
	int countKey;
	int key[3];
	node* parent;
	node* son[4];
};

int insert(node** tree, int elem);
void printTree(node* tree);
BOOL find(node* tree, int elem);
node* delKey(node* tree, int elem);
void treeFree(node* tree);

#endif // !TREE23_H
