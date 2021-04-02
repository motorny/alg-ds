#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable:4996)

#define t 3 //B-tree parametr/degree

typedef enum {
	FALSE = 0,
	TRUE = 1,
}bool_t;

typedef struct btree {
	int n;
  bool_t isLeaf;
	int keys[2*t-1];
	struct btree *c[2*t]; //array of pointers to children
} b_tree;

typedef enum DeleteStatus {
	NOT_FOUND,
	SUCCESS,
	NOT_ENOUGH_KEYS,
} DeleteStatus;
//to know what to do after removing key from node

b_tree* root = NULL;

b_tree* CreateNewNode() {
	b_tree* newnode = (b_tree*)malloc(sizeof(b_tree));
	if (!newnode)
		return NULL;
	newnode->n = 0;
	newnode->isLeaf = TRUE;

	for ( int i = 0; i < (2 * t); i++)
		newnode->c[i] = NULL;

	return newnode;
}

b_tree* KeyFind(b_tree* tree,  int key) {
	if (!tree)
		return NULL;
	 int i = 0;

	while (i < tree->n && key > tree->keys[i])
		i++;

	//we have found our number or key does not exist
	if (i < tree->n && key == tree->keys[i])
		return tree;
	else if (tree->isLeaf) 
		return NULL;

	return KeyFind(tree->c[i], key);
}

//i - index of full node as son of x
void B_Tree_Split_Child(b_tree* x,  int i) {
	 int j;
	b_tree* z = CreateNewNode(); //new node
	b_tree* y = x->c[i]; //full children node
	//x - nonfull node

	z->isLeaf = y->isLeaf;
	z->n = t - 1;

	for (j = 0; j < z->n; j++)
		z->keys[j] = y->keys[j + t];

	if (!y->isLeaf) {
		for (j = 0; j < (z->n) + 1; j++) {
			z->c[j] = y->c[j + t];
			y->c[j + t] = NULL;
		}
	}

	y->n = t - 1;

	if (x->c[i + 1] != NULL) {
		j = i + 1;
		while (x->c[j] != NULL)
			j++;

		for (j; j > i + 1; j--) {
			x->c[j] = x->c[j - 1];
			x->keys[j - 1] = x->keys[j - 2];
		}
	}
	x->c[i + 1] = z;
	x->keys[i] = y->keys[t - 1];
	x->n++;
}

void B_Tree_Insert_Nonfull(b_tree* x,  int k) {
	 int i = (x->n) - 1;

	//if leaf, add here
	if (x->isLeaf) {
		while (i >= 0 && k < x->keys[i]) {
			x->keys[i + 1] = x->keys[i];
			i--;
		}
		x->keys[i + 1] = k;
		x->n++;
	}

	//if not leaf, look at children
	else {
		while (i >= 0 && k < x->keys[i])
			i--;
		i++;

		if (x->c[i]->n == 2*t-1) {
			B_Tree_Split_Child(x, i);
			if (k > x->keys[i])
				i++;
		}
		B_Tree_Insert_Nonfull(x->c[i], k);
	}
}

void KeyInsert( int key, b_tree** root) {
	b_tree* r = (*root), * s = NULL;

	if (KeyFind((*root), key))
		return;

	if (!(*root)) {
		(*root) = CreateNewNode();
		(*root)->keys[0] = key;
		(*root)->n++;
		return;
	}

	if (r->n == 2*t-1) {
		s = CreateNewNode();
		(*root) = s;
		s->isLeaf = FALSE;
		s->n = 0;
		s->c[0] = r;
		B_Tree_Split_Child(s, 0);
		B_Tree_Insert_Nonfull(s, key);
	}
	else
		B_Tree_Insert_Nonfull(r, key);
}

int FindPosition(int key, int* arr, int n) {
	int pos = 0;
	while (pos < n && key > arr[pos])
		pos++;
	return pos;
}

