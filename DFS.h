#pragma once

#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED

typedef struct {
  int numOfList;
  int visided;
  int *edges;
}vertex_t;

typedef struct {
  int sizeList; 
  vertex_t* vertex;
}adjList_t;

int DFS(adjList_t* adj, int i);
void CreateAdjList(adjList_t* adj);
#endif