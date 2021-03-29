#include "treap.h"


node* CreateNode(int value) {
  node* new_n = (node*)malloc(sizeof(node));

  if (new_n == NULL)
    return NULL;
  new_n->left = NULL;
  new_n->right = NULL;
  new_n->value = value;
  new_n->prior = rand();
  new_n->count = 1;

  return new_n;
}

int GetNodeCount(node* node) {
  if (node == NULL)
    return 0;
  else
    return node->count;
}

void UpdateNodeCount(node* node) {
  if (node != NULL)
    node->count = GetNodeCount(node->left) + GetNodeCount(node->right) + 1;
}


node* Merge(node* left, node* right) {
  node* result = NULL;

  if (left == NULL)
    result = right;
  else if (right == NULL)
    result = left;
  else if (left->prior < right->prior) {
    right->left = Merge(left, right->left);
    result = right;
  }
  else {
    left->right = Merge(left->right, right);
    result = left;
  }
  UpdateNodeCount(result);

  return result;
}

void Split(int key, node* root, node** left, node** right, int add) {
  int current_key = 0;

  if (root == NULL) {
    *left = NULL;
    *right = NULL;
    return;
  }
  current_key = GetNodeCount(root->left) + add;

  if (key <= current_key) {
    Split(key, root->left, left, &(root->left), add);
    *right = root;
  }
  else {
    Split(key, root->right, &(root->right), right, add + 1 + GetNodeCount(root->left));
    *left = root;
  }
  UpdateNodeCount(root);
}

void Insert(int value, int position, node** root) {
  node* new_n = CreateNode(value);
  node* head = NULL;
  node* tail = NULL;
  bool_t check = FALSE;
  Check(value, *root, &check);
  if ((new_n == NULL) || (position < 0) || check)
    return;
  else {
    Split(position, *root, &head, &tail, 0);
    *root = Merge(Merge(head, new_n), tail);
  }
}


int Delete(int position, node** root) {
  int result = 1;
  node* element_position = NULL;
  node* head = NULL;
  node* tail = NULL;
  node* new_tail = NULL;

  if (position < 0)
    return result;

  Split(position, *root, &head, &tail, 0);
  Split(1, tail, &element_position, &new_tail, 0);
  if (element_position != NULL) {
    result = 0;
    free(element_position);
  }
  *root = Merge(head, new_tail);
  return result;
}

void FreeTree(node* root) {
  if (root != NULL) {
    FreeTree((root)->left);
    FreeTree((root)->right);
    free(root);
    root = NULL;
  }
}


void Check(int value, node* root, bool_t* contains) {
  if (root != NULL) {
    if (root->value == value)
      * contains = TRUE;
    Check(value, root->left, contains);
    Check(value, root->right, contains);
  }
}


void Find(int value, node* root, node** result) {
  if ((*result == NULL) && (root != NULL)) {
    if (root->value == value) {
      *result = root;
    }
    Find(value, root->left, result);
    Find(value, root->right, result);
  }
}


void DeleteValue(int value, node** root, bool_t* deleted) {
  node* right = NULL, * left = NULL;
  if ((*root != NULL) && (*deleted == 0)) {
    if ((*root)->value == value) {
      node* left = (*root)->left;
      node* right = (*root)->right;
      free(*root);
      *root = Merge(left, right);
      *deleted = TRUE;
      return;
    }
    DeleteValue(value, &((*root)->left), deleted);
    DeleteValue(value, &((*root)->right), deleted);
  }

}