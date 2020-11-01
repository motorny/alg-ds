#include "pch.h"
#include "..\LabCGraph\DFS.c"

TEST(DFS, emptyGraph_Return2)
{
	int result = readGeneralInf();
	ASSERT_EQ(2, result);
}

TEST(DFS, OneVertex_ReturnAnswer0)
{
	ANSWER ans;
	ans.answer = (int*)malloc(sizeof(int));
	inf.countVertex = 1;
	inf.countRibs = 0;
	DFS(0, ans);
	ASSERT_EQ(0, ans.answer[0]);
	free(ans.answer);
}

TEST(DFS, ManyVertex_ReturnTrueAnswer)
{
	ANSWER ans;
	ans.answer = (int*)malloc(5 * sizeof(int));
	inf.countRibs = 6;
	inf.countVertex = 5;
	inf.ribs = (int**)malloc(6 * sizeof(int*));
	for (int i = 0; i < 6; i++)
	{
		inf.ribs[i] = (int*)malloc(2 * sizeof(int));
	}
	inf.vertex = (STATE*)malloc(5 * sizeof(int));
	for (int i = 0; i < 5; i++)
	{
		inf.vertex[i] = notVisited;
	}
	inf.ribs[0][0] = 0;
	inf.ribs[0][1] = 1;
	inf.ribs[1][0] = 0;
	inf.ribs[1][1] = 2;
	inf.ribs[2][0] = 1;
	inf.ribs[2][1] = 2;
	inf.ribs[3][0] = 2;
	inf.ribs[3][1] = 3;
	inf.ribs[4][0] = 2;
	inf.ribs[4][1] = 4;
	inf.ribs[5][0] = 3;
	inf.ribs[5][1] = 4;
	ans = DFS(0, ans);
	ASSERT_EQ(0, ans.answer[0]);
	ASSERT_EQ(1, ans.answer[1]);
	ASSERT_EQ(2, ans.answer[2]);
	ASSERT_EQ(3, ans.answer[3]);
	ASSERT_EQ(4, ans.answer[4]);

	free(inf.vertex);
	for (int i = 0; i < inf.countVertex * inf.countVertex; i++)
	{
		free(inf.ribs[i]);
	}
	free(inf.ribs);
	free(ans.answer);
}