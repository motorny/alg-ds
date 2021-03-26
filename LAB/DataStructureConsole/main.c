
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
#include /*DataStructure Header*/
#include <stdio.h>

#pragma warning(disable:4996)

int main(void)
{
  int r;
  SetDataStructure(/*Get, Free, Find, Add, Remove*/);
  r = StartConsole();
  DumpLeaks();
  return r;
}