#include <stdlib.h>

#include "HashTableList.h"
#include "HashTable.h"

HASH_TABLE* HashTableCreate(int size)
{
  HASH_TABLE* tmp;
  int i;
  tmp = malloc(sizeof(HASH_TABLE));

  tmp->Size = size;
  tmp->Data = malloc(sizeof(HASH_LIST) * size);
  for (i = 0; i < size; i++)
    tmp->Data[i].Root = NULL;
  return tmp;
}

void HashTableClear(HASH_TABLE* tmp)
{
  unsigned i;
  for (i = 0; i < tmp->Size; i++)
    HashListClear(&tmp->Data[i]);
  free(tmp->Data);
  free(tmp);
}

void HashTableAdd(HASH_TABLE* tmp, char *Data)
{
  int hash_res;
  if (tmp == NULL)
    return;
  hash_res = HashFunction(tmp, Data);
  HashListAdd(&(tmp->Data[hash_res]), Data);
}

void HashTableDelete(HASH_TABLE* tmp, char *Data)
{
  int hash_res;
  if (tmp == NULL)
    return;
  hash_res = HashFunction(tmp, Data);
  HashListDelete(&(tmp->Data[hash_res]), Data);
}

int HashTableFind(HASH_TABLE* tmp, char *Data)
{
  int hash_res;
  if (tmp == NULL)
    return FALSE;
  hash_res = HashFunction(tmp, Data);
  return HashListFind(&(tmp->Data[hash_res]), Data);
}