#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include"graph.h"
#include"queue.h"
#pragma warning(disable:4996)


int main(void) {
	int n, l = 0;
	scanf("%i", &n);
	char* str = ReadString(n, &l) ;
	graph_t* graph;
	graph = StrToGraph(str, n, l);
	BFS(graph);
	freeGraph(graph);
}