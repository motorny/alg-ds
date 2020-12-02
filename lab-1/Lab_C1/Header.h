#pragma once
#include "pch.h"
typedef enum {
	NO,
	YES
}cond_t;

typedef struct node_t {
	int peak;
	struct node_t* next;
}node_t;

typedef struct {
	int numvertices;
	struct node_t* adjlists;
	cond_t* isvisited;
}graph_t;

graph_t* Readlist(graph_t* graph, int n);

graph_t* Creategraph(int vert);

void DFS(graph_t* graph, node_t* list);

void Destroy(graph_t* graph);
