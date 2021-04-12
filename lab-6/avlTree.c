#include "avlTree.h"

tree_t* RightRotate(tree_t* tree) {
	tree_t* temp = tree->left;
	tree->left = temp->right;
	temp->right = tree;
	temp->balance = 0;
	tree->balance = 0;
	tree = temp;
	return tree;
}

tree_t* LeftRotate(tree_t* tree) {
	tree_t* temp = tree->right;
	tree->right = temp->left;
	temp->left = tree;
	tree->balance = 0;
	temp->balance = 0;
	tree = temp;
	return tree;
}

int Balance(tree_t** tree, int flag, int balanceCase) {
	if (balanceCase == 1) { //adding to the left subtree
		if ((*tree)->balance == -1) {
			if ((*tree)->left->balance == -1) {
				(*tree) = RightRotate((*tree));
			}
			else if ((*tree)->left->balance == 1) {
				int balance = (*tree)->left->right->balance;
				(*tree)->left = LeftRotate((*tree)->left);
				(*tree) = RightRotate((*tree));

				if(balance == -1)
					(*tree)->right->balance = 1;
				else if(balance == 1)
					(*tree)->left->balance = -1;
			}
			else if ((*tree)->left->balance == 0) {
				(*tree) = RightRotate((*tree));
				(*tree)->right->balance = -1;
				(*tree)->balance = 1;
			}
			flag = FINISHED;
		}
		else if ((*tree)->balance == 1) {
			(*tree)->balance = 0;
			flag = FINISHED;
		}
		else if ((*tree)->balance == 0) {
			(*tree)->balance = -1;
		}
	}
	else if (balanceCase == 2) { //adding to the right subtree
		if ((*tree)->balance == 1) {
			if ((*tree)->right->balance == 1) {
				(*tree) = LeftRotate((*tree));
			}
			else if ((*tree)->right->balance == -1) {
				int balance = (*tree)->right->left->balance;
				(*tree)->right = RightRotate((*tree)->right);
				(*tree) = LeftRotate((*tree));

				if(balance == 1)
					(*tree)->left->balance = -1;
				else if(balance == -1)
					(*tree)->right->balance = 1;
			}
			else if ((*tree)->right->balance == 0) {
				(*tree) = LeftRotate((*tree));
				(*tree)->left->balance = 1;
				(*tree)->balance = -1;
			}
			flag = FINISHED;
		}
		else if ((*tree)->balance == -1) {
			(*tree)->balance = 0;
			flag = FINISHED;
		}
		else if ((*tree)->balance == 0) {
			(*tree)->balance = 1;
		}
	}
	else if (balanceCase == 3) { //deletion from the left subtree
		if ((*tree)->balance == 1) {
			if ((*tree)->right->balance == 1) {
				(*tree) = LeftRotate((*tree));
			}
			else if ((*tree)->right->balance == -1) {
				int balance = (*tree)->right->left->balance;
				(*tree)->right = RightRotate((*tree)->right);
				(*tree) = LeftRotate((*tree));

				if(balance == 1)
					(*tree)->left->balance = -1;
				else if(balance == -1)
					(*tree)->right->balance = 1;
			}
			else if ((*tree)->right->balance == 0) {
				(*tree) = LeftRotate((*tree));
				(*tree)->left->balance = 1;
				(*tree)->balance = -1;
				flag = FINISHED;
			}
		}
		else if ((*tree)->balance == -1) {
			(*tree)->balance = 0;
		}
		else if ((*tree)->balance == 0) {
			(*tree)->balance = 1;
			flag = FINISHED;
		}
	}
	else if (balanceCase == 4) { //deletion from the right subtree
		if ((*tree)->balance == -1) {
			if ((*tree)->left->balance == -1) {
				(*tree) = RightRotate((*tree));
			}
			else if ((*tree)->left->balance == 1) {
				int balance = (*tree)->left->right->balance;
				(*tree)->left = LeftRotate((*tree)->left);
				(*tree) = RightRotate((*tree));

				if(balance == -1)
					(*tree)->right->balance = 1;
				else if(balance == 1)
					(*tree)->left->balance = -1;
			}
			else if ((*tree)->left->balance == 0) {
				(*tree) = RightRotate((*tree));
				(*tree)->right->balance = -1;
				(*tree)->balance = 1;
				flag = FINISHED;
			}
		}
		else if ((*tree)->balance == 0) {
			(*tree)->balance = -1;
			flag = FINISHED;
		}
		else if ((*tree)->balance == 1) {
			(*tree)->balance = 0;
		}
	}
	return flag;
}
int AddNodeByKey(tree_t** tree, int key) {
	int flag = NOT_FINISHED;
	if (!(*tree)) {
		(*tree) = (tree_t*)malloc(sizeof(tree_t));
		if (!(*tree))
			return ERROR;

		(*tree)->key = key;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		(*tree)->balance = 0;
		flag = NEED_BALANCE;
	}
	else {
		if (key < (*tree)->key) {
			flag = AddNodeByKey(&((*tree)->left), key);
			if (flag == NEED_BALANCE) {
				flag = Balance(tree, flag, 1);
			}
		}
		else if (key > (*tree)->key) {
			flag = AddNodeByKey(&((*tree)->right), key);
			if (flag == NEED_BALANCE) {
				flag = Balance(tree, flag, 2);
			}
		}
		else 
			return ERROR; //key == (*tree)->key => was not added
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
		return ERROR;

	if (key < (*tree)->key) {
		flag = DeleteByKey(&((*tree)->left), key);
		if (flag == NEED_BALANCE) {
			flag = Balance(tree, flag, 3);
		}
	}
	else if (key > (*tree)->key) {
		flag = DeleteByKey(&((*tree)->right), key);
		if (flag == NEED_BALANCE) {
			flag = Balance(tree, flag, 4);
		}
	}
	else { //found
		tree_t* temp = *tree;
		if ((*tree)->left == NULL && (*tree)->right == NULL) {
			free(temp);
			(*tree) = NULL;
			flag = NEED_BALANCE;
		}
		else if ((*tree)->right == NULL && (*tree)->left != NULL) {
			(*tree) = (*tree)->left;
			free(temp);
			flag = NEED_BALANCE;
		}
		else if ((*tree)->left == NULL && (*tree)->right != NULL) {
			(*tree) = (*tree)->right;
			free(temp);
			flag = NEED_BALANCE;
		}
		else {
			tree_t* current = (*tree)->left;
			while (current->right != NULL) { //find the rightmost node to remove in the left subtree
				current = current->right;
			}
			(*tree)->key = current->key;
			flag = DeleteByKey(&((*tree)->left), current->key); //need to balance
			if (flag == NEED_BALANCE) { //removed from tre left subtree
				flag = Balance(tree, flag, 3);
			}
		}
	}
	return flag;
}

int DestroyTree(tree_t* tree){
	if (!tree)
		return ERROR;
	tree->key = 0;
	DestroyTree(tree->left);
	DestroyTree(tree->right);
	free(tree);

	return FINISHED;
}

void PrintTree(tree_t* tree, int level) {
	int i = 0;
	if (tree) {
		PrintTree(tree->left, level + 1);
		for (i = 0; i < level; i++)
			printf("    ");
		printf("%i(%i)\n", tree->key, tree->balance);
		PrintTree(tree->right, level + 1);
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
	//PrintTree(tree, 0);
	DestroyTree(tree);

	/*_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);*/

	return 0;
}