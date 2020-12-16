#include "IT_Lib.h"

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)


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

TreeItem* TreeAdd(Tree* tree_p, int leftX, int rightX, int id)
{
  char turn = 'L';
  TreeItem* prevItem_p = NULL;
  TreeItem* item_p = tree_p->root_p;

  while (item_p != NULL)
  {
    if (leftX < item_p->leftX)
    {
      prevItem_p = item_p;
      item_p = item_p->childL_p;
      turn = 'L';
    }
    else if (leftX > item_p->leftX)
    {
      prevItem_p = item_p;
      item_p = item_p->childR_p;
      turn = 'R';
    }
    else if (item_p->rightX == rightX)
    {
      return NULL;
    }
    else
    {
      prevItem_p = item_p;
      item_p = item_p->childL_p;
      turn = 'L';
    }
  }
  item_p = (TreeItem*)malloc(sizeof(TreeItem));
  if (item_p == NULL)
  {
    return NULL;
  }
  item_p->parent_p = prevItem_p;
  item_p->childL_p = NULL;
  item_p->childR_p = NULL;
  item_p->leftX = leftX;
  item_p->rightX = rightX;
  item_p->rightMax = rightX;
  item_p->id = id;
  if (prevItem_p != NULL)
  {
    if (turn == 'L')
    {
      prevItem_p->childL_p = item_p;
    }
    else
    {
      prevItem_p->childR_p = item_p;
    }
    while (prevItem_p != NULL)
    {
      prevItem_p->rightMax = max(prevItem_p->rightMax, rightX);
      prevItem_p = prevItem_p->parent_p;
    }
  }
  else
  {
    tree_p->root_p = item_p;
    item_p->parent_p = NULL;
  }
  tree_p->count++;
  return item_p;
}

int TreeFind(Tree* tree_p, int leftX, int rightX)
{
  TreeItem* item_p = tree_p->root_p;
  while (item_p != NULL)
  {
    if (leftX < item_p->leftX)
    {
      item_p = item_p->childL_p;
    }
    else if (leftX > item_p->leftX)
    {
      item_p = item_p->childR_p;
    }
    else if (rightX == item_p->rightX)
    {
      return item_p->id;
    }
    else
    {
      item_p = item_p->childL_p;
    }
  }
  return BST_ERROR;
}

int TreeRemove(Tree* tree_p, int leftX, int rightX)
{
  TreeItem* item_p = tree_p->root_p;
  TreeItem* maxItem_p, * parent_p;
  while (item_p != NULL)
  {
    if (leftX < item_p->leftX)
    {
      item_p = item_p->childL_p;
    }
    else if (leftX > item_p->leftX)
    {
      item_p = item_p->childR_p;
    }
    else if (rightX == item_p->rightX)
    {
      break;
    }
    else
    {
      item_p = item_p->childL_p;
    }
  }
  if (item_p == NULL)
  {
    return BST_ERROR;
  }
  
  if (item_p->childL_p != NULL)
  {
    maxItem_p = item_p->childL_p;

    while (maxItem_p->childR_p != NULL)
    {
      maxItem_p = maxItem_p->childR_p;
    }
    parent_p = maxItem_p->parent_p;
    if (maxItem_p == parent_p->childL_p)
    {
      parent_p->childL_p = maxItem_p->childL_p;
    }
    else
    {
      parent_p->childR_p = maxItem_p->childL_p;
    }
    if (maxItem_p->childL_p != NULL)
    {
      maxItem_p->childL_p->parent_p = parent_p;
    }
    item_p->leftX = maxItem_p->leftX;
    item_p->rightX = maxItem_p->rightX;
    item_p->id = maxItem_p->id;
    free(maxItem_p);
  }
  else if (item_p->childR_p != NULL)
  {
    maxItem_p = item_p->childR_p;

    while (maxItem_p->childL_p != NULL)
    {
      maxItem_p = maxItem_p->childL_p;
    }
    parent_p = maxItem_p->parent_p;
    if (maxItem_p == parent_p->childL_p)
    {
      parent_p->childL_p = maxItem_p->childR_p;
    }
    else
    {
      parent_p->childR_p = maxItem_p->childR_p;
    }
    if (maxItem_p->childR_p != NULL)
    {
      maxItem_p->childR_p->parent_p = parent_p;
    }
    item_p->leftX = maxItem_p->leftX;
    item_p->rightX = maxItem_p->rightX;
    item_p->id = maxItem_p->id;
    free(maxItem_p);
  }
  else
  {
    parent_p = item_p->parent_p;
    if (parent_p != NULL)
    {
      if (item_p == parent_p->childL_p)
      {
        parent_p->childL_p = NULL;
      }
      else
      {
        parent_p->childR_p = NULL;
      }
    }
    else
    {
      tree_p->root_p = NULL;
    }
    free(item_p);
  }
  while (parent_p != NULL)
  {
    parent_p->rightMax = parent_p->rightX;
    if (parent_p->childL_p != NULL)
    {
      parent_p->rightMax = max(parent_p->rightMax, parent_p->childL_p->rightMax);
    }
    if (parent_p->childR_p != NULL)
    {
      parent_p->rightMax = max(parent_p->rightMax, parent_p->childR_p->rightMax);
    }
    parent_p = parent_p->parent_p;
  }
  tree_p->count--;
  return BST_OK;
}

