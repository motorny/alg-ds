
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DumpLeaks() _CrtDumpMemoryLeaks()

#else

#include <stdlib.h>
#define DumpLeaks()

#endif // _DEBUG

#include "DataStructureConsole.h"
#include "DataStructureLibWrapper.h"
#include <stdio.h>

#pragma warning(disable:4996)

int main(void)
{
  int r;
  SetDataStructure(WrapperGet, WrapperFree, WrapperFind, WrapperAdd, WrapperRemove);
  r = StartConsole();
  DumpLeaks();
  return r;
}