#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
//#include "23Tree.h"

typedef struct Tree23 {

	struct Tree23* left;
	int left_val;
	struct Tree23* right;
	int right_val;
	struct Tree23* mid;
	int max_son;
	struct Tree23* firstleft;
	struct Tree23* firstright;
} Tree23;

Tree23* Update(Tree23* tree, Tree23* left, Tree23* mid, Tree23* right) {

	if (tree) {
		tree->left = left;
		tree->left_val = (tree->left == NULL ? -1 : tree->left->max_son);
		tree->mid = mid;
		tree->right_val = (tree->mid == NULL ? -1 : tree->mid->max_son);
		tree->right = right;
		tree->max_son = (tree->right == NULL ? tree->mid == NULL ? tree->left->max_son : -1 : tree->right->max_son);
	}
	else
		return tree;
}

Tree23* AddNumber(int number) {

	Tree23* node = (Tree23*)malloc(sizeof(Tree23));
	if (node) {
		node->left = node->right = node->mid = node->firstleft = node->firstleft = NULL;
		node->left_val = node->max_son = number;
		node->right_val = -1;
	}
	return node;
}

void DeleteNode(Tree23* node) {

	if (node) {
		node->left = node->right = node->mid = node->firstright = node->firstleft = NULL;
		node->left_val = node->right_val = node->max_son = -1;
		free(node);
	}
}

void DestroyTree(Tree23* tree) {

	if (tree) {
		DestroyTree(tree->left);
		DestroyTree(tree->mid);
		DestroyTree(tree->right);
		DeleteNode(tree);
	}
}

Tree23* Split(Tree23* A, Tree23* node, Tree23* B, Tree23* del, Tree23* a, Tree23* b, Tree23* c, Tree23* d) {

	A = Update(A == NULL ? AddNumber(-1) : A, a, NULL, b);
	B = Update(B == NULL ? AddNumber(-1) : B, c, NULL, d);
	node = Update(node == NULL ? AddNumber(-1) : node, A, NULL, B);
	DeleteNode(del);
	return node;
}

int IsNotNULL(Tree23* node) {

	return node != NULL && node->left != NULL && node->mid == NULL && node->right != NULL;
}

Tree23* Merge(Tree23* tree, Tree23* left, Tree23* mid, Tree23* right, Tree23* del) {

	if (IsNotNULL(left) && IsNotNULL(mid) && IsNotNULL(right)) {
		left = Update(left, left->left, left->right, mid->left);
		right = Update(right, mid->right, right->left, right->right);
		tree = Update(tree, left, NULL, right);
		DeleteNode(mid);
	}
	else
		tree = Update(tree, left, mid, right);
	DeleteNode(del);
	return tree;
}

int IsTreeSons(Tree23* node) {

	return node != NULL && node->left != NULL && node->mid != NULL && node->right != NULL;
}

Tree23* Balance(Tree23* tree, Tree23* a, Tree23* b, Tree23* c, Tree23* d, Tree23* toFree) {

	if (IsNotNULL(a) && IsNotNULL(b) && IsNotNULL(c) && tree->right == d) {
		toFree = Merge(toFree, a, b, c, NULL);
		return Merge(tree, toFree->left, toFree->right, d, toFree);
	}
	else if (IsNotNULL(b) && IsNotNULL(c) && IsNotNULL(d)) {
		toFree = Merge(toFree, b, c, d, NULL);
		return Merge(tree, a, toFree->left, toFree->right, toFree);
	}
	else if (IsTreeSons(c) && IsNotNULL(d)) {
		a = Merge(a, a->left, a->right, b->left, NULL);
		b = Merge(b, b->right, c->left, c->mid, NULL);
		c = Merge(c, c->right, d->left, d->right, d);
		return Merge(tree, a, b, c, toFree);
	}
	else if (IsTreeSons(b) && IsNotNULL(a)) {
		d = Merge(d, c->right, d->left, d->right, NULL);
		c = Merge(c, b->mid, b->right, c->left, NULL);
		b = Merge(b, a->left, a->right, b->left, a);
		return Merge(tree, b, c, d, toFree);
	}
	return Split(tree->left == a ? NULL : toFree, tree->mid == b || tree->mid == c ? NULL : toFree, tree->right == d ? NULL : toFree, tree, a, b, c, d);
}

int IsLeftMax(Tree23* node) {

	return node != NULL && node->left_val == node->max_son;
}

void Unite(Tree23* left, Tree23* mid, Tree23* right) {

	if (left)
		left->firstright = mid;
	mid->firstleft = left;
	mid->firstright = right;
	if (right)
		right->firstleft = mid;
}

