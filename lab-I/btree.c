#include "btree.h"

BTREE* CreateNode() {
	BTREE* node = (BTREE*)malloc(sizeof(BTREE));
	if (!node)
		return NULL;
	node->num_of_keys = 0;
	node->leaf = LEAF;
	for (int i = 0; i < 2 * T; i++) {
		node->children[i] = NULL;
	}
	return node;
}

int Position(int value, int* values, int num_of_keys) {
	int pos = 0;
	while (pos < num_of_keys && value > values[pos])
		pos++;
	return pos;
}

void Split(BTREE* node, int position) {
	BTREE* newnode = CreateNode();
	BTREE* fullchild = node->children[position];
	newnode->num_of_keys = T - 1;
	newnode->leaf = fullchild->leaf;
	for (int i = 0; i < T - 1; i++) {
		newnode->values[i] = fullchild->values[i + T];
	}
	if (fullchild->leaf == NOT_LEAF) {
		for (int i = 0; i < T; i++) {
			newnode->children[i] = fullchild->children[i + T];
			fullchild->children[i + T] = NULL;
		}
	}

	fullchild->num_of_keys = T - 1;
	int counter = position + 1;
	while (node->children[counter] != NULL) {
		counter++;
	}
	for (counter; counter > position + 1; counter--) {
		node->children[counter] = node->children[counter - 1];
		node->values[counter - 1] = node->values[counter - 2];
	}
	node->children[position + 1] = newnode;
	node->values[position] = fullchild->values[T - 1];
	node->num_of_keys++;
}

void InsertIfNotFull(BTREE* node, int value) {
	int position = node->num_of_keys - 1;
	if (node->leaf == LEAF) {
		while (position >= 0 && value < node->values[position]) {
			node->values[position + 1] = node->values[position];
			position--;
		}
		node->num_of_keys++;
		node->values[position + 1] = value;
	}

	else {
		while (position >= 0 && value < node->values[position])
			position--;

		position++;
		if (node->children[position]->num_of_keys == 2 * T - 1) {
			Split(node, position);
			if (node->values[position] < value)
				position++;
		}
		InsertIfNotFull(node->children[position], value);
	}
}

void Insert(BTREE** tree, int value) {
	if (!(*tree)) {
		(*tree) = CreateNode();
		(*tree)->values[0] = value;
		(*tree)->num_of_keys = 1;
		return;
	}
	if (Search((*tree), value) == SUCCESS)
		return;
	if ((*tree)->num_of_keys < 2 * T - 1) {
		InsertIfNotFull((*tree), value);
	}
	else {
		BTREE* newnode = CreateNode();
		BTREE* buf = (*tree);
		(*tree) = newnode;
		newnode->leaf = NOT_LEAF;
		newnode->num_of_keys = 0;
		newnode->children[0] = buf;
		Split(newnode, 0);
		InsertIfNotFull(newnode, value);
	}
}

int Search(BTREE* tree, int value) {
	if (!tree)
		return FAIL;
	int counter = 0;
	
	while (counter < tree->num_of_keys && value > tree->values[counter]) {
		counter++;
	}
	if (counter < tree->num_of_keys && value == tree->values[counter])
		return SUCCESS;
	else if (tree->leaf == LEAF) return FAIL;

	return Search(tree->children[counter], value);
}

int RemovingKey(BTREE* tree, int value) {
	if (!tree)
		return FAIL;

	int minimum = (T - 1) / 2;

	int num_of_keys = tree->num_of_keys; //check smth later
	int* values = tree->values;
	BTREE** children = tree->children;

	int position = Position(value, values, num_of_keys);

	if (!children[0]) {
		if (value < values[position] || position == num_of_keys)
			return FAIL;
		for (int i = position + 1; i < num_of_keys; i++) {
			values[i - 1] = values[i];
			children[i] = children[i + 1];
		}
		tree->num_of_keys--;
		if (tree->num_of_keys >= minimum)
			return SUCCESS;
		else
			return NOT_ENOUGH_KEYS;
	}

	BTREE* buf1;
	int num_of_keys1;
	BTREE* buf2;

	if (position < num_of_keys && value == values[position]) {
		buf1 = children[position];
		for(;;) {
			num_of_keys1 = buf1->num_of_keys;
			buf2 = buf1->children[num_of_keys1];
			if (!buf2)
				break;
			buf1 = buf2;
		}
		values[position] = buf1->values[num_of_keys1 - 1];
		buf1->values[num_of_keys1 - 1] = value;
	}
	int status = RemovingKey(children[position], value);
	if (status != NOT_ENOUGH_KEYS)
		return status;

	BTREE* left;
	BTREE* right;

	if (position > 0 && children[position - 1]->num_of_keys > minimum) {
		left = children[position - 1];
		right = children[position];
		right->children[right->num_of_keys + 1] = right->children[right->num_of_keys];
		for (int i = right->num_of_keys; i > 0; i--) {
			right->values[i] = right->values[i - 1];
			right->children[i] = right->children[i - 1];
		}
		right->num_of_keys++;
		right->values[0] = values[position - 1];
		right->children[0] = left->children[left->num_of_keys];
		values[position - 1] = left->values[--left->num_of_keys];
		return SUCCESS;
	}

	if (position < num_of_keys && children[position + 1]->num_of_keys > minimum) {
		left = children[position];
		right = children[position + 1];
		left->values[left->num_of_keys] = values[position];
		left->children[left->num_of_keys + 1] = right->children[0];
		values[position] = right->values[0];
		left->num_of_keys++;
		right->num_of_keys--;
		for (int i = 0; i < right->num_of_keys; i++) {
			right->values[i] = right->values[i + 1];
			right->children[i] = right->children[i + 1];
		}
		right->children[right->num_of_keys] = right->children[right->num_of_keys + 1];
	}

	if (position == num_of_keys) {
		left = children[position - 1];
		right = children[position];
		left->values[left->num_of_keys] = values[position - 1];
	}
	else {
		left = children[position];
		right = children[position + 1];
		left->values[left->num_of_keys] = values[position];
	}
	left->children[left->num_of_keys + 1] = right->children[0];
	for (int i = 0; i < right->num_of_keys; i++) {
		left->values[left->num_of_keys + i + 1] = right->values[i];
		left->children[left->num_of_keys + i + 2] = right->children[i + 1];
	}
	left->num_of_keys = left->num_of_keys + right->num_of_keys + 1;
	free(right);
	for (int i = position + 1; i < num_of_keys; i++) {
		values[i - 1] = values[i];
		children[i] = children[i + 1];
	}
	tree->num_of_keys--;
	if (tree->num_of_keys >= minimum)
		return SUCCESS;
	else return NOT_ENOUGH_KEYS;
}

void Delete(BTREE* tree, int value) {
	if (!tree)
		return NULL;
	int status = RemovingKey(tree, value);
	if (status == NOT_ENOUGH_KEYS) {
		BTREE* freenode = tree;
		tree = tree->children[0];
		free(freenode);
	}
}

void Print(BTREE* tree, int lvl) {
	if (!tree)
		return;
	int i;
	for (i = 0; i <= tree->num_of_keys - 1; i++) {
		Print(tree->children[i], lvl + 1);
		for (int j = 0; j <= lvl; j++)
			printf("   ");
		printf("%d\n", tree->values[i]);
	}
	Print(tree->children[i], lvl + 1);
}

void Clear(BTREE* tree) {
	if (!tree)
		return;
	if (tree->leaf == NOT_LEAF) {
		for (int i = 0; i <= tree->num_of_keys; i++) {
			Clear(tree->children[i]);
			free(tree->children[i]);
		}
	}
	free(tree);
}