int TreeFree(Tree* tree_p)
{
  if (tree_p == NULL)
  {
    return BST_ERROR;
  }
  else
  {
    TreeItem* item_p = tree_p->root_p, * tmp;

    while (1)
    {
      if (item_p == NULL)
      {
        break;
      }
      if (item_p->childL_p != NULL)
      {
        item_p = item_p->childL_p;
        continue;
      }
      if (item_p->childR_p != NULL)
      {
        item_p = item_p->childR_p;
        continue;
      }
      if (item_p->parent_p != NULL)
      {
        if (item_p == item_p->parent_p->childL_p)
        {
          item_p->parent_p->childL_p = NULL;
        }
        else
        {
          item_p->parent_p->childR_p = NULL;
        }
      }
      tmp = item_p;
      item_p = item_p->parent_p;
      free(tmp);
    }
    free(tree_p);
    return BST_OK;
  }
}

int TreeIntersect(Tree * tree_p, int leftX, int rightX, int* outputArray, int maxCount)
{
  TreeItem* item_p = tree_p->root_p, * prevItem_p = NULL;
  char state;
  int i = 0;
  while (item_p != NULL)
  {
    //спуск
    if (prevItem_p == NULL || prevItem_p == item_p->parent_p)
    {
      if (rightX >= item_p->leftX && leftX <= item_p->rightX)
      {
        outputArray[i] = item_p->id;
        i++;
      }
      state = 'L';
    }
    //Возврат слева
    else if (item_p->childL_p == prevItem_p)
    {
      state = 'R';
    }
    //Возврат справа
    else if (item_p->childR_p == prevItem_p)
    {
      state = 'U';
    }
    if (state == 'L')
    {
      if (item_p->childL_p == NULL || item_p->childL_p->rightMax < leftX)
      {
        state = 'R';
      }
      else
      {
        prevItem_p = item_p;
        item_p = item_p->childL_p;
        continue;
      }
    }
    if (state == 'R')
    {
      if (item_p->childR_p == NULL || item_p->leftX >= rightX)
      {
        state = 'U';
      }
      else
      {
        prevItem_p = item_p;
        item_p = item_p->childR_p;
        continue;
      }
    }
    if (state == 'U')
    {
      prevItem_p = item_p;
      item_p = item_p->parent_p;
      continue;
    }
  }
  return i;
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

int TreePrintIntervals(Tree* tree_p, int itemTextSize)
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
  TreeCountPrintX(tree_p, itemTextSize*4 + 5, 0);
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
    printf("[%*i;%*i:%*i;%*i]", itemTextSize, iNd.item_p->leftX, itemTextSize, iNd.item_p->id, itemTextSize, iNd.item_p->rightMax, itemTextSize, iNd.item_p->rightX);
    i += itemTextSize * 4 + 5;
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
