#include <malloc.h>
#include <stdio.h>
#include "memallocator.h"

#define NUM 516 

typedef struct list_t {
  struct list_t* next;
  int size;
  int check;
} list_t;

typedef struct {
  int size;
}end_t;

char* head = NULL;
list_t* firstMemPart = NULL;
int globalSize = 0;
int err = 0;

int memgetminimumsize() {

  return sizeof(list_t) + sizeof(int);
}

int memgetblocksize() {

  return sizeof(list_t) + sizeof(int);
}

int meminit(void* memory, int size) {
  if (!memory) {
    err = 1;
    return 1;
  }
  else if (size <= memgetblocksize()) {
    err = 2;
    return 2;
  }
  else {
    head = (char*)memory;
    globalSize = size;
    firstMemPart = (list_t*)memory;
    firstMemPart->size = size - memgetminimumsize();
    firstMemPart->next = NULL;
    ((end_t*)((char*)firstMemPart + firstMemPart->size + sizeof(list_t)))->size = firstMemPart->size;
    return 0;
  }
}

void* memalloc(int size) {

  list_t* memory = NULL;
  list_t** nextMemPart = &firstMemPart;
  list_t** freeMemPart = NULL;
  void* result;
  int i = 0;

  if (size + memgetminimumsize() > globalSize || !head || size < 0)
    return NULL;

  while (*nextMemPart) {
    if ((*nextMemPart)->size >= size) {
      freeMemPart = nextMemPart;
      i++;
      if (i == 2)
        break;
    }
    nextMemPart = &(*nextMemPart)->next;
  }

  if (!freeMemPart)
    return NULL;

  memory = *freeMemPart;
  if (memory->size > size + memgetminimumsize()) {
    (*freeMemPart) = (list_t*)((char*)memory + size + memgetminimumsize());
    (*freeMemPart)->size = memory->size - size - memgetminimumsize();
    (*freeMemPart)->next = memory->next;
    ((end_t*)((char*)memory + memory->size + sizeof(list_t)))->size = (*freeMemPart)->size;
    memory->next = NULL;
    memory->size = size;
    memory->check = NUM;
    ((end_t*)((char*)memory + memory->size + sizeof(list_t)))->size = -1;
  }
  else {
    *freeMemPart = (*freeMemPart)->next;
    ((end_t*)((char*)memory + memory->size + sizeof(list_t)))->size = -1;
    memory->next = NULL;
    memory->check = NUM;
  }
  result = (char*)memory + sizeof(list_t);
  return result;
}

void memdone() {

  if (globalSize <= 0 || !head || firstMemPart && (globalSize == firstMemPart->size + memgetblocksize()))
    return;
  else
    err = 2;
}

void memfree(void* memory) {

  int indicator = 0;
  list_t* freeMemPart = (list_t*)((char*)memory - sizeof(list_t)), * first = NULL;
  list_t** temp = NULL;
  end_t* end = NULL;

  if (!memory || !head || ((char*)memory - sizeof(list_t) < (char*)head) || (char*)memory + sizeof(int) > globalSize + head || freeMemPart->check != NUM || ((end_t*)((char*)freeMemPart + freeMemPart->size + sizeof(list_t)))->size > 0)
    return;

  end = (end_t*)((char*)freeMemPart - sizeof(end_t));

  if ((char*)end > head && end->size != -1) {
    first = (list_t*)((char*)end - end->size - sizeof(list_t));
    if ((char*)first >= (char*)head) {
      indicator = 1;
      first->size = first->size + freeMemPart->size + memgetminimumsize();
      freeMemPart->check = 0;
      ((end_t*)((char*)first + first->size + sizeof(list_t)))->size = first->size;
      freeMemPart = first;
    }
  }

  first = (list_t*)((char*)freeMemPart + freeMemPart->size + memgetminimumsize());

  if ((char*)first - globalSize < (char*)head) {
    end = (end_t*)((char*)first + first->size + sizeof(list_t));
    if (end->size != -1 && (char*)end - globalSize < head) {
      freeMemPart->size = freeMemPart->size + first->size + memgetminimumsize();
      end->size = freeMemPart->size;
      temp = &firstMemPart;
      while (*temp && (*temp != first))
        temp = &(*temp)->next;
      *temp = freeMemPart;
      if (indicator)
        if ((first->next != freeMemPart) && (freeMemPart->next == first))
          freeMemPart->next = first->next;
        else
          *temp = first->next;
      else
        freeMemPart->next = first->next;
      indicator = 1;
    }
  }
  if (indicator == 0) {
    freeMemPart->next = firstMemPart;
    firstMemPart = freeMemPart;
    ((end_t*)((char*)freeMemPart + freeMemPart->size + sizeof(list_t)))->size = freeMemPart->size;
  }
  else
    return;
}