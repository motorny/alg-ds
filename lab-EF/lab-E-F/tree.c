#include "tree.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int TreeAdd(node_t** tree, int num) {
  node_t* newNode = (node_t*)malloc(sizeof(node_t));
  node_t* nodeTmp = NULL;

  if (newNode == NULL)
    return FALSE;

  newNode->key = num;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->num = 1;

  if (*tree == NULL) {
    *tree = newNode;
    newNode->parent = NULL;
  }
  else {
    while (*tree != NULL) {
      nodeTmp = *tree;
      if ((*tree)->key < num) {
        tree = &((*tree)->right);
      }
      else if ((*tree)->key > num) {
        tree = &((*tree)->left);
      }
      else {
        free(newNode);
        return FALSE;
      }
    }

    *tree = newNode;
    newNode->parent = nodeTmp;
  }

  while (newNode->parent != NULL) {
    newNode = newNode->parent;
    newNode->num++;
  }

  return TRUE;
}

node_t* TreeFind(node_t* tree, int num) {
  while (tree != NULL) {
    if (tree->key > num)
      tree = tree->left;
    else if (tree->key < num)
      tree = tree->right;
    else
      return tree;
  }

  return NULL;
}

static node_t* findMax(node_t* tree) {
  if (tree == NULL)
    return NULL;

  while (tree->right != NULL)
    tree = tree->right;

  return tree;
}

int TreeDel(node_t** tree, int num) {
  node_t* nodeToDel = NULL, * tmp = NULL;

  if (*tree != NULL) {
    nodeToDel = TreeFind(*tree, num);
    if (nodeToDel != NULL) {
      if (nodeToDel->left == NULL && nodeToDel->right == NULL) {
        if (nodeToDel->parent != NULL) {
          if (nodeToDel == nodeToDel->parent->left)
            nodeToDel->parent->left = NULL;
          else
            nodeToDel->parent->right = NULL;
        }
        else {
          *tree = NULL;
        }
      }
      else if (nodeToDel->left != NULL && nodeToDel->right == NULL) {
        if (nodeToDel->parent != NULL) {
          nodeToDel->left->parent = nodeToDel->parent;
          if (nodeToDel == nodeToDel->parent->left)
            nodeToDel->parent->left = nodeToDel->left;
          else
            nodeToDel->parent->right = nodeToDel->left;
        }
        else {
          *tree = nodeToDel->left;
          (*tree)->parent = NULL;
        }
      }
      else if (nodeToDel->right != NULL && nodeToDel->left == NULL) {
        if (nodeToDel->parent != NULL) {
          nodeToDel->right->parent = nodeToDel->parent;
          if (nodeToDel == nodeToDel->parent->left)
            nodeToDel->parent->left = nodeToDel->right;
          else
            nodeToDel->parent->right = nodeToDel->right;
        }
        else {
          *tree = nodeToDel->right;
          (*tree)->parent = NULL;
        }
      }
      else {
        tmp = findMax(nodeToDel->left);
        nodeToDel->key = tmp->key;
        TreeDel(&(nodeToDel->left), tmp->key);

        return TRUE;
      }

      tmp = nodeToDel;
      while (tmp->parent != NULL) {
        tmp = tmp->parent;
        tmp->num--;
      }

      free(nodeToDel);
      return TRUE;
    }
  }

  return FALSE;
}

void TreeClear(node_t** tree) {
  while ((*tree) != NULL)
    TreeDel(tree, (*tree)->key);
}

void TreePrint(node_t* tree) {
  if (tree != NULL) {
    if (tree->left != NULL || tree->right != NULL) {
      printf("%d (", tree->key);
      TreePrint(tree->left);
      printf(") (");
      TreePrint(tree->right);
      printf(")");
    }
    else {
      printf("%d", tree->key);
    }
  }
}

static int treeHeight(node_t* tree) {
  int heightL = 0, heightR = 0;

  if (tree != NULL) {
    heightL = treeHeight(tree->left);
    heightR = treeHeight(tree->right);

    return ((heightL > heightR) ? heightL : heightR) + 1;
  }

  return 0;
}

static void printEmptyBlock(void) {
  int counter = 0;

  for (; counter < BLOCKSIZE; counter++)
    printf(" ");
}

static void printLvl(int lvl, int height, int lvlNum, node_t** cur) {
  int counter = 0, counter1 = 0;
  int shift = (int)pow(2, height - lvl);

  if (cur != NULL && lvl > 0 && height >= lvl) {
    for (; counter < shift - 1; counter++) {
      printEmptyBlock();
    }
    for (counter = 0; counter < lvlNum; counter++) {
      if (cur[counter] == NULL)
        printEmptyBlock();
      else
        printf("%5d", cur[counter]->key);
      if (counter != lvlNum - 1) {
        for (counter1 = 0; counter1 < shift * 2 - 1; counter1++) {
          printEmptyBlock();
        }
      }
      else
        printf("\n");
    }
  }
}

void TreePrettyPrint(node_t* tree) {
  int height = treeHeight(tree);
  int counter = 0, lvlCounter = 1, lvlNum = 1, size;
  node_t** cur, **next, **tmp;

  if (tree != NULL) {
    size = (int)pow(2, height);
    cur = (node_t * *)malloc(size * sizeof(node_t*));
    next = (node_t * *)malloc(size * sizeof(node_t*));
    if (cur == NULL || next == NULL) {
      free(cur);
      free(next);
      return;
    }
    cur[0] = tree;
    printLvl(lvlCounter, height, lvlNum, cur);
    for (; lvlCounter < height; lvlCounter++) {
      for (counter = 0; counter < lvlNum; counter++) {
        if (cur[counter] != NULL) {
          next[2 * counter] = cur[counter]->left;
          next[2 * counter + 1] = cur[counter]->right;
        }
        else {
          next[2 * counter] = NULL;
          next[2 * counter + 1] = NULL;
        }
      }
      lvlNum *= 2;
      tmp = cur;
      cur = next;
      next = tmp;
      printLvl(lvlCounter + 1, height, lvlNum, cur);
    }

    free(cur);
    free(next);
  }
}

static int size(node_t* node) {
  if (node == NULL || node->left == NULL)
    return 1;

  return node->left->num + 1;
}

static int number(node_t* node) {
  node_t* p;
  int r = size(node);

  if (node != NULL)
    while (node->parent != NULL) {
      p = node->parent;

      if (node == p->right)
        r += size(p->left);

      node = node->parent;
    }
  else
    return FALSE;

  return r;
}

static node_t* getKMin(node_t* tree, int k) {
  int r;

  if (tree == NULL)
    return NULL;

  if (tree->left != NULL) {
    r = tree->left->num + 1;
  }
  else
    r = 1;

  if (r != k) {
    if (k < r)
      tree = getKMin(tree->left, k);
    else
      tree = getKMin(tree->right, k - r);
  }

  return tree;
}
//
node_t* FindKLower(node_t* tree, int key, int k) {
  int curNodeK;
  node_t* curNode;

  if (tree == NULL)
    return NULL;

  curNode = TreeFind(tree, key);
  if (curNode == NULL)
    return NULL;

  curNodeK = number(curNode);
  if (curNodeK - k <= 0 || curNodeK - k > tree->num)
    return NULL;

  return getKMin(tree, curNodeK - k);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */