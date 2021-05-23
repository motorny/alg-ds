#include <cstdio>
#include <cstdlib>

typedef struct Node {
	int key;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
} Node_t;


Node_t *Insert(Node_t *node, int key) {
	if (node == NULL) {
		node = (Node_t *)malloc(sizeof(Node_t));
		if (node == NULL)
			return NULL;
		node->key = key;
		node->left = node->right = node->parent = NULL;
	}
	else {
		if (key < node->key) {
			node->left = Insert(node->left, key);
			node->left->parent = node;
		}
		else {
			if (key > node->key) {
				node->right = Insert(node->right, key);
				node->right->parent = node;
			}
		}
	}
	return node;
}

Node_t *Search(Node_t *node, int key) {
	Node_t *tmp = NULL;
	if (node == NULL)
		return NULL;
	if (node->key == key)
		return node;
	else if (key < node->key)
		tmp = Search(node->left, key);
	else
		tmp = Search(node->right, key);
	return tmp;
}

Node_t *Delete(Node_t *node, int key) {
	if (node == NULL)
		return node;
	else if (key < node->key)
		node->left = Delete(node->left, key);
	else if (key > node->key)
		node->right = Delete(node->right, key);
	else if (node->left != NULL && node->right != NULL) {
		Node_t *tmp = node->right;
		while (tmp->left != NULL)
			tmp = tmp->left;
		node->key = tmp->key;
		node->right = Delete(node->right, node->key);
	}
	else {
		Node_t *parent = node->parent;
		if (node->left != NULL) {
			node = node->left;
			node->parent = parent;
		}
		else if (node->right != NULL) {
			node = node->right;
			node->parent = parent;
		}
		else
			node = NULL;
	}
	return node;
}

void FreeTree(Node_t *node) {
	if (node == NULL)
		return;
	FreeTree(node->left);
	FreeTree(node->right);
	free(node);
}

void Left(Node_t& node) {
	Node_t* parent = node.parent;
	Node_t* right = node.right;
	Node_t* tmp = NULL;
	if (parent) {
		if (parent->left == &node)
			parent->left = right;
		else parent->right = right;
	}
	tmp = right->left;
	right->left = &node;
	node.right = tmp;
	node.parent = right;
	right->parent = parent;
	if (node.right)
		node.right->parent = &node;
}

void Right(Node_t & node) {
	Node_t* parent = node.parent;
	Node_t* left = node.left;
	Node_t* tmp = NULL;
	if (parent) {
		if (parent->right == &node)
			parent->right = left;
		else parent->left = left;
	}
	tmp = left->right;
	left->right = &node;
	node.left = tmp;
	node.parent = left;
	left->parent = parent;
	if (node.left)
		node.left->parent = &node;
}

Node_t *Splay(Node_t *&root) {
	while (root->parent != NULL) {
		if (root == root->parent->left) {
			if (root->parent->parent == NULL)
				Right(*root->parent);
			else if (root->parent == root->parent->parent->left) {
				Right(*root->parent->parent);
				Right(*root->parent);
			}
			else {
				Right(*root->parent);
				Left(*root->parent);
			}
		}
		else {
			if (root->parent->parent == NULL)
				Left(*root->parent);
			else if (root->parent == root->parent->parent->right) {
				Left(*root->parent->parent);
				Left(*root->parent);
			}
			else {
				Left(*root->parent);
				Right(*root->parent);
			}
		}
	}
	return root;
}