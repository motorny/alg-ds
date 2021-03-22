#include "btree.h"

static int removeNode(b_tree_node_t* node, int key);

void BTreeInit(b_tree_t* tree) {
  tree->root = NULL;
}

static int bTreeSplitChild(b_tree_node_t* node, int index) {
  if (index > 2 * T - 1)
    return IND_ERR;
  else if (node == NULL)
    return MFAIL;
  else {
    b_tree_node_t* newNode = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));
    b_tree_node_t* childNode = node->children[index];

    if (newNode == NULL)
      return MEM_ERR;

    newNode->leaf = childNode->leaf;
    newNode->count = T - 1;
    memcpy(&newNode->key[0], &childNode->key[T], (T - 1) * sizeof(int));

    if (childNode->leaf == FALSE)
      memcpy(&newNode->children[0], &childNode->children[T], (T) * sizeof(b_tree_node_t*));
    childNode->count = T - 1;

    if (node->count > index)
      memmove(&node->children[index + 2], &node->children[index + 1], (node->count - index) * sizeof(b_tree_node_t*));
    node->children[index + 1] = newNode;

    if (node->count > index)
      memmove(&node->key[index + 1], &node->key[index], (node->count - index) * sizeof(int));
    node->key[index] = childNode->key[T - 1];
    node->count++;

    return SUCCESS;
  }
}

static int binarySearch(int arr[], int length, int key) {
  int first = 0;
  int last = length;

  if (length == 0)
    return 0;
  if (key < arr[first])
    return 0;
  if (key > arr[last - 1])
    return last;

  while (first < last)
    if (key <= arr[first + (last - first) / 2])
      last = first + (last - first) / 2;
    else
      first = first + (last - first) / 2 + 1;

  return last;
}

int BTreeInsert(b_tree_t* tree, int key) {
  int index = 0;
  b_tree_node_t* node;

  if (tree == NULL)
    return MFAIL;

  if (tree->root == NULL) {
    b_tree_node_t* newRoot = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));

    if (newRoot == NULL)
      return MEM_ERR;

    newRoot->count = 0;
    newRoot->leaf = TRUE;

    tree->root = newRoot;
  }
  else if (tree->root->count == 2 * T - 1) {
    b_tree_node_t* newRoot = (b_tree_node_t*)malloc(sizeof(b_tree_node_t));

    if (newRoot == NULL)
      return MEM_ERR;

    newRoot->children[0] = tree->root;
    newRoot->leaf = FALSE;
    newRoot->count = 0;

    tree->root = newRoot;
  }
  else if (tree->root->count > 0) {
    index = binarySearch(tree->root->key, tree->root->count, key);
    if (index < tree->root->count && tree->root->key[index] == key)
      return SUCCESS;
  }

  node = tree->root;
  while (node->leaf == FALSE) {
    if (node->children[index]->count == 2 * T - 1) {
      if (bTreeSplitChild(node, index) != SUCCESS)
        return MFAIL;

      if (key > node->key[index])
        index++;
    }
    if (index < node->count && node->key[index] == key)
      return SUCCESS;
    node = node->children[index];
    index = binarySearch(node->key, node->count, key);
    if (index < node->count && node->key[index] == key)
      return SUCCESS;
  }

  if (node->count > index)
    memmove(&node->key[index + 1], &node->key[index], (node->count - index) * sizeof(int));
  node->key[index] = key;
  node->count++;

  return SUCCESS;
}

b_tree_node_t* BTreeFind(b_tree_t* tree, int key) {
  int index = 0;
  b_tree_node_t* node;

  if (tree == NULL)
    return NULL;

  node = tree->root;
  if (node == NULL)
    return NULL;

  while (node->leaf == FALSE) {
    index = binarySearch(node->key, node->count, key);

    if (index < node->count && node->key[index] == key)
      return node;

    node = node->children[index];
  }
  index = binarySearch(node->key, node->count, key);

  if (index < node->count && node->key[index] == key)
    return node;
  else
    return NULL;
}

static void clear(b_tree_node_t* node) {
  int counter;

  if (node->leaf == FALSE) {
    for (counter = 0; counter <= node->count; counter++) {
      clear(node->children[counter]);
      free(node->children[counter]);
    }
  }
  else
    return;
}

void BTreeClear(b_tree_t* tree) {
  if (tree->root != NULL) {
    clear(tree->root);
    free(tree->root);
    tree->root = NULL;
  }
}

static void print(b_tree_node_t* node, int level) {
  int i;

  if (node != NULL && level >= 0) {
    for (i = 0; i < level; i++)
      printf("    ");
    for (i = 0; i < node->count; i++) {
      printf("%i", node->key[i]);
      if (i != node->count - 1)
        printf(", ");
    }
    printf("\n");
    if (node->leaf == TRUE)
      return;
    for (i = 0; i <= node->count; i++)
      print(node->children[i], level + 1);
  }
}

void BTreePrint(b_tree_t* tree) {
  if (tree != NULL && tree->root != NULL)
    print(tree->root, 0);
}

