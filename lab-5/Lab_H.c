#include <stdlib.h>
#include "Lab_H.h"

static node* CreateNode(int value, int level, node* left, node* right)
{
  node* Me = malloc(sizeof(node));
  Me->left = left;
  Me->right = right;
  Me->value = value;
  Me->level = level;
  return Me;
}

//  L <- T                         L-> T
// A B     R             to       A   B R
//
static void Skew(node** El)
{
  node* T = *El;
  if (T != NULL && T->left != NULL && T->left->level == T->level)
  {
    node* L = T->left;
    node* A = L->left;
    node* B = L->right;
    node* R = T->right;

    L->left = A;
    L->right = T;
    T->left = B;
    T->right = R;

    *El = L;
  }
}

//  T -> R -> X             R
// A    B          to     T   X
//                       A B
static void Split(node** El)
{
  node* T = *El;
  if (T != NULL && T->right != NULL && T->right->right != NULL &&
    T->right->level == T->level && T->right->right->level == T->level)
  {
    node* R = T->right;
    node* A = T->left;
    node* B = R->left;
    node* X = R->right;
    R->right = X;
    R->left = T;
    T->left = A;
    T->right = B;
    R->level++;
    *El = R;
  }
}

static void RecalculateLevel(node* A)
{
  if (A == NULL)
    return;
  int leftlevel = A->left == NULL ? 0 : A->left->level;
  int rightlevel = A->right == NULL ? 0 : A->right->level;
  int should = min(leftlevel, rightlevel) + 1;
  if (should < A->level)
  {
    A->level = should;
    if (should < rightlevel)
      A->right->level = should;
  }
}


static int AddNode(int value, node** El)
{
  int rez = 0;
  if (*El == NULL)
  {
    *El = CreateNode(value, 1, NULL, NULL);
    return 1;
  }
  if ((*El)->value > value)
    rez = AddNode(value, &((*El)->left));
  else if ((*El)->value < value)
    rez = AddNode(value, &((*El)->right));
  else
    rez = 0;
  if (rez)
  {
    Skew(El);
    Split(El);
  }
  return rez;
}

static int DeleteNode(int value, node** El)
{
  int rez = 0;
  if (*El == NULL)
    return 0;
  if ((*El)->value > value)
    rez = DeleteNode(value, &((*El)->left));
  else if ((*El)->value < value)
    rez = DeleteNode(value, &((*El)->right));
  else
  {
    if ((*El)->left == NULL && (*El)->right == NULL) // case 1 - no childs
    {
      free(*El);
      *El = NULL;
      return 1;
    }
    else if ((*El)->left == NULL) // case 2.1 - 1 child and it is right
    {
      node* T = (*El);
      node* R = (*El)->right;
      *El = R;
      free(T);
      return 1;
    }
    else if ((*El)->right == NULL) // case 2.2 - 1 child and it is left
    {
      node* T = (*El);
      node* L = (*El)->left;
      *El = L;
      free(T);
      return 1;
    }
    else                          // case 3 two childs
    {
      node* T = (*El);
      node** Change = &((*El)->right);
      while ((*Change)->left != NULL)
        Change = &((*Change)->left);
      {
        int tmp = T->value;
        T->value = (*Change)->value;
        (*Change)->value = tmp;
      }
      rez = DeleteNode(value, &(*El)->right);
    }
  }
  if (rez)
  {
    RecalculateLevel(*El);
    Skew(El);
    Skew(&((*El)->right));
    if ((*El)->right != NULL)
      Skew(&((*El)->right->right));
    Split(El);
    Split(&((*El)->right));
  }
  return rez;
}

static int FindNode(int value, node* El)
{
  while (El != NULL)
  {
    if (El->value > value)
      El = El->left;
    else if (El->value < value)
      El = El->right;
    else
      return 1;
  }
  return 0;
}

int AATreeAddElement(AATree* Tree, int value)
{
  if (Tree == NULL)
    return 0;
  return AddNode(value, &(Tree->Root));
}

int AATreeDeleteElement(AATree* Tree, int value)
{
  if (Tree == NULL)
    return 0;
  return DeleteNode(value, &(Tree->Root));
}

int AATreeFindElement(AATree Tree, int value)
{
  return FindNode(value, Tree.Root);
}

void NodeFree(node* T)
{
  if (T == NULL)
    return;
  NodeFree(T->left);
  NodeFree(T->right);
  free(T);
}

void AATreeFree(AATree* T)
{
  if (T == NULL)
    return;
  NodeFree(T->Root);
  T->Root = NULL;
}
