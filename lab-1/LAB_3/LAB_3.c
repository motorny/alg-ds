#include "pch.h"
#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#pragma warning (disable:4996)

dop_t Dop = { 0, NULL };

graph_t* Transform(graph_t* graph, int n) {
	node_t* addnode = NULL, * ptr, * add, * vertex;
	cond_t start = TRUE, exit = FALSE;
	int i;
	for (i = 0; i < n; i++) {
		exit = FALSE;
		ptr = &graph->list[i];
		ptr = ptr->next;
		while (ptr) {
			vertex = &graph->list[ptr->top];
			exit = FALSE;
			vertex = vertex->next;
			while (vertex) {
				if (vertex->top == graph->list[i].top) {
					exit = TRUE;
					break;
				}
				vertex = vertex->next;
			}
			if (exit == FALSE) {
				add = (node_t*)malloc(sizeof(node_t));
				if (!add)
					return NULL;
				add->top = graph->list[i].top;
				add->next = NULL;
				vertex = &graph->list[ptr->top];
				while (vertex->next) {
					if (vertex->next->top > graph->list[i].top)
					{
						add->next = vertex->next;
						vertex->next = add;
						break;
					}
					vertex = vertex->next;
				}
				if (!vertex->next)
					vertex->next = add;
			}
			ptr = ptr->next;
		}
	}
	return graph;
}

graph_t* Readlist(graph_t* graph, int n) {
	int i = 0, numvertex = 0;
	char* stop, arr[300];
	node_t* addnode = NULL;
	cond_t start = TRUE;
	Dop.nums = (int*)malloc(n * sizeof(int));
	if (!Dop.nums)
		return NULL;
	for (i = 0; i < n; i++) {
		graph->list[i].top = i;
		graph->isinside[i] = FALSE;
		fgets(arr, 300, stdin);
		stop = arr;
		addnode = &graph->list[i];
		addnode->next = NULL;
		do { //is it the end of line
			if (*stop >= '0' && *stop <= '9') {
				if (start == TRUE) { 
					start = FALSE;
					while (*stop >= '0' && *stop <= '9')
						stop++;
				}
				else { // read nearby vertexes
					numvertex = 0;
					while (*stop >= '0' && *stop <= '9') {
						numvertex = numvertex * 10 + ((int)(*stop) - (int)'0');
						stop++;
					}
					addnode->next = (node_t*)malloc(sizeof(node_t));
					if (addnode->next == NULL)
						return NULL;
					addnode = addnode->next;
					addnode->top = numvertex;
					addnode->next = NULL;
				}
			}
			else
				stop++;
		} while (*stop != '\n');
		start = TRUE;
	}
	graph = Transform(graph, n);
	return graph;
}

graph_t* Creategraph(int n) {
	if (n <= 0)
		return NULL;
	int i = 0;
	graph_t* newgraph = (graph_t*)malloc(n * sizeof(graph_t));
	if (!newgraph)
		return NULL;
	newgraph->number = n;
	newgraph->isinside = (cond_t*)malloc(n * sizeof(cond_t));
	if (!newgraph->isinside)
		return NULL;
	newgraph->list = (node_t*)malloc(n * sizeof(node_t));
	if (!newgraph->list)
		return NULL;
	return newgraph;
}

void DFS(graph_t* graph, node_t* list) {
	int i = 0;
	node_t* newlist;
	if (graph->isinside[list->top] == TRUE)
		return;
	else graph->isinside[list->top] = TRUE;
	Dop.nums[Dop.first] = list->top;
	Dop.first += 1;
	newlist = &graph->list[i];
	while (newlist->top != list->top)
		newlist = &graph->list[++i];
	while (newlist)
	{
		if (graph->isinside[newlist->top] == FALSE)
			DFS(graph, newlist);
		newlist = newlist->next;
	}
}

void Destroy(graph_t* graph) {
	node_t* freeptr;
	int i = 0;
	for (i = 0; i < graph->number; ++i) {

		while (graph->list[i].next) {
			freeptr = graph->list[i].next;
			graph->list[i].next = graph->list[i].next->next;
			free(freeptr);
		}
	}
	if (graph->list)
		free(graph->list);
	if (graph->isinside)
		free(graph->isinside);
	if (graph)
		free(graph);
}

int main(void) {
	int i, size = 0;
	graph_t* graph;
	scanf_s("%d\n", &size);
	graph = Creategraph(size);
	if (!graph)
		return -1;
	graph = Readlist(graph, size);
	if (!graph)
		return 0;
	graph = Transform(graph, size);
	if (!graph)
		return 0;
	DFS(graph, graph->list);
	for (i = 0; i < Dop.first; i++)
		printf("%d ", Dop.nums[i]);
	Destroy(graph);
	return 0;
}
