
#include "LabI_12.h"

node_t* CreateNode() {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	if (!node)
		return NULL;
	node->n = 0;
	node->isleaf = YES;
	for (int i = 0; i < 2 * T; i++) {
		node->children[i] = NULL;
	}
	return node;
}
//поиск
node_t* Find(node_t* node, int key) {
	if (!node)
		return NULL;
	int counter = 0;

	while (counter < node->n && key > node->key[counter]) {
		counter++;
	}
	if (counter < node->n && key == node->key[counter])
		return node;
	else if (node->isleaf == YES) return NULL;

	return Find(node->children[counter], key);
}
err_t Search(int key) {
	if (!ROOT) {
		return FAIL;
	}
	if (Find(ROOT, key) != NULL) {
		return SUCCESS;
	}
	return FAIL;
}

int Position(int key, int* values, int n) {
	int pos = 0;
	while (pos < n && key > values[pos])
		pos++;
	return pos;
}

//добавление
void SplitChild(node_t* node, int i) {
	node_t* z = CreateNode();
	if (!z) {
		return;
	}
	node_t* y = node->children[i];
	int j;
	z->isleaf = y->isleaf;
	z->n = T - 1;
	for (j = 0; j < z->n; j++) {
		z->key[j] = y->key[j + T];
	}
	if (y->isleaf == NO) {
		for (j = 0; j < T; j++) {
			z->children[j] = y->children[j + T];
			y->children[j + T] = NULL;
		}
	}
	y->n = T - 1;
	if (node->children[i + 1] != NULL) {
		j = i + 1;
		while (node->children[j] != NULL)
			j++;
		for (j; j > i + 1; j--) {
			node->children[j] = node->children[j - 1];
			node->key[j - 1] = node->key[j - 2];
		}
	}
	node->children[i + 1] = z;
	node->key[i] = y->key[T - 1];
	node->n++;
}
void AddNonFull(node_t* node, int key) {
	int i = node->n - 1;
	if (node->isleaf == YES) {
		for (i; i >= 0 && key < node->key[i]; i--) {
			node->key[i + 1] = node->key[i];
		}
		node->key[i + 1] = key;
		node->n++;
	}
	else {
		for (i; i >= 0 && key < node->key[i]; i--);
		i += 1;
		if (node->children[i]->n == 2 * T - 1) {
			SplitChild(node, i);
			if (key > node->key[i]) {
				i += 1;
			}
		}
		AddNonFull(node->children[i], key);
	}
}
void Add(int key) {
	if (!ROOT) {
		ROOT = CreateNode();
		if (!ROOT) {
			return;
		}
		ROOT->isleaf = YES;
		ROOT->n = 1;
		ROOT->key[0] = key;
	}
	if (Find(ROOT, key) != NULL) {
		return;
	}
	if (ROOT->n == 2 * T - 1) {
		node_t* newnode = CreateNode();
		if (!newnode) {
			return;
		}
		newnode->isleaf = NO;
		newnode->n = 0;
		newnode->children[0] = ROOT;
		ROOT = newnode;
		SplitChild(newnode, 0);
		AddNonFull(newnode, key);
		return;
	}
	else
		AddNonFull(ROOT, key);
}


//печать
void PrintNode(node_t* node, int level) {
	if (!node)
		return;
	int i, j;
	for (i = 0; i < node->n; i++) {
		PrintNode(node->children[i], level + 1);
		for (j = 0; j <= level; j++)
			printf("   ");
		printf("%d\n", node->key[i]);
	}
	PrintNode(node->children[i], level + 1);
}
void PrintTree() {
	if (ROOT) {
		PrintNode(ROOT, 0);
	}
}

//удаление
err_t RemoveKey(node_t* node, int key) {
	if (!node)
		return FAIL;

	int min = (T - 1) / 2;

	int num = node->n;
	int* keys = node->key;
	node_t** children = node->children;
	int i;
	node_t* buf1;
	int num1;
	node_t* buf2;
	node_t* l;
	node_t* r;

	int p = Position(key, keys, num);

	if (node->isleaf == YES) {
		if (key < keys[p] || p == num)
			return FAIL;
		for (i = p + 1; i < num; i++) {
			keys[i - 1] = keys[i];
			children[i] = children[i + 1];
		}
		node->n--;
		if (node == ROOT) {
			min = 1;
		}
		if (node->n >= min)
			return SUCCESS;
		else
			return ERR_KEYS;
	}

	if (p < num && key == keys[p]) {
		buf1 = children[p];
		while (1) {
			num1 = buf1->n;
			buf2 = buf1->children[num1];
			if (!buf2)
				break;
			buf1 = buf2;
		}
		keys[p] = buf1->key[num1 - 1];
		buf1->key[num1 - 1] = key;
	}
	int status = RemoveKey(children[p], key);
	if (status != ERR_KEYS)
		return status;

	if (p > 0 && children[p - 1]->n > min) {
		l = children[p - 1];
		r = children[p];
		r->children[r->n + 1] = r->children[r->n];
		for (i = r->n; i > 0; i--) {
			r->key[i] = r->key[i - 1];
			r->children[i] = r->children[i - 1];
		}
		r->n++;
		r->key[0] = keys[p - 1];
		r->children[0] = l->children[l->n];
		keys[p - 1] = l->key[--l->n];
		return SUCCESS;
	}

	if (p < num && children[p + 1]->n > min) {
		l = children[p];
		r = children[p + 1];
		l->key[l->n] = keys[p];
		l->children[l->n + 1] = r->children[0];
		keys[p] = r->key[0];
		l->n++;
		r->n--;
		for (i = 0; i < r->n; i++) {
			r->key[i] = r->key[i + 1];
			r->children[i] = r->children[i + 1];
		}
		r->children[r->n] = r->children[r->n + 1];
		return SUCCESS;
	}

	if (p == num) {
		l = children[p - 1];
		r = children[p];
		l->key[l->n] = keys[p - 1];
	}
	else {
		l = children[p];
		r = children[p + 1];
		l->key[l->n] = keys[p];
	}
	l->children[l->n + 1] = r->children[0];
	for (i = 0; i < r->n; i++) {
		l->key[l->n + i + 1] = r->key[i];
		l->children[l->n + i + 2] = r->children[i + 1];
	}
	l->n = l->n + r->n + 1;
	free(r);
	for (i = p + 1; i < num; i++) {
		keys[i - 1] = keys[i];
		children[i] = children[i + 1];
	}
	node->n--;
	if (node->n >= min)
		return SUCCESS;
	else return ERR_KEYS;
}
void Remove(int key) {
	if (!ROOT) {
		return;
	}
	err_t err = RemoveKey(ROOT, key);
	if (err == ERR_KEYS) {
		node_t* tmp = ROOT;
		ROOT = ROOT->children[0];
		free(tmp);
	}
}

//удаление дерева
void Clear(node_t* node) {
	if (!node)
		return;
	if (node->isleaf == NO) {
		int i;
		for (i = 0; i <= node->n; i++) {
			Clear(node->children[i]);
		}
	}
	free(node);

}
void FreeTree() {
	if (!ROOT) {
		return;
	}
	Clear(ROOT);
}
