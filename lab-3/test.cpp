#include "pch.h"

extern "C" {
#include "..\\C2_alg\pre_order.h"
#include "..\\C2_alg\pre_order.c"
}

TEST(DFS, DFS_1Dot_ReturnsCorrectAnswer) {

  int size = 1;
  int matrix[1];
  int result[1];
  int state[1];

  matrix[0] = 1;
  result[0] = -1;
  DepthFirstSearch(1, size, matrix, state, 0, &result);
  ASSERT_EQ(result[0], 0);
}

TEST(DFS, DFS_2MoreDots_ReturnCorrectAnswer) {

  int size = 2;
  int matrix[4];
  int result[2];
  int state[2];

  matrix[0] = 0;
  matrix[1] = 1;
  matrix[2] = 1;
  matrix[3] = 0;

  result[0] = -1;
  result[1] = -1;
  DepthFirstSearch(1, size, matrix, state, 0, &result);
  ASSERT_EQ(result[0], 0);
  ASSERT_EQ(result[1], 1);
}

TEST(DFS, DFS_IncorrectData_Returns0) {

  int size = 1;
  int matrix[1];
  int result[1];
  int state[1];

  result[0] = -1;

  ASSERT_EQ(DepthFirstSearch(1, size, matrix, state, 2, &result), 0);
}