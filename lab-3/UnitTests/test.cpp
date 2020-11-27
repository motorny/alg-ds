#include "pch.h"
#include "../GrafLib/GrafLib.h"

TEST(GetGraph, ZeroVertexCount_ReturnNULL) {
  EXPECT_EQ(GetGraph(0), (void*)0);
}

TEST(GetGraph, NegativeVertexCount_ReturnNULL) {
  EXPECT_EQ(GetGraph(-1), (void*)0);
}

TEST(GetGraph, TooBigVertexCount_ReturnNULL) {
  EXPECT_EQ(GetGraph(1000000000), (void*)0);
}

TEST(GetGraph, ValideVertexCount_ValidPointer) {
  Graph graph;
  graph = GetGraph(3);
  EXPECT_NE(graph, (void*)0);
  FreeGraph(graph);
}

TEST(AddConnectionToGraph, NullGraph_ReturnFALSE) {
  Graph graph;
  graph = NULL;
  EXPECT_EQ(AddConnectionToGraph(graph, 0, 1), FALSE);
}

TEST(AddConnectionToGraph, NegativeIndex_ReturnFALSE) {
  Graph graph;
  graph = GetGraph(3);
  EXPECT_EQ(AddConnectionToGraph(graph, 0, -1), FALSE);
  FreeGraph(graph);
}

TEST(AddConnectionToGraph, OutOfRengeIndex_ReturnFALSE) {
  Graph graph;
  graph = GetGraph(3);
  EXPECT_EQ(AddConnectionToGraph(graph, 0, 3), FALSE);
  FreeGraph(graph);
}

TEST(AddConnectionToGraph, DiferentIndexes_ReturnTRUE) {
  Graph graph;
  graph = GetGraph(3);
  EXPECT_EQ(AddConnectionToGraph(graph, 0, 1), TRUE);
  FreeGraph(graph);
}

TEST(AddConnectionToGraph, EqualIndexes_ReturnTRUE) {
  Graph graph;
  graph = GetGraph(3);
  EXPECT_EQ(AddConnectionToGraph(graph, 0, 0), TRUE);
  FreeGraph(graph);
}

TEST(PrintGraph, NullGraph_ReturnFALSE) {
  Graph graph;
  graph = NULL;
  EXPECT_EQ(PrintGraph(graph, stdout), FALSE);
}

TEST(PrintGraph, NoConnectionGraph_ReturnTrue) {
  Graph graph;
  graph = GetGraph(3);
  EXPECT_EQ(PrintGraph(graph, stdout), TRUE);
  //Output 0
  printf("\n");
  FreeGraph(graph);
}

TEST(PrintGraph, ConnectedGraph_ReturnTrue) {
  Graph graph;
  graph = GetGraph(3);

  AddConnectionToGraph(graph, 0, 2);
  AddConnectionToGraph(graph, 2, 1);

  EXPECT_EQ(PrintGraph(graph, stdout), TRUE);
  //Output 0 2 1
  printf("\n");
  FreeGraph(graph);
}

TEST(PrintGraph, NotConnectedGraph_ReturnTrue) {
  Graph graph;
  graph = GetGraph(4);

  AddConnectionToGraph(graph, 0, 1);
  AddConnectionToGraph(graph, 1, 3);

  EXPECT_EQ(PrintGraph(graph, stdout), TRUE);
  //Output 0 1 3
  printf("\n");
  FreeGraph(graph);
}

