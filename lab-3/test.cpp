#include "pch.h"

extern "C" {
#include "../Lab-C-1/Lab-C-1.c"
}

//                 |------>------|
//  building graph |             |
//                [0] -> [1] -> [2]

graph_t* CreateSimpleDirectedGraph() {
  const int size = 3;
  elem_t* temp;
  graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
  if (!graph)
    return NULL;
  graph->numofvertexes = size;
  graph->lists = (elem_t*)malloc(size * sizeof(elem_t));
  if (!graph->lists) {
    DestroyGraph(graph);
    return NULL;
  }

  graph->lists[0].next = (elem_t*)malloc(sizeof(elem_t));
  if (!graph->lists[0].next) {
    DestroyGraph(graph);
    return NULL;
  }
  temp = graph->lists[0].next;
  temp->vertex = 1;
  temp->next = (elem_t*)malloc(sizeof(elem_t));
  if (!temp->next) {
    DestroyGraph(graph);
    return NULL;
  }
  temp = temp->next;
  temp->vertex = 2;
  temp->next = NULL;

  graph->lists[1].next = (elem_t*)malloc(sizeof(elem_t));
  if (!graph->lists[1].next) {
    DestroyGraph(graph);
    return NULL;
  }
  temp = graph->lists[1].next;
  temp->vertex = 2;
  temp->next = NULL;

  graph->lists[2].next = NULL;

  return graph;
}

graph_t* CreateSimpleUndirectedGraph() {
  const int size = 3;
  elem_t* temp;
  graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
  if (!graph)
    return NULL;
  graph->numofvertexes = size;
  graph->lists = (elem_t*)malloc(size * sizeof(elem_t));
  if (!graph->lists) {
    DestroyGraph(graph);
    return NULL;
  }

  graph->lists[0].next = (elem_t*)malloc(sizeof(elem_t));
  if (!graph->lists[0].next) {
    DestroyGraph(graph);
    return NULL;
  }
  temp = graph->lists[0].next;
  temp->vertex = 1;
  temp->next = (elem_t*)malloc(sizeof(elem_t));
  if (!temp->next) {
    DestroyGraph(graph);
    return NULL;
  }

  temp = temp->next;
  temp->vertex = 2;
  temp->next = NULL;

  graph->lists[1].next = (elem_t*)malloc(sizeof(elem_t));
  if (!graph->lists[1].next) {
    DestroyGraph(graph);
    return NULL;
  }
  temp = graph->lists[1].next;
  temp->vertex = 0;
  temp->next = (elem_t*)malloc(sizeof(elem_t));
  if (!temp->next) {
    DestroyGraph(graph);
    return NULL;
  }
  temp = temp->next;
  temp->vertex = 2;
  temp->next = NULL;

  graph->lists[2].next = (elem_t*)malloc(sizeof(elem_t));
  if (!graph->lists[2].next) {
    DestroyGraph(graph);
    return NULL;
  }
  temp = graph->lists[2].next;
  temp->vertex = 0;
  temp->next = (elem_t*)malloc(sizeof(elem_t));
  if (!temp->next) {
    DestroyGraph(graph);
    return NULL;
  }
  temp = temp->next;
  temp->vertex = 1;
  temp->next = NULL;

  return graph;
}

//in main fuction DFS() will not be called if <=0 vertexes. Check 1 vertex
TEST(DFS, DFS_OneVertex_ValidAnswer) {
  const int size = 1;
  graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
  graph->numofvertexes = size;

  graph->lists = (elem_t*)malloc(size * sizeof(elem_t));
  graph->lists[0].vertex = 0;
  graph->lists[0].next = NULL;

  DFS(graph, &(graph->lists[0]));

  EXPECT_EQ(graphOrder.top, 1);
  EXPECT_EQ(graphOrder.numbers[0], graph->lists[0].vertex);

  DestroyGraph(graph);
}

//  Creating graph: 
// [0]      [1]->[2]
TEST(DFS, DFS_ZeroVertexIsAlone_DFSReturnsOnlyOneVertex) {
  const int size = 3;
  graph_t* graph = (graph_t*)malloc(sizeof(graph_t));

  graph->numofvertexes = size;

  graph->lists = (elem_t*)malloc(size * sizeof(elem_t));

  graph->lists[0].vertex = 0;
  graph->lists[0].next = NULL;

  graph->lists[1].vertex = 1;
  graph->lists[1].next = (elem_t*)malloc(sizeof(elem_t));
  graph->lists[1].next->vertex = 2;
  graph->lists[1].next->next = NULL;

  graph->lists[2].vertex = 2;
  graph->lists[2].next = (elem_t*)malloc(sizeof(elem_t));
  graph->lists[2].next->vertex = 1;
  graph->lists[2].next->next = NULL;

  DFS(graph, &(graph->lists[0]));

  EXPECT_EQ(graphOrder.top, 1);
  EXPECT_EQ(graphOrder.numbers[0], 0);

  DestroyGraph(graph);
}

TEST(DFS, DFS_DfsInUndirectedGraph_ReturnSuccess) {
  int i;
  graph_t* graph = CreateSimpleUndirectedGraph();

  DFS(graph, &(graph->lists[0]));

  for (i = 0; i < graphOrder.top; ++i)
    EXPECT_EQ(graphOrder.numbers[i], i); //[0]->[1]->[2]

  DestroyGraph(graph);
}


TEST(UndirectedGraphCreate, UndirectedGraphCreate_CreateFromDirected_TheyAreEqual) {
  int i;
  graph_t* graph1 = CreateSimpleDirectedGraph();
  graph_t* graph2 = CreateSimpleUndirectedGraph();

  graph1 = UndirectedGraphCreate(graph1);

  EXPECT_EQ(graph1->numofvertexes, graph2->numofvertexes);

  for (i = 0; i < graph1->numofvertexes; ++i) {
    EXPECT_EQ(graph1->lists[i].vertex, graph2->lists[i].vertex);
    EXPECT_EQ(graph1->lists[i].next->vertex, graph2->lists[i].next->vertex);
    EXPECT_EQ(graph1->lists[i].next->next->vertex, graph2->lists[i].next->next->vertex);
    EXPECT_EQ(graph1->lists[i].next->next->next, graph2->lists[i].next->next->next); //NULL
  }
  DestroyGraph(graph1);
  DestroyGraph(graph2);
}
