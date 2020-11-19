#include"graph.h"
#include<assert.h>
#include<ctype.h>

matrix_t* Create(char* str) {
	char* tstr;
	int size = 0,fnum = 0,snum = 0,crow= 0;
	if (!str)
		return NULL;
	size = (int)strtod(str, &tstr);
	matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
	if (!matrix)
		return NULL;
	matrix->numCol = size;
	matrix->numRow = size;
	matrix->isRib = calloc(matrix->numCol * matrix->numRow , sizeof(int));
	if (!matrix->isRib) {
		return NULL;
	}
	do{
		if (tstr) {
			fnum = (int)strtod(tstr, &tstr);
			snum = (int)strtod(tstr, &tstr);
		}
		if (fnum > size - 1 || snum > size - 1 || fnum < 0 || snum < 0)
			return NULL;
		*(matrix->isRib + fnum * (matrix->numCol) + snum) = 1;
		*(matrix->isRib + snum * (matrix->numCol) + fnum) = 1;
	} while (fnum != snum);
	*(matrix->isRib) = 0;
	return matrix;
}

int Dfs(matrix_t* matrix, int v, int* visited) {
	int i = 1;
	if (!matrix || v < 0 || !visited)
		return 0;
	visited[v] = 1;
	printf("%i ", v);
	for (i; i < matrix->numCol; i++) {
		if (*(matrix->isRib + v * (matrix->numCol) + i) && !visited[i])
			Dfs(matrix, i,visited);
	}
	return 1;
}

int Destroy(matrix_t* matrix) {
	if (matrix) {
		free(matrix->isRib);
		free(matrix);
		return 1;
	}
	return 0;
}

char* ReadString() {
	char* str = NULL, * ptr = NULL;
	int i = 0;
	str = (char*)malloc(2 * sizeof(char));
	if (!str)
		return NULL;
	while ((str[i] = (char)fgetc(stdin)) != EOF) {
		i++;
		ptr = realloc(str, (i + 1) * sizeof(char));
		if (ptr)
			str = ptr;
		else
			return NULL;
	}
	return str;
}