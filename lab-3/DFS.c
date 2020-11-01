#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "DFS.h"

#define INFORMATION_READED 1
#define EMPTY_INPUT 2
#define MEMORY_ALOCATE_FAIL -1

typedef enum
{
	notVisited,
	visited
} STATE;

typedef struct
{
	int countVertex;
	int countRibs;
	int** ribs;
	STATE* vertex;
} GENERALINF;

int countShadedVert;
GENERALINF inf;

int readGeneralInf()
{
	char c, str[100];
	int index = 0
		, indexAdj = 0
		, indexRib = 0;

	c = getchar();
	if (c == EOF)
	{
		return EMPTY_INPUT;
	}
	while (c != '\n')
	{
		if (c == EOF)
		{
			return INFORMATION_READED;
		}
		str[index++] = c;
		c = getchar();
	}
	str[index] = '\0';
	inf.countVertex = atoi(str);
	inf.vertex = (STATE*)malloc(sizeof(STATE) * inf.countVertex + 1);
	if (inf.vertex == NULL)
	{
		return MEMORY_ALOCATE_FAIL;
	}
	for (int i = 0; i < inf.countVertex; i++)
	{
		inf.vertex[i] = notVisited;
	}
	inf.ribs = (int**)malloc(sizeof(int*) * inf.countVertex * inf.countVertex);
	if (inf.ribs == NULL)
	{
		return MEMORY_ALOCATE_FAIL;
	}
	for (int i = 0; i < inf.countVertex * inf.countVertex; i++)
	{
		inf.ribs[i] = (int*)malloc(2 * sizeof(int));
		if (inf.ribs == NULL)
		{
			return MEMORY_ALOCATE_FAIL;
		}
	}
	index = 0;
	c = getchar();
	while (c != EOF)
	{
		if (c == ' ' || c == '\n')
		{
			str[index] = '\0';
			inf.ribs[indexRib][indexAdj++] = atoi(str);
			index = 0;
		}
		else
		{
			str[index++] = c;
		}
		if (c == '\n')
		{
			indexAdj = 0;
			indexRib++;
		}
		c = getchar();
	}
	inf.countRibs = indexRib;

	return INFORMATION_READED;
}

ANSWER DFS(int vertex, ANSWER ans)
{
	int min = inf.countVertex;
	inf.vertex[vertex] = visited;
	countShadedVert++;
	ans.answer[ans.answerIndex++] = vertex;

	while (countShadedVert != inf.countVertex)
	{
		for (int i = 0; i < inf.countRibs; i++)
		{
			if (inf.ribs[i][0] == vertex && inf.vertex[inf.ribs[i][1]] == notVisited && inf.ribs[i][1] < min)
			{
				min = inf.ribs[i][1];
			}
			if (inf.ribs[i][1] == vertex && inf.vertex[inf.ribs[i][0]] == notVisited && inf.ribs[i][0] < min)
			{
				min = inf.ribs[i][0];
			}
		}
		if (min != inf.countVertex)
		{
			ans = DFS(min, ans);
			min = inf.countVertex;
		}
		else
		{
			return ans;
		}
	}
	return ans;
}

void clearMemory()
{
	free(inf.vertex);
	for (int i = 0; i < inf.countVertex * inf.countVertex; i++)
	{
		free(inf.ribs[i]);
	}
	free(inf.ribs);
}