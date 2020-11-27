#include <stdio.h>
#include <stdlib.h>
#include "../GrafLib/GrafLib.h"

#pragma warning(disable:4996)

int main(void)
{
  Graph* graph_p;
  int count, indexA, indexB;

  if (scanf("%i", &count) == 0 || count <= 0)
  {
    return -1;
  }

  graph_p = GetGraph(count);
  if (graph_p == NULL)
  {
    return -1;
  }

  while (!feof(stdin) && 2 == scanf("%i %i%*[ \n]", &indexA, &indexB))
  {
    if (!AddConnectionToGraph(graph_p, indexA, indexB))
    {
      FreeGraph(graph_p);
      return -1;
    }
  }

  if (!PrintGraph(graph_p, stdout))
  {
    return -1;
  }

  FreeGraph(graph_p);

  return 0;
}