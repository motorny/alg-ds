#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable: 4996)
#include "bPlusTree.h"


bplus_t * InitTree() {
	bplus_t* root = (bplus_t*)malloc(sizeof(bplus_t));
	if (root) {
		root->leaf = 1;
		root->key_count = 0;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		for (int i = 0; i < 2 * DEGREE + 1; i++)
			root->child[i] = NULL;
	}
	return root;
}
void Destroy(bplus_t** root) {
	if (!(*root)->leaf) {
		for (int i = 0; i < (*root)->key_count; i++) 
			Destroy(&((*root)->child[i]));
	}
	free(*root);
	*root = NULL;
}

void Split(bplus_t** root, bplus_t* node) {
	int i, key, pos;
	bplus_t* newnode = malloc(sizeof(bplus_t));
	newnode->leaf = 0;
	newnode->key_count = 0;
	newnode->left = NULL;
	newnode->right = NULL;
	for (i = 0; i < 2 * DEGREE + 1; i++) 
		newnode->child[i] = NULL;
	if (node->right) {
		newnode->right = node->right;
		node->right->left = newnode;
		node->right = newnode;
		newnode->left = node;
	}
	else {
		newnode->right = node->right;
		node->right = newnode;
		newnode->left = node;
	}

	key = node->key[DEGREE];
	newnode->key_count = DEGREE - 1;
	node->key_count = DEGREE;
	for (i = 0; i < newnode->key_count; i++) {
		newnode->key[i] = node->key[i + DEGREE + 1];
		newnode->child[i] = node->child[i + DEGREE + 1];
		node->child[i + DEGREE + 1] = NULL;
	}
	newnode->child[newnode->key_count] = node->child[2 * DEGREE];
	node->child[2 * DEGREE] = NULL;

	if (node->leaf) {
		newnode->key_count++;
		newnode->leaf = 1;
		for (i = newnode->key_count - 1; i >= 1; i--) 
			newnode->key[i] = newnode->key[i - 1];
		newnode->key[0] = node->key[DEGREE];
	}

	if (node == (*root)) {
		(*root) = malloc(sizeof(bplus_t));
		if (*root) {
			(*root)->key[0] = key;
			(*root)->child[0] = node;
			(*root)->child[1] = newnode;

			for (i = 0; i < 2 * DEGREE + 1; i++) {
				if (newnode->child[i]) 
					newnode->child[i]->parent = newnode;
				if (node->child[i]) 
					node->child[i]->parent = node;
			}
			(*root)->leaf = 0;
			(*root)->parent = NULL;
			(*root)->left = NULL;
			(*root)->right = NULL;
			for (i = 2; i < 2 * DEGREE + 1; i++) 
				(*root)->child[i] = NULL;
			(*root)->key_count = 1;
			node->parent = (*root);
			newnode->parent = (*root);
		}
	}
	else {
		newnode->parent = node->parent;
		bplus_t* parent = node->parent;

		pos = 0;
		while (pos < parent->key_count && (parent->key[pos] < key)) 
			pos++;

		for (i = parent->key_count; i >= pos + 1; i--) 
			parent->key[i] = parent->key[i - 1];

		for (i = parent->key_count + 1; i >= pos + 2; i--) 
			parent->child[i] = parent->child[i - 1];

		for (i = 0; i < 2 * DEGREE; i++) {
			if (newnode->child[i]) 
				newnode->child[i]->parent = newnode;
		}
		parent->key[pos] = key;
		parent->child[pos + 1] = newnode;
		parent->key_count++;

		if (parent->key_count == 2 * DEGREE) 
			Split(root, parent);
	}
}

bplus_t* FindLeaf(bplus_t* root, int key) {
	bplus_t* cur = NULL;
	if (root) {
		cur = root;
		while (cur->leaf != 1) {
			for (int i = 0; i <= cur->key_count; i++) {
				if (i == cur->key_count || key < cur->key[i]) {
					cur = cur->child[i];
					break;
				}
			}
		}
	}
	return cur;
}

