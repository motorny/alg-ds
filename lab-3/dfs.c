#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#include "DFS.h"

void PrintMatrix(int graphSize, int* graphMatrix) {
	if (graphMatrix == NULL || graphSize < 1)
		return;

	for (int i = 0; i < graphSize; i++) {
		for (int j = 0; j < graphSize; j++)
			printf("%i ", graphMatrix[i * graphSize + j]);
		printf("\n");
	}
}

int GraphInit(int** matrix, int* size) {
	char buff[MAX_SIZE];
	char sym = 0;
	int i = 0, vertex1 = -1, vertex2 = -1;
	// Читаем размер
	sym = getchar();
	if (sym == EOF)
		return FAIL;
	while (sym != '\n') {
		if (sym == EOF)
			return SUCCESS;
		buff[i] = sym;
		i++;
		sym = getchar();
	}
	buff[i] = '\0';

	// Конвертируем в число
	*size = atoi(buff);

	if (*size < 1)
		return FAIL;

	// Выделим память на матрицу
	*matrix = (int*)malloc(sizeof(int) * (*size) * (*size));
	if (*matrix == NULL)
		return FAIL;
	// Заполним нулями
	memset(*matrix, 0, (*size) * (*size) * sizeof(int));

	if (*size == 1)
		return SUCCESS;

	i = 0;
	sym = getchar();
	while (sym != EOF) {
		// Первая вершина записалась
		if (sym == ' ') {
			buff[i] = '\0';
			vertex1 = atoi(buff);
			i = 0;
		}
		// Вторая
		else if (sym == '\n') {
			buff[i] = '\0';
			vertex2 = atoi(buff);
			i = 0;
			// Имея обе вершины, внесем их в матрицу
			(*matrix)[vertex1 + (*size) * vertex2] = 1;
			(*matrix)[vertex1 * (*size) + vertex2] = 1;
		}
		else {
			buff[i] = sym;
			i++;
		}
		sym = getchar();
	}
	return SUCCESS;
}

int DepthFirstSearch(int ifFirstCycle, int size, int* matrix, int* vertexStateArray, int currVertex, int** result) {

	 int nextVertex;
	static int i = 0;

	if ((currVertex < 0) || (currVertex >= size))
		return FAIL;

	if (ifFirstCycle == 1) {
		i = 0;
		memset(vertexStateArray, NOT_VISITED, size * (sizeof(int)));
	}

	if (vertexStateArray[currVertex] != VISITED) {
		(*result)[i++] = currVertex;
		vertexStateArray[currVertex] = VISITED;
	}

	for (nextVertex = 0; nextVertex < size; nextVertex++) {
		if ((vertexStateArray[nextVertex] == NOT_VISITED) && (matrix[currVertex * size + nextVertex] == 1) && (currVertex != nextVertex)) {
			DepthFirstSearch(0, size, matrix, vertexStateArray, nextVertex, result);
		}
	}

	return SUCCESS;
}
