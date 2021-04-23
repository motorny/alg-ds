#include <stdio.h>
#include <stdlib.h>

#include "HashTable.h"

/* LIST SUPPORT */
/* END OF LIST SUPPORT */



int main(void)
{
  HASH_TABLE *Table = HashTableCreate(100000);

  while (TRUE)
  {
    int ch;
    char key[300];
    int q;
    ch = getchar();
    getchar();
    switch (ch)
    {
    case 'a':
      scanf("%s", key);
      HashTableAdd(Table, key);
      break;
    case 'r':
      scanf("%s", key);
      HashTableDelete(Table, key);
      break;
    case 'f':
      scanf("%s", key);
      q = HashTableFind(Table, key);
      printf(q ? "yes\n" : "no\n");
      break;
    default:
      HashTableClear(Table);
      return 0;
      break;
    }
    ch = getchar();
  }
  return 0;
}