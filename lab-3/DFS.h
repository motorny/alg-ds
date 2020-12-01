#ifndef _DFS_H__
#define _DFS_H__
#pragma once
#pragma warning (disable: 4996)

typedef struct {
	int size, **matrix;
}t_Graf;

typedef struct {
	int size, *arr;
}t_Answer;

t_Answer DFS(t_Graf *graf);

t_Graf *ScanGrafFromStdin(void);

void DelGraf(t_Graf *graf);

#endif // !_DFS_H__