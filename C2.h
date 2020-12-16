#ifndef C2_H_INCLUDED__
#define C2_H_INCLUDED__

#pragma once

#include <stdio.h>

typedef enum {
  WHITE,
  GRAY,
  BLACK,
} color_t;

typedef struct edge_t {
  struct node_t* node;
  struct edge_t* next;
} edge_t;

typedef struct node_t {
  int edgesQ;
  color_t color;
  edge_t* edges;
} node_t;

node_t* CreateGraph(int n, int* err);

void AddEdge(node_t* node1, node_t* node2, int *err);

void DestroyGraph(node_t* nodes, int n);

// Read function -> no tests
node_t* FillFromStream(FILE* fp, int *n, int* err);

// Print function -> no tests
void PrintEdges(node_t* nodes, int n);

void RunDFS(int* ans, node_t* nodes, int n);

// Print function -> no tests
void PrintDFS(int* ans, int n);

#endif