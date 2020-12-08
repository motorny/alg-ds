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
  tree_t* temp = (*tree), *newnode, *ptr = (*tree);

  newnode = (tree_t*)malloc(sizeof(tree_t));
  if (!newnode)
    return;
  newnode->left = NULL;
  newnode->right = NULL;
  newnode->parent = NULL;
  newnode->num = num;

  if (!(*tree)) {
    (*tree) = newnode;
    return;
  }

  while (ptr) {
    if (num < ptr->num) {
      if (ptr->left)
        ptr = ptr->left;
      else
        break;
    }

    else if (num > ptr->num) {
      if (ptr->right)
        ptr = ptr->right;
      else
        break;
    }

    else {//such node exists
      free(newnode);
      return;
    }
  }

  //put new node
  if (num < ptr->num)
    ptr->left = newnode;
  else
    ptr->right = newnode;

  newnode->parent = ptr;
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
  tree_t* max=vertex, *parent, *child; //go to left child of vertex and then to right 
  way_t parentway;

  //no childs, free the element
  if (vertex->left == NULL && vertex->right == NULL) {
    if ((vertex == (*tree))) {
      free(vertex);
      (*tree) = NULL;
      return;
    }

    parent = vertex->parent;
    parentway = parent->left == vertex ? LEFT : RIGHT;

    if (parentway == LEFT)
      parent->left = NULL;
    else
      parent->right = NULL;

    free(vertex);
    return;
  }


  //has one child, put child instead of itself
  if ((vertex->left != NULL && vertex->right == NULL) || (vertex->left == NULL && vertex->right != NULL)) {

    if (vertex == (*tree)) { //no parent
      if (vertex->left)
        (*tree) = vertex->left;
      else
        (*tree) = vertex->right;
      (*tree)->parent = NULL;
      free(vertex);
      return;
    }

    parent = vertex->parent;
    parentway = parent->left == vertex ? LEFT : RIGHT;

    if (vertex->left) //only left child
      child = vertex->left;
    else //only right child
      child = vertex->right;

    child->parent = vertex->parent;

    if (parentway == LEFT)
      parent->left = child;
    else
      parent->right = child;

    free(vertex);
    return;
  }

  //node has two childs
  max = max->right;

  while (max->left)
    max = max->left;

  temp = max->num;
  max->num = vertex->num;
  vertex->num = temp;

  //no need to delete max

  //max can have one child on the right
  if (max->right) {
    child= max->right;
    parent = max->parent;
    parentway = parent->left == max ? LEFT : RIGHT;

    if (parentway == LEFT)
      parent->left = child;
    else
      parent->right = child;
    
    child->parent = parent;
  }

  //max has no childs
  else {
    parent = max->parent;
    parentway = parent->left == max ? LEFT : RIGHT;

    if (parentway == LEFT)
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

void PrintTree(tree_t* tree, int level) {
  if (tree) {
    int i;
    PrintTree(tree->left, level + 1);
    for (i = 0; i < level; i++)
      printf("    ");
    printf("%i\n", tree->num);
    PrintTree(tree->right, level + 1);
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
  //PrintTree(tree, 1);
  DestroyTree(tree);

  return 0;
}