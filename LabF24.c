#include "..\IT_Lib\IT_Lib.h"
#include <stdlib.h>
#include <stdio.h>

#pragma warning(disable:4996)

int main(void)
{
  char* command;
  int arg1, arg2, arg3, i, n;
  int outArray[10];
  Tree* tree_p = TreeGet();
  if (tree_p == NULL)
  {
    return -1;
  }
  command = malloc(3);
  if (command == NULL)
  {
    return -1;
  }

  scanf("%*[ \n]");
  while (!feof(stdin) && 4 == scanf("%2s %i %i %i", command, &arg1, &arg2, &arg3))
  {
    switch (command[0])
    {
    case 'a':
      TreeAdd(tree_p, arg1, arg2, arg3);
      break;
    case 'r':
      //r leftX
      TreeRemove(tree_p, arg1, arg2);
      break;
    case 'i':
      //r leftX
      n = TreeIntersect(tree_p, arg1, arg2, outArray, 10);
      for ( i = 0; i < n; i++)
      {
        printf("%i ", outArray[i]);
      }
      printf("\n");
      break;
    case 'f':
      //f leftX
      if (TreeFind(tree_p, arg1, arg2) != NULL)
      {
        printf("yes\n");
      }
      else
      {
        printf("no\n");
      }
      break;
    case 'p':
      TreePrintIntervals(tree_p, arg1);
      break;
    default:
      printf("Incorrect Command\n");
      break;
    }
    scanf("%*[ \n]");
  }
  TreeFree(tree_p);
  return 0;
}
