#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DumpLeaks() _CrtDumpMemoryLeaks()

#else

#include <stdlib.h>
#define DumpLeaks()

#endif // _DEBUG

#include <string.h>
#include "BTree.h"

#define _BTREE_MAX_HEIGHT 50

typedef struct _BTNode_t BTNode_t;

typedef struct _keyItem_t
{
  int key;
  int value;
  BTNode_t* L;
}keyItem_t;

struct _BTNode_t
{
  int count;
  keyItem_t* keyItems;
};

struct _BTree_t
{
  int t;
  int count;
  BTNode_t* root;
};

#define IsLeaf(node) (node->keyItems[0].L == NULL)

static BTNode_t* BTNodeGet(int t)
{
  BTNode_t* node;
  if (t < 2)
  {
    return NULL;
  }
  node = (BTNode_t*)malloc(sizeof(BTNode_t));
  if (!node)
  {
    return NULL;
  }
  node->count = 0;
  node->keyItems = (keyItem_t*)malloc(sizeof(keyItem_t) * t * 2);
  if (!node->keyItems)
  {
    free(node);
    return NULL;
  }
  node->keyItems[0].L = NULL;
  return node;
}

static void BTNodeFree(BTNode_t* node)
{
  free(node->keyItems);
  free(node);
}

BTree_t* BTreeGet(int t)
{
  BTree_t* tree;
  if (t < 2)
  {
    return NULL;
  }
  tree = (BTree_t*)malloc(sizeof(BTree_t));
  if (!tree)
  {
    return NULL;
  }
  tree->count = 0;
  tree->t = t;
  tree->root = NULL;
  return tree;
}

void BTreeFree(BTree_t* tree)
{
  if (tree->root != NULL)
  {
    int depth = 0;
    struct
    {
      BTNode_t* node;
      int index;
    } stack[_BTREE_MAX_HEIGHT] = { {tree->root, -1} };
    while (depth >= 0 && depth < _BTREE_MAX_HEIGHT)
    {
      if (IsLeaf(stack[depth].node))
      {
        BTNodeFree(stack[depth].node);
        depth--;
        continue;
      }
      stack[depth].index++;
      if (stack[depth].index > stack[depth].node->count)
      {
        BTNodeFree(stack[depth].node);
        depth--;
      }
      else
      {
        stack[depth + 1].node = stack[depth].node->keyItems[stack[depth].index].L;
        depth++;
        stack[depth].index = -1;
      }
    }
  }
  free(tree);
}

int BTreeFind(BTree_t* tree, int key, int* value)
{
  BTNode_t* node = tree->root;
  int index;
  while (node != NULL)
  {
    keyItem_t* keyItems = node->keyItems;
    int count = node->count;
    for (index = 0; index < count && keyItems[index].key < key; index++);
    if (index == count || keyItems[index].key != key)
    {
      if (IsLeaf(node))
      {
        break;
      }
      else
      {
        node = keyItems[index].L;
      }
    }
    else
    {
      *value = keyItems[index].value;
      return 1;
    }
  }
  return -1;
}


static void BTNodeInsertSplitedKey(BTNode_t* node, keyItem_t keyItem, int index, BTNode_t* L, BTNode_t* R)
{
  memmove(node->keyItems + index + 1, node->keyItems + index, (node->count + 1 - index) * sizeof(keyItem_t));
  node->count++;
  node->keyItems[index] = keyItem;
  node->keyItems[index].L = L;
  node->keyItems[index + 1].L = R;
}

