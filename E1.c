#define _CRT_SECURE_NO_WARNING
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define ERR 0

#define SUCCESS 1
#define FAIL 0

typedef struct node_t {
	struct node_t* parent;
	struct node_t* right;
	struct node_t* left;
	int data;
}node_t;


node_t* add_node(node_t* root, int newData) {
	if (!root) {
		root = (node_t*)malloc(sizeof(node_t));
		if (!root)return ERR;
		root->parent = NULL;
		root->data = newData;
		root->right = NULL;
		root->left = NULL;
	}
	else {
		node_t* node = root;
		while (node)
		{
			if (node->data == newData)
				break;
			if (node->data > newData) {
				if (node->left)
					node = node->left;
				else {
					node->left = (node_t*)malloc(sizeof(node_t));
					node->left->parent = node;
					node->left->data = newData;
					node->left->left = NULL;
					node->left->right = NULL;
					break;
				}
			}
			else {
				if (node->right)
					node = node->right;
				else {
					node->right = (node_t*)malloc(sizeof(node_t));
					if (node->right)
						node->right->parent = node;
					else
						return ERR;
					node->right->data = newData;
					node->right->left = NULL;
					node->right->right = NULL;
					break;
				}
			}
		}
	}
	return root;
}


int get_max(node_t* root) 
{
	while (root->right)
	{
		root = root->right;
	}
	return root->data;
}
int length(node_t* root, int len) {
	if (root) {
		int a = length(root->left, len + 1);
		int b = length(root->right, len + 1);
		return (a > b) ? a : b;

	}
	else
		return len;
}
node_t* fill_tree(node_t* root) {
	if (root) {
		int a = length(root->left, 0);
		int b = length(root->right, 0);
		root->data = (a > b) ? a - b : b - a;
		fill_tree(root->left);
		fill_tree(root->right);
		return root;
	}
	return NULL;
}

node_t* delete_node(node_t* root, int key) 
{
	if (root)
		if (root->data == key) {
			if (root->parent) {
				if (!root->left && !root->right) {
					if (root->parent->left == root)
						root->parent->left = NULL;
					else
						root->parent->right = NULL;
					free(root);
					root = NULL;
				}
				else if (root->left && !root->right) {
					if (root->parent->left == root) {
						root->parent->left = root->left;
						root->left->parent = root->parent;
					}
					else {
						root->parent->right = root->left;
						root->left->parent = root->parent;
					}
					free(root);
					root = NULL;
				}
				else if (!root->left && root->right) {
					if (root->parent->right == root) {
						root->parent->right = root->right;
						root->right->parent = root->parent;
					}
					else {
						root->parent->left = root->right;
						root->right->parent = root->parent;
					}
					free(root);
					root = NULL;
				}
				else {
					int m = get_max(root->left);
					root->data = m;
					delete_node(root->left, m);
				}
			}
			else {
				if (!root->left && !root->right) {
					free(root);
					root = NULL;

				}
				else if (root->left && !root->right) {
					node_t* tmp = root->left;
					free(root);
					tmp->parent = NULL;
					root = tmp;
				}
				else if (!root->left && root->right) {
					node_t* tmp = root->right;
					free(root);
					tmp->parent = NULL;
					root = tmp;
				}
				else {
					int m = get_max(root->left);
					root->data = m;
					delete_node(root->left, m);
				}
			}
		}
		else if (key > root->data) {
			delete_node(root->right, key);
		}
		else {
			delete_node(root->left, key);
		}
	return root;
}

int find(node_t* root, int key) 
{
	if (root) {
		if (root->data == key)
			return SUCCESS;
		else if (key < root->data)
			return find(root->left, key);
		else
			return find(root->right, key);
	}

	else
    return FAIL;
}

int delete_tree(node_t* root) 
{
	if (root) {
		delete_tree(root->left);
		delete_tree(root->right);
		free(root);
	}


	return SUCCESS;
}

void print_tree(node_t* tree, int key)
{
	if (tree)
	{
		printf("%d %d\n", key, tree->data);
		print_tree(tree->left, key + 1);
		print_tree(tree->right, key + 1);
	}
}


int main(int argc, char* argv[]) 
{

	node_t* root = NULL;
	char c, operation, number[255];
	int index = 0, data;
	c = getchar();
	while (c != EOF)
	{
		operation = c;
		c = getchar();
		while (isspace(c))
		{
			c = getchar();
		}
		while (isdigit(c))
		{
			number[index++] = c;
			c = getchar();
		}
		number[index] = '\0';
		data = atoi(number);
		index = 0;
		switch (operation)
		{
		case 'a':
		{
			root = add_node(root, data);
			break;
		}
		case 'r':
		{
			root = delete_node(root, data);
			break;
		}
		case 'f':
		{
			if (find(root, data))
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
			break;
		}
		default: {
			delete_tree(root);
			return 0;
		}
		}
		if (c == '\n')
		{
			c = getchar();
		}
	}
	delete_tree(root);
	return 0;
}