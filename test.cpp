#include "pch.h"

extern "C" {
#include "../graphbreadthfirstsearch/graphbreadthfirstsearch.c"
}

#define SIZE_OF_TEST_GRAPH 3

TEST(CreateQueue, NotNullPointerValidSize_ReturnTrue) {
	queue_t q;

	EXPECT_EQ(CreateQueue(&q, 1), true);
	EXPECT_EQ(q.size, 1);

	free(q.data);
}
TEST(CreateQueue, NotNullPointerInvalidSize_ReturnFalse) {
	queue_t q;

	EXPECT_EQ(CreateQueue(&q, -1), false);
}

TEST(Push, NotNullPointer_ReturnTrue) {
	queue_t q;
	int a = 1;

	q.size = 1;
	q.data = (int*)malloc(q.size * sizeof(int));
	q.start = 0;
	q.end = 0;

	EXPECT_EQ(Push(a, &q), true);
	EXPECT_EQ(q.data[0], a);

	free(q.data);
}
TEST(Push, PushWithoutCreate_ReturnFalse) {
	queue_t q;
	int a = 1;

	EXPECT_EQ(Push(a, &q), false);
}
TEST(Push, PushInFullQueue_ReturnFalse) {
	queue_t q;
	int a = 1, b = 2;
	
	q.size = 1;
	q.data = (int*)malloc(q.size * sizeof(int));
	q.start = 0;
	q.end = 1;
	q.data[0] = a;

	EXPECT_EQ(Push(b, &q), false);

	free(q.data);
}

TEST(Pop, ValidArguments_ReturnTrue) {
	queue_t q;
	int a = 1, b;
	
	q.size = 1;
	q.data = (int*)malloc(q.size * sizeof(int));
	q.start = 0;
	q.end = 1;
	q.data[0] = a;

	EXPECT_EQ(Pop(&q, &b), true);
	EXPECT_EQ(a, b);

	free(q.data);
}
TEST(Pop, PopFromEmptyQueue_ReturnFalse) {
	queue_t q;
	int a;

	q.size = 1;
	q.data = (int*)malloc(q.size * sizeof(int));
	q.start = 0;
	q.end = 0;

	EXPECT_EQ(Pop(&q, &a), false);

	free(q.data);
}

TEST(DeleteQueue, ValidArgument_ReturnTrue) {
	queue_t q;

	q.size = 1;
	q.data = (int*)malloc(q.size * sizeof(int));
	q.start = 0;
	q.end = 0;

	EXPECT_EQ(DeleteQueue(&q), true);
}

TEST(GraphBreadthFirstSearch, ValidArgument_ReturnTrue) {
	adj_list_t  list;
	int counter;

	list.numOfNodes = SIZE_OF_TEST_GRAPH;
	list.nodes = (node_t*)malloc(SIZE_OF_TEST_GRAPH * sizeof(node_t));
	for (counter = 0; counter < SIZE_OF_TEST_GRAPH; counter++) {
		list.nodes[counter].visited = NOT_VISITED;
		list.nodes[counter].neighbouringNodes = (int*)malloc(SIZE_OF_TEST_GRAPH * sizeof(int));
	}
	list.nodes[0].numOfNeighbouringNodes = 2;
	list.nodes[0].neighbouringNodes[0] = 1;
	list.nodes[0].neighbouringNodes[1] = 2;

	list.nodes[1].numOfNeighbouringNodes = 1;
	list.nodes[1].neighbouringNodes[0] = 0;

	list.nodes[2].numOfNeighbouringNodes = 1;
	list.nodes[2].neighbouringNodes[0] = 0;

	
	EXPECT_EQ(GraphBreadthFirstSearch(&list), true);

	for (counter = 0; counter < SIZE_OF_TEST_GRAPH; counter++)
		free(list.nodes[counter].neighbouringNodes);
	free(list.nodes);
}

TEST(FreeAdjList, ValidArgument_ReturnTrue) {
	adj_list_t  list;
	int counter;

	list.numOfNodes = SIZE_OF_TEST_GRAPH;
	list.nodes = (node_t*)malloc(SIZE_OF_TEST_GRAPH * sizeof(node_t));
	for (counter = 0; counter < SIZE_OF_TEST_GRAPH; counter++) {
		list.nodes[counter].visited = NOT_VISITED;
		list.nodes[counter].neighbouringNodes = (int*)malloc(SIZE_OF_TEST_GRAPH * sizeof(int));
	}
	list.nodes[0].numOfNeighbouringNodes = 2;
	list.nodes[0].neighbouringNodes[0] = 1;
	list.nodes[0].neighbouringNodes[1] = 2;

	list.nodes[1].numOfNeighbouringNodes = 1;
	list.nodes[1].neighbouringNodes[0] = 0;

	list.nodes[2].numOfNeighbouringNodes = 1;
	list.nodes[2].neighbouringNodes[0] = 0;


	EXPECT_EQ(FreeAdjList(&list), true);
}