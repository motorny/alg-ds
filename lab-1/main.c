#include "Header.h"

int main(void) {

  FILE* filename = NULL, * filename2 = NULL;
  table_t* table1 = NULL, * table2 = NULL, * fullTable;

  filename = fopen("input1.txt", "r");
  filename2 = fopen("input2.txt", "r");

  table1 = BuildTable(filename);
  Print(table1);

  table2 = BuildTable(filename2);
  Print(table2);

  fullTable = MergeTable(table1, table2);
  table1 = NULL;
  table2 = NULL;

  printf("\nAFTER MERGING: \n");

  Print(fullTable);
  DestroyTable(fullTable);

  if (filename)
    fclose(filename);
  if (filename2)
    fclose(filename2);
  

  //Memory leaks checking
  _CrtDumpMemoryLeaks();
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

  return 0;
}
