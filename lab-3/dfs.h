#pragma once

typedef struct
{
	int* answer;
	int ansIndex;
} branch;

int ReadGraph();

branch DeepFirstSearch(int vertex, branch ans);

void clearGraph();

typedef enum {
	notVisited,
	visited
} state;

typedef struct {
	int vertexCount;
	int ribsCount;
	int** ribs;
	state* vertex;
} graph_t;

graph_t data;
int countShadedVert;

