#include "gtest/gtest.h"
#include "../DFS.c"

t_Graf *ConvertStrInGraf(const char *str) {
	int i = 0, a, b, error = 0;
	t_Graf *graf = (t_Graf *) malloc(sizeof(t_Graf));

	if ( str == NULL ) {
		free(graf);
		return NULL;
	}

	graf->size = atoi(str);
	if ( graf->size < 1 ) {
		free(graf);
		return NULL;
	}
	while ( str[i++] != '\n' );

	graf->matrix = (int **) malloc(sizeof(int **) * graf->size);
	if ( graf->matrix == NULL ) {
		free(graf);
		return NULL;
	}

	for ( a = 0; a < graf->size; a++ ) {
		graf->matrix[a] = (int *) malloc(sizeof(int *) * graf->size);
		if ( graf->matrix[a] == NULL ) {
			break;
		}
		for ( b = 0; b < graf->size; b++ ) {
			graf->matrix[a][b] = 0;
		}
	}

	if ( a < graf->size ) {
		for ( b = 0; b < a; b++ )
			free(graf->matrix[b]);
		free(graf->matrix);
		free(graf);
		return NULL;
	}

	while ( str[i] != '\0' ) {
		a = atoi(str + i);
		while ( str[i++] != ' ' );
		b = atoi(str + i);
		while ( str[i++] != '\n' );
		if ( a < graf->size && a >= 0 && b < graf->size && b >= 0 ) {
			graf->matrix[a][b] = 1;
			graf->matrix[b][a] = 1;
		}
	}

	return graf;
}

TEST(ConvertStrInGraf, NULLstr_NULL) {
	t_Graf *graf = ConvertStrInGraf(NULL);

	EXPECT_EQ(graf, (t_Graf *)NULL);

}

TEST(ConvertStrInGraf, CorrectStr_ReturnGraf) {
	t_Graf *graf = ConvertStrInGraf("3\n0 1\n1 2\n0 0\n");

	ASSERT_EQ(graf->size, 3);
	EXPECT_EQ(graf->matrix[0][0], 1);
	EXPECT_EQ(graf->matrix[0][1], 1);
	EXPECT_EQ(graf->matrix[0][2], 0);
	EXPECT_EQ(graf->matrix[1][0], 1);
	EXPECT_EQ(graf->matrix[1][1], 0);
	EXPECT_EQ(graf->matrix[1][2], 1);
	EXPECT_EQ(graf->matrix[2][0], 0);
	EXPECT_EQ(graf->matrix[2][1], 1);
	EXPECT_EQ(graf->matrix[2][2], 0);

	DelGraf(graf);
}

TEST(ConvertStrInGraf, NegativNumSize_NULL) {
	t_Graf *graf = ConvertStrInGraf("-2\n0 0\n0 1\n");

	EXPECT_EQ(graf, (t_Graf *) NULL);
}

TEST(ConvertStrInGraf, ZeroNumSize_NULL) {
	t_Graf *graf = ConvertStrInGraf("0\n0 0\n0 1\n");

	EXPECT_EQ(graf, (t_Graf *) NULL);
}


TEST(DFS, ExampleFromTask_str) {
	t_Graf *graf = ConvertStrInGraf("5\n0 1\n0 2\n1 2\n2 3\n2 4\n3 4\n");

	t_Answer ask = DFS(graf);
	ASSERT_EQ(ask.size, 5);
	EXPECT_EQ(ask.arr[0], 0);
	EXPECT_EQ(ask.arr[1], 1);
	EXPECT_EQ(ask.arr[2], 2);
	EXPECT_EQ(ask.arr[3], 3);
	EXPECT_EQ(ask.arr[4], 4);

	free(ask.arr);
	DelGraf(graf);
}

TEST(DFS, VertexLoop_str) {
	t_Graf *graf = ConvertStrInGraf("4\n0 1\n1 1\n0 3\n3 2\n");

	t_Answer ask = DFS(graf);
	ASSERT_EQ(ask.size, 4);
	EXPECT_EQ(ask.arr[0], 0);
	EXPECT_EQ(ask.arr[1], 1);
	EXPECT_EQ(ask.arr[2], 3);
	EXPECT_EQ(ask.arr[3], 2);

	free(ask.arr);
	DelGraf(graf);
}

TEST(DFS, VertexBreak_str) {
	t_Graf *graf = ConvertStrInGraf("4\n0 1\n3 2\n");

	t_Answer ask = DFS(graf);
	ASSERT_EQ(ask.size, 2);
	EXPECT_EQ(ask.arr[0], 0);
	EXPECT_EQ(ask.arr[1], 1);

	free(ask.arr);
	DelGraf(graf);
}

TEST(DFS, OneElement_str) {
	t_Graf *graf = ConvertStrInGraf("1\n");

	t_Answer ask = DFS(graf);
	ASSERT_EQ(ask.size, 1);
	EXPECT_EQ(ask.arr[0], 0);

	free(ask.arr);
	DelGraf(graf);
}