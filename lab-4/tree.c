#include "tree.h"

int CountHeight(tree_t* tree){
	int hLeft = 0, hRight = 0, height = 0;
	if (!tree) //null son
		return 0;
	else
	{
		if (tree->left == NULL && tree->right == NULL) { //node without sons
			return 0;
		}
		else
		{
			hLeft = CountHeight(tree->left); // t->nl = r1
			hRight = CountHeight(tree->right); // t->nr = r2
			if (hLeft > hRight)
				height = hLeft + 1;
			else
				height = hRight + 1;
			tree->differense = DIFFERENCE(hLeft, hRight);
			tree->height = height;
			return height; //in the end return the height of the whole tree
		}
	}
}

int AddNodeByKey(tree_t** tree, int key){
	int flag = 0;
	if ((*tree) == NULL){
		(*tree) = (tree_t*)malloc(sizeof(tree_t));
		if (!(*tree))
			return ERROR;

		(*tree)->key = key;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		(*tree)->differense = 0;
		(*tree)->height = 0;

		flag = FINISHED;
	}
	else{
		if (key < (*tree)->key){
			flag = AddNodeByKey(&((*tree)->left), key);
			if (flag == FINISHED)
				CountHeight(*tree);
		}
		else{
			if (key > (*tree)->key){
				flag = AddNodeByKey(&((*tree)->right), key);
				if (flag == FINISHED)
					CountHeight(*tree);
			}
			else
				flag = NOT_FINISHED;
		}
	}
	return flag;
}

tree_t* FindByKey(tree_t* tree, int key) {
	if (!tree)
		return NOT_FOUND;
	while (tree != NULL) {
		if (key < tree->key) {
			tree = tree->left;
		}
		else {
			if (key > tree->key) {
				tree = tree->right;
			}
			else
				return tree;
		}
	}
	return NOT_FOUND;
}

int DeleteByKey(tree_t** tree, int key) {
	int flag = NOT_FINISHED;
	if ((*tree) == NULL)
		return NOT_FINISHED; //not found

		if (key < (*tree)->key) {
			flag = DeleteByKey(&((*tree)->left), key);
			if (flag)
				CountHeight(*tree);
		}
		else {
			if (key > (*tree)->key) {
				flag = DeleteByKey(&((*tree)->right), key);
				if (flag)
					CountHeight(*tree);
			}
			else {
				tree_t* temp = *tree;
				if ((*tree)->left == NULL && (*tree)->right == NULL) {
					free(temp);
					(*tree) = NULL;
					flag = FINISHED;
				}
				else if ((*tree)->right == NULL && (*tree)->left != NULL) {
					(*tree) = (*tree)->left;
					free(temp);
					flag = FINISHED;
				}
				else {
					if ((*tree)->left == NULL && (*tree)->right != NULL) {
						(*tree) = (*tree)->right;
						free(temp);
						flag = FINISHED;
					}
					else {
						tree_t* current = (*tree)->left;
						while (current->right != NULL) { //find the node to remove in the left subtree
							current = current->right;
						}
						(*tree)->key = current->key;
						flag = DeleteByKey(&((*tree)->left), current->key);
					}					
				}
			}
		}
	return flag;
}

int DestroyTree(tree_t* tree) {
	if (!tree)
		return NOT_FINISHED;

	tree->differense = 0;
	tree->height = 0;
	tree->key = 0;
	DestroyTree(tree->left);
	DestroyTree(tree->right);
	free(tree);

	return FINISHED;
}

void PrintTree(tree_t* tree, int n){
	if (tree != NULL){
		printf("%d key %d/  height: %d  delta: %d\n", n, tree->key, tree->height, tree->differense);
		PrintTree(tree->left, n + 1);
		PrintTree(tree->right, n + 1);
	}
	return;
}

int main(void) {
	tree_t* tree = NULL;

	while (1) {
		int key = 0;
		char function = getchar();
		if (function == EOF || function == '\n')
			break;

		scanf("%d", &key);

		//choosing operator
		if (function == 'a')
			AddNodeByKey(&tree, key);
		else if (function == 'r')
			DeleteByKey(&tree, key);
		else if (function == 'f') {
			if (FindByKey(tree, key))
				printf("yes\n");
			else
				printf("no\n");
		}
		function = getchar(); //get "\n" at the end of str
	}
	DestroyTree(tree);

	return 0;
}