#include "tree.h"

#pragma warning (disable : 4996)

void Insert(SPLAYTREE** tree, int value) {
	if ((*tree) == NULL) {
		(*tree) = (SPLAYTREE*)malloc(sizeof(SPLAYTREE));
		if ((*tree) == NULL)
			return;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		(*tree)->parent = NULL;
		(*tree)->number = value;
	}

	if ((*tree)->number < value) {
		Insert(&((*tree)->right), value);
		(*tree)->right->parent = (*tree);
	}
	else if ((*tree)->number > value) {
		Insert(&((*tree)->left), value);
		(*tree)->left->parent = (*tree);
	}
	else return;
}

SPLAYTREE* Search(SPLAYTREE* tree, int value) {
	if (!tree)
		return NULL;
	if (tree->number == value)
		return tree;

	SPLAYTREE* searched = NULL;

	if (tree->number < value)
		searched = Search(tree->right, value);
	else searched = Search(tree->left, value);

	return searched;
}

SPLAYTREE* MinValueNode(SPLAYTREE* tree) {
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}

void Delete(SPLAYTREE** tree, int value) {
	if ((*tree) == NULL)
		return;

	SPLAYTREE* buffer = NULL;

	if ((*tree)->number == value) {
		if ((*tree)->left == NULL && (*tree)->right == NULL)
			(*tree) = NULL;
		else if ((*tree)->left != NULL && (*tree)->right == NULL) {
			buffer = (*tree)->parent;
			(*tree) = (*tree)->left;
			(*tree)->parent = buffer;
		}
		else if ((*tree)->left == NULL && (*tree)->right != NULL) {
			buffer = (*tree)->parent;
			(*tree) = (*tree)->right;
			(*tree)->parent = buffer;
		}
		else {
			(*tree)->number = MinValueNode((*tree)->right)->number;
			Delete(&((*tree)->right), (*tree)->number);
		}
	}
	else if ((*tree)->number < value)
		Delete(&((*tree)->right), value);
	else Delete(&((*tree)->left), value);
}

void TurnLeft(SPLAYTREE* root) {
	SPLAYTREE* parent = root->parent;
	SPLAYTREE* right_son = root->right;
	SPLAYTREE* buffer = NULL;
	if (parent) {
		if (parent->left == root)
			parent->left = right_son;
		else parent->right = right_son;
	}
	buffer = right_son->left;
	right_son->left = root;
	root->right = buffer;
	root->parent = right_son;
	right_son->parent = parent;
	if (root->right)
		root->right->parent = root;
}

void TurnRight(SPLAYTREE* root) {
	SPLAYTREE* parent = root->parent;
	SPLAYTREE* left_son = root->left;
	SPLAYTREE* buffer = NULL;
	if (parent) {
		if (parent->right == root)
			parent->right = left_son;
		else parent->left = left_son;
	}
	buffer = left_son->right;
	left_son->right = root;
	root->left = buffer;
	root->parent = left_son;
	left_son->parent = parent;
	if (root->left)
		root->left->parent = root;
}

SPLAYTREE* Splay(SPLAYTREE* ptr) {
	while (ptr->parent) {
		//Zig step
		if (ptr == ptr->parent->left && ptr->parent->parent == NULL)
			TurnRight(ptr->parent);
		else if (ptr == ptr->parent->right && ptr->parent->parent == NULL)
			TurnLeft(ptr->parent);

		//Zig-Zig step
		else if (ptr == ptr->parent->left && ptr->parent == ptr->parent->parent->left) {
			TurnRight(ptr->parent->parent);
			TurnRight(ptr->parent);
		}

		else if (ptr == ptr->parent->right && ptr->parent == ptr->parent->parent->right) {
			TurnLeft(ptr->parent->parent);
			TurnLeft(ptr->parent);
		}

		//Zig-Zag step
		else if (ptr == ptr->parent->right && ptr->parent == ptr->parent->parent->left) {
			TurnLeft(ptr->parent);
			TurnRight(ptr->parent);
		}

		else if (ptr == ptr->parent->left && ptr->parent == ptr->parent->parent->right) {
			TurnRight(ptr->parent);
			TurnLeft(ptr->parent);
		}
	}
	return ptr;
}

void Clear(SPLAYTREE* tree) {
	if (tree != NULL) {
		Clear(tree->left);
		Clear(tree->right);
		free(tree);
	}
}
