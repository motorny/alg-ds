#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#else

#include <stdlib.h>

#endif // _DEBUG
#include "randSearchTreap.h"

struct _Treap_t
{
  int key;
  int priority;
  int val;
  struct _Treap_t* L;
  struct _Treap_t* R;
};

static Treap_t* _TreapGet(int key, int priority, int val, Treap_t* L, Treap_t* R)
{
  Treap_t* t = (Treap_t*)malloc(sizeof(Treap_t));
  if (!t)
  {
    return NULL;
  }
  t->priority = priority;
  t->key = key;
  t->val = val;
  t->L = L;
  t->R = R;
  return t;
}

Treap_t* TreapGet()
{
  return NULL;
}

void TreapFree(Treap_t* treap)
{
  int deapth = 0;
  Treap_t* t;
  Treap_t* stack[100] = { treap };
  while (deapth >= 0 && deapth < 100)
  {
    t = stack[deapth];
    if (t)
    {
      stack[deapth] = t->L;
      deapth++;
      stack[deapth] = t->R;
      free(t);
    }
    else
    {
      deapth--;
    }
  }
}

int TreapFind(Treap_t** treap_p, int key, int* val_p)
{
  Treap_t* T = *treap_p;
  while (T != NULL)
  {
    if (T->key < key)
    {
      T = T->R;
    }
    else if (T->key > key)
    {
      T = T->L;
    }
    else
    {
      *val_p = T->val;
      return 1;
    }
  }
  return -1;
}

static void _TreapSplit(int x, Treap_t* treap, Treap_t** L_p, Treap_t** R_p)
{

  int depth = 1;
  int isReturn = 0;;
  struct IterData {
    Treap_t* L;
    Treap_t* R;
    Treap_t* T;
  } iterDataStack[100] = {
    { NULL, NULL, NULL },
    { NULL, NULL, treap }
  };
  struct IterData iterData;

  if (treap == NULL)
  {
    *L_p = NULL;
    *R_p = NULL;
    return;
  }

  while (depth > 0 && depth < 100)
  {
    iterData = iterDataStack[depth];

    if (!isReturn)
    {
      Treap_t* newTreap = NULL;
      if (iterData.T->key <= x)
      {
        if (iterData.T->R == NULL)
        {
          isReturn = 1;
          depth--;
          iterDataStack[depth].R = NULL;
          iterDataStack[depth].L = iterData.T;
        }
        else
        {
          depth++;
          iterDataStack[depth].T = iterData.T->R;
        }
      }
      else
      {
        if (iterData.T->L == NULL)
        {
          isReturn = 1;
          depth--;
          iterDataStack[depth].R = iterData.T;
          iterDataStack[depth].L = NULL;
        }
        else
        {
          depth++;
          iterDataStack[depth].T = iterData.T->L;
        }
      }
    }
    else
    {
      depth--;
      if (iterData.T->key <= x)
      {
        iterDataStack[depth].R = iterData.R;
        iterData.T->R = iterData.L;
        iterDataStack[depth].L = iterData.T;
      }
      else
      {
        iterDataStack[depth].L = iterData.L;
        iterData.T->L = iterData.R;
        iterDataStack[depth].R = iterData.T;
      }
    }
  }
  *L_p = iterDataStack[0].L;
  *R_p = iterDataStack[0].R;
}

static Treap_t* _TreapMerge(Treap_t* L, Treap_t* R)
{
  int depth = 1;
  int isReturn = 0;;
  struct IterData {
    Treap_t* L;
    Treap_t* R;
    Treap_t* newReturn;
  } iterDataStack[100] = {
    { NULL, NULL, NULL },
    { L, R, NULL }
  };
  struct IterData iterData;

  while (depth > 0 && depth < 100)
  {
    iterData = iterDataStack[depth];
    
    if (!isReturn)
    {
      if (iterData.L == NULL)
      {
        isReturn = 1;
        depth--;
        iterDataStack[depth].newReturn = iterData.R;
        continue;
      }
      if (iterData.R == NULL)
      {
        isReturn = 1;
        depth--;
        iterDataStack[depth].newReturn = iterData.L;
        continue;
      }
      depth++;
      if (iterData.L->priority > iterData.R->priority)
      {
        iterDataStack[depth].L = iterData.L->R;
        iterDataStack[depth].R = iterData.R;
      }
      else
      {
        iterDataStack[depth].L = iterData.L;
        iterDataStack[depth].R = iterData.R->L;
      }
    }
    else
    {
      depth--;
      if (iterData.L->priority > iterData.R->priority)
      {
        iterData.L->R = iterData.newReturn;
        iterDataStack[depth].newReturn = iterData.L;
      }
      else
      {
        iterData.R->L = iterData.newReturn;
        iterDataStack[depth].newReturn = iterData.R;
      }
    }
  }
  return iterDataStack[0].newReturn;
}

int TreapAdd(Treap_t** treap_p, int key, int priority, int val)
{
  Treap_t* L;
  Treap_t* R;
  Treap_t* M;
  int tmp;

  M = _TreapGet(key, priority, val, NULL, NULL);
  if (M == NULL || TreapFind(treap_p, key, &tmp) == 1)
  {
    return -1;
  }
  else
  {
    _TreapSplit(key, *treap_p, &L, &R);
    *treap_p = _TreapMerge(_TreapMerge(L, M), R);
    return 1;
  }
}

int TreapRSAdd(Treap_t** treap_p, int key, int val)
{
  return TreapAdd(treap_p, key, rand(), val);
}

int TreapRemove(Treap_t** treap_p, int key, int* val_p)
{
  Treap_t* L;
  Treap_t* R;
  Treap_t* M;
  int ret;
  _TreapSplit(key - 1, *treap_p, &L, &R);
  _TreapSplit(key, R, &M, &R);
  if (!M)
  {
    ret = -1;
  }
  else
  {
    *val_p = M->val;
    ret = 1;
  }
  TreapFree(M);
  *treap_p = _TreapMerge(L, R);
  return ret;
}
