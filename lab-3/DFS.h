#ifndef _DFS_H__
#define _DFS_H__
#pragma once
#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STR 128
#define SUCCESS 0
#define ERROR 1


typedef struct {
	int size;
	int **matrix;
}graph;

char *ReadPotok(FILE *f);

int ConvertsList2Matrix(char *str, graph *mat);

void DestroyMatrix(graph *mat);

void PrintAdjacentList(graph *mat);

void PrintGraphMatrix(graph *mat);

#endif // !_DFS_H__