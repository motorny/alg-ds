#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	VISITED,
	NOT_VISITED
} STATUS;

typedef struct graph_t {
	int* edges;
	int num_of_edges;
	STATUS status;
} GRAPH;

GRAPH* InitGraph(int size);
void ReadGraph(GRAPH* graph);
void DFS(GRAPH* graph, int* summary, int* order, int vertex);
void CheckIncoherence(GRAPH* graph, int* summary, int* order, int size);
void FreeGraph(GRAPH* graph, int size);
