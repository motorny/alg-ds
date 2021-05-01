#include "DataStructureLibWrapper.h"
#include "../HashTableLin/HashTableLin.h"
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

void* WrapperGet()
{
  return (void*)HashTableGet(1046527, 1);
}

void WrapperFree(void* dataStructure)
{
  HashTableFree((HashTable_t*)dataStructure);
}

OUT_CODE WrapperFind(void** dataStructure_p, int key, int* val_p)
{
  int r;
  int* tmp;
  char buff[30];
  sprintf(buff, "%i", key);
  r = HashTableFind((HashTable_t*)(*dataStructure_p), buff, (void**)&tmp);
  switch (r)
  {
  case 1:
    *val_p = *tmp;
    return OC_YES;
    break;
  case -1:
    return OC_NO;
    break;
  default:
    return OC_ERROR;
    break;
  }
}

OUT_CODE WrapperAdd(void** dataStructure_p, int key, int val)
{
  int r;
  int* tmp = (int*)malloc(sizeof(int));
  char buff[30];
  sprintf(buff, "%i", key);
  *tmp = val;
  r = HashTableAdd((HashTable_t*)(*dataStructure_p), buff, (void*)tmp);
  switch (r)
  {
  case 1:
    return OC_YES;
    break;
  case -1:
    free(tmp);
    return OC_NO;
    break;
  default:
    return OC_ERROR;
    break;
  }
}

OUT_CODE WrapperRemove(void** dataStructure_p, int key, int* val_p)
{
  int r;
  int* tmp;
  char buff[30];
  sprintf(buff, "%i", key);
  r = HashTableRemove((HashTable_t*)(*dataStructure_p), buff, (void**)&tmp);
  switch (r)
  {
  case 1:
    *val_p = *tmp;
    free(tmp);
    return OC_YES;
    break;
  case -1:
    return OC_NO;
    break;
  default:
    return OC_ERROR;
    break;
  }
}
