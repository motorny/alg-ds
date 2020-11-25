#pragma once
#ifndef __GRAPH_DFS__
#define __GRAPH_DFS__

#define EMPTY_POINTER -1
#define SUCCESS 0

typedef enum {
	VISITED,
	N_VISITED
} state_t;

typedef struct {
	int* edges;
	int size;
	state_t state;
} node_t;

node_t* GraphInit(int size);

void DFS(node_t* graph, int num, int* result, int* sizeResult);

int GraphFree(node_t* graph, int size);

#endif // !__GRAPH_DFS__


