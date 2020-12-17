#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
#define TRUE 1
#define FALSE 0
typedef int Tree;
struct tree {
  Tree value;
  struct tree* left;
  struct tree* right;
};
struct tree* GetNewNode(Tree value) {
  struct tree* tmp = (struct tree*)malloc(sizeof(struct tree));
  if (tmp == NULL) {
    return NULL;
  }
  tmp->left = NULL;
  tmp->right = NULL;
  tmp->value = value;
  return tmp;
}
int Insert(struct tree** head, int value) {
  struct tree* tmp = NULL;
  if (*head == NULL) {
    *head = GetNewNode(value);
    return TRUE;
  }
  tmp = *head;
  while (tmp) {
    if (value > tmp->value) {
      if (tmp->right != NULL) {
        tmp = tmp->right;
        continue;
      }
      else {
        tmp->right = GetNewNode(value);
        return TRUE;
      }
    }
    else if (value < tmp->value) {
      if (tmp->left != NULL) {
        tmp = tmp->left;
        continue;
      }
      else {
        tmp->left = GetNewNode(value);
        return TRUE;
      }
    }
    else {
      return FALSE;
    }
  }
  return FALSE;
}
int FindByValue(struct tree* root, Tree value, struct tree** outputPtr) {
  while (root) {
    if (root->value > value) {
      root = root->left;
      continue;
    }
    else if (root->value < value) {
      root = root->right;
      continue;
    }
    else {
      (*outputPtr) = root;
      return TRUE;
    }
  }
  (*outputPtr) = NULL;
  return FALSE;
}
int RemoveByValue(struct tree** tree, Tree value) {
  struct tree* root;
  if ((*tree) == NULL) {
    return FALSE;
  }
  if ((*tree)->value > value) {
    RemoveByValue(&((*tree)->left), value);
    return TRUE;
  }
  else if ((*tree)->value < value) {
    RemoveByValue(&((*tree)->right), value);
    return TRUE;
  }
  else {
    if ((*tree)->left && (*tree)->right) {
      struct tree** tmp = &(*tree)->left;
      while ((*tmp)->right) { 
        tmp = &((*tmp)->right);
      }
      (*tree)->value = (*tmp)->value;
      root = (*tmp);
      (*tmp) = (*tmp)->left;
      free(root);
      return TRUE;
    }
    else if ((*tree)->left) {
      root = (*tree);
      (*tree) = (*tree)->left;
      free(root);
      return TRUE;
    }
    else if ((*tree)->right) {
      root = (*tree);
      (*tree) = (*tree)->right;
      free(root);
      return TRUE;
    }
    else {
      free(*tree);
      (*tree) = NULL;
      return TRUE;
    }

  }
}
void Print(struct tree* root, int level) {
  if (root) {
    printf("%i  %i\n", level, root->value);
    Print(root->left, level + 1);
    Print(root->right, level + 1);
  }
}
void Delete(struct tree* tree) {
  if (tree != NULL) {
    Delete(tree->left);
    Delete(tree->right);
    free(tree);
  }
}
void Input(struct tree** tree, char action, int value, int** output, int* sizeOfout) {
  struct tree* buf;
  switch (action){
  case 'a':
    Insert(tree, value);
    break;
  case 'r':
    RemoveByValue(tree, value);
    break;
  case 'f':
    if (FindByValue(*tree, value, &buf)) {
      printf("Y");
    }
    else {
      printf("N");
    }
    break;
  default:
    break;
  }
}
void SubTreeLeaves(struct tree** tree, int** number, int* level) {
  if (tree != NULL) {
    if ((*tree)->left == NULL && (*tree)->right == NULL) {
      (*tree)->value = 1;
      return;
    }
    else if ((*tree)->left == NULL) {
      SubTreeLeaves(&(*tree)->right, number, level);
      (*tree)->value = (*tree)->right->value;
    }
    else if ((*tree)->right == NULL) {
      SubTreeLeaves(&(*tree)->left, number, level);
      (*tree)->value = (*tree)->left->value;
    }
    else {
      SubTreeLeaves(&(*tree)->left, number, level);
      SubTreeLeaves(&(*tree)->right, number, level);
      (*tree)->value = (*tree)->right->value + (*tree)->left->value;
    }
  }
}
int main(void) {
  struct tree* tree = NULL;
  char esc;
  char act;
  int value;
  int* output;
  int out = 1;
  output = (int*)malloc(1*sizeof(int));
  if (!output) {
    return FALSE;
  }
  do {
    act = (char)getchar();
    if (feof(stdin)) {
      break;
    }
    scanf(" %i", &value);
    Input(&tree, act, value, &output, &out);
    scanf("%c", &esc);
  } while (act != EOF);
  for (int i = 0; i < out - 1; i++)
  {
    if (output[i] == TRUE) {
      printf("Y");
    }
    else {
      printf("N");
    }
  }
  free(output);
  return 0;
}
