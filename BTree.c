#include "BTree.h"

BTREE* InitNode() {

	BTREE* node = (BTREE*)malloc(sizeof(BTREE));

	if (node == NULL)
		return NULL;

	node->count = 0;
	node->leaf = LEAF;

	for (int i = 0; i < 2 * T; i++) {
		node->children[i] = NULL;
	}

	return node;
}


int FindPos(int val, int* vals, int count) {
	int pos = 0;

	while (pos < count && val > vals[pos])
		pos++;

	return pos;
}


int Search(BTREE* tree, int val) {
	if (!tree)
		return NOTFOUND;

	int i = 0;

	while (i < tree->count && val > tree->vals[i]) 
		i++;

	if (i < tree->count && val == tree->vals[i])
		return FOUND;
	else if (tree->leaf == LEAF)
		return NOTFOUND;

	return Search(tree->children[i], val);
}


void InsertToFull(BTREE* node, int val) {
	int pos = node->count - 1;

	if (node->leaf == LEAF) {

		while (pos >= 0 && val < node->vals[pos]) {
			node->vals[pos + 1] = node->vals[pos];
			pos--;
		}

		node->count++;
		node->vals[pos + 1] = val;
	}

	else {
		while (pos >= 0 && val < node->vals[pos])
			pos--;

		pos++;

		if (node->children[pos]->count == 2 * T - 1) {

			Split(node, pos);
			if (node->vals[pos] < val)
				pos++;
		}

		InsertToFull(node->children[pos], val);
	}
}


void Split(BTREE* node, int pos) {

	BTREE* new = InitNode();
	BTREE* ch = node->children[pos];

	new->count = T - 1;
	new->leaf = ch->leaf;

	for (int i = 0; i < T - 1; i++) {
		new->vals[i] = ch->vals[i + T];
	}

	if (ch->leaf == NOTLEAF) {

		for (int i = 0; i < T; i++) {
			new->children[i] = ch->children[i + T];
			ch->children[i + T] = NULL;
		}
	}

	ch->count = T - 1;
	int j = pos + 1;
	while (node->children[j] != NULL) {
		j++;
	}
	for (j; j > pos + 1; j--) {
		node->children[j] = node->children[j - 1];
		node->vals[j - 1] = node->vals[j - 2];
	}

	node->children[pos + 1] = new;
	node->vals[pos] = ch->vals[T - 1];
	node->count++;
}


void Insert(BTREE** tree, int val) {

	if (!(*tree)) {
		(*tree) = InitNode();
		(*tree)->vals[0] = val;
		(*tree)->count = 1;
		return;
	}

	if (Search((*tree), val) == NOERROR)
		return;

	if ((*tree)->count < 2 * T - 1) {
		InsertToFull((*tree), val);
	}
	else {
		BTREE* new = InitNode();
		BTREE* tmp = (*tree);
		(*tree) = new;

		new->leaf = NOTLEAF;
		new->count = 0;
		new->children[0] = tmp;

		Split(new, 0);
		InsertToFull(new, val);
	}
}


int DeleteKey(BTREE* tree, int value) {

	if (!tree)
		return ERROR;

	int min = (T - 1) / 2;

	int count = tree->count;
	int* vals = tree->vals;
	BTREE** children = tree->children;

	int pos = FindPos(value, vals, count);

	if (!children[0]) {
		if (value < vals[pos] || pos == count)
			return ERROR;
		for (int i = pos + 1; i < count; i++) {
			vals[i - 1] = vals[i];
			children[i] = children[i + 1];
		}
		tree->count--;
		if (tree->count >= min)
			return NOERROR;
		else
			return NOKEYS;
	}

	BTREE* tmp1;
	int count1;
	BTREE* tmp2;

	if (pos < count && value == vals[pos]) {
		tmp1 = children[pos];

		for (;;) {
			count1 = tmp1->count;
			tmp2 = tmp1->children[count1];

			if (!tmp2)
				break;

			tmp1 = tmp2;
		}

		vals[pos] = tmp1->vals[count1 - 1];
		tmp1->vals[count1 - 1] = value;
	}

	int state = DeleteKey(children[pos], value);
	if (state != NOKEYS)
		return state;

	BTREE* left;
	BTREE* right;

	if (pos > 0 && children[pos - 1]->count > min) {

		left = children[pos - 1];
		right = children[pos];

		right->children[right->count + 1] = right->children[right->count];

		for (int i = right->count; i > 0; i--) {
			right->vals[i] = right->vals[i - 1];
			right->children[i] = right->children[i - 1];
		}

		right->count++;
		right->vals[0] = vals[pos - 1];
		right->children[0] = left->children[left->count];
		vals[pos - 1] = left->vals[--left->count];

		return NOERROR;
	}

	if (pos < count && children[pos + 1]->count > min) {

		left = children[pos];
		right = children[pos + 1];

		left->vals[left->count] = vals[pos];
		left->children[left->count + 1] = right->children[0];
		vals[pos] = right->vals[0];
		left->count++;
		right->count--;

		for (int i = 0; i < right->count; i++) {
			right->vals[i] = right->vals[i + 1];
			right->children[i] = right->children[i + 1];
		}

		right->children[right->count] = right->children[right->count + 1];
	}

	if (pos == count) {
		left = children[pos - 1];
		right = children[pos];
		left->vals[left->count] = vals[pos - 1];
	}

	else {
		left = children[pos];
		right = children[pos + 1];
		left->vals[left->count] = vals[pos];
	}

	left->children[left->count + 1] = right->children[0];

	for (int i = 0; i < right->count; i++) {
		left->vals[left->count + i + 1] = right->vals[i];
		left->children[left->count + i + 2] = right->children[i + 1];
	}

	left->count = left->count + right->count + 1;
	free(right);

	for (int i = pos + 1; i < count; i++) {
		vals[i - 1] = vals[i];
		children[i] = children[i + 1];
	}

	tree->count--;

	if (tree->count >= min)
		return NOERROR;
	else 
		return NOKEYS;
}


void Clear(BTREE* tree) {
	if (!tree)
		return;

	if (tree->leaf == NOTLEAF) {
		for (int i = 0; i <= tree->count; i++) {
			Clear(tree->children[i]);
		}
	}

	free(tree);
}


void DestroyTree(BTREE* tree, int val) {
	
	if (!tree)
		return NULL;

	int state = DeleteKey(tree, val);

	if (state == NOKEYS) {

		BTREE* tmp = tree;
		tree = tree->children[0];
		free(tmp);
	}
}

void PrintTree(BTREE* tree, int floor) {
	int i;

	if (!tree)
		return;

	for (i = 0; i <= tree->count - 1; i++) {
		PrintTree(tree->children[i], floor + 1);

		for (int j = 0; j <= floor; j++)
			printf("   ");

		printf("%d\n", tree->vals[i]);
	}
	PrintTree(tree->children[i], floor + 1);
}