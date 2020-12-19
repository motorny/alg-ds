#include "Graph_dfs.h"

int CreateList(node_t* list, int num) {
	if (list && num) {
		int i;
		for (i = 0; i < num; i++) {
			list[i].index = 0;
			list[i].vertexes = (int*)malloc(num * sizeof(int));
			if (!list[i].vertexes) {
				printf("ERROR: No memory");
				return -1;
			}
			list[i].visit = NOT_VISITED;
		}
		return 1;
	}
	else {
		printf("ERROR: Graph is empty\n");
		return -1;
	}
}

void ReadGraph(node_t* list, int num) {
	int i, curr, next;
	char sym;
	for (i = 0; i < num; i++) {
		scanf("%i%c", &curr, &sym);
		while (sym == ' ') {
			scanf("%i%c", &next, &sym);
			list[curr].vertexes[list[curr].index++] = next;
			list[next].vertexes[list[next].index++] = curr;
		}
	}
}

void DFS(node_t* list, int vertex, int num) {
	if (list && num) {
		int i;
		list[vertex].visit = VISITED;
		printf("%i ", vertex);
		for (i = 0; i < list[vertex].index; i++)
			if (list[list[vertex].vertexes[i]].visit != VISITED)
				DFS(list, list[vertex].vertexes[i], num);
	}
}

void DestroyList(node_t* list, int num) {
	int i;
	for (i = 0; i < num; i++)
		free(list[i].vertexes);
	free(list);
}