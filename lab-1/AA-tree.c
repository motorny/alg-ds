#include <stdlib.h>
#include "AA-tree.h"

#define min(a,b) (a < b ? a : b)

static void Rotation(tree_t* t1, tree_t* t2) {
	tree_t temp;
	temp = *t1;
	*t1 = *t2;
	*t2 = temp;
}
static tree_t* Skew(tree_t* t) {
	if (t == NULL)
		return NULL;
	if (t->left == NULL)
		return t;

	tree_t* l = t->left;
	if (t->level == l->level) {
		Rotation(t, l);
		l->left = t->right;
		t->right = l;
	}
	return t;
}
static tree_t* Split(tree_t* t) {
	if (t == NULL)
		return NULL;
	if (t->right == NULL)
		return t;
	if (t->right->right == NULL)
		return t;

	tree_t* r = t->right;

	if (t->level == r->right->level) {
		Rotation(t, r);
		r->right = t->left;
		t->left = r;
		t->level++;
	}
	return t;
}

tree_t* Find(tree_t* t, int key) {
	tree_t* temp = NULL;

	if (t == NULL)
		return NULL;

	if (t->key == key)
		return t;
	else {
		if (key < t->key)
			temp = Find(t->left, key);
		else
			temp = Find(t->right, key);
	}
	return temp;
}
tree_t* Add(tree_t* t, int key) {
	if (t == NULL) {
		t = (tree_t*)malloc(sizeof(tree_t));
		if (t == NULL)
			return NULL;
		t->key = key;
		t->level = 1;
		t->left = t->right = NULL;
	}
	else {
		if (key < t->key)
			t->left = Add(t->left, key);
		else {
			if (key > t->key)
				t->right = Add(t->right, key);
		}
	}
	t = Skew(t);
	t = Split(t);
	return t;
}

static void NewLevel(tree_t* t) {
	if (t == NULL)
		return;
	int leftLevel, rightLevel, shouldBe;

	if (t->left != NULL)
		leftLevel = t->left->level;
	else
		leftLevel = 0;
	if (t->right != NULL)
		rightLevel = t->right->level;
	else
		rightLevel = 0;

	shouldBe = min(leftLevel, rightLevel) + 1;

	if (shouldBe < t->level) {
		t->level = shouldBe;
		if (shouldBe < rightLevel) {
			t->right->level = shouldBe;
		}
	}
}
static tree_t* Predecessor(tree_t* curNode) {
	curNode = curNode->left;
	while (curNode->right != NULL) {
		curNode = curNode->right;
	}
	return curNode;
}
static tree_t* Successor(tree_t* curNode) {
	curNode = curNode->right;
	while (curNode->left != NULL) {
		curNode = curNode->left;
	}
	return curNode;
}
void Del(tree_t** t, int key) {
	if ((*t) == NULL)
		return;

	if (key < (*t)->key)
		Del(&((*t)->left), key);
	else {
		if (key > (*t)->key)
			Del(&((*t)->right), key);
		else {
			if ((*t)->left == NULL && (*t)->right == NULL) {
				free((*t));
				(*t) = NULL;
				return;
			}
			else if ((*t)->left == NULL) {
				tree_t* temp = Successor((*t));
				(*t)->key = temp->key;
				Del(&((*t)->right), temp->key);
				return;
			}
			else {
				tree_t* temp = Predecessor((*t));
				(*t)->key = temp->key;
				Del(&((*t)->left), temp->key);
				return;
			}
		}
	}

	NewLevel(*t);
	(*t) = Skew((*t));
	(*t)->right = Skew((*t)->right);
	if ((*t)->right != NULL)
		(*t)->right->right = Skew((*t)->right->right);
	(*t) = Split((*t));
	(*t)->right = Split((*t)->right);
}

static void PrintTreeCur(tree_t* tree, int depth) {
	if (tree != NULL) {
		PrintTreeCur(tree->left, depth + 1);
		for (int i = 0; i < depth; ++i)
			printf("       ");
		printf("%d<\n", tree->key);
		PrintTreeCur(tree->right, depth + 1);
	}
}
void PrintTree(tree_t* tree) {
	PrintTreeCur(tree, 0);
}

void DestroyTree(tree_t* t) {
	if (t != NULL) {
		DestroyTree(t->left);
		DestroyTree(t->right);
		free(t);
	}
}
