#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int numRow;
	int numCol;
	int* isRib;
}matrix_t;


matrix_t* Create(char* str);

int Dfs(matrix_t* matrix, int v,int* used);
int Destroy(matrix_t* matrix);

char* ReadString();