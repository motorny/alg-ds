#include <stdlib.h>
#include <stdio.h>
#include "memallocator.h"

char* gMemory = NULL;
int gSize = 0;

typedef struct NodeHeader NodeHeader;
struct NodeHeader
{
  int size;
  int magic_number; // for checking validness of pointer
  NodeHeader* Next;
};

typedef struct NodeEnder
{
  int size;
} NodeEnder;

NodeHeader* FreeSpaceList;

// Init memory system with memory block pMemory.
int meminit(void* pMemory, int size)
{
  if (size < memgetminimumsize())
    return 0;
  gMemory = (char*)pMemory;
  gSize = size;
  FreeSpaceList = (NodeHeader*)pMemory;
  FreeSpaceList->Next = NULL;
  FreeSpaceList->magic_number = 3030;
  FreeSpaceList->size = gSize - sizeof(NodeHeader) - sizeof(NodeEnder);
  ((NodeEnder*)(gMemory + sizeof(NodeHeader) + FreeSpaceList->size))->size = FreeSpaceList->size;
  return 1;
}

// Allocate memory block of size 'size'.
// Returns pointer to memory block is success, 0 otherwise
void* memalloc(int size)
{
  // good block
  NodeHeader** Cur = NULL;
  NodeHeader* NewBlock;
  int Cur_size;
  int Best_size = -1;
  NodeHeader** Tmp = &FreeSpaceList;

  if (!gMemory || size <= 0)
    return NULL;

  // choose best fit 
  while ((*Tmp) != NULL)
  {
    if ((*Tmp)->size >= size)
      if (Best_size == -1 || (*Tmp)->size < Best_size)
      {
        Best_size = (*Tmp)->size;
        Cur = Tmp;
      }
    Tmp = &(*Tmp)->Next;
  }

  if (Cur == NULL)
    return NULL;

  // save pointers to our block
  Cur_size = (*Cur)->size;
  NewBlock = *Cur;

  // if we didn`t need to split
  if (Cur_size <= sizeof(NodeHeader) + sizeof(NodeEnder) + size)
  {
    ((NodeEnder*)((char*)*Cur + sizeof(NodeHeader) + Cur_size))->size = -1;
    *Cur = (*Cur)->Next;
    NewBlock->Next = NULL;
    return (char*)NewBlock + sizeof(NodeHeader);
  }

  // change Ender
  ((NodeEnder*)((char*)*Cur + sizeof(NodeHeader) + Cur_size))->size = Cur_size - (sizeof(NodeHeader) + size + sizeof(NodeEnder));

  // change Header
  *Cur = (NodeHeader*)((char*)*Cur + sizeof(NodeHeader) + size + sizeof(NodeEnder));
  (*Cur)->size = Cur_size - (sizeof(NodeHeader) + size + sizeof(NodeEnder));
  (*Cur)->magic_number = 3030;
  (*Cur)->Next = NewBlock->Next;

  // add new Block
  NewBlock->size = size;
  NewBlock->magic_number = 3030;
  NewBlock->Next = NULL;
  ((NodeEnder*)((char*)NewBlock + sizeof(NodeHeader) + size))->size = -1; // -1 means we cannot fuse blocks
  return (char*)NewBlock + sizeof(NodeHeader);
}

int memgetminimumsize()
{
  return sizeof(NodeHeader) + sizeof(NodeEnder);
}

int memgetblocksize()
{
  return sizeof(NodeHeader) + sizeof(NodeEnder);
}

// Free memory previously allocated by memalloc
void memfree(void* p)
{
  NodeHeader* Header;
  NodeHeader* NextHeader;
  NodeEnder* NextEnder;
  NodeEnder* PrevEnder;
  NodeEnder* Ender;

  if ((char*)p - gMemory < 0 || (char*)p - gMemory >= gSize)
    return;
  if (p == NULL)
    return;

  Header = (NodeHeader*)((char*)p - sizeof(NodeHeader));
  if (Header->magic_number != 3030)
    return;

  PrevEnder = (NodeEnder*)((char*)p - sizeof(NodeHeader) - sizeof(NodeEnder));
  Ender = (NodeEnder*)((char*)p + Header->size);
  NextHeader = (NodeHeader*)((char*)Ender + sizeof(NodeEnder));
  if ((char*)PrevEnder < gMemory || PrevEnder->size == -1) // means we cannot concat ourself with previous block
  {
    Header->Next = FreeSpaceList; // just add block
    Ender->size = Header->size;
    FreeSpaceList = Header;
  }
  else // if we can concat with previous block
  {
    NodeHeader* PrevHeader = (NodeHeader*)((char*)p - sizeof(NodeHeader) - sizeof(NodeEnder) - PrevEnder->size - sizeof(NodeHeader));
    PrevHeader->size += sizeof(NodeHeader) + sizeof(NodeEnder) + Header->size;
    Ender->size = PrevHeader->size;
    Header = PrevHeader;
  }

  if ((char*)NextHeader - gMemory < gSize && NextHeader->magic_number == 3030)
  {
    NextEnder = (NodeEnder*)((char*)NextHeader + sizeof(NodeHeader) + NextHeader->size);
    if (NextEnder->size != -1) // concat with next one
    {
      NodeHeader **tmp = &FreeSpaceList; 
      Header->size += sizeof(NodeHeader) + sizeof(NodeEnder) + NextHeader->size;
      NextHeader->magic_number = 0;
      NextEnder->size = Header->size;
      while (*tmp != NULL && (*tmp)!= NextHeader)
        tmp = &(*tmp)->Next;
      if (*tmp == NextHeader)
        *tmp = (*tmp)->Next;
    }
  }



  return;
}

// You can implement memory leak checks here
void memdone()
{
  NodeHeader* tmp = (NodeHeader*)gMemory;
  while ((char*)tmp - gMemory < gSize)
  {
    NodeEnder* End = (NodeEnder*)((char*)tmp + sizeof(NodeHeader) + tmp->size);
    if (End->size == -1)
    {
      #ifdef SOBAKA
      fprintf(stderr, "return my memory, sobaka");
      #endif
      break;
    }
    tmp = (NodeHeader*)((char*)End + sizeof(NodeEnder));
  }
  gMemory = NULL;
  gSize = 0;
}