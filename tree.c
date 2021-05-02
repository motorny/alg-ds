#include"tree.h"

static tree_t* createTree(void) {
  tree_t* tree;
  tree = (tree_t*)(malloc(sizeof(tree_t)));
  if (tree == NULL)
    return NULL;
  tree->isLeaf = LEAF;
  tree->numOfNode = 0;

  for (int i = 0; i < (2 * ORDER); i++)
    tree->nodes[i] = NULL;

  return tree;
}

//find
tree_t* findKey(tree_t* tree, int key) {
  if (tree == NULL)
    return NULL;

  int pos = 0;
  while (pos < tree->numOfNode && key > tree->keys[pos])
    pos++;

  if (pos < tree->numOfNode && key == tree->keys[pos])
    return tree;
  else//not found 
    if (tree->isLeaf == LEAF)
      return NULL;
    else //if not leaf
      return findKey(tree->nodes[pos], key);
}

//insert
static void splitTree(tree_t* tree, int pos) {
  tree_t* storeTree = createTree();
  tree_t* childTree = tree->nodes[pos];

  storeTree->isLeaf = childTree->isLeaf;
  storeTree->numOfNode = ORDER - 1;
  for (int i = 0; i < storeTree->numOfNode; i++)
    storeTree->keys[i] = childTree->keys[i + ORDER];

  if(childTree->isLeaf == NOTLEAF)
    for (int i = 0; i < storeTree->numOfNode + 1; i++) {
      storeTree->nodes[i] = childTree->nodes[i + ORDER];
      childTree->nodes[i + ORDER] = NULL;
    }
  childTree->numOfNode = ORDER - 1;

  if (tree->nodes[pos + 1] != NULL) {
    int i = pos + 1;

    while (tree->nodes[i] != NULL)
      i++;
    for (i; i > pos + 1; i--) {
        tree->nodes[i] = tree->nodes[i - 1];
        tree->keys[i - 1] = tree->keys[i - 2];
    }
  }
  
  tree->nodes[pos + 1] = storeTree;
  tree->keys[pos] = childTree->keys[ORDER - 1];
  tree->numOfNode++;
}

static void insert(tree_t* tree, int key) {
  int pos = tree->numOfNode - 1;
  
  if (tree->isLeaf == LEAF) {
    while (pos >= 0 && key < tree->keys[pos]) {
      tree->keys[pos + 1] = tree->keys[pos];
      pos--;
    }
    tree->keys[pos + 1] = key;
    tree->numOfNode++;
  }
  else {
    while (pos >= 0 && key < tree->keys[pos])
      pos--;
    pos++;
    if (tree->nodes[pos]->numOfNode == 2 * ORDER - 1) {
        splitTree(tree, pos);
        if (key > tree->keys[pos])
          pos++;
    }
    insert(tree->nodes[pos], key);
  }
}

void insertKey(tree_t** tree, int key) {
  tree_t* root = (*tree);

  if (findKey(*tree, key) != NULL)
    return;

  if ((*tree) == NULL) {//create new node
    (*tree) = createTree();
    (*tree)->keys[0] = key;
    (*tree)->numOfNode++;
    return;
  }

  if (root->numOfNode == 2 * ORDER - 1) {
    tree_t* tmp = createTree();
    (*tree) = tmp;
    tmp->isLeaf = NOTLEAF;
    tmp->numOfNode = 0;
    tmp->nodes[0] = root;
    splitTree(tmp, 0);
    insert(tmp, key);
  }
  else
    insert(root, key);
}

//delete
static int findPos(int* arr, int key, int numOfNodes) {
  int pos = 0;

  while (pos < numOfNodes && key > arr[pos])
    pos++;

  return pos;
}

