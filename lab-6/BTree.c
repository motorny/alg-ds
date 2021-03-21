#include "BTree.h"

BNode * CreateNode(int BTreeDegree)
{
  BNode *tmp = malloc(sizeof(BNode));
  tmp->n = 0;
  tmp->keys = malloc(sizeof(int) * (BTreeDegree - 1));
  tmp->child = malloc(sizeof(BNode *) * (BTreeDegree));
  return tmp;
}
// return key position between elements if exists Overwise return n
int GetPosition(int key, int* key_arr, int n) 
{
  int pos;
  for (pos = 0; pos < n && key > key_arr[pos]; pos++)
    ;
  return pos;
}

// return -1 if we must insert in root, 0 if dublicate and 1 if sucess
int BTreeInsertInternal(BNode* Ptr, int Key, int* SplitKey, BNode** SplitNode, int M) 
{
  BNode* newPtr; // new pointer in case of splitting

  int pos,
    i,
    splitPos, // position of splitting in Node
    newKey;   // new key in case of splitting

  // In case we must split
  BNode* lastPtr;
  int lastKey;


  int value; // result of BTreeInsertInternal on child

  // 1) if we are at NULL - we must insert higher.
  if (Ptr == NULL) 
  {
    *SplitNode = NULL;
    *SplitKey = Key;
    return -1;
  }

  // 2) if we found between our child, it is duplicate. So return falure
  pos = GetPosition(Key, Ptr->keys, Ptr->n);
  if (pos < Ptr->n && Key == Ptr->keys[pos])
    return 0;

  // 3) try to insert in our child. If success - return from recursion
  value = BTreeInsertInternal(Ptr->child[pos], Key, &newKey, &newPtr, M);
  if (value != -1)
    return value;

  // 4) if we must add

  // 4.1) and we have less then maximum
  if (Ptr->n < M - 1) 
  {
    // find newkey if our child ask it
    pos = GetPosition(newKey, Ptr->keys, Ptr->n);
    
    // move keys and pointers 
    for (i = Ptr->n; i > pos; i--) 
    {
      Ptr->keys[i] = Ptr->keys[i - 1];
      Ptr->child[i + 1] = Ptr->child[i];
    }

    /* Insert key */
    Ptr->keys[pos] = newKey;
    Ptr->child[pos + 1] = newPtr;
    Ptr->n++;
    return 1;
  }

  // 4.2) if we have just right amount - add it and split
  if (pos == M - 1)
  {
    lastKey = newKey;
    lastPtr = newPtr;
  }
  else
  {
    lastKey = Ptr->keys[M - 2];
    lastPtr = Ptr->child[M - 1];
    for (i = M - 2; i > pos; i--)
    {
      Ptr->keys[i] = Ptr->keys[i - 1];
      Ptr->child[i + 1] = Ptr->child[i];
    }
    Ptr->keys[pos] = newKey;
    Ptr->child[pos + 1] = newPtr;
  }
  splitPos = (M - 1) / 2;
  (*SplitKey) = Ptr->keys[splitPos];

  (*SplitNode) = CreateNode(M);
  Ptr->n = splitPos;
  (*SplitNode)->n = M - 1 - splitPos;
  for (i = 0; i < (*SplitNode)->n; i++) 
  {
    (*SplitNode)->child[i] = Ptr->child[i + splitPos + 1];
    (*SplitNode)->keys[i] = i < (*SplitNode)->n - 1 ? Ptr->keys[i + splitPos + 1] : lastKey;
  }
  (*SplitNode)->child[(*SplitNode)->n] = lastPtr;
  return -1;
}

void BTreeInsert(BTree* Tree, int Key) {
  BNode* tmp;
  int tmpKey;
  int rez = BTreeInsertInternal(Tree->root, Key, &tmpKey, &tmp, Tree->M);
  if (rez == -1) // we must add element here
  {
    BNode* tmproot = Tree->root;
    Tree->root = CreateNode(Tree->M);
    Tree->root->n = 1;
    Tree->root->keys[0] = tmpKey;
    Tree->root->child[0] = tmproot;
    Tree->root->child[1] = tmp;
  }
}

int BTreeSearch(BTree* Tree, int Key)
{
  int pos, n;
  BNode* ptr = Tree->root;
  while (ptr) 
  {
    n = ptr->n;
    pos = GetPosition(Key, ptr->keys, n);
    if (pos < n && Key == ptr->keys[pos])
      return 1;
    ptr = ptr->child[pos];
  }
  return 0;
}