int AddElem(bplus_t** root, int key) {
	int i, pos = 0;
	bplus_t* leaf = FindLeaf(*root, key);
	if (!leaf) 
		return 0;
	for (i = 0; i < leaf->key_count; i++) {
		if (leaf->key[i] == key) 
			return 0;
	}
	while ((pos < leaf->key_count) && (leaf->key[pos] < key)) 
		pos++;
	for (i = leaf->key_count; i >= pos + 1; i--) 
		leaf->key[i] = leaf->key[i - 1];

	leaf->key[pos] = key;
	leaf->key_count++;
	if (leaf->key_count == 2 * DEGREE) 
		Split(root, leaf);
	return 1;
}

int MinKey(bplus_t* node) {
	for (int i = 0; i < 2 * DEGREE; i++) {
		if (node->child[i]) 
			return MinKey(node->child[i]);
	}
	return node->key[0];
}

void Update(bplus_t* node, int key) {
	bplus_t* tmp = node->parent;
	int pos = 0;

	while (tmp) {
		while ((pos < tmp->key_count) && (tmp->key[pos] < key))
			pos++;
		if (pos < tmp->key_count) {
			if (tmp->key[pos] != MinKey(tmp->child[pos + 1])) 
				tmp->key[pos] = MinKey(tmp->child[pos + 1]);
		}
		tmp = tmp->parent;
	}
}

void DeleteInNode(bplus_t** root, bplus_t* node, int key) {
	int i, pos = 0, flag = 0;
	bplus_t* right_bro;
	bplus_t* left_bro;
	while ((pos < node->key_count) && (node->key[pos] < key)) 
		pos++;

	for (i = pos; i < node->key_count; i++) 
		node->key[i] = node->key[i + 1];
	
	for (i = pos + 1; i <= node->key_count; i++) 
		node->child[i] = node->child[i + 1];
	
	for (i = node->key_count + 1; i < 2 * DEGREE + 1; i++) 
		*(node->child + i) = NULL;
	
	node->key_count--;
	if (node == (*root)) {
		for (i = 0; i < 2 * DEGREE + 1; i++) {
			if (node->child[i]) {
				if (node->child[i]->key_count == 0) 
					node->child[i] = NULL;
				
			}
		}
		if ((*root)->key_count == 0 && (*root)->child[0]) 
			(*root) = (*root)->child[0];
		
		return;
	}
	if (node->key_count >= DEGREE / 2 - 1) 
		Update(node, key);
	
	else {
		right_bro = node->right;
		left_bro = node->left;
		if (left_bro && left_bro->key_count > DEGREE - 1 && (left_bro->parent == node->parent)) {
			left_bro->key_count--;
			node->key_count++;
			for (i = 1; i < node->key_count; i++) {
				node->key[i] = node->key[i - 1];
				node->child[i] = node->child[i - 1];
			}
			node->child[node->key_count] = node->child[node->key_count - 1];
			node->key[0] = left_bro->key[left_bro->key_count];
			node->child[0] = left_bro->child[left_bro->key_count + 1];
			left_bro->child[left_bro->key_count + 1] = NULL;
			if (node->child[0]) 
				node->child[0]->parent = node;
			
			Update(node, key);
		}
		else if (right_bro && right_bro->key_count > DEGREE - 1 && (right_bro->parent == node->parent)) {
			node->key_count++;
			node->key[node->key_count - 1] = right_bro->key[0];
			node->child[node->key_count] = right_bro->child[0];
			if (node->child[node->key_count]) 
				node->child[node->key_count]->parent = node;
			
			for (i = 0; i < right_bro->key_count; i++) {
				right_bro->key[i] = right_bro->key[i + 1];
				right_bro->child[i] = right_bro->child[i + 1];
			}
			for (i = 0; i < 2 * DEGREE; i++) {
				if (right_bro->child[i] == right_bro->child[i + 1] && right_bro->child[i] != NULL) {
					right_bro->child[i + 1] = NULL;
					break;
				}
			}
			right_bro->key_count--;
			Update(node, key);
		}
		else 
			Merge(root, node, key);
	}
}

