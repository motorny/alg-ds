#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

#define TRUE 1

typedef enum {
  NONE = 0,
  LEFT = 1,
  RIGHT = 2
}way_t;

typedef struct tree_t {
  int num;
  struct tree_t* left;
  struct tree_t* parent;
  struct tree_t* right;
} tree_t;

void NodeAppend(tree_t** tree, int num) {
  tree_t* temp = (*tree), *parent = NULL;
  way_t way = NONE;
  //create tree
  if ((*tree) == NULL) {
    (*tree) = (tree_t*)malloc(sizeof(tree_t));
    if (!(*tree))
      return;

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

    else if (num > temp->num){

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

  temp->num = num;
  temp->left = NULL;
  temp->parent = parent;
  temp->right = NULL;
}

tree_t* NodeFind(tree_t* tree, int num) {
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

void NodeRemove(tree_t** tree, tree_t* vertex) {
  if (!vertex)
    return;
  int temp;
  tree_t* max=vertex, *parent; //go to left child of vertex and then to right 
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
  }
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
  int num=0; 
  tree_t* tree = NULL;

  while (TRUE) {
    comand = fgetc(stdin);

    if (comand == EOF || comand == '\n')
      break;
    
    scanf("%i", &num);

    //comands
    if (comand == 'a') //append
      NodeAppend(&tree, num);

    //adress as bool type. Is adress not NULL -> TRUE. Otherwise, FALSE
    else if (comand == 'f') { //find
      if (NodeFind(tree, num))
        printf("yes\n");
      else
        printf("no\n");
    }

    else if (comand == 'r')//remove
      NodeRemove(&tree, NodeFind(tree, num));

    num = 0;
    comand = fgetc(stdin); //get '\n' from stdin
  }

  DestroyTree(tree);
  return 0;
}
