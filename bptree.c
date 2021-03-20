#include"bptree.h"
#include<stdlib.h>
#include<string.h>

BPtree* init() {
	node* nodet = (node*)malloc(sizeof(node));
	if (nodet) {
		nodet->leaf = TRUE;
		nodet->key_num = 0;
		nodet->left = NULL;
		nodet->right = NULL;
		nodet->parent = NULL;
		for (int i = 0; i < 2 * t + 1; i++) {
			nodet->child[i] = NULL;
		}
	}
	BPtree* tree = (BPtree*)malloc(sizeof(BPtree));
	if (tree) {
		tree->root = nodet;
	}
	return tree;
}


void destroy(BPtree* tree) {
	if (tree) {
		destroyNode(tree->root);
		free(tree);
	}
}

void destroyNode(node* node) {
	if (!node->leaf) {
		for (int i = 0; i < node->key_num + 1; i++) {
			destroyNode(node->child[i]);
		}
	}
	free(node);
}
node* findNode(BPtree* tree, int key) {
	node* cur = NULL;
	if(tree)
	  cur = tree->root;
	if (cur) {
		while (cur->leaf != TRUE) {
			for (int i = 0; i <= cur->key_num; i++) {
				if (i == cur->key_num || key < cur->key[i]) {
					cur = cur->child[i];
					break;
				}
			}
		}
	}
	return cur;
}


bool_t insert(BPtree* tree, int key) {
	node* leaf = findNode(tree, key);
	if (!leaf)
		return FALSE;
	for (int i = 0; i < leaf->key_num; i++) {
		if (leaf->key[i] == key)
			return FALSE;
	}
	int pos = 0;
	while ((pos < leaf->key_num) && (leaf->key[pos] < key))
		++pos;

	for (int i = leaf->key_num; i >= pos + 1; i--) {
		leaf->key[i] = leaf->key[i - 1];
	}
	leaf->key[pos] = key;
	leaf->key_num++;
	if (leaf->key_num == 2 * t)
		split(tree, leaf);
	return TRUE;
}
void split(BPtree* tree, node* cnode) {
	node* newnode = malloc(sizeof(node));
	newnode->leaf = FALSE;
	newnode->key_num = 0;
	newnode->left = NULL;
	newnode->right = NULL;
	for (int i = 0; i < 2 * t + 1; i++) {
		newnode->child[i] = NULL;
	}
	if (cnode->right) {
		newnode->right = cnode->right;
		cnode->right->left = newnode;
		cnode->right = newnode;
		newnode->left = cnode;
	}
	else {
		newnode->right = cnode->right;
		cnode->right = newnode;
		newnode->left = cnode;
	}

	int mid_key = cnode->key[t];
	newnode->key_num = t - 1;
	cnode->key_num = t;
	for (int i = 0; i < newnode->key_num; i++) {
		newnode->key[i] = cnode->key[i + t + 1];
		newnode->child[i] = cnode->child[i + t + 1];
		cnode->child[i + t + 1] = NULL;

	}
	newnode->child[newnode->key_num] = cnode->child[2 * t];
	cnode->child[2 * t] = NULL;

	if (cnode->leaf) {
		newnode->key_num++;
		newnode->leaf = TRUE;

		for (int i = newnode->key_num - 1; i >= 1; i--) {
			newnode->key[i] = newnode->key[i - 1];
		}
		newnode->key[0] = cnode->key[t];
	}

	if (cnode == tree->root) {
		tree->root = malloc(sizeof(node));
		if (tree->root) {
			tree->root->key[0] = mid_key;
			tree->root->child[0] = cnode;
			tree->root->child[1] = newnode;

			for (int i = 0; i < 2 * t + 1; i++) {
				if (newnode->child[i]) {
					newnode->child[i]->parent = newnode;
				}
				if (cnode->child[i]) {
					cnode->child[i]->parent = cnode;
				}
			}
			tree->root->leaf = FALSE;
			tree->root->parent = NULL;
			tree->root->left = NULL;
			tree->root->right = NULL;
			for (int i = 2; i < 2 * t + 1; i++) {
				tree->root->child[i] = NULL;
			}
			tree->root->key_num = 1;
			cnode->parent = tree->root;
			newnode->parent = tree->root;
		}
	}
	else {
		newnode->parent = cnode->parent;
		node* parent = cnode->parent;

		int pos = 0;
		while (pos < parent->key_num && (parent->key[pos] < mid_key))
			pos++;

		for (int i = parent->key_num; i >= pos + 1; i--) {
			parent->key[i] = parent->key[i - 1];
		}
		for (int i = parent->key_num + 1; i >= pos + 2; i--) {
			parent->child[i] = parent->child[i - 1];
		}
		for (int i = 0; i < 2 * t; i++) {
			if (newnode->child[i]) {
				newnode->child[i]->parent = newnode;
			}
		}
		parent->key[pos] = mid_key;
		parent->child[pos + 1] = newnode;
		parent->key_num++;

		if (parent->key_num == 2 * t)
			split(tree, parent);
	}
}

void printTree(node* tree, char* dir, int level) {
	if (tree) {
		for (int i = 0; i < tree->key_num; i++) {
			if (strcmp("child", dir) != 1)
				printf("lvl %d key = %d\n", level, tree->key[i]);
			else
				printf("lvl %d child = %d\n", level, tree->key[i]);
		}
		for (int i = 0; i < 2 * t; i++) {
			if (tree->child[i]) {
				printf("child %d\n", i);
				printTree(tree->child[i], "child", level + 1);
			}
		}
	}
}

bool_t deleteEl(BPtree* tree, int key) {
	node* leaf = findNode(tree, key);
	int pos = 0, flag = 0;
	for (int i = 0; i < leaf->key_num; i++) {
		if (leaf->key[i] == key)
			flag = 1;
	}
	if (!flag)
		return FALSE;
	deleteInNode(tree, leaf, key);
	return TRUE;
}

