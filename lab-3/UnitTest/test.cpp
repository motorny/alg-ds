#include "gtest/gtest.h"
#include "../DFS.c"
#include "../DFS.h"

TEST(ConvertsList2Matrix, NULLstr_returnERROR) {
	graph mat;

	EXPECT_EQ(ConvertsList2Matrix(NULL, &mat), ERROR);

}

TEST(ConvertsList2Matrix, NULLmat_returnERROR) {
	char str[] = "1 \n 2 1\n";

	EXPECT_EQ(ConvertsList2Matrix(str, NULL), ERROR);
}

TEST(ConvertsList2Matrix, EmptyStr_returnERROR) {
	graph mat;
	char str[] = " ";

	EXPECT_EQ(ConvertsList2Matrix(str, &mat), ERROR);
}

TEST(ConvertsList2Matrix, Node1_returnSUCCESS) {
	graph mat;
	char str[] = "1\n";

	ASSERT_EQ(ConvertsList2Matrix(str, &mat), SUCCESS);
	EXPECT_EQ(mat.size, 1);
	ASSERT_TRUE(mat.matrix != NULL);
	ASSERT_TRUE(mat.matrix[0] != NULL);
	EXPECT_EQ(mat.matrix[0][0], 0);

	DestroyMatrix(&mat);
}

TEST(ConvertsList2Matrix, Node3_returnSUCCESS) {
	graph mat;
	char str[] = "1 3 2\n2 2\n3 2\n";

	ASSERT_EQ(ConvertsList2Matrix(str, &mat), SUCCESS);
	EXPECT_EQ(mat.size, 3);
	ASSERT_TRUE(mat.matrix != NULL);
	ASSERT_TRUE(mat.matrix[0] != NULL);
	EXPECT_EQ(mat.matrix[0][0], 0);
	EXPECT_EQ(mat.matrix[0][1], 1);
	EXPECT_EQ(mat.matrix[0][2], 1);
	ASSERT_TRUE(mat.matrix[1] != NULL);
	EXPECT_EQ(mat.matrix[1][0], 0);
	EXPECT_EQ(mat.matrix[1][1], 1);
	EXPECT_EQ(mat.matrix[1][2], 0);
	ASSERT_TRUE(mat.matrix[2] != NULL);
	EXPECT_EQ(mat.matrix[2][0], 0);
	EXPECT_EQ(mat.matrix[2][1], 1);
	EXPECT_EQ(mat.matrix[2][2], 0);

	DestroyMatrix(&mat);
}

TEST(ConvertsList2Matrix, BadData_returnERROR) {
	graph mat;
	char str[] = "1\n5 3\n 2 3\n";

	ASSERT_EQ(ConvertsList2Matrix(str, &mat), ERROR);

}