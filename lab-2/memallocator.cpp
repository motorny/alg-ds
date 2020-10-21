
#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#define NOT_ENOUGH_MEMORY     1
#define NULL_POINTER_ON_INPUT 2
#define TOO_SMALL_SIZE        3
#define KEY_NUMBER            79854

typedef struct header {
  int size;
  int key;
  struct header* ptrToNext;
}NodeHeader;

typedef struct ender {
  int size;
}NodeEnder;

char* memory = NULL;
int memSize = 0;
NodeHeader* firstFreeNode = NULL;

int memgetminimumsize()
{
  return sizeof(NodeHeader) + sizeof(int);
}

int memgetblocksize()
{
  return sizeof(NodeHeader) + sizeof(int);
}

//Доделать проверку
bool MemoryLeaksCheckTrueIfNoLeaks()
{
  return (char*)firstFreeNode == memory && (char*)firstFreeNode + firstFreeNode->size + memgetminimumsize() == memory + memSize;
}

int meminit(void* pMemory, int size)
{
  if (!pMemory)
    return NULL_POINTER_ON_INPUT;
  if (size <= memgetblocksize())
    return TOO_SMALL_SIZE;

  memory = (char*)pMemory;
  memSize = size;

  firstFreeNode = (NodeHeader*)memory;
  firstFreeNode->size = memSize - memgetminimumsize();
  firstFreeNode->ptrToNext = NULL;
  firstFreeNode->key = KEY_NUMBER;
  ((NodeEnder*)((char*)firstFreeNode + sizeof(NodeHeader) + firstFreeNode->size))->size = firstFreeNode->size;

  return 0;
}

void* memalloc(int size)
{
  if (memory == NULL || size <= 0 || size + memgetminimumsize() > memSize)
    return NULL;

  NodeHeader** tmp = &firstFreeNode, **currentNodeHeader = NULL;
  int minSize = -1;

  //ищем минимальный подходящий блок

  while (*tmp != NULL)
    {
      if ((*tmp)->size >= size && (minSize == -1 || minSize > (*tmp)->size))
        {
          currentNodeHeader = tmp;
          minSize = (*tmp)->size;
        }
      tmp = &(*tmp)->ptrToNext;
    }

  if (currentNodeHeader == NULL)
    return NULL;

  NodeHeader* newNode = (*currentNodeHeader);
  newNode->key = KEY_NUMBER;

  //не делим

  if (minSize <= size + memgetminimumsize())
    {
      (*currentNodeHeader) = (*currentNodeHeader)->ptrToNext;
      ((NodeEnder*)((char*)newNode + newNode->size + sizeof(NodeHeader)))->size = -1;
      newNode->ptrToNext = NULL;
      return (char*)newNode + sizeof(NodeHeader);
    }

  //делим
  //заполняем отрезаемую (правую) часть блока

  (*currentNodeHeader) = (NodeHeader*)((char*)newNode + memgetminimumsize() + size);
  (*currentNodeHeader)->size = newNode->size - memgetminimumsize() - size;
  (*currentNodeHeader)->key = KEY_NUMBER;
  (*currentNodeHeader)->ptrToNext = newNode->ptrToNext;
  ((NodeEnder*)((char*)newNode + newNode->size + sizeof(NodeHeader)))->size = (*currentNodeHeader)->size;

  //заполняем левую часть

  newNode->size = size;
  newNode->ptrToNext = NULL;
  ((NodeEnder*)((char*)newNode + newNode->size + sizeof(NodeHeader)))->size = -1;

  return (char*)newNode + sizeof(NodeHeader);
}

void memfree(void* p)
{
  NodeHeader* currentNodeHeader = (NodeHeader*)((char*)p - sizeof(NodeHeader));
  NodeHeader* sideHeader = NULL;
  NodeEnder* sideEnder = NULL;
  int united = 0;

  if (p == NULL || currentNodeHeader->key != KEY_NUMBER || memory == NULL || ((char*)p + sizeof(NodeEnder) > (char*)memory + memSize) || (char*)p - sizeof(NodeHeader) < memory)
    return;

  if (((NodeEnder*)((char*)currentNodeHeader + currentNodeHeader->size + sizeof(NodeHeader)))->size > 0)
    return;

  //проверяем возможность объединиться с блоком слева

  sideEnder = (NodeEnder*)((char*)currentNodeHeader - sizeof(NodeEnder));

  if (sideEnder->size != -1 && (char*)sideEnder > memory)
    {
      sideHeader = (NodeHeader*)((char*)sideEnder - sideEnder->size - sizeof(NodeHeader));

      if (sideHeader->key == KEY_NUMBER && (char*)sideHeader >= memory)
        {
          sideHeader->size += currentNodeHeader->size + memgetminimumsize();
          currentNodeHeader->key = 0;
          ((NodeEnder*)((char*)sideHeader + sideHeader->size + sizeof(NodeHeader)))->size = sideHeader->size;
          currentNodeHeader = sideHeader;
          united = 1;
        }
    }

  //проверяем возможность объединиться с блоком справа

  sideHeader = (NodeHeader*)((char*)currentNodeHeader + currentNodeHeader->size + memgetminimumsize());

  if ((char*)sideHeader - memSize < memory && sideHeader->key == KEY_NUMBER)
    {
      sideEnder = (NodeEnder*)((char*)sideHeader + sideHeader->size + sizeof(NodeHeader));

      if ((char*)sideEnder - memSize < memory && sideEnder->size != -1)
        {
          currentNodeHeader->size += sideHeader->size + memgetminimumsize();
          sideEnder->size = currentNodeHeader->size;
          sideHeader->key = 0;

          NodeHeader** tmp = &firstFreeNode;

          while ((*tmp) != NULL && (*tmp) != sideHeader)
            tmp = &(*tmp)->ptrToNext;

          if (*tmp == NULL)// по идее невозможно, если только пользователь не вылезет за рамки запрошенной памяти
            {
              //printf("uncorrect");
              return;
            }

          *tmp = currentNodeHeader;

          //если
          if (united)
            {
              if (sideHeader->ptrToNext == currentNodeHeader)
                *tmp = currentNodeHeader;
              else if (currentNodeHeader->ptrToNext == sideHeader)
                currentNodeHeader->ptrToNext = sideHeader->ptrToNext;
              else
                *tmp = sideHeader->ptrToNext;
            }
          else
            currentNodeHeader->ptrToNext = sideHeader->ptrToNext;

          united = 1;
        }
    }

  if (united)
    return;

  currentNodeHeader->ptrToNext = firstFreeNode;
  firstFreeNode = currentNodeHeader;
  ((NodeEnder*)((char*)currentNodeHeader + currentNodeHeader->size + sizeof(NodeHeader)))->size = currentNodeHeader->size;
}

void memdone()
{
  memory = NULL;
  memSize = 0;
}

#ifdef __cplusplus
}
#endif

#endif