static int getPred(b_tree_node_t* node, int index) {
  b_tree_node_t* cur = node->children[index];

  while (cur->leaf == FALSE)
    cur = cur->children[cur->count];

  return cur->key[cur->count - 1];
}

static int getSucc(b_tree_node_t* node, int index) {
  b_tree_node_t* cur = node->children[index + 1];

  while (cur->leaf == FALSE)
    cur = cur->children[0];

  return cur->key[0];
}

static void merge(b_tree_node_t* node, int index) {
  b_tree_node_t* child = node->children[index];
  b_tree_node_t* sibling = node->children[index + 1];

  child->key[T - 1] = node->key[index];

  memcpy(&child->key[T], &sibling->key[0], sibling->count * sizeof(int));

  if (child->leaf == FALSE)
    memcpy(&child->children[T], &sibling->children[0], (sibling->count + 1) * sizeof(b_tree_node_t*));

  if (node->count > index + 1)
    memmove(&node->key[index], &node->key[index + 1], (node->count - index - 1) * sizeof(int));

  if (node->count > index + 1)
    memmove(&node->children[index + 1], &node->children[index + 2], (node->count - index - 1) * sizeof(b_tree_node_t*));

  child->count += sibling->count + 1;
  node->count--;

  free(sibling);
}

static void removeFromNonLeaf(b_tree_node_t* node, int index) {
  int k = node->key[index];

  if (node->children[index]->count >= T) {
    int pred = getPred(node, index);

    node->key[index] = pred;
    removeNode(node->children[index], pred);
  }
  else if (node->children[index + 1]->count >= T) {
    int succ = getSucc(node, index);

    node->key[index] = succ;
    removeNode(node->children[index + 1], succ);
  }
  else {
    merge(node, index);
    removeNode(node->children[index], k);
  }
}

static void removeFromLeaf(b_tree_node_t* node, int index) {
  if (node->count > index + 1)
    memmove(&node->key[index], &node->key[index + 1], (node->count - index - 1) * sizeof(int));

  node->count--;

  return;
}

static void borrowFromNext(b_tree_node_t* node, int index) {
  b_tree_node_t* child = node->children[index];
  b_tree_node_t* sibling = node->children[index + 1];

  child->key[child->count] = node->key[index];

  if (child->leaf == FALSE)
    child->children[child->count + 1] = sibling->children[0];

  node->key[index] = sibling->key[0];

  memmove(&sibling->key[0], &sibling->key[1], (sibling->count - 1) * sizeof(int));

  if (sibling->leaf == FALSE)
    memmove(&sibling->children[0], &sibling->children[1], sibling->count * sizeof(b_tree_node_t*));

  child->count++;
  sibling->count--;
}

static void borrowFromPrev(b_tree_node_t* node, int index) {
  b_tree_node_t* child = node->children[index];
  b_tree_node_t* sibling = node->children[index - 1];

  memmove(&child->key[1], &child->key[0], child->count * sizeof(int));

  if (child->leaf == FALSE)
    memmove(&child->children[1], &child->children[0], (child->count + 1) * sizeof(b_tree_node_t*));

  child->key[0] = node->key[index - 1];

  if (child->leaf == FALSE)
    child->children[0] = sibling->children[sibling->count];

  node->key[index - 1] = sibling->key[sibling->count - 1];
  child->count++;
  sibling->count--;
}

static void fill(b_tree_node_t* node, int index) {
  if (index != 0 && node->children[index - 1]->count >= T)
    borrowFromPrev(node, index);
  else if (index != node->count && node->children[index + 1]->count >= T)
    borrowFromNext(node, index);
  else {
    if (index != node->count)
      merge(node, index);
    else
      merge(node, index - 1);
  }
}

static int removeNode(b_tree_node_t* node, int key) {
  int index;

  if (node == NULL)
    return MFAIL;

  index = binarySearch(node->key, node->count, key);
  if (index < node->count && node->key[index] == key) {
    if (node->leaf == TRUE)
      removeFromLeaf(node, index);
    else
      removeFromNonLeaf(node, index);
  }
  else {
    int flag = (index == node->count) ? 1 : 0;

    if (node->leaf == TRUE)
      return MFAIL;

    if (node->children[index]->count < T)
      fill(node, index);

    if (flag && index > node->count) {
      if (!removeNode(node->children[index - 1], key))
        return MFAIL;
    }
    else
      if (!removeNode(node->children[index], key))
        return MFAIL;
  }

  return SUCCESS;
}

int BTreeRemove(b_tree_t* tree, int key) {
  int flag;
  if (tree == NULL)
    return MFAIL;

  flag = removeNode(tree->root, key);

  if (tree->root != NULL) {
    if (tree->root->count == 0) {
      b_tree_node_t* tmp = tree->root;

      if (tree->root->leaf == TRUE)
        tree->root = NULL;
      else
        tree->root = tree->root->children[0];

      free(tmp);
    }
  }

  if (!flag)
    return MFAIL;

  return SUCCESS;
}