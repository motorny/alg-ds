#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

#define PARAM 3 
#define FALSE 0
#define TRUE  1

typedef struct btree {
  int num;
  int isLeaf;
  int keys[2 * PARAM - 1];
  struct btree* children[2 * PARAM]; 
} node_t;

typedef enum status {
  NOT_FOUND,
  SUCCESS,
  NOT_ENOUGH_KEYS,
} status_t;

node_t* root = NULL;

node_t* MallocNode() {
  node_t* newnode = (node_t*)malloc(sizeof(node_t));
  if (!newnode)
	return NULL;
  newnode->num = 0;
  newnode->isLeaf = TRUE;

  for (int i = 0; i < (2 * PARAM); i++)
	newnode->children[i] = NULL;

  return newnode;
}

node_t* FindKey(node_t* tree, int key) {
  if (!tree)
	return NULL;
  int i = 0;
  while (i < tree->num && key > tree->keys[i])
	i++;
  if (i < tree->num && key == tree->keys[i])
	return tree;
  else if (tree->isLeaf)
	return NULL;
  return FindKey(tree->children[i], key);
}

void SplitChild(node_t* x, int i) {
  int j;
  node_t* z = MallocNode(); 
  node_t* y = x->children[i]; 

  z->isLeaf = y->isLeaf;
  z->num = PARAM - 1;

  for (j = 0; j < z->num; j++)
	z->keys[j] = y->keys[j + PARAM];

  if (!y->isLeaf) {
	for (j = 0; j < (z->num) + 1; j++) {
	  z->children[j] = y->children[j + PARAM];
	  y->children[j + PARAM] = NULL;
	}
  }

  y->num = PARAM - 1;

  if (x->children[i + 1] != NULL) {
	j = i + 1;
	while (x->children[j] != NULL)
	  j++;

	for (j; j > i + 1; j--) {
	  x->children[j] = x->children[j - 1];
	  x->keys[j - 1] = x->keys[j - 2];
	}
  }
  x->children[i + 1] = z;
  x->keys[i] = y->keys[PARAM - 1];
  x->num++;
}

int Add(node_t* x, int k) {
  int i = (x->num) - 1;

  if (x->isLeaf) {
	while (i >= 0 && k < x->keys[i]) {
	  x->keys[i + 1] = x->keys[i];
	  i--;
	}
	x->keys[i + 1] = k;
	x->num++;
  }

  else {
	while (i >= 0 && k < x->keys[i])
	  i--;
	i++;

	if (x->children[i]->num == 2 * PARAM - 1) {
	  SplitChild(x, i);
	  if (k > x->keys[i])
		i++;
	}
	Add(x->children[i], k);
	return TRUE;
  }
}

int AddKey(node_t** root, int key) {
  node_t* r = (*root), * s = NULL;

  if (FindKey((*root), key))
	return FALSE;

  if (!(*root)) {
	(*root) = MallocNode();
	if (*root)
	  return FALSE;
	(*root)->keys[0] = key;
	(*root)->num++;
	return TRUE;
  }

  if (r->num == 2 * PARAM - 1) {
	s = MallocNode();
	if (!s)
	  return FALSE;
	(*root) = s;
	s->isLeaf = FALSE;
	s->num = 0;
	s->children[0] = r;
	SplitChild(s, 0);
	Add(s, key);
  }
  else
	Add(r, key);
  return TRUE;
}

int FindPosition(int key, int* child, int n) {
  int pos = 0;
  while (pos < n && key > child[pos])
	pos++;
  return pos;
}

