#include "pch.h"

extern "C" {
#include "DFS.h"
}

TEST(DFS, DFS_EmptyGraph_returnNULL) {
  char str[] = "  *";
  int graphSize, * graphMatr, answer;

  answer = ParseStrLikeSTDIN(str, &graphSize, &graphMatr);
  ASSERT_EQ(answer, 0);
}

TEST(DFS, DFS_1NodeGraph_returnAnswerVector) {
  char str[] = "1\n*";
  int graphSize, * graphMatr, answer, *wasThereNodes, *answerVector;

  answer = ParseStrLikeSTDIN(str, &graphSize, &graphMatr);
  ASSERT_EQ(answer, 1);

  wasThereNodes = (int *)malloc(sizeof(int) * graphSize);
  answerVector = (int *)malloc(sizeof(int) * graphSize);
  answerVector[0] = -1;
  DFS(graphSize, graphMatr, wasThereNodes, 0, &answerVector);
  ASSERT_EQ(answerVector[0], 0);

  free(wasThereNodes);
  free(graphMatr);
  free(answerVector);
}

TEST(DFS, DFS_2andMoreNodeGraph_returnAnswerVector) {
  char str[] = "2\n0 1 \n*";
  int graphSize, * graphMatr, answer, * wasThereNodes, * answerVector;

  answer = ParseStrLikeSTDIN(str, &graphSize, &graphMatr);
  ASSERT_EQ(answer, 1);

  wasThereNodes = (int*)malloc(sizeof(int) * graphSize);
  answerVector = (int*)malloc(sizeof(int) * graphSize);

  DFS(graphSize, graphMatr, wasThereNodes, 0, &answerVector);
  answerVector[0] = answerVector[1] = -1;
  ASSERT_EQ(answerVector[0], 0);
  ASSERT_EQ(answerVector[1], 1);

  free(wasThereNodes);
  free(graphMatr);
  free(answerVector);
}

TEST(DFS, DFS_BadDataInSize_returnNULL) {
  char str[] = "BAD DATA!\n0 1 \t\n*";
  int graphSize, * graphMatr, answer;

  answer = ParseStrLikeSTDIN(str, &graphSize, &graphMatr);
  ASSERT_EQ(answer, 0);
}

TEST(DFS, DFS_BadDataInPairsNodes_returnNULL) {
  char str[] = "5\n0 1 \t\nBAD DATA!\t\n4 5\t\n*";
  int graphSize, * graphMatr, answer;

  answer = ParseStrLikeSTDIN(str, &graphSize, &graphMatr);
  ASSERT_EQ(answer, 0);
}
