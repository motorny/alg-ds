#include "2-3_tree.h"
#include <stdlib.h>
#include <stdio.h>

#define IsLeaf(x) (x->child[0] == NULL && x->child[1] == NULL && x->child[2] == NULL)

//FIND FUNCTION

tree_t* Find(tree_t* t, int key) {
	if (t == NULL)
		return NULL;
	tree_t* temp = NULL;

	for (int i = 0; i < t->count; i++) {
		if (key == t->keys[i])
			return t;
	}

	if (key < t->keys[0]) {
		temp = Find(t->child[0], key);
	}
	else if (t->count == 1) {
		temp = Find(t->child[1], key);
	}
	else {
		if (key < t->keys[1])
			temp = Find(t->child[1], key);
		else
			temp = Find(t->child[2], key);
	}
	return temp;
}

//INSERT FUNCTION

void Swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
tree_t* InitNode(int key, tree_t* c1, tree_t* c2, tree_t* c3, tree_t* p) {
	tree_t* t;
	t = malloc(sizeof(tree_t));
	if (t == NULL)
		return NULL;

	t->keys[0] = key;
	t->keys[1] = -1;
	t->keys[2] = -1;
	t->count = 1;
	t->child[0] = c1;
	t->child[1] = c2;
	t->child[2] = c3;
	t->child[3] = NULL;
	t->parent = p;

	return t;
}
void SortKeys(tree_t* t) {
	int temp;
	if (t->count == 1) 
		return;
	else {
		if (t->keys[0] > t->keys[1]) {
			temp = t->keys[1];
			t->keys[1] = t->keys[0];
			t->keys[0] = temp;
		}

		if (t->count == 3) {
			if (t->keys[0] > t->keys[2]) {
				temp = t->keys[2];
				t->keys[2] = t->keys[0];
				t->keys[0] = temp;
			}
			if (t->keys[1] > t->keys[2]) {
				temp = t->keys[2];
				t->keys[2] = t->keys[1];
				t->keys[1] = temp;
			}
		}
	}
}
void AddToNode(tree_t* t, int key) {
	t->keys[t->count++] = key;
	SortKeys(t);
}
tree_t* Split(tree_t* t) {
	tree_t* x = InitNode(t->keys[0], t->child[0], t->child[1], NULL, t->parent);
	if (x == NULL)
		return NULL;
	tree_t* y = InitNode(t->keys[2], t->child[2], t->child[3], NULL, t->parent);
	if (y == NULL) {
		free(x);
		return NULL;
	}
	if (x->child[0])
		x->child[0]->parent = x;
	if (x->child[1])
		x->child[1]->parent = x;
	if (y->child[0])
		y->child[0]->parent = y;
	if (y->child[1])
		y->child[1]->parent = y;

	if (t->parent) {
		AddToNode(t->parent, t->keys[1]);

		if (t->parent->child[0] == t) 
			t->parent->child[0] = NULL;
		else if (t->parent->child[1] == t)
			t->parent->child[1] = NULL;
		else if (t->parent->child[2] == t)
			t->parent->child[2] = NULL;

		if (t->parent->child[0] == NULL) {
			t->parent->child[3] = t->parent->child[2];
			t->parent->child[2] = t->parent->child[1];
			t->parent->child[1] = y;
			t->parent->child[0] = x;
		}
		else if (t->parent->child[1] == NULL) {
			t->parent->child[3] = t->parent->child[2];
			t->parent->child[2] = y;
			t->parent->child[1] = x;
		}
		else {
			t->parent->child[3] = y;
			t->parent->child[2] = x;
		}

		tree_t* temp = t->parent;
		free(t);
		return temp;
	}
	else {
		x->parent = t;
		y->parent = t;

		t->keys[0] = t->keys[1];
		t->child[0] = x;
		t->child[1] = y;
		t->child[2] = NULL;
		t->child[3] = NULL;
		t->parent = NULL;
		t->count = 1;
		return t;
	}
}
tree_t* Add(tree_t* t, int key) {
	if (t == NULL) {
		t = InitNode(key, NULL, NULL, NULL, NULL);
		return t;
	}
	if (IsLeaf(t)) {
		AddToNode(t, key);
	}
	else if (key < t->keys[0]) {
		Add(t->child[0], key);
	}
	else if ((t->count == 1) || ((t->count == 2) && (key < t->keys[1]))) {
		Add(t->child[1], key);
	}
	else {
		Add(t->child[2], key);
	}

	if (t->count <= 2) 
		return t;
	else 
		return Split(t);
}

