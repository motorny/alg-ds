#include "DataStructureLibWrapper.h"
#include "../BTree/BTree.h"

void* WrapperGet()
{
  return (void*)BTreeGet(5);
}

void WrapperFree(void* dataStructure)
{
  BTreeFree((BTree_t*)dataStructure);
}

OUT_CODE WrapperFind(void** dataStructure_p, int key, int* val_p)
{
  int r = BTreeFind((BTree_t*)(*dataStructure_p), key, val_p);
  switch (r)
  {
  case 1:
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
  int r = BTreeAdd((BTree_t*)(*dataStructure_p), key, val);
  switch (r)
  {
  case 1:
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

OUT_CODE WrapperRemove(void** dataStructure_p, int key, int* val_p)
{
  int r = BTreeRemove((BTree_t*)(*dataStructure_p), key, val_p);
  switch (r)
  {
  case 1:
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
