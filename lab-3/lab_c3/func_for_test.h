#ifndef FUNC_FOR_TEST_H__INCLUDED__
#define FUNC_FOR_TEST_H__INCLUDED__
#pragma once

#define M_SUCCESS 1
#define M_FAIL 0

typedef struct {
  int* arr;
  int size;
  int head;
  int tail;
} queue_t;

typedef struct {
  int numOfEdges;
  int* edges;
} node_t;

typedef struct {
  int numOfVertex;
  node_t* nodes;
} adj_list_t;

int InitQueue(queue_t* q, int size);
int Put(queue_t* q, int newEl);
int Get(queue_t* q, int* oldEl);
void DelQueue(queue_t* q);
int BFS(adj_list_t* list, queue_t* q);

#endif