Tree23* Insert(Tree23* tree, int val) {

	if (!tree) {
		Tree23* node = AddNumber(val);
		Tree23* tmp = AddNumber(val);
		node->left = tmp;
		return node;
	}
	Tree23* node = AddNumber(val);
	if (val < tree->left_val) {
		Unite(tree->left->firstleft, node, tree->left);
		return IsLeftMax(tree) ? Update(tree, node, NULL, tree->left) :
			IsNotNULL(tree) ? Merge(tree, node, tree->left, tree->right, NULL) : Split(NULL, NULL, NULL, tree, node, tree->left, tree->mid, tree->right);
	}
	else if (val > tree->max_son) {
		if (IsLeftMax(tree)) {
			Unite(tree->left, node, tree->left->firstright);
			return Update(tree, tree->left, NULL, node);
		}
		Unite(tree->right, node, tree->right->firstright);
		return IsNotNULL(tree) ? Merge(tree, tree->left, tree->right, node, NULL) : Split(NULL, NULL, NULL, tree, tree->left, tree->mid, tree->right, node);
	}
	else if (IsNotNULL(tree) && val > tree->left_val && val < tree->max_son) {
		Unite(tree->left, node, tree->right);
		return Merge(tree, tree->left, node, tree->right, NULL);
	}
	else if (IsTreeSons(tree)) {
		if (val < tree->right_val && val > tree->left_val) {
			Unite(tree->left, node, tree->mid);
			return Split(NULL, NULL, NULL, tree, tree->left, node, tree->mid, tree->right);
		}
		else if (val < tree->max_son && val > tree->right_val) {
			Unite(tree->mid, node, tree->right);
			return Split(NULL, NULL, NULL, tree, tree->left, tree->mid, node, tree->right);
		}
	}
	return tree;
}

int CheckLeftNULL(Tree23* node) {

	return node != NULL && (node->left != NULL && node->left->left == NULL || node->right != NULL && node->right->left == NULL ||
		node->mid != NULL && node->mid->left == NULL) || node == NULL;
}

Tree23* InsertNumber(Tree23* tree, int val) {

	Tree23* node = NULL;
	if (CheckLeftNULL(tree))
		return Insert(tree, val);
	if (val < tree->left_val) {
		node = InsertNumber(tree->left, val);
		if (node != tree->left) {
			if (IsNotNULL(tree))
				return Merge(tree, node->left, node->right, tree->right, node);
			return Balance(tree, node->left, node->right, tree->mid, tree->right, node);
		}
	}
	else if (IsTreeSons(tree) && val < tree->right_val && val > tree->left_val) {
		node = InsertNumber(tree->mid, val);
		if (node != tree->mid)
			return Balance(tree, tree->left, node->left, node->right, tree->right, node);
	}
	else if (val > (IsNotNULL(tree) ? tree->left_val : tree->right_val)) {
		node = InsertNumber(tree->right, val);
		if (tree->right != node) {
			if (IsNotNULL(tree))
				return Merge(tree, tree->left, node->left, node->right, node);
			return Balance(tree, tree->left, tree->mid, node->left, node->right, node);
		}
	}
	return Update(tree, tree->left, tree->mid, tree->right);
}

void Separate(Tree23* left, Tree23* mid, Tree23* right) {

	if (left)
		left->firstright = right;
	if (right)
		right->firstleft = left;
}

Tree23* FirstDelete(Tree23* tree, int val) {

	if (!tree || IsLeftMax(tree) && tree->left_val == val) {
		DestroyTree(tree);
		return NULL;
	}
	if (val == tree->left_val) {
		Separate(tree->left->firstleft, tree->left, tree->left->firstright);
		if (IsNotNULL(tree))
			return Merge(tree, tree->right, NULL, NULL, tree->left);
		return Merge(tree, tree->mid, NULL, tree->right, tree->left);
	}
	else if (val == tree->max_son) {
		Separate(tree->right->firstleft, tree->right, tree->right->firstright);
		return Merge(tree, tree->left, NULL, tree->mid, tree->right);
	}
	else if (IsTreeSons(tree) && val == tree->right_val) {
		Separate(tree->mid->firstleft, tree->mid, tree->mid->firstright);
		return Merge(tree, tree->left, NULL, tree->right, tree->mid);
	}
	return tree;
}

