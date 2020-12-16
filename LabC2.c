#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

void ReadGraph(list_t* graph, int size) {

	int i = 0, j = 0, v1 = 0, v2 = 0;
	char* sv1,* sv2,* t;

	sv1 = (char*)calloc(10, sizeof(char));
	sv2 = (char*)calloc(10, sizeof(char));
	if (!sv1 || !sv2)
		return;

	for (i = 0; i < size; i++) {
		graph[i].st = 0;
		graph[i].size = 0;
	}

	while ((scanf("%s %s", sv1, sv2) != EOF)) {

		v1 = strtol(sv1, &t, 10);
		v2 = strtol(sv2, &t, 10);

		graph[v1].edg = (int*)realloc(graph[v1].edg, (graph[v1].size + 1) * sizeof(int));
		if (!graph[v1].edg) 
			return;
		graph[v1].edg[graph[v1].size] = v2;
		graph[v1].size++;

		graph[v2].edg = (int*)realloc(graph[v2].edg, (graph[v2].size + 1) * sizeof(int));
		if (!graph[v2].edg) 
			return;
		graph[v2].edg[graph[v2].size] = v1;
		graph[v2].size++;
	}

	free(sv2);
	free(sv1);
}


int DeleteGraph(list_t* graph, int size) {

	if (!graph)
		return 0;
	else {
		for (int i = 0; i < size; i++)
			if (graph[i].edg)
				free(graph[i].edg);
		free(graph);
		return 1;
	}
}

void DFS(list_t* graph, int num, int* res, int* size) {

	graph[num].st = 1;
	printf("%i ", num);
	res[*size] = num;
	(*size)++;
	for (int i = 0; i < graph[num].size; i++) 
		if (!graph[graph[num].edg[i]].st)
			DFS(graph, graph[num].edg[i], res, size);
	return;
}

int main() {

	int N, size = 0;
	int* res;
	list_t* graph;

	scanf("%d", &N);

	res = (int*)calloc(N, sizeof(int));
	graph = (list_t*)calloc(N, sizeof(list_t));
	if (!res || !graph) 
		return 0;
	else {
		ReadGraph(graph, N);
		DFS(graph, 0, res, &size);
		DeleteGraph(graph, N);

		free(res);
		return 0;
	}
}