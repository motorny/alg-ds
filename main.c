#define _CRT_SECURE_NO_WARNINGS

#include "graph.h"

int main() {
	int size_graph;
	scanf("%d", &size_graph);
    int* summary = (int*)malloc(size_graph * sizeof(int));
	if (!summary)
		return -1;
	GRAPH* graph = InitGraph(size_graph);
	ReadGraph(graph);
	int order = 0;
	int vertex = 0;
    DFS(graph, summary, &order, vertex);
	CheckIncoherence(graph, summary, &order, size_graph);
	for (int i = 0; i < size_graph; i++)
		printf("%d ", summary[i]);
	FreeGraph(graph, size_graph);
	free(summary);
	return 0;
}