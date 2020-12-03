#pragma warning (diasble: 4996)

#include "graph.h"

GRAPH* InitGraph(int size) {
	if (size <= 0)
		return NULL;
	GRAPH* graph = (GRAPH*)malloc(size * sizeof(GRAPH));
	if (!graph)
		return NULL;
	for (int i = 0; i < size; i++) {
		graph[i].num_of_edges = 0;
		graph[i].edges = NULL;
		graph[i].status = NOT_VISITED;
	}
	return graph;
}

void ReadGraph(GRAPH* graph) {
	if (!graph)
		return;
	int start_edge, end_edge;
	int* buf_for_start;
	int* buf_for_end;
	while (scanf("%d%d", &start_edge, &end_edge) != EOF) {
		buf_for_start = (int*)realloc(graph[start_edge].edges, (graph[start_edge].num_of_edges + 1) * sizeof(int));
		buf_for_end = (int*)realloc(graph[end_edge].edges, (graph[end_edge].num_of_edges + 1) * sizeof(int));
		if (buf_for_start != NULL && buf_for_end != NULL) {
			graph[start_edge].edges = buf_for_start;
			graph[end_edge].edges = buf_for_end;
		}
		else return;
		graph[start_edge].edges[graph[start_edge].num_of_edges] = end_edge;
		graph[end_edge].edges[graph[end_edge].num_of_edges] = start_edge;
		graph[start_edge].num_of_edges++;
		graph[end_edge].num_of_edges++;
	}
}

void DFS(GRAPH* graph, int* summary, int* order, int vertex) {
	if (!graph)
		return;
	graph[vertex].status = VISITED;
	summary[*order] = vertex;
	(*order)++;
	for (int i = 0; i < graph[vertex].num_of_edges; i++) {
		if (graph[graph[vertex].edges[i]].status == NOT_VISITED)
			DFS(graph, summary, order, graph[vertex].edges[i]);
	}
}

void CheckIncoherence(GRAPH* graph, int* summary, int* order, int size) {
	if (!graph)
		return;
	for (int i = 0; i < size; i++) {
		if (graph[i].num_of_edges == 0) {
			summary[(*order)] = i;
			(*order)++;
		}
	}
}

void FreeGraph(GRAPH* graph, int size) {
	if (!graph)
		return;
	for (int i = 0; i < size; i++) 
		free(graph[i].edges);
	free(graph);
}
