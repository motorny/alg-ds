#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


typedef enum {
  NONE = 0,
  LEFT = 1,
  RIGHT = 2
}way_t;

typedef struct tree_t {
  
  int num;
  struct tree_t* left;
  struct tree_t* right;
  struct tree_t* parent;
  
} tree_t;


void Append(tree_t** tree, int num) {

  tree_t* new;
  tree_t* tmp = *tree;

  new = (tree_t*)malloc(sizeof(tree_t));
  if (new == NULL)
    return;

  new->left = NULL;
  new->right = NULL;
  new->parent = NULL;
  new->num = num;

  if (!(*tree)) {
    *tree = new;
    return;
  }

  while (tmp) {

    if (num < tmp->num) {
      if (tmp->left)
        tmp = tmp->left;
      else
        break;
    }

    else if (num > tmp->num) {
      if (tmp->right)
        tmp = tmp->right;
      else
        break;
    }

    else {
      free(new);
      return;
    }
  }

  if (num < tmp->num)
    tmp->left = new;

  else
    tmp->right = new;

  new->parent = tmp;
}


tree_t* Find(tree_t* tree, int num) {
  tree_t* tmp = tree;

  while (tmp) {

    if (num < tmp->num)
      tmp = tmp->left;

    else if (num > tmp->num)
      tmp = tmp->right;

    else
      return tmp;
  }
  return NULL;
}


void Delete(tree_t** tree, tree_t* vert) {

  if (!vert)
    return;

  int tmp;

  tree_t* max = vert, * parent, * child; 
  way_t pway;

  
  if (vert->left == NULL && vert->right == NULL) {
    if ((vert == (*tree))) {
      free(vert);
      (*tree) = NULL;
      return;
    }

    parent = vert->parent;

    if (parent->left == vert)
      pway = LEFT;
    else
      pway = RIGHT;

    if (pway == LEFT)
      parent->left = NULL;
    else
      parent->right = NULL;

    free(vert);
    return;
  }


  if ((vert->left != NULL && vert->right == NULL) || (vert->left == NULL && vert->right != NULL)) {

    if (vert == (*tree)) {
      if (vert->left)
        (*tree) = vert->left;
      else
        (*tree) = vert->right;
      (*tree)->parent = NULL;
      free(vert);
      return;
    }

    parent = vert->parent;

    if (parent->left == vert)
      pway = LEFT;
    else
      pway = RIGHT;

    if (vert->left)
      child = vert->left;
    else
      child = vert->right;

    child->parent = vert->parent;

    if (pway == LEFT)
      parent->left = child;
    else
      parent->right = child;

    free(vert);
    return;
  }


  max = max->right;

  while (max->left)
    max = max->left;

  tmp = max->num;
  max->num = vert->num;
  vert->num = tmp;


  if (max->right) {
    child = max->right;
    parent = max->parent;

    if (parent->left == max)
      pway = LEFT;
    else
      pway = RIGHT;

    if (pway == LEFT)
      parent->left = child;
    else
      parent->right = child;

    child->parent = parent;
  }


  else {
    parent = max->parent;

    if (parent->left == max)
      pway = LEFT;
    else
      pway = RIGHT;

    if (pway == LEFT)
      parent->left = NULL;
    else
      parent->right = NULL;
  }
  free(max);
  return;
}

void DestroyTree(tree_t* tree) {
  if (tree) {
    DestroyTree(tree->left);
    DestroyTree(tree->right);
    free(tree);
  }
}



int main(void) {

  char comand;
  int num = 0;
  tree_t* tree = NULL;

  while (1) {
    comand = fgetc(stdin);

    if (comand == EOF || comand == '\n')
      break;

    scanf("%i", &num);


    if (comand == 'a')
      Append(&tree, num);

    else if (comand == 'f') {

      if (Find(tree, num))
        printf("yes\n");

      else
        printf("no\n");
    }

    else if (comand == 'r')
      Delete(&tree, Find(tree, num));

    num = 0;
    comand = fgetc(stdin);
  }

  DestroyTree(tree);

  return 0;
}