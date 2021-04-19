#include "bplus.h"

#define MAX_LENGTH 100
#define SPACES 4

static node_t* LeafSearch(node_t* node, const int key) {
  int i = 0;

  if (node->leaf)
    return node;

  while (i < node->keyNum && key >= node->key[i])
    ++i;

  return LeafSearch(node->child[i], key);
}

static ERR_STATUS Split(bplus_t* tree, node_t* node) {
  node_t* newNode = malloc(sizeof(node_t));
  if (!newNode)
    return ERROR;


  node_t* newRoot, * prev;
  int median;
  int i, j;

  for (int i = 0; i <= 2 * DEG; ++i) {
    newNode->child[i] = NULL;
  }

  newNode->right = node->right;
  if (node->right) {
    node->right->left = newNode;
  }
  node->right = newNode;
  newNode->left = node;


  median = node->key[DEG];
  newNode->keyNum = DEG - 1;
  node->keyNum = DEG;
  for (i = 0; i < DEG - 1; ++i) {
    newNode->key[i] = node->key[DEG + i + 1];
    newNode->child[i] = node->child[DEG + i + 1];
    node->child[i + DEG + 1] = NULL;
  }

  newNode->child[newNode->keyNum] = node->child[DEG * 2];
  node->child[DEG * 2] = NULL;

  if (node->leaf) {
    newNode->leaf = OK;
    ++newNode->keyNum;

    for (i = newNode->keyNum - 1; i > 0; --i)
      newNode->key[i] = newNode->key[i - 1];
    newNode->key[0] = node->key[DEG];
  }

  if (node == tree->root) {
    newRoot = malloc(sizeof(node_t));
    if (!newRoot) {
      free(newNode);
      return ERROR;
    }
    for (i = 0; i <= 2 * DEG; ++i) {
      if (newNode->child[i]) {
        newNode->child[i]->parent = newNode;
      }
      if (node->child[i]) {
        node->child[i]->parent = node;
      }
    }
    tree->root = newRoot;
    tree->root->key[0] = median;
    tree->root->child[0] = node;
    tree->root->child[1] = newNode;
    tree->root->keyNum = 1;
    tree->root->parent = NULL;
    tree->root->left = NULL;
    tree->root->right = NULL;
    tree->root->leaf = ERROR;
    node->parent = tree->root;
    newNode->parent = tree->root;
    for (i = 2; i <= 2 * DEG; ++i) {
      tree->root->child[i] = NULL;
    }
  }
  else {
    newNode->parent = node->parent;
    prev = node->parent;

    i = 0;
    while (i < prev->keyNum&& median >= prev->key[i])
      ++i;

    for (j = prev->keyNum; j > i; --j)
      prev->key[j] = prev->key[j - 1];

    for (j = prev->keyNum + 1; j > i + 1; --j)
      prev->child[j] = prev->child[j - 1];

    for (j = 0; j < 2 * DEG; ++j)
      if (newNode->child[j])
        newNode->child[j]->parent = newNode;

    prev->key[i] = median;
    prev->child[i + 1] = newNode;
    ++prev->keyNum;

    if (prev->keyNum == 2 * DEG)
      Split(tree, prev);
  }

  return OK;
}

static int FindMinKey(node_t* node) {
  for (int i = 0; i < 2 * DEG; ++i) {
    if (node->child[i]) {
      return FindMinKey(node->child[i]);
    }
  }
  return node->key[0];
}

static void UPD(node_t* node, int key) {
  node_t* prev = node->parent;
  int pos = 0;

  while (prev) {
    while ((pos < prev->keyNum) && (prev->key[pos] < key))
      ++pos;
    if (pos < prev->keyNum) {
      if (prev->key[pos] != FindMinKey(prev->child[pos + 1])) {
        prev->key[pos] = FindMinKey(prev->child[pos + 1]);
      }
    }
    prev = prev->parent;
  }
}

