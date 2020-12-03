#include "pch.h"
#include "C:\Users\79523\source\repos\ALG3\ALG3\graph.c"

GRAPH* TestCoherentGraph() {
	GRAPH* test_graph = (GRAPH*)malloc(3 * sizeof(GRAPH));

	test_graph[0].num_of_edges = 1;
	test_graph[0].edges = (int*)malloc(sizeof(int));
	test_graph[0].edges[0] = 2;
	test_graph[0].status = NOT_VISITED;

	test_graph[1].num_of_edges = 1;
	test_graph[1].edges = (int*)malloc(sizeof(int));
	test_graph[1].edges[0] = 2;
	test_graph[1].status = NOT_VISITED;

	test_graph[2].num_of_edges = 2;
	test_graph[2].edges = (int*)malloc(2 * sizeof(int));
	test_graph[2].edges[0] = 0;
	test_graph[2].edges[1] = 1;
	test_graph[2].status = NOT_VISITED;

	return test_graph;
}

GRAPH* TestIncoherentGraph() {
	GRAPH* test_graph = (GRAPH*)malloc(4 * sizeof(GRAPH));

	test_graph[0].num_of_edges = 1;
	test_graph[0].edges = (int*)malloc(sizeof(int));
	test_graph[0].edges[0] = 3;
	test_graph[0].status = VISITED;

	test_graph[1].num_of_edges = 1;
	test_graph[1].edges = (int*)malloc(sizeof(int));
	test_graph[1].edges[0] = 3;
	test_graph[1].status = VISITED;

	test_graph[2].num_of_edges = 0;
	test_graph[2].edges = NULL;
	test_graph[2].status = NOT_VISITED;

	test_graph[3].num_of_edges = 2;
	test_graph[3].edges = (int*)malloc(2 * sizeof(int));
	test_graph[3].edges[0] = 0;
	test_graph[3].edges[1] = 1;
	test_graph[3].status = VISITED;

	return test_graph;
}

TEST(InitGraph, IncorrectSize) {
	EXPECT_EQ(InitGraph(-1), (GRAPH*)NULL);
}

TEST(InitGraph, InitGraphValid) {
	GRAPH* test_graph = InitGraph(3);
	EXPECT_EQ(test_graph[0].num_of_edges, 0);
	EXPECT_EQ(test_graph[1].num_of_edges, 0);
	EXPECT_EQ(test_graph[2].num_of_edges, 0);
	EXPECT_EQ(test_graph[0].status, NOT_VISITED);
	EXPECT_EQ(test_graph[1].status, NOT_VISITED);
	EXPECT_EQ(test_graph[2].status, NOT_VISITED);
	FreeGraph(test_graph, 3);
}

TEST(DFS, CorrectAnswer) {
	GRAPH* test_graph = TestCoherentGraph();
	int* summary = (int*)malloc(3 * sizeof(int));
	int order = 0;
	int vertex = 0;
	DFS(test_graph, summary, &order, vertex);
	EXPECT_EQ(summary[0], 0);
	EXPECT_EQ(summary[1], 2);
	EXPECT_EQ(summary[2], 1);
	FreeGraph(test_graph, 3);
	free(summary);
}

TEST(CheckIncoherence, CorrectWork) {
	GRAPH* test_graph = TestIncoherentGraph();
	int* summary = (int*)malloc(4 * sizeof(int));
	summary[0] = 0;
	summary[1] = 3;
	summary[2] = 1;
	int order = 3;
	CheckIncoherence(test_graph, summary, &order, 4);
	EXPECT_EQ(summary[3], 2);
	FreeGraph(test_graph, 4);
	free(summary);
}

