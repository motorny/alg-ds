#include <stdio.h>
#include <stdlib.h>

#define ALLOWED 0
#define NOTALLOWED 1
#define ERRORED -1

#pragma warning(disable: 4996)


typedef struct {
	int* vertex;
	int index;
	int flag;
} graph_t;


void Communication(graph_t* list, char separator, int basic) {//устанавливаем связь между текущей вершиной и указанными к ней как смежные
	int linked;
	int ind;
	while (separator == ' ') {
		scanf("%i", &linked);
		ind = list[basic].index++;
		list[basic].vertex[ind] = linked;
		ind = list[linked].index++;
		list[linked].vertex[ind] = basic;
		scanf("%c", &separator);
	}
}

void MakeGraph(graph_t* list, int number) {
	int i, base;
	char separator;
	for (i = 0; i < number; i++) {
		scanf("%i", &base);//первой в строке считывается описывающася в данный момент вершина
		scanf("%c", &separator);
		Communication(list, separator, base);
	}
}

void DFS(graph_t* list, int point, int number) {
	int i, ind;

	printf("%i ", point);

	list[point].flag = NOTALLOWED;

	for (i = 0; i < list[point].index; i++) {
		ind = list[point].vertex[i];
		if (list[ind].flag == ALLOWED)
			DFS(list, list[point].vertex[i], number);
	}
}


int main(void) {
	int N, i;
	scanf("%i", &N);

	graph_t* adjacencyList = (graph_t*)malloc(N * sizeof(graph_t));

	if (!adjacencyList) {
		return ERRORED;
	}

	for (i = 0; i < N; i++) {
		adjacencyList[i].vertex = (int*)malloc(N * sizeof(int));
		if (adjacencyList[i].vertex) {
			adjacencyList[i].index = 0;
			adjacencyList[i].flag = ALLOWED;
		}
		else return ERRORED;
	}

	MakeGraph(adjacencyList, N);
	DFS(adjacencyList, 0, N);

	for (i = 0; i < N; i++)
		free(adjacencyList[i].vertex);
	free(adjacencyList);

	return 0;
}