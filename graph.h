#ifndef GRAPH_H_INCLUDED__
#define GRAPH_H_INCLUDED__
#pragma once
#define MAXLENGTHSTR 100
#define INCORRECTINPUT -10
#define DISCOVERED 1
#define UNDISCOVERED -1

typedef struct node {
  int data;
  struct node* next;
} node_t;
typedef struct graph {
  int numOfVertex;
  node_t** adjList;
} graph_t;


graph_t* readGraph(void);
void BFS(graph_t* graph);
void freeGraph(graph_t* graph);

#endif