#include "pch.h"

extern "C" {
#include "..\\LAB_C2\DFS.h"
#include "..\\LAB_C2\dfs.c"
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(DFS, DFS_1Vertex_retCorrectAnswer) {
	
	int size, * matrix, * result, * state, id;
	
	size = 1;

	matrix = (int*)malloc(sizeof(int) * (size) * (size));

	(matrix)[0] = 1;

	state = (int*)malloc(sizeof(int) * size);
	result = (int*)malloc(sizeof(int) * size);

	result[0] = -1;
	id = DepthFirstSearch(1, size, matrix, state, 0, &result);
	ASSERT_EQ(result[0], 0);

	if (matrix)
		free(matrix);
	if (state)
		free(state);
	if (result)
		free(result);
}

TEST(DFS, DFS_2MoreVertex_retCorrectAnswer) {
	int size, * matrix, * result, * state, id;

	size = 2;

	matrix = (int*)malloc(sizeof(int) * (size) * (size));

	matrix[0] = 0;
	matrix[1] = 1;
	matrix[2] = 1;
	matrix[3] = 0;

	state = (int*)malloc(sizeof(int) * size);
	result = (int*)malloc(sizeof(int) * size);

	result[0] = -1;
	result[0] = -1;
	id = DepthFirstSearch(1, size, matrix, state, 0, &result);
	ASSERT_EQ(result[0], 0);
	ASSERT_EQ(result[1], 1);

	if (matrix)
		free(matrix);
	if (state)
		free(state);
	if (result)
		free(result);
}

TEST(DFS, DFS_IncorrectData_ret0) {
	int size, * matrix, * result, * state, id;

	size = 1;

	matrix = (int*)malloc(sizeof(int) * (size) * (size));
	state = (int*)malloc(sizeof(int) * size);
	result = (int*)malloc(sizeof(int) * size);
	result[0] = -1;

	id = DepthFirstSearch(1, size, matrix, state, 2, &result);
	ASSERT_EQ(id, 0);

	if (matrix)
		free(matrix);
	if (state)
		free(state);
	if (result)
		free(result);
}