status_t RemoveKey(node_t* tree, int key) {
  node_t** c, * l, * r, * temp, * temp1;
  int pos, i, k, n, min, n1;
  int* arr;
  status_t value;

  if (!tree)
	return NOT_FOUND;

  n = tree->num;
  arr = tree->keys;
  c = tree->children;
  min = (PARAM - 1) / 2;

  pos = FindPosition(key, arr, n);
  if (c[0] == NULL) {
	if (pos == n || key < arr[pos])
	  return NOT_FOUND;

	for (i = pos + 1; i < n; i++) {
	  arr[i - 1] = arr[i];
	  c[i] = c[i + 1];
	}
	tree->num--;

	if (tree == root)
	  min = 1;

	if (tree->num >= min)
	  return SUCCESS;
	else
	  return NOT_ENOUGH_KEYS;
  }

  if (pos < n && key == arr[pos]) {
	temp = c[pos];
	while (TRUE) {
	  n1 = temp->num;
	  temp1 = temp->children[n1];
	  if (temp1 == NULL)
		break;
	  temp = temp1;
	}
	arr[pos] = temp->keys[n1 - 1];
	temp->keys[n1 - 1] = key;
  }
  value = RemoveKey(c[pos], key);
  if (value != NOT_ENOUGH_KEYS)
	return value;

  if (pos > 0 && c[pos - 1]->num > min) {
	k = pos - 1;
	l = c[k];
	r = c[pos];
	r->children[r->num + 1] = r->children[r->num];
	for (i = r->num; i > 0; i--) {
	  r->keys[i] = r->keys[i - 1];
	  r->children[i] = r->children[i - 1];
	}
	r->num++;
	r->keys[0] = arr[k];
	r->children[0] = l->children[l->num];
	arr[k] = l->keys[--l->num];
	return SUCCESS;
  }

  if (pos < n && c[pos + 1]->num > min) {
	k = pos;
	l = c[k];
	r = c[k + 1];
	l->keys[l->num] = arr[k];
	l->children[l->num + 1] = r->children[0];
	arr[k] = r->keys[0];
	l->num++;
	r->num--;
	for (i = 0; i < r->num; i++) {
	  r->keys[i] = r->keys[i + 1];
	  r->children[i] = r->children[i + 1];
	}
	r->children[r->num] = r->children[r->num + 1];
	return SUCCESS;
  }

  if (pos == n)
	k = pos - 1;
  else
	k = pos;

  l = c[k];
  r = c[k + 1];

  l->keys[l->num] = arr[k];
  l->children[l->num + 1] = r->children[0];
  for (i = 0; i < r->num; i++) {
	l->keys[l->num + 1 + i] = r->keys[i];
	l->children[l->num + 2 + i] = r->children[i + 1];
  }
  l->num = l->num + r->num + 1;

  free(r); 
  for (i = pos + 1; i < n; i++) {
	arr[i - 1] = arr[i];
	c[i] = c[i + 1];
  }
  if (tree == root)
	min = 1; 
  tree->num--;
  if (tree->num >= min)
	return SUCCESS;
  else
	return NOT_ENOUGH_KEYS;
}

void KeyRemove(int key) {
  node_t* oldroot;
  status_t value = RemoveKey(root, key);
  if (value == NOT_ENOUGH_KEYS) {
	oldroot = root;
	root = root->children[0];
	free(oldroot);
  }
}


int DestroyTree(node_t* tree) {
  if (!tree)
	return FALSE;
  if (!tree->isLeaf) {
	int i;
	for (i = 0; i <= tree->num; i++)
	  DestroyTree(tree->children[i]);
  }
  free(tree);
  return TRUE;
}

void PrintTree(node_t* tree, int lvl) {
  if (!tree)
	return;
  int i, j;
  for (i = 0; i <= tree->num - 1; i++) {
	PrintTree(tree->children[i], lvl + 1);
	for (j = 0; j <= lvl; j++)
	  printf("   ");
	printf("%d\n", tree->keys[i]);
  }
  PrintTree(tree->children[i], lvl + 1);
}

/*
int main() {

  int c = getchar(), number;

  while (c != EOF) {
	scanf("%d", &number);
	switch (c) {
	case 'a':
	  KeyInsert(number, &root);
	  break;
	case 'f':
	  if (FindKey(root, number))
		printf("yes\n");
	  else
		printf("no\n");
	  break;
	case 'r':
	  KeyRemove(number);
	  break;
	default:
	  return 0;
	}

	if ((c = getchar()) == '\n')
	  c = getchar();
  }

  //PrintTree(root, 0);
  DestroyTree(root);

  return 0;
}
*/
