#ifndef _DFS_H__
#define _DFS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0


#pragma warning (disable: 4996)

int ReadGraphInfo(int* graphSize, int** graphMatrix);

/* Parse input string like an input in 'stdin'
 * SPECIFICATION: '*' in end of str = EOF
 * Input: *str - ptr to str
 *        *graphSize - ptr to graph size
 *        **graphMatrix - ptr to graph matrix
 * Output: 1 if all good, 0 if bad
 */
int ParseStrLikeSTDIN(char* str, int* graphSize, int** graphMatrix);

void PrintMatrix(int graphSize, int* graphMatrix);
void PrintDFS(int* answer, int size);
void FreeDFSPointers(int* answer, int* graphMatrix, int* wasTheseNodes);

int DFS(int graphSize, int* graphMatrix, int* wasInTheseNodes, int currentNode, int** answer);

#endif _DFS_H__