DeleteStatus Remove(b_tree* tree, int key) {
	b_tree** c, * l, * r, *temp, *temp1;
	int pos, i, k, n, min, n1;
	int* arr;
	DeleteStatus value;

	if (!tree)
		return NOT_FOUND;

	n = tree->n;
	arr = tree->keys;
	c = tree->c;
	min = (t - 1) / 2;

	pos = FindPosition(key, arr, n);
	// c is a leaf
	if (c[0] == NULL) {
		if (pos == n || key < arr[pos])
			return NOT_FOUND;

		for (i = pos + 1; i < n; i++) {
			arr[i - 1] = arr[i];
			c[i] = c[i + 1];
		}
		tree->n--;

		//if tree is root, there can be 1 key
		if (tree == root)
			min = 1;

		if (tree->n >= min)
			return SUCCESS;
		else
			return NOT_ENOUGH_KEYS;
	}

	//c is not a leaf
	if (pos < n && key == arr[pos]) {
		temp = c[pos];
		while (TRUE) {
			n1 = temp->n;
			temp1 = temp->c[n1];
			if (temp1 == NULL)
				break;
			temp = temp1;
		}
		arr[pos] = temp->keys[n1 - 1];
		temp->keys[n1 - 1] = key;
	}
	value = Remove(c[pos], key);
	if (value != NOT_ENOUGH_KEYS)
		return value;

	//if not enough keys in elem, add
	if (pos > 0 && c[pos - 1]->n > min) {
		k = pos - 1;
		l = c[k];
		r = c[pos];
		r->c[r->n + 1] = r->c[r->n];
		for (i = r->n; i > 0; i--) {
			r->keys[i] = r->keys[i - 1];
			r->c[i] = r->c[i - 1];
		}
		r->n++;
		r->keys[0] = arr[k];
		r->c[0] = l->c[l->n];
		arr[k] = l->keys[--l->n];
		return SUCCESS;
	}

	if (pos < n && c[pos + 1]->n > min) {
		k = pos;
		l = c[k];
		r = c[k + 1];
		l->keys[l->n] = arr[k];
		l->c[l->n + 1] = r->c[0];
		arr[k] = r->keys[0];
		l->n++;
		r->n--;
		for (i = 0; i < r->n; i++) {
			r->keys[i] = r->keys[i + 1];
			r->c[i] = r->c[i + 1];
		}
		r->c[r->n] = r->c[r->n + 1];
		return SUCCESS;
	}

	if (pos == n)
		k = pos - 1;
	else
		k = pos;

	l = c[k];
	r = c[k + 1];

	//merging 2 children
	l->keys[l->n] = arr[k];
	l->c[l->n + 1] = r->c[0];
	for (i = 0; i < r->n; i++) {
		l->keys[l->n + 1 + i] = r->keys[i];
		l->c[l->n + 2 + i] = r->c[i + 1];
	}
	l->n = l->n + r->n + 1;

	free(r); //free right
	for (i = pos + 1; i < n; i++) {
		arr[i - 1] = arr[i];
		c[i] = c[i + 1];
	}
	if (tree == root)
		min = 1; //there can be 1 key in root
	tree->n--;
	if (tree->n >= min)
		return SUCCESS;
	else
		return NOT_ENOUGH_KEYS;
}

void KeyRemove(int key) {
	b_tree* oldroot;
	DeleteStatus value = Remove(root, key); //remove from root
	if (value == NOT_ENOUGH_KEYS) {
		oldroot = root;
		root = root->c[0];
		free(oldroot);
	}
}

//destroy tree (not necessary)
void DestroyTree(b_tree* tree) {
	if (!tree)
		return;
	if (!tree->isLeaf) {
		 int i;
		for (i = 0; i <= tree->n; i++)
			DestroyTree(tree->c[i]);
	}
	free(tree);
	return;
}

//printing rotated tree (not necessary function)
void PrintTree(b_tree* tree,  int lvl) {
	if (!tree)
		return;
	 int i, j;
	for (i = 0; i <= tree->n - 1; i++) {
		PrintTree(tree->c[i], lvl + 1);
		for (j = 0; j <= lvl; j++)
			printf("   ");
		printf("%d\n", tree->keys[i]);
	}
	//printing last son
	PrintTree(tree->c[i], lvl + 1);
}
 
int main() {
	char comand;
	 int num;
	
	while (TRUE) {
		comand = fgetc(stdin);

		if (comand == EOF || comand == '\n')
			break;

		scanf("%i", &num);

		//comands
		if (comand == 'a') //append
			KeyInsert(num, &root);

		//adress as bool type. Is adress not NULL -> TRUE. Otherwise, FALSE
		else if (comand == 'f') { //find
			if (KeyFind(root, num))
				printf("yes\n");
			else
				printf("no\n");
		}

		else if (comand == 'r')//remove
			KeyRemove(num);

		num = 0;
		comand = fgetc(stdin); //get '\n' from stdin
	}
	return 0;
}