#include <stdio.h>
#include <stdlib.h>

typedef struct tree_t {
  int num;
  int order; //order from the smallest number in tree to the biggest
  struct tree_t* left;
  struct tree_t* parent;
  struct tree_t* right;
} tree_t;

typedef enum {
  NONE = 0,
  LEFT = 1,
  RIGHT = 2
}way_t;

//will place order in appending function
void UpdateOrder(tree_t* tree, int* order) {
  if (tree) {
    if(tree->left)
      UpdateOrder(tree->left, order);

    tree->order = *order;
    (*order)++;

    if(tree->right)
      UpdateOrder(tree->right, order);
  }
}

void NodeAppend2(tree_t** tree, int num) {
  tree_t* temp = (*tree), * parent = NULL;
  way_t way = NONE;
  int order = 1;
  //create tree
  if ((*tree) == NULL) {
    (*tree) = (tree_t*)malloc(sizeof(tree_t));
    if (!(*tree))
      return;

    (*tree)->order = order;
    (*tree)->num = num;
    (*tree)->left = NULL;
    (*tree)->right = NULL;
    (*tree)->parent = NULL;
    return;
  }
  parent = *tree;
  //go to child once to put temp2 pointer on parent to put pointers later
  if (num < temp->num) {
    if (temp->left)
      temp = temp->left;
    else//remember where must go
      way = LEFT;
  }
  //go to child once to put temp2 pointer on parent to put pointers later
  else if (num > temp->num) {
    if (temp->right)
      temp = temp->right;
    else
      way = RIGHT;
  }

  while (way == NONE && temp && temp->num != num) {
    parent = temp;

    if (num < temp->num) {

      if (temp->left) {
        parent = temp;
        temp = temp->left;
      }
      else {//remember where must go
        way = LEFT;
        break;
      }
    }

    else if (num > temp->num) {

      if (temp->right) {
        parent = temp;
        temp = temp->right;
      }
      else {
        way = RIGHT;
        break;
      }
    }

  }

  //vertex exists, do nothing
  if (temp && temp->num == num)
    return;

  //temp is empty, create node
  if (way == LEFT) {
    temp->left = (tree_t*)malloc(sizeof(tree_t));
    if (!temp->left)
      return;
    temp = temp->left;
  }
  else if (way == RIGHT) {
    temp->right = (tree_t*)malloc(sizeof(tree_t));
    if (!temp->right)
      return;
    temp = temp->right;
  }

  //put adress of order to return it to this function
  temp->num = num;
  temp->left = NULL;
  temp->parent = parent;
  temp->right = NULL;

  UpdateOrder((*tree), &order);
}

tree_t* KLowerNodeFind(tree_t* tree, int k) {
  if (tree) {

    if (tree->order == k)
      return tree;

    if (KLowerNodeFind(tree->left, k))
      return tree->left;

    if (KLowerNodeFind(tree->right, k))
      return tree->right;
  }
  return NULL;
}

void DestroyTree2(tree_t* tree) {
  if (tree) {
    DestroyTree2(tree->left);
    DestroyTree2(tree->right);
    free(tree);
  }
}

tree_t* NodeFind2(tree_t* tree, int num) {
  tree_t* temp = tree;

  while (temp) {

    if (num < temp->num)
      temp = temp->left;

    else if (num > temp->num)
      temp = temp->right;

    else// found
      return temp;
  }

  return NULL;
}

void NodeRemove2(tree_t** tree, tree_t* vertex) {

  if (!vertex)
    return;
  int temp, order = 1;
  tree_t* max = vertex, * parent; //go to left child of vertex and then to right 
  way_t parentway;

  //change numbers of removing vertex and max
  if (max->left)
    max = max->left;

  while (max->right)
    max = max->right;

  temp = max->num;
  max->num = vertex->num;
  vertex->num = temp;

  //now we should remove 'max'. He can have 1 child on the left.
  if (max->left == NULL && max->right == NULL) {

    if (max == (*tree)) {
      free(max);
      (*tree) = NULL;
      return;
    }

    parent = max->parent;

    parentway = (parent->left == max) ? LEFT : RIGHT;

    if (parentway == LEFT)
      parent->left = NULL;
    else //parentway==RIGHT
      parent->right = NULL;

    free(max);
    UpdateOrder((*tree), &order);
  }

  else { //has one child on the left

    parent = max->parent;
    parentway = (parent->left == max) ? LEFT : RIGHT;

    if (parentway == LEFT) {
      parent->left = max->left;
      max->left->parent = parent;
    }
    else { //parentway == RIGHT
      parent->right = max->left;
      max->left->parent = parent;
    }
    free(max);
    UpdateOrder((*tree), &order);
  }
}

//printing tree rotated on 90 degrees without vertexes which order >= k
void PrintLowerKTree(tree_t* tree, int level, int k) {
  if (tree) {
    PrintLowerKTree(tree->left, level + 1, k);
    if (tree->order < k) {
      for (int i = 0; i < level; i++)
        printf("   ");
      printf("%i\n", tree->num);
    }
    PrintLowerKTree(tree->right, level + 1, k);
  }
}

int main(void) {
  const int k = 6, ONE = 1;
  tree_t* tree = NULL, *find=NULL;

  NodeAppend2(&tree, 7);
  NodeAppend2(&tree, 5);
  NodeAppend2(&tree, 11);
  NodeAppend2(&tree, 2);
  NodeAppend2(&tree, 6);
  NodeAppend2(&tree, 9);
  NodeAppend2(&tree, 15);
  NodeRemove2(&tree, NodeFind2(tree, 2));
  NodeAppend2(&tree, 2);

  find = KLowerNodeFind(tree, k);

  if (find && (find->num)%2 == 0)
    PrintLowerKTree(tree, ONE, k);

  DestroyTree2(tree);
  return 0;
}
