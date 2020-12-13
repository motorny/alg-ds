#include "BST_Lib.h"

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)


int TreeItemGetValue(TreeItem* item_p)
{
  return (item_p) ? item_p->value : 0;
}

int TreeItemGetKey(TreeItem* item_p)
{
  return (item_p) ? item_p->key : 0;
}

Tree* TreeGet(void)
{
  Tree* tree_p = (Tree*)malloc(sizeof(Tree));
  if (tree_p == NULL)
  {
    return NULL;
  }
  tree_p->count = 0;
  tree_p->root_p = NULL;
  return tree_p;
}

TreeItem* TreeAdd(Tree* tree_p, int key, int value)
{
  TreeItem** nextSubtree_pp = &(tree_p->root_p);
  TreeItem* item_p;
  while ((item_p = *nextSubtree_pp) != NULL)
  {
    if (key < item_p->key)
    {
      nextSubtree_pp = &(item_p->childL_p);
    }
    else if (key > item_p->key)
    {
      nextSubtree_pp = &(item_p->childR_p);
    }
    else
    {
      return NULL;
    }
  }
  item_p = (TreeItem*)malloc(sizeof(TreeItem));
  if (item_p == NULL)
  {
    return NULL;
  }
  item_p->childL_p = NULL;
  item_p->childR_p = NULL;
  item_p->key = key;
  item_p->value = value;
  *nextSubtree_pp = item_p;
  tree_p->count++;
  return item_p;
}

int TreeFree(Tree* tree_p)
{
  if (tree_p == NULL)
  {
    return BST_ERROR;
  }
  if (tree_p->count != 0)
  {
    int depth = 1;
    TreeItem* item_p;
    TreeItem** callStack = (TreeItem**)malloc(sizeof(TreeItem*) * tree_p->count);
    if (callStack == NULL)
    {
      return BST_ERROR;
    }
    callStack[0] = tree_p->root_p;
    while (depth > 0)
    {
      depth--;
      item_p = callStack[depth];
      if (item_p->childR_p != NULL)
      {
        callStack[depth] = item_p->childR_p;
        depth++;
      }
      if (item_p->childL_p != NULL)
      {
        callStack[depth] = item_p->childL_p;
        depth++;
      }
      free(item_p);
    }
  }
  free(tree_p);
  return BST_OK;
}

TreeItem* TreeFind(Tree* tree_p, int key)
{
  TreeItem* item_p = tree_p->root_p;
  while (item_p != NULL)
  {
    if (key == item_p->key)
    {
      return item_p;
    }
    else if (key < item_p->key)
    {
      item_p = item_p->childL_p;
    }
    else
    {
      item_p = item_p->childR_p;
    }
  }
  return NULL;
}

int TreeRemove(Tree* tree_p, int key)
{
  TreeItem* item_p = tree_p->root_p;
  TreeItem** nextItem_pp = &(tree_p->root_p);
  while (item_p != NULL)
  {
    if (key == item_p->key)
    {
      break;
    }
    else if (key < item_p->key)
    {
      nextItem_pp = &(item_p->childL_p);
    }
    else
    {
      nextItem_pp = &(item_p->childR_p);
    }
    item_p = *nextItem_pp;
  }
  if (item_p == NULL)
  {
    return BST_ERROR;
  }
  if (item_p->childL_p != NULL)
  {
    TreeItem** nextMaxItem_pp = &(item_p->childL_p);
    TreeItem* maxItem_p = item_p->childL_p;

    while (maxItem_p->childR_p != NULL)
    {
      nextMaxItem_pp = &(maxItem_p->childR_p);
      maxItem_p = maxItem_p->childR_p;
    }
    *nextMaxItem_pp = maxItem_p->childL_p;
    item_p->key = maxItem_p->key;
    item_p->value = maxItem_p->value;
    free(maxItem_p);
  }
  else if (item_p->childR_p != NULL)
  {

    TreeItem** nextMinItem_pp = &(item_p->childR_p);
    TreeItem* minItem_p = item_p->childR_p;

    while (minItem_p->childL_p != NULL)
    {
      nextMinItem_pp = &(minItem_p->childL_p);
      minItem_p = minItem_p->childL_p;
    }
    *nextMinItem_pp = minItem_p->childR_p;
    item_p->key = minItem_p->key;
    item_p->value = minItem_p->value;
    free(minItem_p);
  }
  else
  {
    *nextItem_pp = NULL;
    free(item_p);
  }
  tree_p->count--;
  return BST_OK;
}

typedef struct
{
  TreeItem* item_p;
  int depth;
} itemAndDepth;

typedef struct
{
  int size;
  int count;
  int headIndex;
  int tailIndex;
  itemAndDepth *qPool;
} Queue;