void BTreeDisplay(BNode* ptr) {
  if (ptr) {
    int i;
    for (i = 0; i < ptr->n; i++)
    {
      printf("%d(", ptr->keys[i]);
      if (ptr->child[i])
        BTreeDisplay(ptr->child[i]);
      printf("),");
    }
  }
}

int BTreeDeleteInternal(BNode* Ptr, int Key, int M, int IsRoot) 
{
  int pos, i, pivot, min; 
  int value;
  BNode *lptr, *rptr; // right and left points for merging

  // if key not found
  if (Ptr == NULL)
    return 0;

  // Minimum number of keys in this node
  min = (M - 1) / 2;
  if (IsRoot)
    min = 1;
  pos = GetPosition(Key, Ptr->keys, Ptr->n);

  // if found key and it is a leaf
  if (Ptr->child[0] == NULL) 
  {
    if (pos == Ptr->n || Key < Ptr->keys[pos])
      return 0;

    // Shift keys and pointers left
    for (i = pos + 1; i < Ptr->n; i++)
    {
      Ptr->keys[i - 1] = Ptr->keys[i];
      Ptr->child[i] = Ptr->child[i + 1];
    }
    // and just decrement our value
    return --Ptr->n >= min ? 1 : -1;
  }

  // if found key but p is not a leaf - swap it this most right child element. It is still should be valid
  if (pos < Ptr->n && Key == Ptr->keys[pos]) {
    BNode* qp = Ptr->child[pos], *qp1;
    int nkey;
    while (TRUE) 
    {
      nkey = qp->n;
      qp1 = qp->child[nkey];
      if (qp1 == NULL)
        break;
      qp = qp1;
    }
    Ptr->keys[pos] = qp->keys[nkey - 1];
    qp->keys[nkey - 1] = Key;
  }
  // and go further
  value = BTreeDeleteInternal(Ptr->child[pos], Key, M, FALSE);
  if (value != -1) // if it is -1, we must try to do something with our childs
    return value;

  // maybe ehough just move some elements? please?
  if (pos > 0 && Ptr->child[pos - 1]->n > min) {
    pivot = pos - 1;
    lptr = Ptr->child[pivot];
    rptr = Ptr->child[pos];
    rptr->child[rptr->n + 1] = rptr->child[rptr->n];
    for (i = rptr->n; i > 0; i--) 
    {
      rptr->keys[i] = rptr->keys[i - 1];
      rptr->child[i] = rptr->child[i - 1];
    }
    rptr->n++;
    rptr->keys[0] = Ptr->keys[pivot];
    rptr->child[0] = lptr->child[lptr->n];
    Ptr->keys[pivot] = lptr->keys[--lptr->n];
    return 1;
  }

  if (pos < Ptr->n && Ptr->child[pos + 1]->n > min) {
    pivot = pos;
    lptr = Ptr->child[pivot];
    rptr = Ptr->child[pivot + 1];
    lptr->keys[lptr->n] = Ptr->keys[pivot];
    lptr->child[lptr->n + 1] = rptr->child[0];
    Ptr->keys[pivot] = rptr->keys[0];
    lptr->n++;
    rptr->n--;
    for (i = 0; i < rptr->n; i++) {
      rptr->keys[i] = rptr->keys[i + 1];
      rptr->child[i] = rptr->child[i + 1];
    }
    rptr->child[rptr->n] = rptr->child[rptr->n + 1];
    return 1;
  }

  // We must concatinate... what am I doing with my life...
  if (pos == Ptr->n)
    pivot = pos - 1;
  else
    pivot = pos;

  // merge right node into left node
  lptr = Ptr->child[pivot];
  rptr = Ptr->child[pivot + 1];
  lptr->keys[lptr->n] = Ptr->keys[pivot];
  lptr->child[lptr->n + 1] = rptr->child[0];
  for (i = 0; i < rptr->n; i++)
  {
    lptr->keys[lptr->n + 1 + i] = rptr->keys[i];
    lptr->child[lptr->n + 2 + i] = rptr->child[i + 1];
  }
  lptr->n += rptr->n + 1;
  free(rptr); // Remove right node

  for (i = pos + 1; i < Ptr->n; i++)
  {
    Ptr->keys[i - 1] = Ptr->keys[i];
    Ptr->child[i] = Ptr->child[i + 1];
  }
  return --Ptr->n >= min ? 1 : -1;
}

int BTreeDelete(BTree* Tree, int Key) {
  BNode* tmp;
  int rez = BTreeDeleteInternal(Tree->root, Key, Tree->M, TRUE);
  if (rez == -1)
  {
    tmp = Tree->root;
    Tree->root = Tree->root->child[0];
    free(tmp);
    rez = 1;
  }
  return rez;
}