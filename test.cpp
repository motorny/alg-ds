#include "pch.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

extern "C" {
  #include "C2.h"
}

TEST(TestCreateGraph, GraphOfTwo_NodesAreEmpty) {
  node_t* nodes;
  int err = 0;
  int i, n = 2;

  nodes = CreateGraph(n, &err);

  for (i = 0; i < n; i++) {
    ASSERT_EQ(0, nodes[i].edgesQ);
    ASSERT_EQ(WHITE, nodes[i].color);
    ASSERT_EQ(NULL, nodes[i].edges);
  }

  DestroyGraph(nodes, n);
}

TEST(TestAddEdge, AddToGraphOfTwo_TwoAreLinked) {
  node_t* nodes;
  int err = 0;
  int i, n = 2;

  nodes = (node_t*)malloc(sizeof(node_t) * n);
  for (i = 0; i < n; i++) {
    nodes[i].edgesQ = 0;
    nodes[i].color = WHITE;
    nodes[i].edges = NULL;
  }

  AddEdge(&nodes[0], &nodes[1], &err);
  for (i = 0; i < n; i++) {
    ASSERT_EQ(1, nodes[i].edgesQ);
    ASSERT_EQ(WHITE, nodes[i].color);
    ASSERT_EQ(NULL, nodes[i].edges->next);
  }
  ASSERT_EQ(&nodes[1], nodes[0].edges->node);
  ASSERT_EQ(&nodes[0], nodes[1].edges->node);

  DestroyGraph(nodes, n);
}

TEST(TestAddEdge, AddToGraphOfThree_ThreeAreLinked) {
  node_t* nodes;
  int err = 0;
  int i, n = 3;

  nodes = (node_t*)malloc(sizeof(node_t) * n);
  for (i = 0; i < n; i++) {
    nodes[i].edgesQ = 0;
    nodes[i].color = WHITE;
    nodes[i].edges = NULL;
  }

  AddEdge(&nodes[0], &nodes[1], &err);
  AddEdge(&nodes[1], &nodes[2], &err);
  for (i = 0; i < n; i++)
    ASSERT_EQ(WHITE, nodes[i].color);

  ASSERT_EQ(1, nodes[0].edgesQ);
  ASSERT_EQ(&nodes[1], nodes[0].edges->node);
  ASSERT_EQ(NULL, nodes[0].edges->next);

  ASSERT_EQ(2, nodes[1].edgesQ);
  ASSERT_EQ(&nodes[0], nodes[1].edges->node);
  ASSERT_EQ(&nodes[2], nodes[1].edges->next->node);
  ASSERT_EQ(NULL, nodes[1].edges->next->next);

  ASSERT_EQ(1, nodes[2].edgesQ);
  ASSERT_EQ(&nodes[1], nodes[2].edges->node);
  ASSERT_EQ(NULL, nodes[2].edges->next);

  DestroyGraph(nodes, n);
}

TEST(TestRunDFS, UnlinkedGraph_SequenceCorrect) {
  node_t* nodes;
  int* ans;
  int err = 0;
  int i, n = 4;

  ans = (int*)malloc(sizeof(int) * n);
  nodes = CreateGraph(n, &err);
  AddEdge(&nodes[0], &nodes[1], &err);
  AddEdge(&nodes[2], &nodes[3], &err);

  RunDFS(ans, nodes, n);

  for (i = 0; i < n; i++)
    ASSERT_EQ(i, ans[i]);

  DestroyGraph(nodes, n);
  free(ans);
}

TEST(TestRunDFS, ExampleFromAssignment_SequenceCorrect) {
  node_t* nodes;
  int* ans;
  int err = 0;
  int i, n = 5;

  ans = (int*)malloc(sizeof(int) * n);
  nodes = CreateGraph(n, &err);
  AddEdge(&nodes[0], &nodes[1], &err);
  AddEdge(&nodes[0], &nodes[2], &err);
  AddEdge(&nodes[1], &nodes[2], &err);
  AddEdge(&nodes[2], &nodes[3], &err);
  AddEdge(&nodes[2], &nodes[4], &err);
  AddEdge(&nodes[3], &nodes[4], &err);

  RunDFS(ans, nodes, n);

  for (i = 0; i < n; i++)
    ASSERT_EQ(i, ans[i]);

  DestroyGraph(nodes, n);
  free(ans);
}

int main(int argc, char** argv) {

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}