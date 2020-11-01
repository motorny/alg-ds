#pragma once
typedef struct
{
	int* answer;
	int answerIndex;
} ANSWER;

int readGeneralInf();
ANSWER DFS(int vertex, ANSWER ans);
void clearMemory();