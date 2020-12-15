#include "pch.h"
#include "..\LabC.c"

TEST(InitGraph, NegSize_ReturnNULL) {
	ASSERT_EQ(InitGraph(-1), (adjList_t*)NULL);
}

TEST(InitGraph, 4Integer_ReturnsCorrectAdjListWithVertexes) {
	adjList_t* gr;
	ASSERT_TRUE((gr = InitGraph(4)) != (adjList_t*)NULL);
	ASSERT_EQ(gr[0].num, 0);
	ASSERT_EQ(gr[1].num, 1);
	ASSERT_EQ(gr[2].num, 2);
	ASSERT_EQ(gr[3].num, 3);
	ASSERT_EQ(gr[0].isVisited, FALSE);
	ASSERT_EQ(gr[1].isVisited, FALSE);
	ASSERT_EQ(gr[2].isVisited, FALSE);
	ASSERT_EQ(gr[3].isVisited, FALSE);
	ASSERT_EQ(gr[0].next, (adjList_t*)NULL);
	ASSERT_EQ(gr[1].next, (adjList_t*)NULL);
	ASSERT_EQ(gr[2].next, (adjList_t*)NULL);
	ASSERT_EQ(gr[3].next, (adjList_t*)NULL);
	FreeGraph(gr, 4);
}

TEST(FillGraph, 4Integeres_Add2RibsInGraph) {
	adjList_t* gr = InitGraph(4);
	FillGraph(gr, 0, 1);
	FillGraph(gr, 0, 2);
	ASSERT_EQ(gr[0].next->num, 1);
	ASSERT_EQ(gr[0].next->next->num, 2);
	ASSERT_EQ(gr[0].next->next->next, (adjList_t*)NULL);
	ASSERT_EQ(gr[1].next->num, 0);
	ASSERT_EQ(gr[1].next->next, (adjList_t*)NULL);
	ASSERT_EQ(gr[2].next->num, 0);
	ASSERT_EQ(gr[2].next->next, (adjList_t*)NULL);
	ASSERT_EQ(gr[3].next, (adjList_t*)NULL);
	FreeGraph(gr, 4);
}

TEST(BFS, CorrectValues_CorrectVertexSequence) {
	adjList_t* gr = InitGraph(5);
	int visited[5], queue[5];
	FillGraph(gr, 0, 4);
	FillGraph(gr, 1, 3);
	FillGraph(gr, 1, 4);
	BFS(gr, 0, visited, queue);

	ASSERT_EQ(visited[0], 0);
	ASSERT_EQ(visited[1], 4);
	ASSERT_EQ(visited[2], 1);
	ASSERT_EQ(visited[3], 3);
	FreeGraph(gr, 4);
}