static int BTNodeAdd(BTNode_t* parentNode, int parentIndex, BTNode_t* node, int t, int key, int value)
{
  int r = 0;
  while (r == 0)
  {
    int index;
    if (node->count == 2 * t - 1)
    {
      keyItem_t mid = node->keyItems[t - 1];
      BTNode_t* newNode;
      if (mid.key == key)
      {
        r = -1;
        continue;
      }
      newNode = BTNodeGet(t);
      if (!newNode)
      {
        r = -2;
        continue;
      }
      BTNodeInsertSplitedKey(parentNode, mid, parentIndex, node, newNode);
      memcpy(newNode->keyItems, node->keyItems + t, t * sizeof(keyItem_t));
      newNode->count = t - 1;
      node->count = t - 1;
      if (key > mid.key)
      {
        node = newNode;
      }
    }
    keyItem_t* keyItems = node->keyItems;
    int count = node->count;
    for (index = 0; index < count && keyItems[index].key < key; index++);

    if (index != count && keyItems[index].key == key)
    {
      r = -1;
      continue;
    }
    else
    {
      if (IsLeaf(node))
      {
        memmove(keyItems + index + 1, keyItems + index, (count + 1 - index) * sizeof(keyItem_t));
        node->count++;
        keyItems[index].key = key;
        keyItems[index].value = value;
        keyItems[index].L = NULL;
        r = 1;
        continue;
      }
      else
      {
        parentNode = node; parentIndex = index; node = keyItems[index].L;
        continue;
      }
    }
  }
  return r;
}

int BTreeAdd(BTree_t* tree, int key, int value)
{
  int t;
  int r;
  BTNode_t* node;
  if (!tree->root)
  {
    tree->root = BTNodeGet(tree->t);
    if (!tree->root)
    {
      return -2;
    }
    tree->root->keyItems[0].key = key;
    tree->root->keyItems[0].value = value;
    tree->root->keyItems[0].L = NULL;
    tree->root->keyItems[1].L = NULL;
    tree->root->count++;
    tree->count++;
    return 1;
  }
  t = tree->t;
  node = tree->root;
  if (node->count == 2 * t - 1)
  {
    keyItem_t mid = node->keyItems[t - 1];
    BTNode_t* newNode;
    BTNode_t* newRoot;
    if (mid.key == key)
    {
      return -1;
    }
    newNode = BTNodeGet(t);
    if (!newNode)
    {
      return -2;
    }
    newRoot = BTNodeGet(t);
    if (!newRoot)
    {
      BTNodeFree(newNode);
      return -2;
    }
    newRoot->keyItems[0] = mid;
    newRoot->keyItems[0].L = node;
    newRoot->keyItems[1].L = newNode;
    newRoot->count++;
    memcpy(newNode->keyItems, node->keyItems + t, t * sizeof(keyItem_t));
    newNode->count = t - 1;
    node->count = t - 1;
    tree->root = newRoot;
    if (key > mid.key)
    {
      node = newNode;
    }
  }
  r = BTNodeAdd(NULL, -1, node, t, key, value);
  if (r == 1)
  {
    tree->count++;
  }
  return r;
}

static BTNode_t* BTNodeMerge(BTNode_t* parentNode, int keyIndex, int t)
{
  BTNode_t* L = parentNode->keyItems[keyIndex].L;
  BTNode_t* R = parentNode->keyItems[keyIndex + 1].L;
  L->keyItems[L->count].key = parentNode->keyItems[keyIndex].key;
  L->keyItems[L->count].value = parentNode->keyItems[keyIndex].value;
  L->count++;
  memcpy(L->keyItems + L->count, R->keyItems, (R->count + 1) * sizeof(keyItem_t));
  L->count += R->count;
  BTNodeFree(R);
  memmove(parentNode->keyItems + keyIndex, parentNode->keyItems + keyIndex + 1, (parentNode->count - keyIndex) * sizeof(keyItem_t));
  parentNode->keyItems[keyIndex].L = L;
  parentNode->count--;
  return L;
}

