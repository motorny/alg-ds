#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"
#include "queue.h"

static int initNode(node_t** head) {
  *head = (node_t*)malloc(sizeof(node_t));
  if (*head == NULL)
    return FAIL;
  return SUCCESS;
}
static node_t* add2Graph(node_t* head, int vertexTo) {
  node_t* cur = head;
  //one way
  if (head == NULL) {
    if (initNode(&head) == FAIL)
      return NULL;
    head->data = vertexTo;
    head->next = NULL;
  }
  else {
    while (cur->next != NULL)
      cur = cur->next;
    cur->next = (node_t*)malloc(sizeof(node_t));
    if (cur->next == NULL)
      return NULL;
    cur->next->data = vertexTo;
    cur->next->next = NULL;
  }
  return head;
}

graph_t* readGraph(void) {
  char str[MAXLENGTHSTR];
  char* newStr, *endStr;
  int numOfVertex = 0;
  int vertexFrom, vertexTo;
  graph_t* graph;

  graph = (graph_t*)malloc(sizeof(graph_t));
  fgets(str, MAXLENGTHSTR, stdin);
  numOfVertex = (int)strtod(str, &endStr);
  if (numOfVertex <= 0) {
    graph->numOfVertex = INCORRECTINPUT;
    return graph;
  }
  graph->numOfVertex = numOfVertex;
  if (numOfVertex == 1)
    return graph;
  graph->adjList = malloc(numOfVertex * sizeof(node_t));
  for (int i = 0; i < numOfVertex; i++)
    graph->adjList[i] = NULL;

  while (1) {
    fgets(str, MAXLENGTHSTR, stdin);
    if (str[0] != '\0') {
      newStr = str;
      //get first part of edge
      while (isspace(*newStr))
        newStr++;
      if (feof(stdin))
        return graph;
      if (*newStr < '0' || *newStr >'9') {
        graph->numOfVertex = INCORRECTINPUT;
        return graph;
      }
      vertexFrom = (int)strtod(newStr, &endStr);
      newStr = endStr;
      //get second part of edge
      while (isspace(*newStr))
        newStr++;
      if (*newStr < '0' || *newStr >'9') {
        graph->numOfVertex = INCORRECTINPUT;
        return graph;
      }
      vertexTo = (int)strtod(newStr, &endStr);
      newStr = endStr;
      graph->adjList[vertexFrom] = add2Graph(graph->adjList[vertexFrom], vertexTo);
      graph->adjList[vertexTo] = add2Graph(graph->adjList[vertexTo], vertexFrom);
      if (graph->adjList[vertexFrom] == NULL || graph->adjList[vertexTo] == NULL) {
        graph->numOfVertex = INCORRECTINPUT;
        return graph;
      }
      //read to the end of string
      while (isspace(*newStr))
        newStr++;
    }
    if (feof(stdin))
      return graph;
  }
}
void BFS(graph_t* graph) {
  int* isUsed = (int*)malloc(graph->numOfVertex * sizeof(int));
  int i, curVertex, nextVertex;
  queue_t* queue = createQueue();

  if (graph->numOfVertex <= 0) {
    return;
  }
  if (graph->numOfVertex == 1) {
    printf("0 ");
    return;
  }
  for (i = 0; i < graph->numOfVertex; i++)
    isUsed[i] = UNDISCOVERED;
  if (pushQueue(queue, 0) == FAIL)
    return;
  isUsed[0] = DISCOVERED;
  while (queue->head != NULL) {
    curVertex = popQueue(queue);
    if (curVertex < 0)
      return;
    printf("%i ", curVertex);
    node_t* tmp = graph->adjList[curVertex];
    while (tmp != NULL) {
      nextVertex = tmp->data;
      if (isUsed[nextVertex] == UNDISCOVERED) {
        isUsed[nextVertex] = DISCOVERED;
        if (pushQueue(queue, nextVertex) == FAIL)
          return;
      }
      tmp = tmp->next;
    }
    if (queue->head == NULL) {
      for(i = 0; i < graph->numOfVertex; i++)
        if (graph->adjList[i] != NULL && isUsed[i] != DISCOVERED) {
          if (pushQueue(queue, i) == FAIL)
            return;
          isUsed[i] = DISCOVERED;
          break;
        }
    }
  }
  free(isUsed);
  destroyQueue(queue);
}
void freeGraph(graph_t* graph) {
  if (graph->numOfVertex > 1){
    for (int i = 0; i < graph->numOfVertex; i++) {
      if(graph->adjList[i] != NULL)
        if (graph->adjList[i]->next != NULL) {
          while (graph->adjList[i] != NULL) {
            node_t* tmp = graph->adjList[i];
            graph->adjList[i] = graph->adjList[i]->next;
            free(tmp);
          }
        }
      free(graph->adjList[i]);
    }
    free(graph->adjList);
  }
  free(graph);
}