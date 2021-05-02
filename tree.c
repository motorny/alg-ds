#include"tree.h"


void balance(tree_t* tree, tree_t* node, int key);
void deleteNode(tree_t* tree, tree_t* node, int key);
int findMin(tree_t* tree);

tree_t* createTree(void) {

  tree_t* tree;

  tree = (tree_t*)(malloc(sizeof(tree_t)));
  if (tree == NULL)
    return NULL;

  tree->isLeaf = LEAF;
  tree->numOfNode = 0;
  tree->left = NULL;
  tree->right = NULL;
  tree->parent = NULL;

  for (int i = 0; i < 2 * ORDER + 1; i++)
    tree->nodes[i] = NULL;

  return tree;

}

//find
tree_t* findNode(tree_t* tree, int key) {

  if (tree == NULL)
    return NULL;

  tree_t* curNode = tree;
  while (curNode->isLeaf == NOTLEAF)
    for (int pos = 0; pos <= curNode->numOfNode; pos++)
      if (pos == curNode->numOfNode || key < curNode->keys[pos]) {
        curNode = curNode->nodes[pos];
        break;
      }

  return curNode;

}

int findKey(tree_t* tree, int key) {

  tree_t* node = findNode(tree, key);
  if (node == NULL)
    return NOTFOUND;

  for (int pos = 0; pos < node->numOfNode; pos++)
    if (node->keys[pos] == key)
      return FOUND;

  return NOTFOUND;

}

//split
static void splitTree(tree_t** root, tree_t* node) {

  tree_t* tree = (*root);

  tree_t* newNode = (tree_t*)(malloc(sizeof(tree_t)));
  if (newNode == NULL)
      return;

  newNode->isLeaf = NOTLEAF;
  newNode->numOfNode = 0;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  for (int i = 0; i < 2 * ORDER + 1; i++)
    newNode->nodes[i] = NULL;


  if (node->right != NULL) {
    newNode->right = node->right;
    node->right->left = newNode;
    node->right = newNode;
    newNode->left = node;
  }
  else {
    newNode->right = node->right;
    node->right = newNode;
    newNode->left = node;
  }

  int mid = node->keys[ORDER];
  newNode->numOfNode = ORDER - 1;
  node->numOfNode = ORDER;
  for (int i = 0; i < newNode->numOfNode; i++) {
    newNode->keys[i] = node->keys[i + ORDER + 1];
    newNode->nodes[i] = node->nodes[i + ORDER + 1];
    node->nodes[i + ORDER + 1] = NULL;
  }
  newNode->nodes[newNode->numOfNode] = node->nodes[2 * ORDER];
  node->nodes[2 * ORDER] = NULL;

  if (node->isLeaf == LEAF) {
    newNode->numOfNode++;
    newNode->isLeaf = LEAF;
    for (int i = newNode->numOfNode - 1; i >= 1; i--)
        newNode->keys[i] = newNode->keys[i - 1];
    newNode->keys[0] = node->keys[ORDER];
  }

  if(node == *(root)){
    (*root) = (tree_t*)malloc(sizeof(tree_t));
    if ((*root) == NULL)
      return;

    (*root)->keys[0] = mid;
    (*root)->nodes[0] = node;
    (*root)->nodes[1] = newNode;
    for (int i = 0; i < 2 * ORDER + 1; i++) {
      if (newNode->nodes[i] != NULL)
        newNode->nodes[i]->parent = newNode;
      if (node->nodes[i] != NULL)
        node->nodes[i]->parent = node;
    }
    (*root)->isLeaf = NOTLEAF;
    (*root)->parent = NULL;
    (*root)->left = NULL;
    (*root)->right = NULL;
    for (int i = 2; i < 2 * ORDER + 1; i++)
      (*root)->nodes[i] = NULL;
    (*root)->numOfNode = 1;
    node->parent = (*root);
    newNode->parent = (*root);
  }
  else {
    newNode->parent = node->parent;

    int pos = 0;
    while (pos < node->parent->numOfNode && node->parent->keys[pos] < mid)
      pos++;
    for (int i = node->parent->numOfNode; i >= pos; i--)
      node->parent->keys[i] = node->parent->keys[i - 1];
    for (int i = node->parent->numOfNode + 1; i >= pos + 2; i--)
      node->parent->nodes[i] = node->parent->nodes[i - 1];
    for (int i = 0; i < 2 * ORDER; i++)
      if (newNode->nodes[i] != NULL)
        newNode->nodes[i]->parent = newNode;
    node->parent->keys[pos] = mid;
    node->parent->nodes[pos + 1] = newNode;
    node->parent->numOfNode++;

    if (node->parent->numOfNode == 2 * ORDER)
      splitTree(root, node->parent);
  }

}

//merge
static void mergeTree(tree_t* tree, tree_t* node, int key) {

  tree_t* parent = node->parent;
  tree_t* right = node->right;
  tree_t* left = node->left;
  tree_t* tmp = NULL;
  int pos = 0;

  if (right != NULL && right->parent == node->parent) {
    for (int i = 0; i < right->numOfNode; i++) {
      node->keys[node->numOfNode] = right->keys[i];
      node->nodes[node->numOfNode + 1] = right->nodes[i];
      if (right->nodes[i] != NULL)
        right->nodes[i]->parent = node;
      node->numOfNode++;
    }
    node->nodes[node->numOfNode + 1] = right->nodes[right->numOfNode];
    if (right->nodes[right->numOfNode])
      right->nodes[right->numOfNode]->parent = node;
    if (right->right)
      right->right->left = node;

    node->right = right->right;
    deleteNode(tree, node->parent, findMin(right));
    balance(tree, node, key);
  }
  else {
    for (int i = 0; i < node->numOfNode; i++) {
      left->keys[left->numOfNode] = node->keys[i];
      left->nodes[left->numOfNode + 1] = node->nodes[i];
      if (node->nodes[i] != NULL)
        node->nodes[i]->parent = left;
      left->numOfNode++;
    }
    left->nodes[left->numOfNode + 1] = node->nodes[node->numOfNode];
    if (node->nodes[node->numOfNode])
      node->nodes[node->numOfNode]->parent = left;
    left->right = node->right;
    if (node->right != NULL)
      node->right->left = left;
    deleteNode(tree, left->parent, findMin(node));
    balance(tree, left, key);
  }

}

