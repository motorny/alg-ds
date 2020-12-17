#pragma once
#ifndef _PRE_ORDER_H
#define _PRE_ORDER_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef enum {
  FAIL = 0,
  SUCCESS = 1,
}bool_t;

typedef enum {
  FACED = 0,
  NOT_FACED = 1,
}state_t;

int GraphInit(int** matrix, int* size);//reads size, graph and creates inñident matrix

int DepthFirstSearch(int ifFirstCycle, int size, int* matrix, int* vertexStateArray, int currVertex, int** result);

#endif _PRE_ORDER_H 