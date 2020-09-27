#include <stdlib.h>
#include <string.h>

#include "XORlist.h"

#pragma warning(disable: 4996)

static int initNewElementInList(list_t **newEl, char *newElement) {
  if (!((*newEl) = (list_t*)malloc(sizeof(list_t))))
    return FALSE;
  strncpy((*newEl)->str, newElement, MAX_STR);
  return TRUE;
}

int AddElementToList(xorList_t* list, char *newElement) {
  list_t *prev, *present, *next, 
    *newEl;

  if (strlen(newElement) >= MAX_STR)
    return FALSE;

  if (list->first == NULL) {
    initNewElementInList(&newEl, newElement);
    newEl->xorAddress = 0;

    list->first = newEl;
    return TRUE;
  }
  else if (list->second == NULL) {
    initNewElementInList(&newEl, newElement);
    newEl->xorAddress = 0;

    list->second = newEl;
    return TRUE;
  }
  else if (list->first != NULL && list->second != NULL && (list->first->xorAddress == 0 && list->second->xorAddress == 0)) {
    initNewElementInList(&newEl, newElement);
    list->first->xorAddress = ((int)newEl ^ (int)list->second);
    list->second->xorAddress = ((int)list->first ^ (int)newEl);
    newEl->xorAddress = ((int)list->second ^ (int)list->first);
    return TRUE;
  }
  else {
    initNewElementInList(&newEl, newElement);
    prev = list->first;
    present = next = list->second;
    while ((list_t*)((int)prev ^ (int)(present->xorAddress)) != list->first) {
      next = (list_t*)((int)prev ^ (int)(present->xorAddress));
      prev = present;
      present = next;
    }
    next->xorAddress = ((int)prev ^ (int)newEl);
    newEl->xorAddress = ((int)next ^ (int)list->first);
    list->first->xorAddress = ((int)newEl ^ (int)list->second);

    return TRUE;
  }
}

int FindElementInListByKey(xorList_t* list, char* key) {
  list_t* prev, * present, * next;

  if (strlen(key) >= MAX_STR)
    return FALSE;

  if (list->first == NULL)
    return FALSE;
  else if (list->second == NULL) {
    if (!strcmp(list->first->str, key))
      return TRUE;
    else
      return FALSE;
  }
  else {
    if (!strcmp(list->first->str, key))
      return TRUE;
    else if (!strcmp(list->second->str, key))
      return TRUE;
  
    prev = list->first;
    present = next = list->second;
    while ((list_t*)((int)prev ^ (int)(present->xorAddress)) != list->first) {
      next = (list_t*)((int)prev ^ (int)(present->xorAddress));
      prev = present;
      present = next;
      if (!strcmp(next->str, key))
        return TRUE;
    }
    return FALSE;
  }
}

static int DeleteElementFrom1ElemListByKey(xorList_t* list, char* key) {
  if (!strcmp(list->first->str, key)) {
    free(list->first);
    list->first = NULL;
    return TRUE;
  }
  else
    return FALSE;
}

static int DeleteElementFrom2ElemListByKey(xorList_t* list, char* key) {
  if (!strcmp(list->first->str, key)) {
    free(list->first);
    list->first = list->second;
    list->second = NULL;
    return TRUE;
  }
  else if (!strcmp(list->second->str, key)) {
    free(list->second);
    list->second = NULL;
    return TRUE;
  }
  else
    return FALSE;
}

static int DeleteElementFrom3ElemListByKey(xorList_t* list, char* key) {
  list_t* next = (list_t *)((int)list->first ^ list->second->xorAddress);

  if (!strcmp(list->first->str, key)) {
    list->second->xorAddress = next->xorAddress = 0;
    free(list->first);
    list->first = list->second;
    list->second = next;
    return TRUE;
  }
  else if (!strcmp(list->second->str, key)) {
    list->first->xorAddress = next->xorAddress = 0;
    free(list->second);
    list->second = next;
    return TRUE;
  }
  if (!strcmp(next->str, key)) {
    list->first->xorAddress = list->second->xorAddress = 0;
    free(next);
    return TRUE;
  }
  else
    return FALSE;
}

int DeleteElementFromListByKey(xorList_t* list, char* key) {
  list_t* prev, * present, * next, *afterNext;

  if (strlen(key) >= MAX_STR)
    return FALSE;

  // если 0 элементов
  if (list->first == NULL)
    return FALSE;
  // если 1 элемент
  else if (list->second == NULL)
    return DeleteElementFrom1ElemListByKey(list, key);
  // если 2 элемент
  else if (list->first != NULL && list->second != NULL && (list->first->xorAddress == 0 && list->second->xorAddress == 0))
    return DeleteElementFrom2ElemListByKey(list, key);
  // если 3 и более элемента
  else {
    prev = list->first;
    present = list->second;
    next = (list_t*)((int)prev ^ present->xorAddress);

    // если 3 элемента
    if ((list_t*)((int)present ^ next->xorAddress) == list->first)
      return DeleteElementFrom3ElemListByKey(list, key);

    // если больше 3х элементов
    if (!strcmp(list->first->str, key)) {
      prev = (list_t*)(list->first->xorAddress ^ (int)list->second);
      prev->xorAddress = (prev->xorAddress ^ (int)list->first) ^ (int)list->second;
      list->second->xorAddress = (int)next ^ (int)prev;
      free(list->first);
      list->first = list->second;
      list->second = next;
      return TRUE;
    }
    else if (!strcmp(list->second->str, key)) {
      prev = (list_t *)(list->first->xorAddress ^ (int)list->second);
      present = (list_t *)((int)list->second ^ next->xorAddress);
      list->first->xorAddress = (int)prev ^ (int)next;
      next->xorAddress = (int)list->first ^ (int)present;
      free(list->second);
      list->second = next;
      return TRUE;
    }

    while ((list_t*)((int)prev ^ (int)(present->xorAddress)) != list->first) {
      next = (list_t*)((int)prev ^ (int)(present->xorAddress));
      if (!strcmp(next->str, key)) {
        afterNext = (list_t *)((int)present ^ (int)(next->xorAddress));
        present->xorAddress = (int)prev ^ (int)(afterNext);
        afterNext->xorAddress = (int)present ^ ((int)next ^ (int)(afterNext->xorAddress));
        free(next);
        return TRUE;
      }
      prev = present;
      present = next;
    }
    return FALSE;
  }
}

