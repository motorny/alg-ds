#include"F22.h"

tree_t* addTree(tree_t* tree, int low, int high) {
  if (tree == NULL) {
    tree = (tree_t*)malloc(sizeof(tree_t));
    if (tree == NULL)
      return NULL;
    tree->high = high;
    tree->low = low;
    tree->max = high;
    tree->left = NULL;
    tree->right = NULL;
  }
  else {
    if (low < tree->low)
      tree->left = addTree(tree->left, low, high);
    else {
      if (low > tree->low)
        tree->right = addTree(tree->right, low, high);
    }
  }
  if (tree->max < high)
    tree->max = high;
  return tree;
}
static tree_t* minimumTree(tree_t* tree) {
  if (tree->left == NULL)
    return tree;
  return minimumTree(tree->left);
}
static int findMaxArray(int array[N]) {
  int max = array[0];
  int i;
  for (i = 0; i < N; i++) {
    if(array[i] > max)
      max = array[i];
  }
  return max;
}
static void maxOfSubtree(tree_t* tree, int* res) {
  int i = 0;
  int max[N];
  if (tree != NULL && (tree->left != NULL || tree->right != NULL)) {
    memset(max, SMALLNUMBER, sizeof(int));
    if (tree->left != NULL) {
      maxOfSubtree(tree->left, res);
      max[i++] = tree->left->high;
    }
    if (tree->right != NULL) {
      maxOfSubtree(tree->right, res);
      max[i++] = tree->right->high;
    }
    max[i] = tree->high;
    *res = findMaxArray(max);
  }
  if (tree != NULL) {
    *res = tree->high;
  }
}
static tree_t* fixTree(tree_t* tree) {
  int res;
  if (tree != NULL) {
      maxOfSubtree(tree, &res);
    tree->max = res;
    tree->left = fixTree(tree->left);
    tree->right = fixTree(tree->right);
  }
  return tree;
}
tree_t* delTree(tree_t* tree, int low, int high) {
  if (tree == NULL)
    return tree;
  if (low < tree->low)
    tree->left = delTree(tree->left, low, high);
  else {
    if (low > tree->low || high != tree->high)
      tree->right = delTree(tree->right, low, high);
    else {
        if (tree->left != NULL && tree->right != NULL) {
            tree_t* max = minimumTree(tree->right);
            tree->low = max->low;
            tree->high = max->high;
            tree->max = max->max;
            tree->right = delTree(tree->right, max->low, max->high);
            tree = fixTree(tree);
        }
        else {
          if (tree->left != NULL){
            tree_t* tmp = tree;
            tree = tree->left;
            tree = fixTree(tree);
            free(tmp);
            }
          else
            if (tree->right != NULL){
              tree_t* tmp = tree;
              tree = tree->right;
              tree = fixTree(tree);
              free(tmp);
              }
            else {
              tree_t* tmp = tree;
              tree = NULL;
              tree = fixTree(tree);
              free(tmp);
            }
        }
    }
  }
  return tree;
}
int findTree(tree_t* tree, int low, int high) {
  tree_t* tmp = tree;
  while (tmp != NULL) {
    if (tmp->low == low && tmp->high == high)
      return FOUND;
    else
      if(low < tmp->low)
        tmp = tmp->left;
      else
        if(low > tmp->low || high != tmp->high)
          tmp = tmp->right;
  }
  return NOTFOUND;
}
void intersect(tree_t* tree, int low, int high) {
  if (tree == NULL)
    return;
  if(!((tree->low > high) || (tree->high<low)))
    printf("Interval [%i,%i] intersects with [%i,%i]\n",low, high, tree->low, tree->high);
  if (tree->left != NULL && tree->left->max >= low)
    intersect(tree->left, low, high);
  intersect(tree->right, low, high);
}
void printTree(tree_t* tree, int index) {
  if (tree != NULL) {
    printf("level:%i low:%i high:%i max:%i\n", index, tree->low, tree->high, tree->max);
    printTree(tree->left, index + 1);
    printTree(tree->right, index + 1);
  }
}
void freeTree(tree_t* tree) {
  if (tree != NULL) {
    freeTree(tree->right);
    freeTree(tree->left);
    free(tree);
  }
}