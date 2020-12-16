#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#pragma warining(disable:4996)

typedef struct node_t{
	int key;
	int data;
	int placeInOrder;
	node_t* left;
	node_t* right;
} node_t;

typedef node_t tree_t ;

tree_t* InitTree(int key){
	tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
	if(tree==NULL){
		return NULL;
	}
	tree->key = key;
	tree->data = 0;
	tree->left=NULL;
	tree->right=NULL;
	return tree;
}

void Add(tree_t** tree, int key){
	if(tree==NULL){
		return;
	}
	if(*(tree)==NULL){
		*(tree)=InitTree(key);
	}
	if(key<(*(tree))->key){
		Add(&((*(tree))->left), key);
	}
	else if(key>(*(tree))->key){
		Add(&((*(tree))->right), key);
	}
}

tree_t* getMax(tree_t* tree)
{
	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	return tree;
}

void DeleteNode(tree_t** tree, int key)
{
	if(tree==NULL){
		return;
	}
	if ((*tree) == NULL)
	{
		return;
	}
	if (key < (*tree)->key)
	{
		DeleteNode(&((*tree)->left), key);
	}
	else if (key > (*tree)->key)
		{
			DeleteNode(&((*tree)->right), key);
		}
	else if ((*tree)->left == NULL && (*tree)->right == NULL)
		{
			(*tree) = NULL;
		}
	else if ((*tree)->left != NULL && (*tree)->right == NULL)
		{
			(*tree) = (*tree)->left;
		}
		else
		{
			if ((*tree)->left == NULL && (*tree)->right != NULL)
			{
				(*tree) = (*tree)->right;
			}
			else
			{
				tree_t* max = getMax((*tree)->left);
				(*tree)->key = max->key;
				DeleteNode(&((*tree)->left), max->key);
			}
		}	
}

int FindbyKey(tree_t* tree, int key){
	node_t* node = tree;
	if(tree==NULL){
		return 0;
	}
	while(node!=NULL){
		if(node->key==key){
			return 1;
		}
		if(key<node->key){
			node=node->left;
		}
		else if(key>node->key){
			node=node->right;
		}
	}
	return 0;
}

int IsNum(char a) {
	if (a >= '0' && a <= '9') return 1;
	else return 0;
}

int isspace(char a){
	if(a==' '){
		return 1;
	}
	return 0;
}

int strToNum(char* str) {
	int i = 0;
	int num = 0;
	while (IsNum(str[i])) {
		num = num * 10 + str[i] - '0';
		i++;
	}
	return num;
}

void GetCommands(tree_t** tree)
{
	char c, operation, number[20];
	int index = 0, key;

	c = getchar();
	while (c != EOF)
	{
		if(isspace(c)){
			while (isspace(c))
		{
			c = getchar();
		}
		}
		operation = c;
		c = getchar();
		while (isspace(c))
		{
			c = getchar();
		}
		while (IsNum(c))
		{
			number[index++] = c;
			c = getchar();
		}
		number[index] = 0;
		key = strToNum(number);
		index = 0;
		switch (operation)
		{
		case 'a':
		{
			Add(tree, key);
			break;
		}
		case 'r':
		{
			DeleteNode(tree, key);
			break;
		}
		case 'f':
		{
			if (FindbyKey(*tree, key))
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
			break;
		}
		}
		if (c == '\n')
		{
			c = getchar();
		}
	}
}

void DestroyTree(tree_t* tree)
{
	if (tree != NULL)
	{
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}
}

void PrintTree(tree_t* tree) {
	if(tree){
		printf("%d ", tree->placeInOrder);
		PrintTree(tree->left);
		PrintTree(tree->right);
	}
}

int CountPlaceInOrder(tree_t* tree, int n){
	if(tree->left==NULL && tree->right==NULL){
		tree->placeInOrder=n;
		return n;
	}
	if(tree->left!=NULL){
		n=CountPlaceInOrder(tree->left, n)+1;
	}
	tree->placeInOrder=n;
	if(tree->right!=NULL){
		n=CountPlaceInOrder(tree->right, n+1);
	}
	return n;
}

int FindKLeast(tree_t* tree, int k){
	node_t* node = tree;
	if(tree==NULL){
		return 0;
	}
	while(node!=NULL){
		if(node->placeInOrder==k){
			return node->key;
		}
		if(k<node->placeInOrder){
			node=node->left;
		}
		else if(k>node->placeInOrder){
			node=node->right;
		}
	}
	return -1;
}

int main(void){
	int key;
	tree_t* tree = NULL;
	GetCommands(&tree);
	CountPlaceInOrder(tree, 0);
	scanf("%d", &key);
	key=FindKLeast(tree, key);
	if(key<0){
		printf("No element with such number\n");
	}
	else printf("%d", key);
	DestroyTree(tree);
	return 0;
}

#ifdef __cplusplus
}
#endif
