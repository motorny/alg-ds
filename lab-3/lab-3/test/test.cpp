#include "pch.h"
#include "..\lab-3\graph.h"
//#include "..\lab-3\graphDFS.cpp"

const int SIMPLE_GRAPH_SIZE = 3;

node_t* CreateSimpleGraph() {
	node_t firstNode = { NULL,2,N_VISITED };
	node_t secondNode = { NULL, 2,N_VISITED };
	node_t thirdNode = { NULL, 2,N_VISITED };

	firstNode.edges = (int*)calloc(2, sizeof(int));
	secondNode.edges = (int*)calloc(2, sizeof(int));
	thirdNode.edges = (int*)calloc(2, sizeof(int));

	firstNode.edges[0] = 1;
	firstNode.edges[1] = 2;

	secondNode.edges[0] = 0;
	secondNode.edges[1] = 2;

	thirdNode.edges[0] = 0;
	thirdNode.edges[1] = 1;

	node_t* graph = (node_t*)calloc(3, sizeof(node_t));
	graph[0] = firstNode;
	graph[1] = secondNode;
	graph[2] = thirdNode;
	return graph;
}



TEST(TestGraphDFS, CorrectDfsArrayReturnValidVal) {
	node_t* graph = CreateSimpleGraph();
	int result[] = {0,1,2};
	int* resultDFS = (int*)calloc(3,sizeof(int));
	int resultSize = 0;
	DFS(graph, 0, resultDFS, &resultSize);
	EXPECT_EQ(result[0], resultDFS[0]);
	EXPECT_EQ(result[1], resultDFS[1]);
	EXPECT_EQ(result[2], resultDFS[2]);
	free(resultDFS);
	GraphFree(graph, SIMPLE_GRAPH_SIZE);
}


TEST(TestGraphFree, EmptyGraphPointerReturnNull) {
	node_t* null = NULL;
	EXPECT_EQ(EMPTY_POINTER,GraphFree(null,SIMPLE_GRAPH_SIZE));
}

TEST(TestGraphFree, CorrectWorkReturnSuccess) {
	node_t* graph = CreateSimpleGraph();
	EXPECT_EQ(SUCCESS, GraphFree(graph, SIMPLE_GRAPH_SIZE));
}