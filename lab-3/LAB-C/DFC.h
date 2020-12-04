#ifndef DFC
#define DFC

#pragma once
typedef struct vertex_t {
  int number;
  struct vertex_t* vertex;
} vertex_t;

typedef struct {
  vertex_t* begin;
  vertex_t* end;
} adjList_t;

#ifdef __cplusplus
extern "C" {
#endif

  void FreeList(adjList_t* list);

  int ReadAdjList(adjList_t adjLists[], int length, FILE* fl);

  int* DFS(adjList_t adjLists[], int length, int* lengthDFS);

#ifdef __cplusplus
}
#endif

#endif#pragma once