void deleteInNode(BPtree* tree, node* tec, int key) {
	int pos = 0;
	int flag = 0;
	int i = 0;
	while ((pos < tec->key_num) && (tec->key[pos] < key))
		pos++;

	for (int i = pos; i < tec->key_num; i++) {
		tec->key[i] = tec->key[i + 1];
	}
	for (int i = pos + 1; i <= tec->key_num; i++) {
		tec->child[i] = tec->child[i + 1];
	}
	for (int i = tec->key_num + 1; i < 2 * t + 1; i++) {
		*(tec->child + i) = NULL;
	}
	tec->key_num--;
	if (tec == tree->root) {
		for (int i = 0; i < 2 * t + 1; i++) {
			if (tec->child[i]) {
				if (tec->child[i]->key_num == 0) {
					tec->child[i] = NULL;
				}
			}
		}
		if (tree->root->key_num == 0 && tree->root->child[0]) {
			tree->root = tree->root->child[0];
		}
		return;
	}
	if (tec->key_num >= t/ 2- 1) {
		update(tree, tec, key);
	}
	else {
		node* right_sibling = tec->right;
		node* left_sibling = tec->left;
		if (left_sibling && left_sibling->key_num > t - 1 && (left_sibling->parent == tec->parent)) {
			left_sibling->key_num--;
			tec->key_num++;
			for (int i = 1; i < tec->key_num; i++) {
				tec->key[i] = tec->key[i - 1];
				tec->child[i] = tec->child[i - 1];
			}
			tec->child[tec->key_num] = tec->child[tec->key_num - 1];
			tec->key[0] = left_sibling->key[left_sibling->key_num];
			tec->child[0] = left_sibling->child[left_sibling->key_num + 1];
			left_sibling->child[left_sibling->key_num + 1] = NULL;
			if (tec->child[0]) {
				tec->child[0]->parent = tec;
			}
			update(tree, tec, key);
		}
		else if (right_sibling && right_sibling->key_num > t - 1 && (right_sibling->parent == tec->parent)) {
			tec->key_num++;

			tec->key[tec->key_num - 1] = right_sibling->key[0];
			tec->child[tec->key_num] = right_sibling->child[0];
			if (tec->child[tec->key_num])
				tec->child[tec->key_num]->parent = tec;
			for (int i = 0; i < right_sibling->key_num; i++) {
				right_sibling->key[i] = right_sibling->key[i + 1];
				right_sibling->child[i] = right_sibling->child[i + 1];
			}
			for (int i = 0; i < 2 * t; i++) {
				if (right_sibling->child[i] == right_sibling->child[i + 1] && right_sibling->child[i] != NULL) {
					right_sibling->child[i + 1] = NULL;
					break;
				}
			}
			right_sibling->key_num--;
			update(tree, tec, key);
		}
		else {
			merge(tree, tec, key);
		}
	}
}
void merge(BPtree* tree, node* tec, int key) {
	node* parent = tec->parent;
	node* right_sibling = tec->right;
	node* left_sibling = tec->left;
	int pos = 0;
	node* tmp = NULL;
	if (right_sibling && (right_sibling->parent == tec->parent)) {
		for (int i = 0; i < right_sibling->key_num; i++) {
			tec->key[tec->key_num] = right_sibling->key[i];
			tec->child[tec->key_num + 1] = right_sibling->child[i];
			if (right_sibling->child[i])
				right_sibling->child[i]->parent = tec;
			tec->key_num++;
		}
		tec->child[tec->key_num + 1] = right_sibling->child[right_sibling->key_num];
		if (right_sibling->child[right_sibling->key_num])
			right_sibling->child[right_sibling->key_num]->parent = tec;
		if (right_sibling->right)
			right_sibling->right->left = tec;

		tec->right = right_sibling->right;
		deleteInNode(tree, tec->parent, min_key(right_sibling));
		update(tree, tec, key);
	}
	else {
		for (int i = 0; i < tec->key_num; i++) {
			left_sibling->key[left_sibling->key_num] = tec->key[i];
			left_sibling->child[left_sibling->key_num + 1] = tec->child[i];
			if (tec->child[i])
				tec->child[i]->parent = left_sibling;
			left_sibling->key_num++;
		}
		left_sibling->child[left_sibling->key_num + 1] = tec->child[tec->key_num];
		if (tec->child[tec->key_num]) {
			tec->child[tec->key_num]->parent = left_sibling;
		}

		left_sibling->right = tec->right;
		if (tec->right)
			tec->right->left = left_sibling;

		deleteInNode(tree, left_sibling->parent, min_key(tec));
		update(tree, left_sibling, key);
	}
}
int min_key(node* nodec) {
	for (int i = 0; i < 2 * t; i++) {
		if (nodec->child[i]) {
			return min_key(nodec->child[i]);
		}
	}
	return nodec->key[0];
}


void update(BPtree* tree, node* tec, int key) {
	node* tmp = tec->parent;
	int pos = 0;
	
	while (tmp) {
		while ((pos < tmp->key_num) && (tmp->key[pos] < key))
			pos++;
		if (pos < tmp->key_num) {
			if (tmp->key[pos] != min_key(tmp->child[pos + 1])) {
				tmp->key[pos] = min_key(tmp->child[pos + 1]);
			}
		}
		tmp = tmp->parent;
	}
}

bool_t findEl(BPtree* tree, int key) {
	node* leaf = findNode(tree, key);

	for (int i = 0; i < leaf->key_num; i++) {
		if (leaf->key[i] == key)
			return TRUE;
	}
	return FALSE;
}
