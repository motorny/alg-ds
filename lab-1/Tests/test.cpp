#include "pch.h"

extern "C" {
#include "../Lab_3/Header.h"
#include "../LAB_3/LAB_3.c"
}

TEST(One_Element, DFS) {
	graph_t* graph;
	int size = 1;
	graph = Creategraph(size);

	graph->list[0].top = 0;
	graph->list[0].next = NULL;

	Dop.nums = (int*)malloc(sizeof(int));
	DFS(graph, graph->list);
	EXPECT_EQ(Dop.nums[0], graph->list[0].top);
	Destroy(graph);
}

TEST(Five_Elements, DFS) {
	graph_t* graph;
	int size = 5;
	graph = Creategraph(size);

	graph->list[0].top = 0;
	graph->list[0].next = NULL;

	graph->list[1].top = 1;
	graph->list[1].next = NULL;

	graph->list[2].top = 2;
	graph->list[2].next = NULL;

	graph->list[3].top = 3;
	graph->list[3].next = NULL;

	graph->list[4].top = 4;
	graph->list[4].next = NULL;

	DFS(graph, graph->list);
	EXPECT_EQ(Dop.nums[0], 0);
	Destroy(graph);
}