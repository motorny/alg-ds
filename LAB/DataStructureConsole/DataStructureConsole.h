#pragma once
#include <stdio.h>

typedef enum _OUT_CODE
{
  OC_OK = 0,
  OC_YES = 1,
  OC_NO = -1,
  OC_ERROR = -2
}OUT_CODE;

typedef void* _dsGet();

typedef void _dsFree(void* dataStructure);

typedef OUT_CODE _dsFind(void** dataStructure_p, int key, int* val_p);

typedef OUT_CODE _dsAdd(void** dataStructure_p, int key, int val);

typedef OUT_CODE _dsRemove(void** dataStructure_p, int key, int* val_p);

void SetDataStructure(_dsGet* dsGet, _dsFree* dsFree, _dsFind* dsFind, _dsAdd* dsAdd, _dsRemove* dsRemove);

int StartConsole(void);