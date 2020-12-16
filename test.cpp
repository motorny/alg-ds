#pragma warning(disable:4996)

#include "pch.h"
extern "C"
{
#include "graph.h"
}

TEST(TestDFS, TestGood) {

	list_t* testGraph = (list_t*)calloc(3, sizeof(list_t));
	list_t testGraph0 = { 2, 0, NULL };
	list_t testGraph1 = { 2, 0, NULL };
	list_t testGraph2 = { 2, 0, NULL };
	int res[] = { 0,1,2 };
	int* testRes = (int*)calloc(3, sizeof(int));
	int size = 0;

	testGraph0.edg = (int*)calloc(2, sizeof(int));
	testGraph0.edg[0] = 1;
	testGraph0.edg[1] = 2;
	testGraph1.edg = (int*)calloc(2, sizeof(int));
	testGraph1.edg[0] = 0;
	testGraph1.edg[1] = 2;
	testGraph2.edg = (int*)calloc(2, sizeof(int));
	testGraph2.edg[0] = 0;
	testGraph2.edg[1] = 1;

	testGraph[0] = testGraph0;
	testGraph[1] = testGraph1;
	testGraph[2] = testGraph2;

	DFS(testGraph, 0, testRes, &size);

	EXPECT_EQ(res[0], testRes[0]);
	EXPECT_EQ(res[1], testRes[1]);
	EXPECT_EQ(res[2], testRes[2]);

	free(testRes);
	DeleteGraph(testGraph, 3);
}

TEST(TestDeleteGraph, TestNotGood) {

	list_t* testGraph = NULL;
	EXPECT_EQ(0, DeleteGraph(testGraph, 3));
}

TEST(TestDeleteGraph, TestGood) {

	list_t* testGraph = (list_t*)calloc(3, sizeof(list_t));
	list_t graph0 = { 2, 0, NULL };
	list_t graph1 = { 2, 0, NULL };
	list_t graph2 = { 2, 0, NULL };

	graph0.edg = (int*)calloc(2, sizeof(int));
	graph0.edg[0] = 1;
	graph0.edg[1] = 2;
	graph1.edg = (int*)calloc(2, sizeof(int));
	graph1.edg[0] = 0;
	graph1.edg[1] = 2;
	graph2.edg = (int*)calloc(2, sizeof(int));
	graph2.edg[0] = 0;
	graph2.edg[1] = 1;

	testGraph[0] = graph0;
	testGraph[1] = graph1;
	testGraph[2] = graph2;

	EXPECT_EQ(1, DeleteGraph(testGraph, 3));
}