static int DeleteElementFrom3ElemListByAddress(xorList_t *list, int address) {
  list_t* next = (list_t*)((int)list->first ^ list->second->xorAddress);

  if (list->first->xorAddress == address) {
    list->second->xorAddress = next->xorAddress = 0;
    free(list->first);
    list->first = list->second;
    list->second = next;
    return TRUE;
  }
  else if (list->second->xorAddress == address) {
    list->first->xorAddress = next->xorAddress = 0;
    free(list->second);
    list->second = next;
    return TRUE;
  }
  else if (next->xorAddress == address) {
    list->first->xorAddress = list->second->xorAddress = 0;
    free(next);
    return TRUE;
  }
  else
    return FALSE;
}

int DeleteElementFromListByAddress(xorList_t* list, int address) {
  list_t* prev, * present, * next, *afterNext;

  // если у нас 0-2 элементов, то XOR список не сможет образоваться
  if (list->first == NULL || list->second == NULL || (list->first->xorAddress == 0 && list->second->xorAddress == 0))
    return FALSE;
  else {
    prev = list->first;
    present = list->second;
    next = (list_t*)((int)prev ^ present->xorAddress);

    // если 3 элемента
    if ((list_t *)((int)present ^ next->xorAddress) == list->first)
      return DeleteElementFrom3ElemListByAddress(list, address);

    // если больше трех
    if (list->first->xorAddress == address) {
      prev = (list_t*)(list->first->xorAddress ^ (int)list->second);
      prev->xorAddress = (prev->xorAddress ^ (int)list->first) ^ (int)list->second;
      list->second->xorAddress = (int)next ^ (int)prev;
      free(list->first);
      list->first = list->second;
      list->second = next;
      return TRUE;
    }
    else if (list->second->xorAddress == address) {
      prev = (list_t*)(list->first->xorAddress ^ (int)list->second);
      present = (list_t*)((int)list->second ^ next->xorAddress);
      list->first->xorAddress = (int)prev ^ (int)next;
      next->xorAddress = (int)list->first ^ (int)present;
      free(list->second);
      list->second = next;
      return TRUE;
    }

    while ((list_t*)((int)prev ^ (int)(present->xorAddress)) != list->first) {
      next = (list_t*)((int)prev ^ (int)(present->xorAddress));
      if (next->xorAddress == address) {
        afterNext = (list_t*)((int)present ^ (int)(next->xorAddress));
        present->xorAddress = (int)prev ^ (int)(afterNext);
        afterNext->xorAddress = (int)present ^ ((int)next ^ (int)(afterNext->xorAddress));
        free(next);
        return TRUE;
      }
      prev = present;
      present = next;
    }
    return FALSE;
  }
}

int createIterator(xorIter_t* iter, xorList_t* list) {
  iter->container = list->first;
  iter->next = list->second;
  return TRUE;
}

char* getFromIter(xorIter_t iter) {
  if (iter.container == NULL)
    return FALSE;
  else
    return iter.container->str;
}

int nextInIter(xorIter_t* iter) {
  list_t* tmp;
  if (iter->container != NULL && iter->next != NULL && (iter->container->xorAddress != 0 && iter->next->xorAddress != 0)) {
    tmp = (list_t*)((int)iter->container ^ iter->next->xorAddress);
    iter->container = iter->next;
    iter->next = tmp;
    return TRUE;
  }
  else if (iter->container != NULL && iter->next != NULL && !(iter->container->xorAddress != 0 && iter->next->xorAddress != 0)) {
    iter->container = iter->next;
    iter->next = NULL;
    return TRUE;
  }
  return FALSE;
}

int clearList(xorList_t* list) {
  list_t* next, * present;

  if (list->first == NULL)
    return TRUE;
  else if (list->second == NULL) {
    free(list->first);
    list->first = NULL;
    return TRUE;
  }
  else if (list->first != NULL && list->second != NULL && (list->first->xorAddress == 0 && list->second->xorAddress == 0)) {
    free(list->first);
    free(list->second);
    list->first = list->second = NULL;
    return TRUE;
  }
  else {
    present = (list_t*)((int)list->first ^ list->second->xorAddress);
    next = (list_t*)((int)list->second ^ present->xorAddress);
   
    while (next != list->first) {
      list->second->xorAddress = (int)list->first ^ (int)next;
      next->xorAddress = (int)list->second ^ ((int)present ^ next->xorAddress);
      free(present);

      present = (list_t*)((int)list->first ^ list->second->xorAddress);
      next = (list_t*)((int)list->second ^ present->xorAddress);
    }
    free(present);
    free(list->second);
    free(list->first);
    list->first = list->second = NULL;
    return TRUE;
  }
}
