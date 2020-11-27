#include <stdio.h>
#include <stdlib.h>
#include "GrafLib.h"

#pragma warning(disable:4996)

typedef struct _VertexListItem
{
  int index;
  struct _VertexListItem* next;
} VertexListItem;

typedef struct
{
  VertexListItem connectionsList;
  BOOL isVisited;
} Vertex;

struct Graph_
{
  Vertex* vertices;
  int vertexCount;
};

BOOL AddConnectionToList(VertexListItem* list, int index)
{
  VertexListItem* newItem;
  VertexListItem* item;
  VertexListItem* nextItem;
  newItem = (VertexListItem*)malloc(sizeof(VertexListItem));
  if (newItem == NULL)
  {
    return FALSE;
  }
  newItem->index = index;
  nextItem = list;
  do {
    item = nextItem;
    nextItem = item->next;
  }while (nextItem != NULL && nextItem->index < index);
  if (nextItem == NULL || nextItem->index > index)
  {
    item->next = newItem;
    newItem->next = nextItem;
  }
  return TRUE;
}

BOOL AddConnectionToGraph(Graph graph, int indexA, int indexB)
{
  if (graph != NULL && indexA < graph->vertexCount && indexA >= 0 && indexB < graph->vertexCount && indexB >= 0)
  {
    return (AddConnectionToList(&graph->vertices[indexA].connectionsList, indexB)
      && AddConnectionToList(&graph->vertices[indexB].connectionsList, indexA));
  }
  else
  {
    return FALSE;
  }
}

Graph GetGraph(int vertexCount)
{
  if (vertexCount < 1)
  {
    return NULL;
  }
  else
  {
    int i;
    Graph graph = (Graph)malloc(sizeof(struct Graph_));
    if (graph == NULL)
    {
      return NULL;
    }
    graph->vertexCount = vertexCount;
    graph->vertices = (Vertex*)malloc((vertexCount) * sizeof(Vertex));
    if (graph->vertices == NULL)
    {
      free(graph);
      return NULL;
    }
    for (i = 0; i < vertexCount; i++)
    {
      graph->vertices[i].isVisited = FALSE;
      graph->vertices[i].connectionsList.index = -1;
      graph->vertices[i].connectionsList.next = NULL;
    }

    return graph;
  }
}

void FreeGraph(Graph graph)
{
  if (graph != NULL)
  {
    int i;
    int count = graph->vertexCount;
    VertexListItem* item, * nextItem;
    for (i = 0; i < count; i++)
    {
      item = graph->vertices[i].connectionsList.next;
      while (item != NULL)
      {
        nextItem = item->next;
        free(item);
        item = nextItem;
      }
    }
    free(graph->vertices);
    free(graph);
  }
}

void ResetGraphVisits(Graph graph)
{
  int i;
  int count = graph->vertexCount;
  for (i = 0; i < count; i++)
  {
    graph->vertices[i].isVisited = FALSE;
  }
}

BOOL PrintGraph(Graph graph, FILE* stream)
{
  if (graph == NULL)
  {
    return FALSE;
  }
  else
  {
    VertexListItem* connection;
    int depth = 0;
    struct vertexCallData
    {
      int index;
      VertexListItem* lastConnection;
    } *vertexCallStack = (struct vertexCallData*)malloc((graph->vertexCount + 1) * sizeof(struct vertexCallData));

    if (vertexCallStack == NULL)
    {
      return FALSE;
    }

    ResetGraphVisits(graph);

    fprintf(stream, "0 ");
    graph->vertices[0].isVisited = TRUE;
    vertexCallStack[depth].index = 0;
    vertexCallStack[depth].lastConnection = &graph->vertices[0].connectionsList;

    while (depth >= 0)
    {
      connection = vertexCallStack[depth].lastConnection->next;
      while (connection != NULL && graph->vertices[connection->index].isVisited)
      {
        connection = connection->next;
      }
      if (connection == NULL)
      {
        depth--;
      }
      else
      {
        vertexCallStack[depth].lastConnection = connection;
        fprintf(stream, "%i ", connection->index);
        graph->vertices[connection->index].isVisited = TRUE;
        depth++;
        vertexCallStack[depth].index = connection->index;
        vertexCallStack[depth].lastConnection = &graph->vertices[connection->index].connectionsList;
      }
    }
    free(vertexCallStack);
    return TRUE;
  }
}
