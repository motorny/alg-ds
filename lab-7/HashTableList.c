#include <stdlib.h>
#include <string.h>

#include "HashTable.h"
#include "HashTableList.h"

void HashListAdd(HASH_LIST* L, char *Data)
{
  HASH_LIST_ELEMENT** El = NULL;
  HASH_LIST_ELEMENT* tmp;
  El = &(L->Root);
  while ((*El) != NULL && strncmp((*El)->Data, Data, STRING_MAX_SIZE) < 0) // Untill next becomes bigger than us
    El = &((*El)->Next);

  if ((*El) != NULL && !(*El)->IsDeleted && strncmp((*El)->Data, Data, STRING_MAX_SIZE) == 0)
    return;

  if ((*El) != NULL && (*El)->IsDeleted) // if we can put our data 
  {
    (*El)->IsDeleted = FALSE;
    strncpy((*El)->Data, Data, STRING_MAX_SIZE);
    return;
  }

  tmp = malloc(sizeof(HASH_LIST_ELEMENT));
  strncpy(tmp->Data, Data, STRING_MAX_SIZE);
  tmp->IsDeleted = FALSE;
  tmp->Next = (*El);
  (*El) = tmp;

  return;
}

int HashListFind(HASH_LIST* L, char *Data)
{
  HASH_LIST_ELEMENT* El;
  El = L->Root;
  while (El != NULL)
  {
    if (strncmp(El->Data,Data, STRING_MAX_SIZE) == 0 && !El->IsDeleted)
      return 1;
    El = El->Next;
  }
  return 0;
}

int HashListDelete(HASH_LIST* L, char *Data)
{
  HASH_LIST_ELEMENT* El;
  El = L->Root;
  while (El != NULL)
  {
    if (strncmp(El->Data, Data, STRING_MAX_SIZE) == 0 && !El->IsDeleted)
    {
      El->IsDeleted = TRUE;
      return 1;
    }
    El = El->Next;
  }
  return 0;
}

void HashListClear(HASH_LIST* L)
{
  HASH_LIST_ELEMENT* El, * Next;
  El = L->Root;
  if (El == NULL)
    return;
  Next = El->Next;
  while (El != NULL)
  {
    free(El);
    El = Next;
    if (Next != NULL)
      Next = Next->Next;
  }
  return;
}
