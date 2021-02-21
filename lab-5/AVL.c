#include "AVL.h"

// is tree balanced?
int bFactor(node_t* p) {
	return Height(p->right) - Height(p->left);
}

// if the height is incorrect we fix it
void FixHeight(node_t* p) {
	unsigned int hl = Height(p->left);
	unsigned int hr = Height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

// returns the height of node
unsigned int Height(node_t* p) {
	return p ? p->height : 0;
}

// right rotation
node_t* RotateRight(node_t* p) {
	node_t* q = p->left;
	p->left = q->right;
	q->right = p;
	FixHeight(p);
	FixHeight(q);
	return q;
}

// left rotation
node_t* RotateLeft(node_t* q) {
	node_t* p = q->right;
	q->right = p->left;
	p->left = q;
	FixHeight(q);
	FixHeight(p);
	return p;
}

// tries to balance tree if it is not balanced
node_t* Balance(node_t* p) {
	FixHeight(p);
	if (bFactor(p) == 2) {
		if (bFactor(p->right) < 0)
			p->right = RotateRight(p->right);
		return RotateLeft(p);
	}
	if (bFactor(p) == -2) {
		if (bFactor(p->left) > 0)
			p->left = RotateLeft(p->left);
		return RotateRight(p);
	}
	// if all is ok
	return p;
}

// inserting where "k" is key
node_t* Insert(node_t* p, int k) {

	// if we have no tree we create branch
	if (!p) {
		p = (node_t*)malloc(sizeof(node_t));
		p->key = k;
		p->left = p->right = 0;
		p->height = 1;
		return p;
	}
	if (k < p->key)
		p->left = Insert(p->left, k);
	else
		p->right = Insert(p->right, k);
	return Balance(p);
}

// searching a node with minimal key
node_t* FindMin(node_t* p) {
	return p->left ? FindMin(p->left) : p;
}

// removing a node with minimal key
node_t* RemoveMin(node_t* p) {
	if (p->left == 0)
		return p->right;
	p->left = RemoveMin(p->left);
	return Balance(p);
}

// removing a node 
node_t* RemoveNode(node_t* p, int k) {
	if (!p)
		return NULL;
	if (k < p->key)
		p->left = RemoveNode(p->left, k);
	else if (k > p->key)
		p->right = RemoveNode(p->right, k);
	else { //  k == p->key 
		node_t* q = p->left;
		node_t* r = p->right;
		free(p);
		if (!r)
			return q;
		node_t* min = FindMin(r);
		min->right = RemoveMin(r);
		min->left = q;
		return Balance(min);
	}
	return Balance(p);
}

node_t* FindNodeByKey(node_t* p, int k) {
	node_t* q = p;
	if (!p)
		return NULL;
	if (p->key > k) {
		q = FindNodeByKey(p->left, k);
	}
	else if (p->key < k) {
		q = FindNodeByKey(p->right, k);
	}
	else
		q = p;
	return q;
}

// reading string
char* ReadStr() {
	int i = 0, size = 2;
	int block = 8;
	char* str = (char*)malloc(sizeof(char) * size), * tmp = NULL;
	if (str == NULL)
		return NULL;
	while ((str[i++] = fgetc(stdin)) != EOF) {
		if (i >= size) {
			size += block;
			tmp = realloc(str, (size) * sizeof(char));
			if (tmp)
				str = tmp;
			else
				return NULL;
		}
	}
	str[i - 1] = 0;
	return str;
}

// prints data about node
void PrintTree(node_t* root) {
	if (root) {
		printf("key = %d\n", root->key);
		PrintTree(root->left);
		PrintTree(root->right);
	}
}

// destroying tree
void DestroyTree(node_t* tree) {
	if (tree) {
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}
}
