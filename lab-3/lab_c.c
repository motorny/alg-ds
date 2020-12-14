#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma warning(disable:4996)

#define LAST_VERT -1
#define MEM_ERROR -2
#define MEM_CONST 10

//Тип для определения посещенности той или иной вершины
typedef enum {
	VISITED,
	NOT_VISITED
} state_t;

//Структура для каждой вершины
typedef struct vertex {
	int numConn;
	int* connVert;
	state_t visited;
}vertex;

//Структура очереди
typedef struct {
	int numElem;
	int* elements;
}queue;

//Далее идут функция для очереди

void startQueue(queue* queue) {
	queue->numElem = 0;
	queue->elements = NULL;
}

void Push(queue* queue, int toPush) {
	int i = 0;
	queue->numElem++;
	queue->elements = realloc(queue->elements, queue->numElem * sizeof(int));
	if (!queue->elements) {
		return;
	}
	for (i = queue->numElem - 1; i > 0; i--) {
		queue->elements[i] = queue->elements[i - 1];
	}
	queue->elements[0] = toPush;
}

int Pop(queue* queue) {
	int pop = queue->elements[queue->numElem - 1];
	queue->numElem--;
	if (queue->numElem != 0) {
		queue->elements = realloc(queue->elements, queue->numElem * sizeof(int));
		if (!queue->elements) {
			return MEM_ERROR;
		}
	}
	else {
		free(queue->elements);
		queue->elements = NULL;
	}
	return pop;
}

//В этой функции для вершины добавляем соединение с другой вершиной
void AddNewConnection(vertex* vertexes, int changVert, int addVert) {
	int placeForVert = LAST_VERT;
	int i = 0;
	int temp = -1;

	vertexes[changVert].connVert = realloc(vertexes[changVert].connVert, (vertexes[changVert].numConn + 1) * sizeof(int));
	if (!vertexes[changVert].connVert) {
		return;
	}
	//Ищем место для добавляемой вершины
	for (i = 0; i < vertexes[changVert].numConn; i++) {
		if (vertexes[changVert].connVert[i] > addVert) {
			placeForVert = i;
			break;
		}
	}
	if (placeForVert == LAST_VERT) {
		vertexes[changVert].connVert[vertexes[changVert].numConn] = addVert;
	}
	if (placeForVert != LAST_VERT) {
		temp = vertexes[changVert].connVert[placeForVert];
		vertexes[changVert].connVert[placeForVert] = addVert;
		vertexes[changVert].connVert[vertexes[changVert].numConn] = temp;
	}
	vertexes[changVert].numConn++;
}

//В этой функции ищем все возможные соединения
//Считываем данные
void FindConnections(vertex* vertexes, int knotsC) {
	int vert1 = -1, vert2 = -1;
	char* fNum;
	char* sNum;

	fNum = (char*)malloc(MEM_CONST * sizeof(char));
	if (!fNum) {
		return;
	}
	sNum = (char*)malloc(MEM_CONST * sizeof(char));
	if (!sNum) {
		return;
	}

	while ((scanf("%s %s", fNum, sNum) != EOF)) {
		vert1 = atoi(fNum);
		vert2 = atoi(sNum);
		AddNewConnection(vertexes, vert1, vert2);
		AddNewConnection(vertexes, vert2, vert1);
	}

	free(fNum);
	free(sNum);
}

//Функция, выполняющая обход графа в ширину
void BFS(vertex* vertexes, queue* queue) {
	int cVert = -1;
	Push(queue, 0);
	vertexes[0].visited = VISITED;
	while (queue->numElem > 0) {
		cVert = Pop(queue);
		printf("%d ", cVert);
		for (int i = 0; i < vertexes[cVert].numConn; i++) {
			if (vertexes[vertexes[cVert].connVert[i]].visited == NOT_VISITED) {
				Push(queue, vertexes[cVert].connVert[i]);
				vertexes[vertexes[cVert].connVert[i]].visited = VISITED;
			}
		}
	}
}

int main(void) {
	int number = 0;
	vertex* vertexes = NULL;
	queue queue;

	scanf("%d", &number);

	vertexes = malloc(sizeof(vertex) * number);
	for (int i = 0; i < number; i++) {
		vertexes[i].numConn = 0;
		vertexes[i].connVert = NULL;
		vertexes[i].visited = NOT_VISITED;
	}

	FindConnections(vertexes, number);
	startQueue(&queue);
	BFS(vertexes, &queue);

	for (int i = 0; i < number; i++) {
		free(vertexes[i].connVert);
	}
	free(vertexes);

	return 0;
}