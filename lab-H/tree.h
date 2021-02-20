#ifndef TREE_H
#define TREE_H

#define FAILED_TO_ALLOCATE_MEMORY -1
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
	struct NODE* left;
	struct NODE* right;
} Node;

int insert(Node** head, const int elem);
void printTree(Node** head);
int findNode(Node* head, const int elem);
void removeNode(Node** head, int elem);
void treeFree(Node* head);

#endif // !TREE_H

