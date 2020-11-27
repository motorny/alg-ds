#pragma once

#ifdef __cplusplus	
extern "C" {
#endif

typedef int BOOL;
#define TRUE ((BOOL)1)
#define FALSE ((BOOL)0)

typedef struct Graph_* Graph;

Graph GetGraph(int vertexCount);

void FreeGraph(Graph graph);

BOOL AddConnectionToGraph(Graph graph, int indexA, int indexB);

BOOL PrintGraph(Graph graph, FILE* stream);

#ifdef __cplusplus	
}
#endif