Tree23* SecondDelete(Tree23* tree, Tree23* left, Tree23* mid, Tree23* right) {

	if (IsLeftMax(left)) {
		if (IsNotNULL(mid)) {
			left = Merge(left, left->left, mid->left, mid->right, mid);
			return Update(tree, left, NULL, right);
		}
		mid = Split(left, NULL, mid, NULL, left->left, mid->left, mid->mid, mid->right);
		return Merge(tree, mid->left, mid->right, right, mid);
	}
	else if (IsLeftMax(mid)) {
		if (IsNotNULL(left)) {
			mid = Merge(mid, left->left, left->right, mid->left, left);
			return Update(tree, mid, NULL, right);
		}
		else if (IsNotNULL(right)) {
			mid = Merge(mid, mid->left, right->left, right->right, right);
			return Update(tree, left, NULL, mid);
		}
		left = Split(left, NULL, mid, NULL, left->left, left->mid, left->right, mid->left);
		return Merge(tree, left->left, left->right, right, left);
	}
	else if (IsLeftMax(right)) {
		if (IsNotNULL(mid)) {
			right = Merge(right, mid->left, mid->right, right->left, mid);
			return Update(tree, left, NULL, right);
		}
		mid = Split(mid, NULL, right, NULL, mid->left, mid->mid, mid->right, right->left);
		return Merge(tree, left, mid->left, mid->right, mid);
	}
	return Update(tree, left, mid, right);
}

Tree23* Delete(Tree23* tree, int val) {

	Tree23* node = NULL;
	if (CheckLeftNULL(tree))
		return FirstDelete(tree, val);
	if (val <= tree->left_val) {
		node = Delete(tree->left, val);
		if (IsLeftMax(node)) {
			if (IsNotNULL(tree)) {
				if (IsNotNULL(tree->right)) {
					node->left = Merge(tree, node->left, tree->right->left, tree->right->right, tree->right);
					return node;
				}
				return Split(node, tree, tree->right, NULL, node->left, tree->right->left, tree->right->mid, tree->right->right);
			}
			return SecondDelete(tree, node, tree->mid, tree->right);
		}
	}
	else if (IsTreeSons(tree) && val <= tree->right_val && val > tree->left_val) {
		node = Delete(tree->mid, val);
		if (IsLeftMax(node))
			return SecondDelete(tree, tree->left, node, tree->right);
	}
	else if (val > IsTreeSons(tree) ? tree->right_val : tree->left_val && val <= tree->max_son) {
		node = Delete(tree->right, val);
		if (IsLeftMax(node)) {
			if (IsNotNULL(tree)) {
				if (IsNotNULL(tree->left)) {
					node->left = Merge(tree, tree->left->left, tree->left->right, node->left, tree->left);
					return node;
				}
				return Split(tree->left, tree, node, NULL, tree->left->left, tree->left->mid, tree->left->right, node->left);
			}
			return SecondDelete(tree, tree->left, tree->mid, node);
		}
	}
	return Merge(tree, tree->left, tree->mid, tree->right, NULL);
}

Tree23* DeleteNumber(Tree23* tree, int val) {

	tree = Delete(tree, val);
	if (IsLeftMax(tree) && !CheckLeftNULL(tree)) {
		Tree23* node = tree->left;
		DeleteNode(tree);
		return node;
	}
	else
		return tree;
}

Tree23* FindNumber(Tree23* tree, int val) {

	if (tree) {
		if (tree->left == NULL && tree->right == NULL && tree->mid == NULL)
			return val == tree->left_val ? tree : NULL;
		else if (val <= tree->left_val)
			return FindNumber(tree->left, val);
		else if (tree->mid != NULL && val <= tree->right_val && val > tree->left_val)
			return FindNumber(tree->mid, val);
		return FindNumber(tree->right, val);
	}
	else
		return NULL;
}

void Print(Tree23* tree) {

	if (tree) {
		while (!CheckLeftNULL(tree))
			tree = tree->left;
		if (tree) {
			tree = tree->left;
			while (tree) {
				printf("%d ", tree->left_val);
				tree = tree->firstright;
			}
		}
	}
}


int main(void) {

	Tree23* tree = NULL;
	int letter, number;

	letter = getchar();
	while (letter != EOF) {

		scanf("%d", &number);
		switch (letter) {
		case 'a':
			tree = InsertNumber(tree, number);
			break;
		case 'r':
			tree = DeleteNumber(tree, number);
			break;
		case 'f':
			printf(FindNumber(tree, number) == NULL ? "no\n" : "yes\n");
			break;
		default:
			break;
		}

		letter = getchar();
		if (letter == '\n')
			letter = getchar();
	}
	Print(tree);
	DestroyTree(tree);
	return 0;
}