//insert
void insertKey(tree_t** root, int key) {

  tree_t* tree = (*root);
  tree_t* leaf = findNode(tree, key);
  if (leaf == NULL)
    return;

  for (int i = 0; i < leaf->numOfNode; i++)
    if (leaf->keys[i] == key)
      return;

  int pos = 0;
  while (pos < leaf->numOfNode && leaf->keys[pos] < key)
    ++pos;

  for (int i = leaf->numOfNode; i >= pos + 1; i--)
    leaf->keys[i] = leaf->keys[i - 1];

  leaf->keys[pos] = key;
  leaf->numOfNode++;
  if (leaf->numOfNode == 2 * ORDER)
    splitTree(root, leaf);

}


//find min
static int findMin(tree_t* tree) {

  for (int pos = 0; pos < 2 * ORDER; pos++)
    if (tree->nodes[pos])
      return findMin(tree->nodes[pos]);

  return tree->keys[0];

}

//update tree
static void balance(tree_t* tree, tree_t* node, int key) {

  tree_t* tmp = node->parent;
  int pos = 0;

  while (tmp != NULL) {
    while (pos < tmp->numOfNode && tmp->keys[pos] < key)
      pos++;
    if (pos < tmp->numOfNode)
      if (tmp->keys[pos] != findMin(tmp->nodes[pos + 1]))
        tmp->keys[pos] = findMin(tmp->nodes[pos + 1]);
    tmp = tmp->parent;
  }

}

//delete
static void deleteNode(tree_t* tree, tree_t* node, int key) {

  int pos = 0;
  while (pos < node->numOfNode && node->keys[pos] < key)
    pos++;
  for (int i = pos; i < node->numOfNode; i++)
    node->keys[i] = node->keys[i + 1];
  for (int i = pos + 1; i <= node->numOfNode; i++)
    node->nodes[i] = node->nodes[i + 1];
  for (int i = node->numOfNode + 1; i < 2 * ORDER + 1; i++)
    *(node->nodes + i) = NULL;
  node->numOfNode--;
  if (node == tree) {
    for (int i = 0; i < 2 * ORDER + 1; i++)
      if (node->nodes[i] != NULL)
        if (node->nodes[i]->numOfNode == 0)
          node->nodes[i] = NULL;
    if (tree->numOfNode == 0 && tree->nodes[0] != NULL)
      tree = tree->nodes[0];
    return;
  }

  if (node->numOfNode >= 1)
    balance(tree, node, key);
  else
    if (node->numOfNode < ORDER - 1) {
      tree_t* right = node->right;
      tree_t* left = node->left;
      if (left != NULL && left->numOfNode > (ORDER - 1) && left->parent == node->parent) {
        left->numOfNode--;
        node->numOfNode++;
        for (int i = 1; i < node->numOfNode; i++) {
          node->keys[i] = node->keys[i - 1];
          node->nodes[i] = node->nodes[i - 1];
        }
        node->nodes[node->numOfNode] = node->nodes[node->numOfNode - 1];
        node->keys[0] = left->keys[left->numOfNode];
        node->nodes[0] = left->nodes[left->numOfNode + 1];
        left->nodes[left->numOfNode + 1] = NULL;
        if (node->nodes[0] != NULL)
          node->nodes[0]->parent = node;
        balance(tree, node, key);
      }
      else
        if (right != NULL && right->numOfNode > (ORDER - 1) && right->parent == node->parent) {
          node->numOfNode++;
          node->keys[node->numOfNode - 1] = right->keys[0];
          node->nodes[node->numOfNode] = right->nodes[0];
          if (node->nodes[node->numOfNode] != NULL)
            node->nodes[node->numOfNode]->parent = node;
          for (int i = 0; i < right->numOfNode; i++) {
            right->keys[i] = right->keys[i + 1];
            right->nodes[i] = right->nodes[i + 1];
          }
          for (int i = 0; i < 2 * ORDER; i++)
            if (right->nodes[i] == right->nodes[i + 1] && right->nodes[i] != NULL) {
              right->nodes[i + 1] = NULL;
              break;
            }
          right->numOfNode--;
          balance(tree, node, key);
        }
        else
          mergeTree(tree, node, key);
    }

}

void deleteKey(tree_t* tree, int key) {

  if (tree == NULL)
    return;
  if (findKey(tree, key) == NOTFOUND)
    return;

  tree_t* node = findNode(tree, key);
  deleteNode(tree, node, key);

}

void deleteTree(tree_t* tree) {

  if (tree == NULL)
    return;

  if (tree->isLeaf == NOTLEAF)
    for (int i = 0; i <= tree->numOfNode; i++)
      deleteTree(tree->nodes[i]);

  free(tree);

}

void printTree(tree_t* tree, int index, int child) {

  if (tree != NULL) {
    for (int i = 0; i < tree->numOfNode; i++)
      printf("lvl %i child %i key %i\n", index, child, tree->keys[i]);
    for (int i = 0; i < 2 * ORDER; i++)
      if (tree->nodes[i])
        printTree(tree->nodes[i], index + 1, i);
  }

}