static int delete(tree_t* tree,tree_t** root, int key) {

  if (tree == NULL)
    return NOTFOUND;

  int numOfNodes = tree->numOfNode;
  int* arr = tree->keys;
  tree_t** nodes = tree->nodes;
  int pos = findPos(arr, key, numOfNodes);
  int min = (ORDER - 1) / 2;
  if (nodes[0] == NULL) {
    if (pos == numOfNodes || key < arr[pos])
      return NOTFOUND;
    for (int i = pos + 1; i < numOfNodes; i++) {
      arr[i - 1] = arr[i];
      nodes[i] = nodes[i + 1];
    }
    tree->numOfNode--;

    if (tree == (*root))
      min = 1;
    if (tree->numOfNode >= min)
      return FOUND;
    else
      return NOTENOUGHNODES;
  }
  if (pos < numOfNodes && key == arr[pos]) {
    tree_t* tmp = nodes[pos];
    int num;
    while (1) {
      num = tmp->numOfNode;
      tree_t* temp = tmp->nodes[num];
      if (temp == NULL)
        break;
      tmp = temp;
    }
    arr[pos] = tmp->keys[num - 1];
    tmp->keys[num - 1] = key;
  }

  int result = delete(nodes[pos],&nodes[pos], key);
  if (result != NOTENOUGHNODES)
    return result;

  int index;
  tree_t* left;
  tree_t* right;
  if (pos > 0 && nodes[pos - 1]->numOfNode > min) {
    index = pos - 1;
    left = nodes[index];
     right = nodes[pos];
    right->nodes[right->numOfNode + 1] = right->nodes[right->numOfNode];

    for (int i = right->numOfNode; i > 0; i--) {
      right->keys[i] = right->keys[i - 1];
      right->nodes[i] = right->nodes[i - 1];
    }
    right->numOfNode++;
    right->keys[0] = arr[index];
    right->nodes[0] = left->nodes[left->numOfNode];
    arr[index] = left->keys[--left->numOfNode];
    return FOUND;
  }

  if (pos < numOfNodes && nodes[pos + 1]->numOfNode  > min) {
    index = pos;
    left = nodes[index];
    right = nodes[index + 1];
    left->keys[left->numOfNode] = arr[index];
    left->nodes[left->numOfNode + 1] = right->nodes[0];
    arr[index] = right->keys[0];
    left->numOfNode++;
    right->numOfNode--;
    for (int i = 0; i < right->numOfNode; i++) {
      right->keys[i] = right->keys[i + 1];
      right->nodes[i] = right->nodes[i + 1];
    }
    right->nodes[right->numOfNode] = right->nodes[right->numOfNode + 1];
    return FOUND;
  }

  if (pos == numOfNodes)
    index = pos - 1;
  else
    index = pos;

  left = nodes[index];
  right = nodes[index + 1];

  left->keys[left->numOfNode] = arr[index];
  left->nodes[left->numOfNode + 1] = right->nodes[0];
  for (int i = 0; i < right->numOfNode; i++) {
    left->keys[left->numOfNode + 1 + i] = right->keys[i];
    left->nodes[left->numOfNode + 2 + i] = right->nodes[i + 1];
  }
  left->numOfNode = left->numOfNode + right->numOfNode + 1;

  free(right);
  for (int i = pos + 1; i < numOfNodes; i++) {
    arr[i - 1] = arr[i];
    nodes[i] = nodes[i + 1];
  }
  if (tree == *root)
    min = 1;
  tree->numOfNode--;
  if (tree->numOfNode >= min)
    return FOUND;
  else
    return NOTENOUGHNODES;
}

void deleteKey(tree_t** root, int key) {
  tree_t* tmp;
  int result = delete((*root), root, key);
  if (result == NOTENOUGHNODES) {
    tmp = *root;
    *root = (*root)->nodes[0];
    free(tmp);
  }
}

void deleteTree(tree_t* tree) {
  if (tree == NULL)
    return;

  if (tree->isLeaf == NOTLEAF)
    for (int i = 0; i <= tree->numOfNode; i++)
      deleteTree(tree->nodes[i]);

  free(tree);
}