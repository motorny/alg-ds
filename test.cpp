#include "pch.h"
extern"C"{
#include"graph.h"
}

TEST(Create_NUllstr, returnNULL) {
	EXPECT_TRUE(Create(NULL) == NULL);
}

TEST(Create_ValidStr, returnPtr) {
	EXPECT_TRUE(Create("2\n0 1\n") != NULL);
}

TEST(Dfs_NULLMatrix, return0) {
	matrix_t* matrix = NULL;
	int* arr = (int*)malloc(2 * sizeof(int));
  EXPECT_EQ(Dfs(matrix,1,arr), 0);
  free(arr);
}

TEST(Dfs_Negativevertex, return0) {
	matrix_t* matrix = NULL;
	matrix = Create("2\n0 1\n");
	int* arr = (int*)malloc(2 * sizeof(int));
	EXPECT_EQ(Dfs(matrix, -1, arr), 0);
	free(arr);
}

TEST(Dfs_Nullarr, return0) {
	matrix_t* matrix = NULL;
	matrix = Create("2\n0 1\n");
	int* arr = NULL;
	EXPECT_EQ(Dfs(matrix, -1, arr), 0);
}

TEST(Dfs_ValidInput, return1) {
	matrix_t* matrix = NULL;
	matrix = Create("2\n0 1\n");
	int* arr = (int*)malloc(2 * sizeof(int));
	EXPECT_EQ(Dfs(matrix, 0, arr), 1);
	free(arr);
}

TEST(Destroy_NULLmtx, return0) {
	matrix_t* matrix = NULL;
	EXPECT_EQ(Destroy(matrix), 0);
}

TEST(Destroy_Validmtx, return1) {
	matrix_t* matrix = NULL;
	matrix = Create("2\n0 1\n");
	EXPECT_EQ(Destroy(matrix), 1);

}