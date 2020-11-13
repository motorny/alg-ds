#include "memallocator.h"
#include <stdlib.h>


#define BLOCK_SIZE ((int)(sizeof(ItemHead) + sizeof(ItemEnd)))
#define ALLOC_KEY 42*42*42

typedef struct ItemHead {
  union {
    struct ItemHead* next_p;
    int key;
  };
  int size;
}ItemHead;

typedef struct ItemEnd {
  union {
    ItemHead* head_p;
    int key;
  };
}ItemEnd;

#define ItemData_p(item_p) ((char*)(item_p) + sizeof(ItemHead))
#define ItemPointerFromDataPointer(data_p) ((ItemHead*)((char*)(data_p) - sizeof(ItemHead)))
#define ItemEndP_p(item_p) ((ItemEnd*)((char*)(item_p) + (item_p->size - sizeof(ItemEnd))))


static void* pool;
static int poolSize;
static ItemHead* headItem_p;


typedef enum {
  TRUE = 1,
  FALSE = 0
}BOOL;



int memgetminimumsize()
{
  return BLOCK_SIZE;
}

int memgetblocksize()
{
  return BLOCK_SIZE;
}

int meminit(void* pMemory, int size)
{
  if (pMemory == NULL || size < BLOCK_SIZE)
  {
    return 0;
  }
  pool = pMemory;
  poolSize = size;
  headItem_p = (ItemHead*)pool;
  headItem_p->next_p = NULL;
  headItem_p->size = size;
  ItemEndP_p(headItem_p)->head_p = headItem_p;
  return 1;
}

void memdone()
{
  pool = NULL;
  headItem_p = NULL;
  poolSize = 0;
}

static ItemHead* SplitItem(ItemHead* item_p, int firstItemSize)
{
  ItemHead* newItem_p = (ItemHead*)((char*)item_p + firstItemSize);
  newItem_p->size = item_p->size - firstItemSize;
  item_p->size = firstItemSize;
  ItemEndP_p(item_p)->head_p = item_p;
  ItemEndP_p(newItem_p)->head_p = newItem_p;
  return newItem_p;
}

void* memalloc(int size)
{
  ItemHead* item_p = headItem_p;
  ItemHead* nextItem_p;
  ItemHead** prevItemNextPointer_p = &(headItem_p);
  int fullBlockSize = size + BLOCK_SIZE;
  BOOL isFullBlock = FALSE;
  if (size <= 0 || pool == NULL)
  {
    return NULL;
  }
  while (item_p != NULL)
  {
    if (item_p->size == fullBlockSize)
    {
      isFullBlock = TRUE;
      break;
    }
    else if (item_p->size - fullBlockSize > 0)
    {
      if (item_p->size - fullBlockSize > BLOCK_SIZE)
      {
        isFullBlock = FALSE;
        break;
      }
      else
      {
        isFullBlock = TRUE;
        break;
      }
    }
    else
    {
      prevItemNextPointer_p = &(item_p->next_p);
      item_p = item_p->next_p;
    }
  }
  if (item_p == NULL)
  {
    return NULL;
  }
  else
  {
    nextItem_p = item_p->next_p;

    if (isFullBlock)
    {
      *prevItemNextPointer_p = nextItem_p;
    }
    else
    {
      ItemHead* newItem_p = SplitItem(item_p, fullBlockSize);
      *prevItemNextPointer_p = newItem_p;
      newItem_p->next_p = nextItem_p;
    }
    item_p->key = ALLOC_KEY;
    ItemEndP_p(item_p)->key = ALLOC_KEY;
    return ItemData_p(item_p);
  }
}

static BOOL OutOfPool(void* item_p, int size)
{
  if (item_p == NULL)
  {
    return TRUE;
  }
  {
    int diff = (char*)item_p - (char*)pool;
    return (diff < 0 || diff > poolSize - size) ? TRUE : FALSE;
  }

}

static BOOL RemoveItemFromList(ItemHead* targetItem_p)
{
  ItemHead** prevItemNextPointer_p = &(headItem_p);
  ItemHead* item_p = headItem_p;
  while (item_p != NULL && item_p != targetItem_p)
  {
    prevItemNextPointer_p = &(item_p->next_p);
    item_p = item_p->next_p;
  }
  if (item_p == NULL)
  {
    return FALSE;
  }
  *prevItemNextPointer_p = targetItem_p->next_p;
  return TRUE;
}

void memfree(void* p)
{
  ItemHead* item_p = ItemPointerFromDataPointer(p);
  ItemHead* leftItem_p;
  ItemHead* rightItem_p;
  ItemEnd* tmpEnd_p;
  ItemHead* tmpHead_p;
  if (pool == NULL)
  {
    return;
  }
  if (OutOfPool(item_p, BLOCK_SIZE) || item_p->key != ALLOC_KEY
    || OutOfPool(tmpEnd_p = ItemEndP_p(item_p), sizeof(ItemEnd)) || tmpEnd_p->key != ALLOC_KEY)
  {
    return;
  }
  tmpEnd_p = (ItemEnd*)item_p - 1;
  if (OutOfPool(tmpEnd_p, sizeof(ItemEnd)) || tmpEnd_p->key == ALLOC_KEY)
  {
    leftItem_p = NULL;
  }
  else
  {
    leftItem_p = tmpEnd_p->head_p;
  }
  tmpHead_p = (ItemHead*)(ItemEndP_p(item_p) + 1);
  if (OutOfPool(tmpHead_p, BLOCK_SIZE) || tmpHead_p->key == ALLOC_KEY)
  {
    rightItem_p = NULL;
  }
  else
  {
    rightItem_p = tmpHead_p;
  }
  if (rightItem_p == NULL)
  {
    if (leftItem_p == NULL)
    {
      item_p->next_p = headItem_p;
      headItem_p = item_p;
      ItemEndP_p(item_p)->head_p = item_p;
    }
    else
    {
      item_p->key = -ALLOC_KEY;
      leftItem_p->size = leftItem_p->size + item_p->size;
      ItemEndP_p(leftItem_p)->head_p = leftItem_p;
    }
  }
  else
  {
    if (leftItem_p == NULL)
    {
      ItemHead** prevItemNextPointer_p = &(headItem_p);
      ItemHead* itm_p = headItem_p;
      while (itm_p != NULL && itm_p != rightItem_p)
      {
        prevItemNextPointer_p = &(itm_p->next_p);
        itm_p = itm_p->next_p;
      }
      *prevItemNextPointer_p = item_p;

      item_p->next_p = rightItem_p->next_p;
      ItemEndP_p(item_p)->key = -ALLOC_KEY;
      item_p->size = item_p->size + rightItem_p->size;
      rightItem_p->key = -ALLOC_KEY;
      ItemEndP_p(item_p)->head_p = item_p;
    }
    else
    {
      RemoveItemFromList(rightItem_p);
      rightItem_p->key = -ALLOC_KEY;
      item_p->key = -ALLOC_KEY;
      ItemEndP_p(item_p)->key = -ALLOC_KEY;
      leftItem_p->size = leftItem_p->size + item_p->size + rightItem_p->size;
      ItemEndP_p(leftItem_p)->head_p = leftItem_p;
    }
  }
}
