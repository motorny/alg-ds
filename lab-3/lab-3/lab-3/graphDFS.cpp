#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"


node_t* GraphInit(int size) {
	int i = 0, j = 0, val = 0, adjacent = 0;
	char* strVal;
	char* strAdj;
	char* tmp;
	strVal = (char*)calloc(10, sizeof(char));
	if (!strVal) {
		perror("not enough memory;\n");
		exit(1);
	}
	strAdj = (char*)calloc(10, sizeof(char));
	if (!strAdj) {
		perror("not enough memory;\n");
		exit(1);
	}
	node_t* graph = (node_t*)calloc(size, sizeof(node_t));
	if (!graph) {
		perror("not enough memory;\n");
		exit(1);
	}


	for (i = 0; i < size; i++) {
		graph[i].state = N_VISITED;
		//graph[i].edges = (int*)calloc(1, sizeof(int));// every node's connected to at least 1 other node
		graph[i].size = 0;
	}
	
	

	while ((scanf("%s %s",strVal,strAdj) != EOF)) {
		val = strtol(strVal, &tmp, 10);
		adjacent = strtol(strAdj, &tmp, 10);

		graph[val].edges = (int*)realloc(graph[val].edges, (graph[val].size + 1) * sizeof(int));
		if (!graph[val].edges) {
			perror("not enough memory;\n");
			exit(1);
		}
		graph[val].edges[graph[val].size++] = adjacent;

		graph[adjacent].edges = (int*)realloc(graph[adjacent].edges, (graph[adjacent].size + 1) * sizeof(int));
		if (!graph[adjacent].edges) {
			perror("not enough memory;\n");
			exit(1);
		}
		graph[adjacent].edges[graph[adjacent].size++] = val;
	}
	
	
	free(strAdj);
	free(strVal);
	return graph;
}

void DFS(node_t* graph, int num,int* result, int* sizeResult) {
	graph[num].state = VISITED;
	printf("%d ", num);
	result[(*sizeResult)++] = num;
	for (int i = 0; i < graph[num].size; i++) {
		if (graph[graph[num].edges[i]].state == N_VISITED)
			DFS(graph, graph[num].edges[i],result,sizeResult);
	}
	return;
}

int GraphFree(node_t* graph, int size) {
	if (!graph) {
		printf("empty pointer\n");
		return EMPTY_POINTER;
	}
	for (int i = 0; i < size; i++) {
		if (graph[i].edges)
			free(graph[i].edges);
	}
	free(graph);

	return SUCCESS;
}


int main() {
	int size;
	int* result;
	int sizeResult = 0;
	node_t* graph;
	
	
	scanf("%d", &size);
	result = (int*)calloc(size, sizeof(int));
	if (!result) {
		perror("not enough memory;\n");
		exit(1);
	}
	
	graph = GraphInit(size);
	DFS(graph, 0,result,&sizeResult);
	
	
	GraphFree(graph, size);
	free(result);
	return 0;
}