#pragma once

typedef enum {
	TRUE,
	FALSE
}cond_t;

typedef struct node_t {
	int top;
	struct node_t* next;
}node_t;

typedef struct {
	int number;
	struct node_t* list;
	cond_t* isinside;
}graph_t;

typedef struct dop_t {
	int first;
	int* nums;
}dop_t;

graph_t* Transform(graph_t* graph, int n);

graph_t* Readlist(graph_t* graph, int n);

graph_t* Creategraph(int n);

void DFS(graph_t* graph, node_t* list);

void Destroy(graph_t* graph);