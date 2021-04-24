#include "b+_tree.h"

Btree* tree_create() {
	int i;
	Btree* root = (Btree*)malloc(sizeof(Btree));
	if (root) {
		root->leaf = TRUE;
		root->key_count = 0;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		for (i = 0; i < 2 * DEGREE + 1; i++) {
			root->child[i] = NULL;
		}
	}
	return root;
}

void tree_delete(Btree** root) {
	int i;
	if (!(*root)->leaf) {
		for (i = 0; i < (*root)->key_count; i++) {
			tree_delete(&((*root)->child[i]));
		}
	}
	free(*root);
	*root = NULL;
}

void split(Btree** root, Btree* node) {
	int i, key, pos;
	Btree* new_node = tree_create();
	if (node->right) {
		new_node->right = node->right;
		node->right->left = new_node;
		node->right = new_node;
		new_node->left = node;
	}
	else {
		new_node->right = node->right;
		node->right = new_node;
		new_node->left = node;
	}

	key = node->key[DEGREE];
	new_node->key_count = DEGREE - 1;
	node->key_count = DEGREE;
	for (i = 0; i < new_node->key_count; i++) {
		new_node->key[i] = node->key[i + DEGREE + 1];
		new_node->child[i] = node->child[i + DEGREE + 1];
		node->child[i + DEGREE + 1] = NULL;
	}
	new_node->child[new_node->key_count] = node->child[2 * DEGREE];
	node->child[2 * DEGREE] = NULL;

	if (node->leaf) {
		new_node->key_count++;
		new_node->leaf = TRUE;
		for (i = new_node->key_count - 1; i >= 1; i--) {
			new_node->key[i] = new_node->key[i - 1];
		}
		new_node->key[0] = node->key[DEGREE];
	}

	if (node == (*root)) {
		(*root) = (Btree*)malloc(sizeof(Btree));
		if (*root) {
			(*root)->key[0] = key;
			(*root)->child[0] = node;
			(*root)->child[1] = new_node;

			for (i = 0; i < 2 * DEGREE + 1; i++) {
				if (new_node->child[i]) {
					new_node->child[i]->parent = new_node;
				}
				if (node->child[i]) {
					node->child[i]->parent = node;
				}
			}
			(*root)->leaf = FALSE;
			(*root)->parent = NULL;
			(*root)->left = NULL;
			(*root)->right = NULL;
			for (i = 2; i < 2 * DEGREE + 1; i++) {
				(*root)->child[i] = NULL;
			}
			(*root)->key_count = 1;
			node->parent = (*root);
			new_node->parent = (*root);
		}
	}
	else {
		new_node->parent = node->parent;
		Btree* parent = node->parent;

		pos = 0;
		while (pos < parent->key_count && (parent->key[pos] < key)) {
			pos++;
		}

		for (i = parent->key_count; i >= pos + 1; i--) {
			parent->key[i] = parent->key[i - 1];
		}
		for (i = parent->key_count + 1; i >= pos + 2; i--) {
			parent->child[i] = parent->child[i - 1];
		}
		for (i = 0; i < 2 * DEGREE; i++) {
			if (new_node->child[i]) {
				new_node->child[i]->parent = new_node;
			}
		}
		parent->key[pos] = key;
		parent->child[pos + 1] = new_node;
		parent->key_count++;

		if (parent->key_count == 2 * DEGREE) {
			split(root, parent);
		}
	}
}
Btree* leaf_find(Btree* root, int key) {
	Btree* current = NULL;
	int i;
	if (root) {
		current = root;
		while (current->leaf != TRUE) {
			for (i = 0; i <= current->key_count; i++) {
				if (i == current->key_count || key < current->key[i]) {
					current = current->child[i];
					break;
				}
			}
		}
	}
	return current;
}
bool_t elem_insert(Btree** root, int key) {
	int i, pos = 0;
	Btree* leaf = leaf_find(*root, key);
	if (!leaf) {
		return FALSE;
	}
	for (i = 0; i < leaf->key_count; i++) {
		if (leaf->key[i] == key) {
			return FALSE;
		}
	}
	while ((pos < leaf->key_count) && (leaf->key[pos] < key)) {
		pos++;
	}
	for (i = leaf->key_count; i >= pos + 1; i--) {
		leaf->key[i] = leaf->key[i - 1];
	}
	leaf->key[pos] = key;
	leaf->key_count++;
	if (leaf->key_count == 2 * DEGREE) {
		split(root, leaf);
	}
	return TRUE;
}
int minimum(Btree* node) {
	for (int i = 0; i < 2 * DEGREE; i++) {
		if (node->child[i]) {
			return minimum(node->child[i]);
		}
	}
	return node->key[0];
}
void tree_update(Btree* node, int key) {
	Btree* update = node->parent;
	int pos = 0;

	while (update) {
		while ((pos < update->key_count) && (update->key[pos] < key)) {
			pos++;
		}
		if (pos < update->key_count) {
			if (update->key[pos] != minimum(update->child[pos + 1])) {
				update->key[pos] = minimum(update->child[pos + 1]);
			}
		}
		update = update->parent;
	}
}
void merge(Btree** root, Btree* node, int key) {
	Btree* parent = node->parent;
	Btree* right = node->right;
	Btree* left = node->left;
	int i, pos = 0;
	Btree* tmp = NULL;
	if (right && (right->parent == node->parent)) {
		for (i = 0; i < right->key_count; i++) {
			node->key[node->key_count] = right->key[i];
			node->child[node->key_count + 1] = right->child[i];
			if (right->child[i]) {
				right->child[i]->parent = node;
			}
			node->key_count++;
		}
		node->child[node->key_count + 1] = right->child[right->key_count];
		if (right->child[right->key_count]) {
			right->child[right->key_count]->parent = node;
		}
		if (right->right) {
			right->right->left = node;
		}
		node->right = right->right;
		del_from_node(root, node->parent, minimum(right));
		tree_update(node, key);
	}
	else {
		for (i = 0; i < node->key_count; i++) {
			left->key[left->key_count] = node->key[i];
			left->child[left->key_count + 1] = node->child[i];
			if (node->child[i]) {
				node->child[i]->parent = left;
			}
			left->key_count++;
		}
		left->child[left->key_count + 1] = node->child[node->key_count];
		if (node->child[node->key_count]) {
			node->child[node->key_count]->parent = left;
		}
		left->right = node->right;
		if (node->right) {
			node->right->left = left;
		}
		del_from_node(root, left->parent, minimum(node));
		tree_update(left, key);
	}
}
void del_from_node(Btree** root, Btree* node, int key) {
	int i, pos = 0, flag = 0;
	Btree* right;
	Btree* left;
	while ((pos < node->key_count) && (node->key[pos] < key)) {
		pos++;
	}
	for (i = pos; i < node->key_count; i++) {
		node->key[i] = node->key[i + 1];
	}
	for (i = pos + 1; i <= node->key_count; i++) {
		node->child[i] = node->child[i + 1];
	}
	for (i = node->key_count + 1; i < 2 * DEGREE + 1; i++) {
		*(node->child + i) = NULL;
	}
	node->key_count--;
	if (node == (*root)) {
		for (i = 0; i < 2 * DEGREE + 1; i++) {
			if (node->child[i]) {
				if (node->child[i]->key_count == 0) {
					node->child[i] = NULL;
				}
			}
		}
		if ((*root)->key_count == 0 && (*root)->child[0]) {
			(*root) = (*root)->child[0];
		}
		return;
	}
	if (node->key_count >= DEGREE / 2 - 1) {
		tree_update(node, key);
	}
	else {
		right = node->right;
		left = node->left;
		if (left && left->key_count > DEGREE - 1 && (left->parent == node->parent)) {
			left->key_count--;
			node->key_count++;
			for (i = 1; i < node->key_count; i++) {
				node->key[i] = node->key[i - 1];
				node->child[i] = node->child[i - 1];
			}
			node->child[node->key_count] = node->child[node->key_count - 1];
			node->key[0] = left->key[left->key_count];
			node->child[0] = left->child[left->key_count + 1];
			left->child[left->key_count + 1] = NULL;
			if (node->child[0]) {
				node->child[0]->parent = node;
			}
			tree_update(node, key);
		}
		else if (right && right->key_count > DEGREE - 1 && (right->parent == node->parent)) {
			node->key_count++;
			node->key[node->key_count - 1] = right->key[0];
			node->child[node->key_count] = right->child[0];
			if (node->child[node->key_count]) {
				node->child[node->key_count]->parent = node;
			}
			for (i = 0; i < right->key_count; i++) {
				right->key[i] = right->key[i + 1];
				right->child[i] = right->child[i + 1];
			}
			for (i = 0; i < 2 * DEGREE; i++) {
				if (right->child[i] == right->child[i + 1] && right->child[i] != NULL) {
					right->child[i + 1] = NULL;
					break;
				}
			}
			right->key_count--;
			tree_update(node, key);
		}
		else {
			merge(root, node, key);
		}
	}
}

bool_t elem_delete(Btree** root, int key) {
	int i, pos = 0, flag = 0;
	Btree* leaf = leaf_find(*root, key);
	for (i = 0; i < leaf->key_count; i++) {
		if (leaf->key[i] == key) {
			flag = 1;
			break;
		}
	}
	if (!flag) {
		return FALSE;
	}
	del_from_node(root, leaf, key);
	return TRUE;
}

bool_t elem_find(Btree** root, int key) {
	Btree* leaf = leaf_find(*root, key);
	for (int i = 0; i < leaf->key_count; i++) {
		if (leaf->key[i] == key)
			return TRUE;
	}
	return FALSE;
}