static void DeleteInNode(bplus_t* tree, node_t* node, int key) {
  int pos = 0, i = 0;
  node_t* right, * left;
  while (pos < node->keyNum && node->key[pos] < key)
    ++pos;

  for (i = pos; i < node->keyNum; ++i)
    node->key[i] = node->key[i + 1];

  for (i = pos + 1; i <= node->keyNum; ++i)
    node->child[i] = node->child[i + 1];

  for (i = node->keyNum + 1; i <= 2 * DEG; ++i)
    node->child[i] = NULL;

  --node->keyNum;

  if (node == tree->root) {
    for (i = 0; i <= 2 * DEG; ++i) {
      if (node->child[i]) {
        if (node->child[i]->keyNum == 0) {
          node->child[i] = NULL;
        }
      }
    }
    if (tree->root->keyNum == 0 && node->child[0]) {
      tree->root = tree->root->child[0];
    }
    return;
  }
  if (node->keyNum >= DEG / 2 - 1) {
    UPD(node, key);
    return;
  }

  right = node->right;
  left = node->left;
  if (left && left->keyNum > DEG - 1 && left->parent == node->parent) {
    --left->keyNum;
    ++node->keyNum;

    for (i = 1; i < node->keyNum - 1; ++i) {
      node->key[i] = node->key[i - 1];
      node->child[i] = node->child[i - 1];
    }
    node->child[node->keyNum] = node->child[node->keyNum - 1];
    node->key[0] = left->key[left->keyNum];
    node->child[0] = left->child[left->keyNum + 1];
    left->child[left->keyNum + 1] = NULL;
    if (node->child[0])
      node->child[0]->parent = node;

    UPD(node, key);
  }
  else if (right && right->keyNum > DEG - 1 && right->parent == node->parent) {
    --right->keyNum;
    ++node->keyNum;

    node->key[node->keyNum - 1] = right->key[0];
    node->child[node->keyNum] = right->child[0];
    if (node->child[node->keyNum])
      node->child[node->keyNum]->parent = node;

    for (i = 0; i < right->keyNum - 1; ++i) {
      right->key[i] = right->key[i + 1];
      right->child[i] = right->child[i + 1];
    }
    right->child[i] = right->child[i + 1];

    for (i = 0; i < 2 * DEG; ++i) {
      if (right->child[i] == right->child[i + 1] && right->child[i] != NULL) {
        right->child[i + 1] = NULL;
        break;
      }
    }
    UPD(node, key);
  }

  else {
    if (right && right->parent == node->parent) {
      for (i = 0; i < right->keyNum; ++i) {
        node->key[node->keyNum] = right->key[i];
        node->child[node->keyNum + 1] = right->child[i];
        if (right->child[i])
          right->child[i]->parent = node;
        ++node->keyNum;
      }
      node->child[node->keyNum + 1] = right->child[right->keyNum];

      if (right->child[right->keyNum])
        right->child[right->keyNum]->parent = node;
      if (right->right)
        right->right->left = node;

      node->right = right->right;
      DeleteInNode(tree, node->parent, FindMinKey(right));
      UPD(node, key);
    }
    else {
      for (i = 0; i < node->keyNum; ++i) {
        left->key[left->keyNum] = node->key[i];
        left->child[left->keyNum + 1] = node->child[i];
        if (node->child[i])
          node->child[i]->parent = left;
        left->keyNum++;
      }
      left->child[left->keyNum + 1] = node->child[node->keyNum];
      if (node->child[node->keyNum]) {
        node->child[node->keyNum]->parent = left;
      }

      left->right = node->right;
      if (node->right)
        node->right->left = left;

      DeleteInNode(tree, left->parent, FindMinKey(node));
      UPD(left, key);
    }
  }
}

static void FreeNode(node_t* node) {
  int i;
  if (node->leaf)
    free(node);
  else
    for (i = 0; i <= node->keyNum; ++i) {
      FreeNode(node->child[i]);
    }
}

static int GetHeight(bplus_t* tree) {
  int res = 0;
  node_t* node = tree->root;
  while (node != NULL && !node->leaf) {
    node = node->child[0];
    ++res;
  }
  return res;
}


bplus_t* BplusCreate() {
  bplus_t* newTree = malloc(sizeof(bplus_t));
  int i;

  if (newTree) {
    newTree->root = malloc(sizeof(node_t));
    if (!newTree->root) {
      free(newTree);
      return NULL;
    }
    newTree->root->leaf = OK;
    newTree->root->keyNum = 0;
    newTree->root->left = NULL;
    newTree->root->right = NULL;
    newTree->root->parent = NULL;
    for (i = 0; i <= 2 * DEG; ++i) {
      newTree->root->child[i] = NULL;
    }
  }

  return newTree;
}

ERR_STATUS BplusInsert(bplus_t* tree, const int key) {
  node_t* node;
  int i = 0, j = 0;

  if (!tree)
    return ERROR;

  node = LeafSearch(tree->root, key);

  while ((i < node->keyNum) && (key >= node->key[i])) {
    if (key == node->key[i])
      return ERROR;
    ++i;
  }

  for (j = node->keyNum; j > i; --j) {
    node->key[j] = node->key[j - 1];
  }
  node->key[i] = key;
  ++node->keyNum;

  if (node->keyNum == 2 * DEG)
    return Split(tree, node);

  return OK;
}

