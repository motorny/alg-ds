#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "main.h"

vertex_t* CreateList(int arr[], int length) {
  vertex_t* listBegin = (vertex_t*)malloc(sizeof(vertex_t));
  vertex_t* curElement = listBegin;
  int i;
  assert(listBegin);
  listBegin->number = arr[0];
  for (i = 1; i < length; i++) {
    curElement->vertex = (vertex_t*)malloc(sizeof(vertex_t));
    assert(curElement->vertex);
    curElement = curElement->vertex;
    curElement->number = arr[i];
  }
  curElement->vertex = NULL;
  return listBegin;
}

TEST(ReadAdjList, returnTrueADJList) {
  adjList_t* adjLists = (adjList_t*)malloc(sizeof(adjList_t) * 10);
  int error;
  assert(adjLists);
  printf("0 5 7 8 9\n1 3 5 6 8 9\n2 4\n3 6 8 9\n4 7 8\n5 7\n6 7\n7 8\n8 9\n9\n");
  error = ReadAdjList(adjLists, 10);

  EXPECT_EQ(adjLists[0].begin->number, 5);
  EXPECT_EQ(adjLists[0].begin->vertex->number, 7);
  EXPECT_EQ(adjLists[0].begin->vertex->vertex->number, 8);
  EXPECT_EQ(adjLists[0].begin->vertex->vertex->vertex->number, 9);

  EXPECT_EQ(adjLists[7].begin->number, 0);
  EXPECT_EQ(adjLists[7].begin->vertex->number, 2);
  EXPECT_EQ(adjLists[7].begin->vertex->vertex->number, 4);
  EXPECT_EQ(adjLists[7].begin->vertex->vertex->vertex->number, 5);
  EXPECT_EQ(adjLists[7].begin->vertex->vertex->vertex->vertex->number, 6);
  EXPECT_EQ(adjLists[7].begin->vertex->vertex->vertex->vertex->vertex->number, 8);
}

TEST(DFS, returnDFS) {
  adjList_t* adjLists = (adjList_t*)malloc(sizeof(adjList_t) * 11);
  int lengthDFS;
  int* dfs;
  int arr[][3] = { {1, 2}, {0, 3, 4}, {0, 7}, {1}, {1, 5, 6}, {4}, {4}, {2, 8, 9}, {7, 10}, {7}, {8} };
  assert(adjLists);
  adjLists[0].begin = CreateList(arr[0], 2);
  adjLists[1].begin = CreateList(arr[1], 3);
  adjLists[2].begin = CreateList(arr[2], 2);
  adjLists[3].begin = CreateList(arr[3], 1);
  adjLists[4].begin = CreateList(arr[4], 3);
  adjLists[5].begin = CreateList(arr[5], 1);
  adjLists[6].begin = CreateList(arr[6], 1);
  adjLists[7].begin = CreateList(arr[7], 3);
  adjLists[8].begin = CreateList(arr[8], 2);
  adjLists[9].begin = CreateList(arr[9], 1);
  adjLists[10].begin = CreateList(arr[10], 1);
  dfs = DFS(adjLists, 11, &lengthDFS);
  EXPECT_EQ(dfs[0], 0);
  EXPECT_EQ(dfs[1], 1);
  EXPECT_EQ(dfs[2], 3);
  EXPECT_EQ(dfs[3], 4);
  EXPECT_EQ(dfs[4], 5);
  EXPECT_EQ(dfs[5], 6);
  EXPECT_EQ(dfs[6], 2);
  EXPECT_EQ(dfs[7], 7);
  EXPECT_EQ(dfs[8], 8);
  EXPECT_EQ(dfs[9], 10);
  EXPECT_EQ(dfs[10], 9);
}