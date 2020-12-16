#pragma once

typedef struct {
	int size;
	int st;
	int* edg;
} list_t;

void ReadGraph(list_t* graph, int size);

int DeleteGraph(list_t* graph, int size);

void DFS(list_t* graph, int num, int* res, int* size);
