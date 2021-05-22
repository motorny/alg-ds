#include "btree.h"

Btree* newnode_init() {
	Btree* node = (Btree*)malloc(sizeof(Btree));
	if (!node)
		return NULL;

	node->n = 0;
	node->leaf = LEAF;
	for (int i = 0; i < 2 * DEGREE; i++) {
		node->children[i] = NULL;
	}
	return node;
}

int get_position(int value, int* values, int num_of_keys) {
	int pos = 0;
	while (pos < num_of_keys && value > values[pos])
		pos++;
	return pos;
}

void split(Btree* node, int position) {
	Btree* newnode = newnode_init();
	Btree* fullchild = node->children[position];
	newnode->n = DEGREE - 1;
	newnode->leaf = fullchild->leaf;
	for (int i = 0; i < DEGREE - 1; i++) {
		newnode->values[i] = fullchild->values[i + DEGREE];
	}
	if (fullchild->leaf == NOT_LEAF) {
		for (int i = 0; i < DEGREE; i++) {
			newnode->children[i] = fullchild->children[i + DEGREE];
			fullchild->children[i + DEGREE] = NULL;
		}
	}

	fullchild->n = DEGREE - 1;
	int counter = position + 1;
	while (node->children[counter] != NULL) {
		counter++;
	}
	for (counter; counter > position + 1; counter--) {
		node->children[counter] = node->children[counter - 1];
		node->values[counter - 1] = node->values[counter - 2];
	}
	node->children[position + 1] = newnode;
	node->values[position] = fullchild->values[DEGREE - 1];
	node->n++;
}

void notfull_insert(Btree* node, int value) {
	int position = node->n - 1;
	if (node->leaf == LEAF) {
		while (position >= 0 && value < node->values[position]) {
			node->values[position + 1] = node->values[position];
			position--;
		}
		node->n++;
		node->values[position + 1] = value;
	}

	else {
		while (position >= 0 && value < node->values[position])
			position--;

		position++;
		if (node->children[position]->n == 2 * DEGREE - 1) {
			split(node, position);
			if (node->values[position] < value)
				position++;
		}
		notfull_insert(node->children[position], value);
	}
}

void insert(Btree** tree, int value) {
	if (!(*tree)) {
		(*tree) = newnode_init();
		(*tree)->values[0] = value;
		(*tree)->n = 1;
		return;
	}
	if (search((*tree), value) == SUCCESS)
		return;
	if ((*tree)->n < 2 * DEGREE - 1) {
		notfull_insert((*tree), value);
	}
	else {
		Btree* newnode = newnode_init();
		Btree* buf = (*tree);
		(*tree) = newnode;
		newnode->leaf = NOT_LEAF;
		newnode->n = 0;
		newnode->children[0] = buf;
		split(newnode, 0);
		notfull_insert(newnode, value);
	}
}

int search(Btree* tree, int value) {
	if (!tree)
		return FAIL;
	int counter = 0;

	while (counter < tree->n && value > tree->values[counter]) {
		counter++;
	}
	if (counter < tree->n && value == tree->values[counter])
		return SUCCESS;
	else if (tree->leaf == LEAF) return FAIL;

	return search(tree->children[counter], value);
}

int remove(Btree* tree, int value) {
	if (!tree)
		return FAIL;

	int minimum = (DEGREE - 1) / 2;

	int num_of_keys = tree->n;
	int* values = tree->values;
	Btree** children = tree->children;

	int position = get_position(value, values, num_of_keys);

	if (!children[0]) {
		if (value < values[position] || position == num_of_keys)
			return FAIL;
		for (int i = position + 1; i < num_of_keys; i++) {
			values[i - 1] = values[i];
			children[i] = children[i + 1];
		}
		tree->n--;
		if (tree->n >= minimum)
			return SUCCESS;
		else
			return NOT_ENOUGH_KEYS;
	}

	Btree* buf1;
	int num_of_keys1;
	Btree* buf2;

	if (position < num_of_keys && value == values[position]) {
		buf1 = children[position];
		for (;;) {
			num_of_keys1 = buf1->n;
			buf2 = buf1->children[num_of_keys1];
			if (!buf2)
				break;
			buf1 = buf2;
		}
		values[position] = buf1->values[num_of_keys1 - 1];
		buf1->values[num_of_keys1 - 1] = value;
	}
	int status = remove(children[position], value);
	if (status != NOT_ENOUGH_KEYS)
		return status;

	Btree* left;
	Btree* right;

	if (position > 0 && children[position - 1]->n > minimum) {
		left = children[position - 1];
		right = children[position];
		right->children[right->n + 1] = right->children[right->n];
		for (int i = right->n; i > 0; i--) {
			right->values[i] = right->values[i - 1];
			right->children[i] = right->children[i - 1];
		}
		right->n++;
		right->values[0] = values[position - 1];
		right->children[0] = left->children[left->n];
		values[position - 1] = left->values[--left->n];
		return SUCCESS;
	}

	if (position < num_of_keys && children[position + 1]->n > minimum) {
		left = children[position];
		right = children[position + 1];
		left->values[left->n] = values[position];
		left->children[left->n + 1] = right->children[0];
		values[position] = right->values[0];
		left->n++;
		right->n--;
		for (int i = 0; i < right->n; i++) {
			right->values[i] = right->values[i + 1];
			right->children[i] = right->children[i + 1];
		}
		right->children[right->n] = right->children[right->n + 1];
	}

	if (position == num_of_keys) {
		left = children[position - 1];
		right = children[position];
		left->values[left->n] = values[position - 1];
	}
	else {
		left = children[position];
		right = children[position + 1];
		left->values[left->n] = values[position];
	}
	left->children[left->n + 1] = right->children[0];
	for (int i = 0; i < right->n; i++) {
		left->values[left->n + i + 1] = right->values[i];
		left->children[left->n + i + 2] = right->children[i + 1];
	}
	left->n = left->n + right->n + 1;
	free(right);
	for (int i = position + 1; i < num_of_keys; i++) {
		values[i - 1] = values[i];
		children[i] = children[i + 1];
	}
	tree->n--;
	if (tree->n >= minimum)
		return SUCCESS;
	else return NOT_ENOUGH_KEYS;
}

void delete(Btree* tree, int value) {
	if (!tree)
		return NULL;
	int status = remove(tree, value);
	if (status == NOT_ENOUGH_KEYS) {
		Btree* freenode = tree;
		tree = tree->children[0];
		free(freenode);
	}
}

void print(Btree* tree, int lvl) {
	if (!tree)
		return;
	int i;
	for (i = 0; i <= tree->n - 1; i++) {
		print(tree->children[i], lvl + 1);
		for (int j = 0; j <= lvl; j++)
			printf("   ");
		printf("%d\n", tree->values[i]);
	}
	print(tree->children[i], lvl + 1);
}

void clear(Btree* tree) {
	if (!tree)
		return;
	if (tree->leaf == NOT_LEAF) {
		for (int i = 0; i <= tree->n; i++) {
			clear(tree->children[i]);
		}
	}
	free(tree);
}

int main()
{

}