#include "pch.h"
extern "C" {
#include "..//Lab_C1/Lab_C1.c"
}

TEST(DFS_OneElement, DFS_RightAnswer) {
	graph_t* graph;
	int numvertices = 1;
	graph = Creategraph(numvertices);
	graph->adjlists[0].peak = 0;
	graph->adjlists[0].next = NULL;
	numbers = (int*)malloc(sizeof(int));
	DFS(graph, graph->adjlists);
	EXPECT_EQ(numbers[0], graph->adjlists[0].peak);
	Destroy(graph);
}



TEST(DFS_ThreeElemWithoutAdjacentVertexes, DFS_Zero) {
	graph_t* graph;
	int numvertices = 3;
	graph = Creategraph(numvertices);
	graph->adjlists[0].peak = 0;
	graph->adjlists[0].next = NULL;

	graph->adjlists[1].peak = 1;
	graph->adjlists[1].next = NULL;

	graph->adjlists[2].peak = 2;
	graph->adjlists[2].next = NULL;
	DFS(graph, graph->adjlists);
	EXPECT_EQ(numbers[0], 0);
	Destroy(graph);
}