int RemoveElem(bplus_t** root, int key) {
	int i, pos = 0, flag = 0;
	bplus_t* leaf = FindLeaf(*root, key);
	for (i = 0; i < leaf->key_count; i++) {
		if (leaf->key[i] == key) {
			flag = 1;
			break;
		}
	}
	if (!flag) 
		return 0;
	
	DeleteInNode(root, leaf, key);
	return 1;
}

void Merge(bplus_t** root, bplus_t* node, int key) {
	bplus_t* parent = node->parent;
	bplus_t* right_bro = node->right;
	bplus_t* left_bro = node->left;
	int i, pos = 0;
	bplus_t* tmp = NULL;
	if (right_bro && (right_bro->parent == node->parent)) {
		for (i = 0; i < right_bro->key_count; i++) {
			node->key[node->key_count] = right_bro->key[i];
			node->child[node->key_count + 1] = right_bro->child[i];
			if (right_bro->child[i]) 
				right_bro->child[i]->parent = node;
			node->key_count++;
		}
		node->child[node->key_count + 1] = right_bro->child[right_bro->key_count];
		if (right_bro->child[right_bro->key_count]) 
			right_bro->child[right_bro->key_count]->parent = node;
		if (right_bro->right) 
			right_bro->right->left = node;
		node->right = right_bro->right;
		DeleteInNode(root, node->parent, MinKey(right_bro));
		Update(node, key);
	}
	else {
		for (i = 0; i < node->key_count; i++) {
			left_bro->key[left_bro->key_count] = node->key[i];
			left_bro->child[left_bro->key_count + 1] = node->child[i];
			if (node->child[i]) 
				node->child[i]->parent = left_bro;

			left_bro->key_count++;
		}
		left_bro->child[left_bro->key_count + 1] = node->child[node->key_count];
		if (node->child[node->key_count]) 
			node->child[node->key_count]->parent = left_bro;

		left_bro->right = node->right;
		if (node->right) 
			node->right->left = left_bro;

		DeleteInNode(root, left_bro->parent, MinKey(node));
		Update(left_bro, key);
	}
}

void PrintTree(bplus_t** root, int level) {
	int i;
	for (i = 0; i < (*root)->key_count; i++) 
		printf("lvl %d key = %d\n", level, (*root)->key[i]);

	for (int i = 0; i < 2 * DEGREE; i++) {
		if ((*root)->child[i]) {
			printf("child %d\n", i);
			PrintTree(&((*root)->child[i]), level + 1);
		}
	}
}

int FindElem(bplus_t** root, int key) {
	bplus_t* leaf = FindLeaf(*root, key);
	for (int i = 0; i < leaf->key_count; i++) {
		if (leaf->key[i] == key)
			return 1;
	}
	return 0;
}

void ToDo(bplus_t** root) {
	int value;
	int check = 1;
	char buffer = getchar();
	while (buffer != EOF) {
		scanf("%d", &value);
		if (buffer == 'a') 
			check = AddElem(root, value);
		else if (buffer == 'r') 
			check = RemoveElem(root, value);
		else if (buffer == 'f') {
			if (FindElem(root, value)) 
				printf("yes\n");
			else 
				printf("no\n");
		}
		else {
			printf("Incorrect input");
			return;
		}
		buffer = getchar();
		if (buffer == '\r' || buffer == '\n')
			buffer = getchar();
	}
	return;
}

int main(void) {
	bplus_t* tree;
	tree = InitTree();
	ToDo(&tree);
	Destroy(&tree);
	return 0;
}