ERR_STATUS BplusSearch(const bplus_t* tree, const int key) {
  node_t* leaf;
  int i;

  if (!tree) {
    return ERROR;
  }

  leaf = LeafSearch(tree->root, key);

  for (i = 0; i < leaf->keyNum; ++i)
    if (leaf->key[i] == key)
      return FOUND;
  return NOT_FOUND;
}

ERR_STATUS BplusDelete(bplus_t* tree, const int key) {
  node_t* leaf = LeafSearch(tree->root, key);
  int i;
  if (!leaf)
    return ERROR;

  for (i = 0; i < leaf->keyNum; ++i)
    if (leaf->key[i] == key) {
      DeleteInNode(tree, leaf, key);
      return OK;
    }

  return ERROR;
}

void BplusFree(bplus_t* tree) {
  if (tree) {
    FreeNode(tree->root);
    free(tree);
  }
}

bplus_t* Merge(bplus_t* t1, bplus_t* t2) {
  int h1 = GetHeight(t1);
  int h2 = GetHeight(t2);
  int tmpH;
  int i;

  node_t* n1 = h1 >= h2 ? t1->root : t2->root;
  node_t* n2 = h1 < h2 ? t1->root : t2->root;

  bplus_t* tmp;
  int flag = 0;
  if (h2 > h1) {
    flag = 1;
    tmp = t1;
    t1 = t2;
    t2 = tmp;

    tmpH = h1;
    h1 = h2;
    h2 = tmpH;
  }

  while (h1 > h2 + 1) {
    n1 = flag ? n1->child[0] : n1->child[n1->keyNum - 1];
    --h1;
  }

  if (!flag)
    n1->child[n1->keyNum] = n2;
  else {
    n1->child[n1->keyNum + 1] = n1->child[n1->keyNum];
    for (i = n1->keyNum; i > 0; --i) {
      n1->key[i] = n1->key[i - 1];
      n1->child[i] = n1->child[i - 1];
    }
    n1->child[0] = n2;
  }

  ++n1->keyNum;
  if (n1->keyNum == 2 * DEG)
    Split(t1, n1);

  return t1;
}

void BplusSplit(bplus_t* tree, int key, bplus_t* t1, bplus_t* t2) {
  bplus_t* left[MAX_LENGTH];
  bplus_t* right[MAX_LENGTH];
  int lpos = 0;
  int rpos = 0;

  node_t* node = tree->root;
  int i, j;
  while (node && !node->leaf) {
    i = 0;
    while (node->key[i] < key) {
      left[lpos++] = BplusCreate();
      left[lpos - 1]->root = node->child[i];
      ++i;
    }
    for (j = i + 1; i <= node->keyNum; ++j) {
      right[rpos++] = BplusCreate();
      right[rpos - 1]->root = node->child[i];
    }
    node = node->child[i];
  }

  t1 = BplusCreate();
  t2 = BplusCreate();

  if (!node)
    return;

  i = 0;

  left[lpos++] = BplusCreate();
  while (node->key[i] < key) {
    BplusInsert(left[lpos - 1], node->key[i]);
    ++i;
  }

  right[rpos++] = BplusCreate();
  while (i < node->keyNum) {
    BplusInsert(right[rpos - 1], node->key[i]);
    ++i;
  }

  for (i = 0; i < lpos; ++i) {
    t1 = Merge(t1, left[i]);
  }
  for (i = 0; i < rpos; ++i) {
    t2 = Merge(t2, right[i]);
  }

  return;
}

static void PrintSubtree(node_t* node, int space) {
  if (!node) {
    return;
  }

  int i, j;
  if (node->leaf) {
    for (i = node->keyNum - 1; i >= 0; --i) {
      for (j = 0; j < space; ++j) {
        printf(" ");
      }
      printf("%i", node->key[i]);
      printf("\n");
    }
  }
  else {
    for (i = node->keyNum; i > node->keyNum / 2; --i) {
      PrintSubtree(node->child[i], space + SPACES);
    }
    for (i = 0; i < node->keyNum; ++i) {
      for (j = 0; j < space; ++j) {
        printf(" ");
      }
      printf("%i", node->key[i]);
      printf("\n");
    }
    for (i = node->keyNum / 2; i >= 0; --i) {
      PrintSubtree(node->child[i], space + SPACES);
    }
  }

  return;
}

void BplusPrint(bplus_t* tree) {
  if (!tree)
    return;
  PrintSubtree(tree->root, 0);

  return;
}