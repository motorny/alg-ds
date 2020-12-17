#include "tree.h"

#pragma warning (disable: 4996)

int addInter(node_t** tree, int left_border, int right_border) {
  
  if(left_border > right_border)
    return FALSE;
  
  if((*tree) == NULL) {
    (*tree) = (node_t*)malloc(sizeof(node_t));
    if((*tree) == NULL)
      return FALSE;
    (*tree)->left_border = left_border;
    (*tree)->right_border = right_border;
    //(*tree)->left = NULL;
    //(*tree)->right = NULL;
  }

  if(left_border < (*tree)->left_border)
      addInter(&((*tree)->left), left_border, right_border);

  else if (right_border > (*tree)->right_border || left_border > (*tree)->left_border)
      addInter(&((*tree)->right), left_border, right_border);
  return TRUE;
} // вроде ок

int deleteInter(node_t** tree, int left_border, int right_border) {
  node_t* delElem;
  if ((*tree) == NULL) 
    return FALSE;

  if (left_border < (*tree)->left_border) {
    deleteInter(&((*tree)->left), left_border, right_border);
    return TRUE;
  }
  else if (right_border != (*tree)->right_border || left_border > (*tree)->left_border) {
    deleteInter(&((*tree)->right), left_border, right_border);
    return TRUE;
  }
  else {
    if ((*tree)->left != NULL && (*tree)->right != NULL) {
      node_t** tmp = &(*tree)->left;
      
      while ((*tmp)->right)
        tmp = &((*tmp)->right);

      (*tree)->left_border = (*tmp)->left_border;
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
  return FALSE;
}
// вроде норм

int findInter(node_t* tree, int left_border, int right_border) {
  //if(tree == NULL)
    //return FALSE;
  while (tree != NULL) {
    if (tree->left_border == left_border && tree->right_border == right_border) 
      return TRUE;
    else if(left_border < tree->left_border) {
      tree = tree->left;
      continue;
    }
    else if (right_border != tree->right_border || left_border > tree->left_border) {
        tree = tree->right;
        continue;
    }
  }
  return FALSE;
}
 // тоже ок

void intersectInterval(node_t* tree, int left_border, int right_border, inter_t(*arr)[SIZE], int* level) {
  if (tree != NULL) {
    
    if (left_border <= tree->right_border && right_border >= tree->left_border) {
      (*arr)[*level].left_border = tree->left_border;
      (*arr)[*level].right_border = tree->right_border;

      (*level)++;
    }
    intersectInterval(tree->left, left_border, right_border, arr, level);
    intersectInterval(tree->right, left_border, right_border, arr, level);
  }
}

void printInterTree(node_t* tree, int level) {
  if (tree != NULL) {
    printf("level: %i  (%i    %i) \n",level, tree->left_border, tree->right_border);
    printInterTree(tree->left, level + 1);
    printInterTree(tree->right, level + 1);
  }
}