static Queue* QueueGet(int size)
{
  Queue* queue;
  if (size <= 0)
  {
    return NULL;
  }
  queue = malloc(sizeof(Queue));
  if (queue == NULL)
  {
    printf("!!!Memory!!");
    return NULL;
  }
  queue->count = 0;
  queue->size = size;
  queue->qPool = malloc(sizeof(itemAndDepth) * queue->size);
  if (queue->qPool == NULL)
  {
    free(queue);
    printf("!!!Memory!!");
    return NULL;
  }
  queue->headIndex = 0;
  queue->tailIndex = 0;
  return queue;
}

static void QueueFree(Queue* queue)
{
  if (queue == NULL)
  {
    return;
  }
  free(queue->qPool);
  free(queue);
}

static void QueuePush(Queue* queue, TreeItem* item_p, int depth)
{
  if (queue == NULL)
  {
    return;
  }
  queue->qPool[queue->headIndex].item_p = item_p;
  queue->qPool[queue->headIndex].depth = depth;
  queue->headIndex = (queue->headIndex + 1) % queue->size;
  queue->count++;
}

static itemAndDepth QueuePull(Queue* queue)
{
  itemAndDepth iNd;
  if (queue == NULL)
  {
    itemAndDepth null = { NULL, 0 };
    return null;
  }
  iNd = queue->qPool[queue->tailIndex];
  queue->tailIndex = (queue->tailIndex + 1) % queue->size;
  queue->count--;
  return iNd;
}

int TreeHightDifToValue(Tree* tree_p)
{
  int myReturn = -1;
  int depth = 0;
  TreeItem* item_p;
  TreeItem** widthCallStak;
  if (tree_p == NULL || tree_p->count <= 0 || tree_p->root_p == NULL)
  {
    return BST_ERROR;
  }
  widthCallStak = malloc(sizeof(TreeItem*) * (tree_p->count + 2));
  if (widthCallStak == NULL)
  {
    return BST_ERROR;
  }
  widthCallStak[0] = tree_p->root_p;
  while (depth >= 0 && depth < tree_p->count + 1)
  {
    item_p = widthCallStak[depth];
    if (item_p == NULL)
    {
      myReturn = 0;
      depth--;
    }
    else if (myReturn == -1)
    {
      item_p->value = -1;
      depth++;
      widthCallStak[depth] = item_p->childL_p;
    }
    else if (item_p->value == -1)
    {
      item_p->value = myReturn;
      myReturn = -1;
      depth++;
      widthCallStak[depth] = item_p->childR_p;
    }
    else
    {
      item_p->value = myReturn - item_p->value;
      myReturn = ((item_p->value > 0) ? (myReturn) : (myReturn - item_p->value)) + 1;
      depth--;
    }
  }
  free(widthCallStak);
  return BST_OK;
}

static void TreeCountPrintX(Tree* tree_p, int itemTextSize, int leftOfset)
{
  int myReturn = -1;
  int depth = 0;
  TreeItem* item_p;
  TreeItem** widthCallStak;
  if (tree_p == NULL || tree_p->count <= 0 || tree_p->root_p == NULL || itemTextSize < 0)
  {
    return;
  }
  widthCallStak = malloc(sizeof(TreeItem*) * (tree_p->count + 2));
  if (widthCallStak == NULL)
  {
    printf("!!!Memory!!");
    return;
  }
  widthCallStak[0] = tree_p->root_p;
  while (depth >= 0)
  {
    item_p = widthCallStak[depth];
    if (item_p == NULL)
    {
      myReturn = leftOfset;
      depth--;
    }
    else if (myReturn == -1)
    {
      depth++;
      widthCallStak[depth] = item_p->childL_p;
    }
    else
    {
      item_p->printX = myReturn;
      myReturn = -1;
      leftOfset = item_p->printX + itemTextSize;
      widthCallStak[depth] = item_p->childR_p;
    }
  }
  free(widthCallStak);
}

int TreePrint(Tree* tree_p, int itemTextSize, TreeItemGetInfo info)
{
  int depth = 0;
  int i = 0;
  itemAndDepth iNd;
  Queue* queue;
  if (tree_p == NULL || itemTextSize < 0)
  {
    return BST_ERROR;
  }
  if (tree_p->count == 0 || tree_p->root_p == NULL)
  {
    printf("NONE\n");
    return BST_ERROR;
  }
  queue = QueueGet(tree_p->count);
  TreeCountPrintX(tree_p, itemTextSize, 0);
  QueuePush(queue, tree_p->root_p, 0);
  while (queue->count > 0)
  {
    iNd = QueuePull(queue);
    if (depth != iNd.depth)
    {
      depth = iNd.depth;
      i = 0;
      printf("\n");
    }
    for (; i < iNd.item_p->printX; i++)
    {
      putchar(' ');
    }
    printf("%*i", itemTextSize, info(iNd.item_p));
    i += itemTextSize;
    if (iNd.item_p->childL_p != NULL)
    {
      QueuePush(queue, iNd.item_p->childL_p, depth + 1);
    }
    if (iNd.item_p->childR_p != NULL)
    {
      QueuePush(queue, iNd.item_p->childR_p, depth + 1);
    }
  }
  printf("\n");
  QueueFree(queue);
  return BST_OK;
}
