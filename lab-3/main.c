#include "DFS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>


int main(void) {
	int size = 0;
	int* matrix;
	int index = 0;
	int i = 0;
	int check = 0;

	check = GraphInit(&matrix, &size);
	if (check != SUCCESS) {
		if (matrix)
			free(matrix);
		return 0;
	}

	int* state = (int*)malloc(sizeof(int) * size);
	if (state == NULL) {
		if (matrix)
			free(matrix);
		return 0;
	}
	memset(state, NOT_VISITED, size * (sizeof(int)));

	int* result = (int*)malloc(sizeof(int) * size);
	if (result == NULL) {
		if (matrix)
			free(matrix);
		return 0;
	}

	PrintMatrix(size, matrix);


	if ((matrix) && (state) && (size > 0)) {
		check = DepthFirstSearch(1, size, matrix, state, 0, &result);
	}

	if (check == FAIL) {
		printf("something's wrong");
	}

	for (i = 0; i < size; i++)
		printf("%i ", result[i]);

	if (matrix)
		free(matrix);
	if (state)
		free(state);
	if (result)
		free(result);
	return 0;
}

