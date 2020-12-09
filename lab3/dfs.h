#pragma once

#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED

#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#pragma warning(disable: 4996)

typedef enum {
    NOT_VISITED,
    VISITED
} visit_t;

typedef struct {
    int* vertexes, index, visit;
} node_t;


int CreateList(node_t* list, int num);
void ReadGraph(node_t* list, int num);
void DFS(node_t* list, int vertex, int num);
void DestroyList(node_t* list, int num);

#endif