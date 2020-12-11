#pragma once
#ifndef _DFS_H
#define _DFS_H

#define MAX_SIZE 100

#pragma warning (disable: 4996)

typedef enum {
	FAIL = 0,
	SUCCESS = 1,
}bool_t;

typedef enum {
	NOT_VISITED = 0,
	VISITED = 1,
}state_t;

int GraphInit(int** matrix, int* size);

void PrintMatrix(int graphSize, int* graphMatrix);

int DepthFirstSearch(int ifFirstCycle, int size, int* matrix, int* vertexStateArray, int currVertex, int** result);

#endif _DFS_H