#include "tree.h"
#include "math.h"

static int CountNumberWidth(int key)
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
    (*t)->width = CountNumberWidth(key);
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
  if (T == NULL)
    return 0;
  return DeleteNode(&T->root, key);
}

int TreeAddElement(tree *T, int key)
{
  if (T == NULL)
    return 0;
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

static int CountWidth(node *t)
{
  if (t == NULL)
    return 0;
  if (!t->left && !t->right)
    return t->width = CountNumberWidth(t->key);
  if (!t->left)
    return t->width = CountNumberWidth(t->key) + CountWidth(t->right) + 1; // 2 for spaces
  if (!t->right)
    return t->width = CountNumberWidth(t->key) + CountWidth(t->left) + 1; // 2 for spaces
  return t->width = CountNumberWidth(t->key) + CountWidth(t->left) + CountWidth(t->right) + 2; // 2 for spaces
}

static void PrintNode(node *t, int IsWidth)
{
  int spaces;

  if (!t)
    return;
  if (t->left)
    spaces = t->left->width + 1;
  else
    spaces = 0;

  for (int i = 0; i < spaces; i++)
    printf(" ");

  if (IsWidth)
  {
    printf("%i", t->width);
    spaces = +CountNumberWidth(t->key) - CountNumberWidth(t->width);
  }
  else
  {
    printf("%i", t->key);
    spaces = 0;
  }

  if (t->right)
    spaces += t->right->width;

  for (int i = 0; i < spaces; i++)
    printf(" ");
}

static int PrintLevel(node *t, int level, int curLevel, int IsWidth, node *root)
{
  int offset = 0, leftEnd = 0, rightEnd = 0, len;

  if (!t)
    return 1;

  if (level == curLevel)
  {
    PrintNode(t, IsWidth);
    return 0;
  }

  if (t->left)
  {
    leftEnd = PrintLevel(t->left, level, curLevel + 1, IsWidth, root);
    printf(" ");
  }
  else
  {
    leftEnd = 1;
    //offset = root->width - t->width - CountNumberWidth(t->key) * 2;
    //for (int i = 0; i < offset; i++)
//      printf(" ");
  }

  len = CountNumberWidth(t->key);
  for (int i = 0; i < len; i++)
    printf(" ");

  if (t->right)
  {
    printf(" ");
    rightEnd = PrintLevel(t->right, level, curLevel + 1, IsWidth, root);
  }
  else
  {
    rightEnd = 1;
    //offset = root->width - t->width - CountNumberWidth(t->key) * 2;
    //for (int i = 0; i < offset; i++)
//      printf(" ");
  }

  return leftEnd && rightEnd;
}

void TreePrint(tree t)
{
  int level = 0, isEnd = 0;
  node *cur;

  if (!t.root)
    return;

  cur = t.root;

  CountWidth(t.root);

  while (!isEnd)
  {
    isEnd = PrintLevel(t.root, level, 0, FALSE, t.root);
    printf("\n");
    PrintLevel(t.root, level, 0, TRUE, t.root);
    printf("\n");
    level++;
  }

}

static node *GetK(node *t, int k)
{
  int  r;

  if (t->left)
    r = t->left->number + 1;
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

static void PrintLower(node *t, int k)
{
  int r;
  if (t == NULL)
    return;

  PrintLower(t->left, k);
  if (t->left)
    r = t->left->number + 1;
  else
    r = 1;
  if (r < k)
    printf("%i ", t->key);
  else
    return;
  PrintLower(t->right, k - r);
}

node * TreeKLower(tree T, int k)
{
  node *t = T.root;
  if (t == NULL || k <= 0 || k > t->number)
    return NULL;
  t = GetK(t, k);
  if (t->key % 2 == 0)
    PrintLower(T.root, k);
  printf("\n");
  return t;
}

void NodeFree(node* T)
{
  if (T == NULL)
    return;
  NodeFree(T->left);
  NodeFree(T->right);
  free(T);
}

void TreeFree(tree* T)
{
  if (T == NULL)
    return;
  NodeFree(T->root);
  T->root = NULL;
}