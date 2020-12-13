#include "tree.h"

#pragma warning (disable: 4996)

int minSubtree(node_t* tree) {
  int l, r, minH;
  if (tree == NULL) {
    return FALSE;
  }
  if (tree != NULL) {
    if (tree->left != NULL)
      l = minSubtree(tree->left);
    else
      l = 0;
    if (tree->right != NULL) 
      r = minSubtree(tree->right);
    else 
      r = 0;
    if (l == 0 && r != 0)
      minH = r + 1;
    else if (l != 0 && r == 0)
      minH = l + 1;
    else
      minH = min(l,r) + 1;
    tree->height = minH;
    return minH;
  }
} 

int addNode(node_t** tree, int elem) {
  node_t* newElem = (node_t*)malloc(sizeof(node_t));
  if (newElem == NULL)
    return FALSE;
  
  newElem->key = elem;

  newElem->left = NULL; 
  newElem->right = NULL;
  
  if(tree == NULL)
    (*tree) = newElem;
  else {
    while(*tree != NULL)
      if((*tree)->key < elem)
        tree = &((*tree)->right);

      else if((*tree)->key > elem)
        tree = &((*tree)->left);
      
      else if ((*tree)->key == elem)
        return FALSE;
    
    (*tree) = newElem;
  }
  return TRUE;
} 

int deleteElem(node_t** tree, int elem) {
  node_t* delElem;
  if ((*tree) == NULL) 
    return FALSE;

  if (elem < (*tree)->key) {
    deleteElem(&((*tree)->left), elem);
    return TRUE;
  }
  else if (elem > (*tree)->key) {
    deleteElem(&((*tree)->right), elem);
    return TRUE;
  }
  else {
    if ((*tree)->left != NULL && (*tree)->right != NULL) {
      node_t** tmp = &(*tree)->left;
      
      while ((*tmp)->right)
        tmp = &((*tmp)->right);

      (*tree)->key = (*tmp)->key;
      delElem = (*tmp);
      (*tmp) = (*tmp)->left;
      delElem = NULL;
      return TRUE;
    }

    else if ((*tree)->left != NULL) {
      delElem = (*tree);
      (*tree) = (*tree)->left;
      delElem = NULL;
      return TRUE;
    }

    else if ((*tree)->right != NULL) {
      delElem = (*tree);
      (*tree) = (*tree)->right;
      delElem = NULL;
      return TRUE;
    }

    else {
      free(*tree);
      (*tree) = NULL;
      return TRUE;
    }
  }
}

int findElem(node_t* tree, int elem) {
  if(tree == NULL)
    return FALSE;
  else if(elem == tree->key)
    return TRUE;
  else if(elem < tree->key)
    findElem(tree->left, elem);
  else if(elem > tree->key)
    findElem(tree->right, elem);
} 

void printHeightTree(node_t* tree, int level) {
  if (tree != NULL) {
    printf("%i \n", tree->height);
    printHeightTree(tree->left, level + 1);
    printHeightTree(tree->right, level + 1);
  }
}

node_t* funcTree(node_t* tree) {
  char func;
  int key, strFuncElem;

  while (1) {
    func= getchar();
    if (func == EOF)
      return tree;
    while (func == '\0' || func == '\n' || isspace(func) != 0)
      strFuncElem = getchar();
    strFuncElem = scanf("%i", &key);
    switch (func) {
    case('a'):
      addNode(&tree, key);
      break;
    case('r'):
      deleteElem(&tree, key);
      break;
    case('f'):
      if (findElem(tree, key) == 1)
        printf("yes\n");
      else
        printf("no\n");
      break;
    default:
      break;
    }
    strFuncElem = getchar();
  }
}

void deleteTree(node_t* tree) {
  if (tree != NULL) {
    tree->height = 0;
    tree->key = 0;
    tree->left = NULL;
    tree->right = NULL;
  }
}
