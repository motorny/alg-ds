#include "tree.h"
#include "math.h"

static int CountWidth(int key)
{
  int ans = 0;
  if (key < 0)
    ans++;
  key = abs(key);
  while (key != 0)
  {
    key /= 10;
    ans++;
  }
  return ans;
}

static int AddNode(node **t, int key)
{
  if (*t == NULL)
  {
    *t = (node*)malloc(sizeof(node));
    (*t)->key = key;
    (*t)->number = 1;
    (*t)->parent = NULL;
    (*t)->width = CountWidth(key);
    (*t)->left = (*t)->right = NULL;
    return TRUE;
  }
  if (key > (*t)->key)
  {
    int res = AddNode(&((*t)->right), key);
    if (res)
    {
      (*t)->right->parent = (*t);
      (*t)->number++;
    }
    return res;
  }
  if (key < (*t)->key)
  {
    int res = AddNode(&((*t)->left), key);
    if (res)
    {
      (*t)->left->parent = (*t);
      (*t)->number++;
    }
    return res;
  }
  return FALSE;
}

static void DeleteCurrent(node **t)
{
  node *p = *t;
  if ((*t)->left == NULL && (*t)->right == NULL)
    *t = NULL;
  else if ((*t)->left == NULL)
    *t = (*t)->right;
  else if ((*t)->right == NULL)
    *t = (*t)->left;
  else
  {
    node **tmp = &(*t)->left;
    while ((*tmp)->right != NULL)
      tmp = &(*tmp)->right;
    (*t)->key = (*tmp)->key;
    p = *tmp;
    (*tmp) = (*tmp)->left;
  }
  free(p);
}

static int DeleteNode(node **t, int x)
{
  if ((*t) == NULL)
    return FALSE;

  if (x > (*t)->key)
  {   
    int res = DeleteNode(&(*t)->right, x);
    if (res)
      (*t)->number--;
    return res;
  }
  if (x < (*t)->key)
  {
    int res = DeleteNode(&(*t)->left, x);
    if (res)
      (*t)->number--;
    return res;
  }
  
  DeleteCurrent(t);
  return TRUE;
}


int TreeDeleteElement(tree *T, int key)
{
  return DeleteNode(&T->root, key);
}

int TreeAddElement(tree *T, int key)
{
  return AddNode(&T->root, key);
}

node * TreeFindElement(tree T, int key)
{
  node *t = T.root;
  while (TRUE)
  {
    if (t == NULL)
      return NULL;
    if (key > t->key)
    {
      t = t->right;
      continue;
    }
    if (key < t->key)
    {
      t = t->left;
      continue;
    }
    return t;
  }
}
/*
static int CountH(node *t)
{
  if (t == NULL)
    return 0;
  if (t->left == 0 && t->right == 0)
    return 1;
  int a = CountH(t->left);
  int b = CountH(t->right);
  return max(a, b);
}

int *A = NULL;
int H = 0;
int x = 0;

static void PrepareA(node *t, int y)
{
  if (t == NULL)
    return;
  PrepareA(t->left, y + 2);
  A[x * H + y] = t->key;
  A[x * H + y + 1] = t->width;
  x++;
  PrepareA(t->right, y + 2);
}

void TreePrint(tree *T)
{
  H = CountH(T->root);
  A = malloc(T->root->number * H * 2);
  memset(A, 0, T->root->number * H * 2 * sizeof(int));
  PrepareA(T->root, 0, T->root->number * H * 2 * sizeof(int));
  for (int i = 0; i < H; i += 2)
  {
    // print elements
    for (int j = 0; j <= x; j++)
    {
      if (A[j * H + i] == 0)
        printf(" ");
      else
      {
        printf("%i", A[j * H + i]);
      }
    }
  }
}
*/

node *GetK(node *t, int k)
{
  int  r;

  if (t->left)
  {
    r = t->left->number + 1;
  }
  else
    r = 1;
  if (r != k)
  {
    if (k < r)
      t = GetK(t->left, k);
    else
      t = GetK(t->right, k - r);
  }
  return t;

}

node * TreeKLower(node *N, int k)
{
  node *f;
  int r = 1 - k;
  if (N->left != NULL)
    r += N->left->number;

  while (N->parent != NULL)
  {
    f = N->parent;
    if (N == f->right)
    {
      r += 1;
      if (f->left != NULL)
        r += f->left->number;
      if (r >= 0)
        return GetK(f, r);
    }
    N = N->parent;
  }
  return NULL;
}