//DELETE FUNCTION

void DelFromNode(tree_t* t, int key) {
	if (t->count >= 1 && t->keys[0] == key) {
		t->keys[0] = t->keys[1];
		t->keys[1] = t->keys[2];
		t->count--;
	}
	else if (t->count == 2 && t->keys[1] == key) {
		t->keys[1] = t->keys[2];
		t->count--;
	}
}
tree_t* Redistribute(tree_t* leaf) {
	tree_t* parent = leaf->parent;
	tree_t* child[3] = { parent->child[0], parent->child[1], parent->child[2] };

	if ((parent->count == 2) && (child[0]->count < 2) && (child[1]->count < 2) && (child[2]->count < 2)) {
		if (child[0] == leaf) {
			parent->child[0] = parent->child[1];
			parent->child[1] = parent->child[2];
			parent->child[2] = NULL;
			AddToNode(parent->child[0], parent->keys[0]);

			parent->child[0]->child[2] = parent->child[0]->child[1];
			parent->child[0]->child[1] = parent->child[0]->child[0];

			if (leaf->child[0] != NULL)
				parent->child[0]->child[0] = leaf->child[0];
			else if (leaf->child[1] != NULL)
				parent->child[0]->child[0] = leaf->child[1];
			
			if (parent->child[0]->child[0] != NULL)
				parent->child[0]->child[0]->parent = parent->child[0];

			DelFromNode(parent, parent->keys[0]);
			free(child[0]);
		}
		else if (child[1] == leaf) {
			AddToNode(child[0], parent->keys[0]);
			DelFromNode(parent, parent->keys[0]);

			if (leaf->child[0] != NULL)
				child[0]->child[2] = leaf->child[0];
			else if (leaf->child[1] != NULL)
				child[0]->child[2] = leaf->child[1];

			if (child[0]->child[2] != NULL)
				child[0]->child[2]->parent = child[0];

			parent->child[1] = parent->child[2];
			parent->child[2] = NULL;

			free(child[1]);
		}
		else if (child[2] == leaf) {
			AddToNode(child[1], parent->keys[1]);
			parent->child[2] = NULL;
			DelFromNode(parent, parent->keys[1]);

			if (leaf->child[0] != NULL)
				child[1]->child[2] = leaf->child[0];
			else if (leaf->child[1] != NULL)
				child[1]->child[2] = leaf->child[1];

			if (child[1]->child[2] != NULL)
				child[1]->child[2]->parent = child[1];

			free(child[2]);
		}
	}
	else if ((parent->count == 2) && ((child[0]->count == 2) || (child[1]->count == 2) || (child[2]->count == 2))) {
		if (child[2] == leaf) {
			if (leaf->child[0] != NULL) {
				leaf->child[1] = leaf->child[0];
				leaf->child[0] = NULL;
			}

			AddToNode(leaf, parent->keys[1]);
			if (child[1]->count == 2) {
				parent->keys[1] = child[1]->keys[1];
				DelFromNode(child[1], child[1]->keys[1]);

				leaf->child[0] = child[1]->child[2];
				child[1]->child[2] = NULL;
				if (leaf->child[0] != NULL)
					leaf->child[0]->parent = leaf;
			}
			else if (child[0]->count == 2) {
				parent->keys[1] = child[1]->keys[0];
				leaf->child[0] = child[1]->child[1];
				child[1]->child[1] = child[1]->child[0];
				if (leaf->child[0] != NULL)
					leaf->child[0]->parent = leaf;

				child[1]->keys[0] = parent->keys[0];
				parent->keys[0] = child[0]->keys[1];
				DelFromNode(child[0], child[0]->keys[1]);

				child[1]->child[0] = child[0]->child[2];
				if (child[1]->child[0] != NULL)
					child[1]->child[0]->parent = child[1];
				child[0]->child[2] = NULL;
			}
		}
		else if (child[1] == leaf) {
			if (child[2]->count == 2) {
				if (leaf->child[0] == NULL) {
					leaf->child[0] = leaf->child[1];
					leaf->child[1] = NULL;
				}
				AddToNode(child[1], parent->keys[1]);
				parent->keys[1] = child[2]->keys[0];
				DelFromNode(child[2], child[2]->keys[0]);

				child[1]->child[1] = child[2]->child[0];
				if (child[1]->child[1] != NULL)
					child[1]->child[1]->parent = child[1];

				child[2]->child[0] = child[2]->child[1];
				child[2]->child[1] = child[2]->child[2];
				child[2]->child[2] = NULL;
			}
			else if (child[0]->count == 2) {
				if (leaf->child[1] == NULL)
					leaf->child[1] = leaf->child[0];
				leaf->child[0] = NULL;
			}

			AddToNode(child[1], parent->keys[0]);
			parent->keys[0] = child[0]->keys[1];
			DelFromNode(child[0], child[0]->keys[1]);

			child[1]->child[0] = child[0]->child[2];
			if (child[1]->child[0] != NULL)
				child[1]->child[0]->parent = child[1];

			child[0]->child[2] = NULL;
		}
		else if (child[0] == leaf) {
			if (leaf->child[0] == NULL) {
				leaf->child[0] = leaf->child[1];
				leaf->child[1] = NULL;
			}
			AddToNode(child[0], parent->keys[0]);

			if (child[1]->count == 2) {
				parent->keys[0] = child[1]->keys[0];
				DelFromNode(child[1], child[1]->keys[0]);
				child[0]->child[1] = child[1]->child[0];
				if (child[0]->child[1] != NULL)
					child[0]->child[1]->parent = child[0];
				child[1]->child[0] = child[1]->child[1];
				child[1]->child[1] = child[1]->child[2];
				child[1]->child[2] = NULL;
			}
			else if (child[2]->count == 2) {
				parent->keys[0] = child[1]->keys[0];
				child[1]->keys[0] = parent->keys[1];
				parent->keys[1] = child[2]->keys[0];
				DelFromNode(child[2], child[2]->keys[0]);
				child[0]->child[1] = child[1]->child[0];
				if (child[0]->child[1] != NULL)
					child[0]->child[1]->parent = child[0];
				child[1]->child[0] = child[1]->child[1];
				child[1]->child[1] = child[2]->child[0];
				if (child[1]->child[1] != NULL)
					child[1]->child[1]->parent = child[1];
				child[2]->child[0] = child[2]->child[1];
				child[2]->child[1] = child[2]->child[2];
				child[2]->child[2] = NULL;
			}
		}
	}
	else if (parent->count == 1) {
		AddToNode(leaf, parent->keys[0]);
		if (child[0] == leaf && child[1]->count == 2) {
			parent->keys[0] = child[1]->keys[0];
			DelFromNode(child[1], child[1]->keys[0]);

			if (leaf->child[0] == NULL)
				leaf->child[0] = leaf->child[1];

			leaf->child[1] = child[1]->child[0];
			child[1]->child[0] = child[1]->child[1];
			child[1]->child[1] = child[1]->child[2];
			child[1]->child[2] = NULL;

			if (leaf->child[1] != NULL)
				leaf->child[1]->parent = leaf;
		}
		else if (child[1] == leaf && child[0]->count == 2) {
			parent->keys[0] = child[0]->keys[1];
			DelFromNode(child[0], child[0]->keys[1]);

			if (leaf->child[1] == NULL)
				leaf->child[1] = leaf->child[0];

			leaf->child[0] = child[0]->child[2];
			child[0]->child[2] = NULL;

			if (leaf->child[0] != NULL)
				leaf->child[0]->parent = leaf;
		}
	}
	return parent;
}
tree_t* Merge(tree_t* leaf) {
	tree_t* parent = leaf->parent;

	if (parent->child[0] == leaf) {
		AddToNode(parent->child[1], parent->keys[0]);
		parent->child[1]->child[2] = parent->child[1]->child[1];
		parent->child[1]->child[1] = parent->child[1]->child[0];

		if (leaf->child[0] != NULL)
			parent->child[1]->child[0] = leaf->child[0];
		else if (leaf->child[1] != NULL)
			parent->child[1]->child[0] = leaf->child[1];

		if (parent->child[1]->child[0] != NULL)
			parent->child[1]->child[0]->parent = parent->child[1];

		DelFromNode(parent, parent->keys[0]);
		free(parent->child[0]);
		parent->child[0] = NULL;
	}
	else if (parent->child[1] == leaf) {
		AddToNode(parent->child[0], parent->keys[0]);

		if (leaf->child[0] != NULL)
			parent->child[0]->child[2] = leaf->child[0];
		else if (leaf->child[1] != NULL)
			parent->child[0]->child[2] = leaf->child[1];
		if (parent->child[0]->child[2] != NULL)
			parent->child[0]->child[2]->parent = parent->child[0];

		DelFromNode(parent, parent->keys[0]);
		free(parent->child[1]);
		parent->child[1] = NULL;
	}
	if (parent->parent == NULL) {
		tree_t* temp = NULL;
		if (parent->child[0] != NULL)
			temp = parent->child[0];
		else
			temp = parent->child[1];

		temp->parent = NULL;
		free(parent);
		return temp;
	}
	return parent;
}
tree_t* Fix(tree_t* leaf) {
	if (leaf->count == 0 && leaf->parent == NULL) {
		free(leaf);
		return NULL;
	}
	if (leaf->count != 0) {
		if (leaf->parent)
			return Fix(leaf->parent);
		else
			return leaf;
	}
	tree_t* parent = leaf->parent;
	if (parent->child[0]->count == 2 || parent->child[1]->count == 2 || parent->count == 2)
		leaf = Redistribute(leaf);
	else if (parent->count == 2 && parent->child[2]->count == 2)
		leaf = Redistribute(leaf);
	else
		leaf = Merge(leaf);
	return Fix(leaf);
}
tree_t* FindMin(tree_t* t) {
	if (t == NULL)
		return t;
	if (t->child[0] == NULL)
		return t;
	else
		return FindMin(t->child[0]);
}
tree_t* Del(tree_t* t, int key) {
	tree_t* item = Find(t, key);
	if (item == NULL)
		return t;

	tree_t* min;
	if (item->keys[0] == key)
		min = FindMin(item->child[1]);
	else
		min = FindMin(item->child[2]);

	if (min != NULL) {
		int* a = (key == item->keys[0] ? &(item->keys[0]) : &(item->keys[1]));
		Swap(a, &(min->keys[0]));

		item = min;
	}
	DelFromNode(item, key);
	return Fix(item);
}

//PRINT FUNCTION

void PrintTreeCur(tree_t* t, int depth) {
	int i;
	if (t != NULL) {
		PrintTree(t->child[0], depth + 1);
		for (int i = 0; i < depth; i++)
			printf("       ");

		if (t->count == 1)
			printf("%d<\n", t->keys[0]);
		else if (t->count == 2)
			printf("%d, %d<\n", t->keys[0], t->keys[1]);

		PrintTree(t->child[1], depth + 1);
		for (int i = 0; i < depth; i++)
			printf("       ");

		if (t->count == 1)
			printf("%d<\n", t->keys[0]);
		else if (t->count == 2)
			printf("%d, %d<\n", t->keys[0], t->keys[1]);

		PrintTree(t->child[2], depth + 1);
	}
}
void PrintTree(tree_t* tree) {
	PrintTreeCur(tree, 0);
}