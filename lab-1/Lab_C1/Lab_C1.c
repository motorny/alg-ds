#include "pch.h"
#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#pragma warning (disable:4996)



int top = 0; //the number of vertices to output
int* numbers = NULL; //array of vertices, which we need to print



//Function of read the list and writing it to graph
graph_t* Readlist(graph_t* graph, int n) {
	int i = 0, number = 0, numvertex = 0;
	char* stop, arr[500]; // stop is the cursor that we move to read elements or stop to read
	node_t* helpnode = NULL, * ptr, * addptr, * vertexptr;
	cond_t start = YES, exit = NO;
	numbers = (int*)malloc(n * sizeof(int));
	if (!numbers)
		return NULL;
	for (i = 0; i < n; i++) {
		graph->adjlists[i].peak = i;
		graph->isvisited[i] = NO;
		fgets(arr, 500, stdin);
		stop = arr;
		helpnode = &graph->adjlists[i];
		helpnode->next = NULL;
		while (*stop != '\n') { //checking of the end of line
			if (*stop >= '0' && *stop <= '9') {
				if (start == YES) { //vertex number
					start = NO;
					while (*stop >= '0' && *stop <= '9')
						stop++;
				}
				else { // read adjacent vertices of the graph
					numvertex = 0;
					while (*stop >= '0' && *stop <= '9') {
						numvertex = numvertex * 10 + ((int)(*stop) - (int)'0');
						stop++;
					}
					helpnode->next = (node_t*)malloc(sizeof(node_t));
					if (helpnode->next == NULL)
						return NULL;
					helpnode = helpnode->next;
					helpnode->peak = numvertex;
					helpnode->next = NULL;
				}
			}
			else
				stop++;
		}// move to next line
		start = YES;
	}
	//processing each vertex
	for (i = 0; i < n; i++) {
		exit = NO;//condition of exit from vertex
		ptr = &graph->adjlists[i];
		ptr = ptr->next;
		while (ptr != NULL) {
			vertexptr = &graph->adjlists[ptr->peak];
			exit = NO;
			vertexptr = vertexptr->next;
			while (vertexptr) {
				if (vertexptr->peak == graph->adjlists[i].peak) {
					exit = YES;
					break;
				}
				vertexptr = vertexptr->next;
			}
			if (exit == NO) { // didn't get to the end
				addptr = (node_t*)malloc(sizeof(node_t));
				if (addptr == NULL)
					return NULL;
				addptr->peak = graph->adjlists[i].peak;
				addptr->next = NULL;
				vertexptr = &graph->adjlists[ptr->peak];
				while (vertexptr->next != NULL) {
					if (vertexptr->next->peak > graph->adjlists[i].peak)
					{
						addptr->next = vertexptr->next;
						vertexptr->next = addptr;
						break;
					}
					vertexptr = vertexptr->next;
				}
				if (vertexptr->next == NULL)
					vertexptr->next = addptr;
			}
			ptr = ptr->next;
		}
	}
	return graph;
}


graph_t* Creategraph(int vert) {
	if (vert <= 0)
		return NULL;
	int i = 0;
	graph_t* newgraph = (graph_t*)malloc(vert * sizeof(graph_t));
	if (!newgraph)
		return NULL;
	newgraph->numvertices = vert;
	newgraph->isvisited = (cond_t*)malloc(vert * sizeof(cond_t));
	if (!newgraph->isvisited)
		return NULL;
	newgraph->adjlists = (node_t*)malloc(vert * sizeof(node_t));
	if (!newgraph->adjlists)
		return NULL;
	return newgraph;
}

// Depth-first search
void DFS(graph_t* graph, node_t* list) {
	int i = 0;
	node_t* newlist;
	if (graph->isvisited[list->peak] == YES)
		return;
	else graph->isvisited[list->peak] = YES;
	numbers[top] = list->peak;
	top = top + 1;
	newlist = &graph->adjlists[i];
	while (newlist->peak != list->peak) 
		newlist = &graph->adjlists[++i];
	while (newlist != NULL)
	{
		if (graph->isvisited[newlist->peak] == NO)
			DFS(graph, newlist);
		newlist = newlist->next;
	}
}

void Destroy(graph_t* graph) {
	node_t* freeptr;
	int i = 0;
	for (i = 0; i < graph->numvertices; ++i) {

		while (graph->adjlists[i].next != NULL) {
			freeptr = graph->adjlists[i].next;
			graph->adjlists[i].next = graph->adjlists[i].next->next;
			free(freeptr);
		}
	}
	if (graph->adjlists != NULL)
		free(graph->adjlists);
	if (graph->isvisited != NULL)
		free(graph->isvisited);
	if (graph != NULL)
		free(graph);
}

int main(void) {
	int i = 0, size = 0;
	graph_t* graph;
	scanf("%d\n", &size);
	graph = Creategraph(size);
	if (!graph)
		return -1;
	graph = Readlist(graph, size);
	if (!graph)
		return 0;
	DFS(graph, graph->adjlists);
	for (i = 0; i < top; i++)
		printf("%d ", numbers[i]);
	Destroy(graph);
	return 0;
}