#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)
#define S 3

typedef struct NODE {
  int  n;
  int  keys[S - 1];
  struct NODE* p[S];
} node;
typedef enum KeyStatus {
  Duplicate,
  SearchingError,
  Luck,
  LessKeys,
  InsertIt
} KeyStatus;
node* root = NULL;
int SearchPos(int key, int* key_arr, int n) {
  int pos = 0;
  while (pos < n && key > key_arr[pos]) {
    pos++;
  }
  return pos;
}
KeyStatus Delete(node* ptr, int key) {
  int i;
  int pos;
  int pivot;
  int n;
  int min;
  int* key_arr;
  KeyStatus value;
  node** p;
  node* left;
  node* right;
  if (ptr == NULL) {
    return SearchingError;
  }
  n = ptr->n;
  key_arr = ptr->keys;
  p = ptr->p;
  min = (S - 1) / 2;
  pos = SearchPos(key, key_arr, n);
  if (p[0] == NULL) {
    if (pos == n || key < key_arr[pos]) {
      return SearchingError;
    }
    for (i = pos + 1; i < n; i++) {
      key_arr[i - 1] = key_arr[i];
      p[i] = p[i + 1];
    }
    return --ptr->n >= (ptr == root ? 1 : min) ? Luck : LessKeys;
  }
  if (pos < n && key == key_arr[pos]) {
    node* qp = p[pos], * qp1;
    int newkey;
    while (1) {
      newkey = qp->n;
      qp1 = qp->p[newkey];
      if (qp1 == NULL) {
        break;
      }
      qp = qp1;
    }
    key_arr[pos] = qp->keys[newkey - 1];
    qp->keys[newkey - 1] = key;
  }
  value = Delete(p[pos], key);
  if (value != LessKeys) {
    return value;
  }
  if (pos > 0 && p[pos - 1]->n > min) {
    pivot = pos - 1;
    left = p[pivot];
    right = p[pos];
    right->p[right->n + 1] = right->p[right->n];
    for (i = right->n; i > 0; i--) {
      right->keys[i] = right->keys[i - 1];
      right->p[i] = right->p[i - 1];
    }
    right->n++;
    right->keys[0] = key_arr[pivot];
    right->p[0] = left->p[left->n];
    key_arr[pivot] = left->keys[--left->n];
    return Luck;
  }
  if (pos < n && p[pos + 1]->n > min) {
    pivot = pos;
    left = p[pivot];
    right = p[pivot + 1];
    left->keys[left->n] = key_arr[pivot];
    left->p[left->n + 1] = right->p[0];
    key_arr[pivot] = right->keys[0];
    left->n++;
    right->n--;
    for (i = 0; i < right->n; i++) {
      right->keys[i] = right->keys[i + 1];
      right->p[i] = right->p[i + 1];
    }
    right->p[right->n] = right->p[right->n + 1];
    return Luck;
  }
  if (pos == n) {
    pivot = pos - 1;
  }
  else {
    pivot = pos;
  }
  left = p[pivot];
  right = p[pivot + 1];
  left->keys[left->n] = key_arr[pivot];
  left->p[left->n + 1] = right->p[0];
  for (i = 0; i < right->n; i++) {
    left->keys[left->n + 1 + i] = right->keys[i];
    left->p[left->n + 2 + i] = right->p[i + 1];
  }
  left->n = left->n + right->n + 1;
  free(right);
  for (i = pos + 1; i < n; i++) {
    key_arr[i - 1] = key_arr[i];
    p[i] = p[i + 1];
  }
  return --ptr->n >= (ptr == root ? 1 : min) ? Luck : LessKeys;
}
void DeleteNode(int key) {
  node* uproot;
  KeyStatus value;
  value = Delete(root, key);
  switch (value) {
  case LessKeys:
    uproot = root;
    root = root->p[0];
    free(uproot);
    break;
  default:
    return;
  }
}
KeyStatus Ins(node* ptr, int key, int* topkey, node** newnode) {
  node* newptr;
  node* lastptr;
  int pos;
  int i;
  int n;
  int splitpos;
  int nkey;
  int lastkey;
  KeyStatus value;
  if (ptr == NULL) {
    *newnode = NULL;
    *topkey = key;
    return InsertIt;
  }
  n = ptr->n;
  pos = SearchPos(key, ptr->keys, n);
  if (pos < n && key == ptr->keys[pos]) {
    return Duplicate;
  }
  value = Ins(ptr->p[pos], key, &nkey, &newptr);
  if (value != InsertIt) {
    return value;
  }
  if (n < S - 1) {
    pos = SearchPos(nkey, ptr->keys, n);
    for (i = n; i > pos; i--) {
      ptr->keys[i] = ptr->keys[i - 1];
      ptr->p[i + 1] = ptr->p[i];
    }
    ptr->keys[pos] = nkey;
    ptr->p[pos + 1] = newptr;
    ++ptr->n;
    return Luck;
  }
  if (pos == S - 1) {
    lastkey = nkey;
    lastptr = newptr;
  }
  else {
    lastkey = ptr->keys[S - 2];
    lastptr = ptr->p[S - 1];
    for (i = S - 2; i > pos; i--) {
      ptr->keys[i] = ptr->keys[i - 1];
      ptr->p[i + 1] = ptr->p[i];
    }
    ptr->keys[pos] = nkey;
    ptr->p[pos + 1] = newptr;
  }
  splitpos = (S - 1) / 2;
  (*topkey) = ptr->keys[splitpos];
  (*newnode) = (node*)malloc(sizeof(node));
  ptr->n = splitpos;
  (*newnode)->n = S - 1 - splitpos;
  for (i = 0; i < (*newnode)->n; i++) {
    (*newnode)->p[i] = ptr->p[i + splitpos + 1];
    if (i < (*newnode)->n - 1) {
      (*newnode)->keys[i] = ptr->keys[i + splitpos + 1];
    }
    else {
      (*newnode)->keys[i] = lastkey;
    }
  }
  (*newnode)->p[(*newnode)->n] = lastptr;
  return InsertIt;
}
void Insert(int key) {
  node* newnode;
  int upKey;
  KeyStatus value;
  value = Ins(root, key, &upKey, &newnode);
  if (value == InsertIt) {
    node* uproot = root;
    root = (node*)malloc(sizeof(node));
    root->n = 1;
    root->keys[0] = upKey;
    root->p[0] = uproot;
    root->p[1] = newnode;
  }
}

void Show(node* ptr, int bl) {
  if (ptr) {
    int i;
    for (i = 1; i <= bl; i++) {
      printf(" ");
    }
    for (i = 0; i < ptr->n; i++) {
      printf("%d ", ptr->keys[i]);
    }
    printf("\n");
    for (i = 0; i <= ptr->n; i++) {
      Show(ptr->p[i], bl + 10);
    }
  }
}
void Search(int key) {
  int n;
  int pos;
  int i;
  node* ptr = root;
  while (ptr) {
    n = ptr->n;
    pos = SearchPos(key, ptr->keys, n);
    if (pos < n && key == ptr->keys[pos]) {
      printf("yes\n");
      return;
    }
    ptr = ptr->p[pos];
  }
  printf("no\n");
}


int main(void) {
  char selection;
  int key;
  while (!feof(stdin)) {
    scanf("%c", &selection);
    switch (selection) {
    case 'a':
      scanf("%d", &key);
      Insert(key);
      break;
    case 'r':
      scanf("%d", &key);
      DeleteNode(key);
      break;
    case 'f':
      scanf("%d", &key);
      Search(key);
      break;
    case 'v':
      Show(root, 0);
      break;
    }
  }
  return 0;
}