static BTNode_t* BTNodeComplete(BTNode_t* parentNode, int parentIndex, BTNode_t* node, int t)
{
  if (parentIndex != 0 && parentNode->keyItems[parentIndex - 1].L->count > t - 1)
  {
    BTNode_t* L = parentNode->keyItems[parentIndex - 1].L;
    memmove(node->keyItems + 1, node->keyItems, (node->count + 1) * sizeof(keyItem_t));
    node->count++;
    node->keyItems[0].key = parentNode->keyItems[parentIndex - 1].key;
    node->keyItems[0].value = parentNode->keyItems[parentIndex - 1].value;
    node->keyItems[0].L = L->keyItems[L->count].L;
    L->count--;
    parentNode->keyItems[parentIndex - 1].key = L->keyItems[L->count].key;
    parentNode->keyItems[parentIndex - 1].value = L->keyItems[L->count].value;
    return node;
  }
  else if (parentIndex != parentNode->count && parentNode->keyItems[parentIndex + 1].L->count > t - 1)
  {
    BTNode_t* R = parentNode->keyItems[parentIndex + 1].L;
    node->keyItems[node->count].key = parentNode->keyItems[parentIndex].key;
    node->keyItems[node->count].value = parentNode->keyItems[parentIndex].value;
    node->count++;
    node->keyItems[node->count].L = R->keyItems[0].L;
    parentNode->keyItems[parentIndex].key = R->keyItems[0].key;
    parentNode->keyItems[parentIndex].value = R->keyItems[0].value;
    memmove(R->keyItems, R->keyItems + 1, R->count * sizeof(keyItem_t));
    R->count--;
    return node;
  }
  else
  {
    if (parentIndex != parentNode->count)
    {
      return BTNodeMerge(parentNode, parentIndex, t);
    }
    else
    {
      return BTNodeMerge(parentNode, parentIndex - 1, t);
    }
  }
}
static int BTNodeRemove(BTNode_t* node, int t, int key, int* value)
{
  int r = 0;
  while (r == 0)
  {
    int index;
    keyItem_t* keyItems = node->keyItems;
    int count = node->count;
    for (index = 0; index < count && keyItems[index].key < key; index++);
    if (index != count && keyItems[index].key == key)
    {
      if (value) *value = keyItems[index].value;
      if (IsLeaf(node))
      {
        memmove(keyItems + index, keyItems + index + 1, (count - index) * sizeof(keyItem_t));
        node->count--;
        r = 1;
        continue;
      }
      else
      {
        BTNode_t* L = keyItems[index].L;
        BTNode_t* R = keyItems[index + 1].L;
        if (L->count > t - 1)
        {
          BTNode_t* maxNode = L;
          int maxKey;
          while (!IsLeaf(maxNode))
          {
            maxNode = maxNode->keyItems[maxNode->count].L;
          }
          maxKey = maxNode->keyItems[maxNode->count - 1].key;
          keyItems[index].key = maxKey;
          keyItems[index].value = maxNode->keyItems[maxNode->count - 1].value;
          node = L; t; key = maxKey; value = NULL;
          continue;
        }
        else if (R->count > t - 1)
        {
          BTNode_t* minNode = R;
          int minKey;
          while (!IsLeaf(minNode))
          {
            minNode = minNode->keyItems[0].L;
          }
          minKey = minNode->keyItems[0].key;
          keyItems[index].key = minKey;
          keyItems[index].value = minNode->keyItems[0].value;
          node = R; key = minKey; value = NULL;
          continue;
        }
        else
        {
          L = BTNodeMerge(node, index, t);
          node = L;
          continue;
        }
      }
    }
    else
    {
      if (IsLeaf(node))
      {
        r = -1;
        continue;
      }
      else
      {
        BTNode_t* nextNode = keyItems[index].L;
        if (nextNode->count == t - 1)
        {
          nextNode = BTNodeComplete(node, index, nextNode, t);
        }
        node = nextNode;
        continue;
      }
    }
  }
  return r;
}

int BTreeRemove(BTree_t* tree, int key, int* value)
{
  if (tree->root == NULL)
  {
    return -1;
  }
  else
  {
    int r = BTNodeRemove(tree->root, tree->t, key, value);
    if (r == 1)
    {
      tree->count--;
    }
    if (tree->root->count == 0)
    {
      BTNode_t* newRoot = tree->root->keyItems[0].L;
      BTNodeFree(tree->root);
      tree->root = newRoot;
    }
    return r;
  }
}