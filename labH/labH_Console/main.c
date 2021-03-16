
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DumpLeaks() _CrtDumpMemoryLeaks()

#else

#include <stdlib.h>
#define DumpLeaks()

#endif // _DEBUG

#include "labH_Console.h"
#include "../randSearchTreap/randSearchTreap.h"
#include <stdio.h>

#pragma warning(disable:4996)

int main(void)
{
  int r;
  SetDataStructure(TreapGet, TreapFree, TreapFind, TreapRSAdd, TreapRemove);
  r = StartConsole();
  DumpLeaks();
  return r;
}