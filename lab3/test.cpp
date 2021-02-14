#include "gtest/gtest.h"
#include "pch.h"

extern "C"
{
#include "Lab3.h"
}


TEST(Create_Q, Size_SUCCESS) {
	queue_t q;

	EXPECT_EQ(CreateQ(&q, 10), SUCCESS);
	DeleteQ(&q);
}

TEST(Create_Q, Size_FAIL) {
	queue_t q;

	EXPECT_EQ(CreateQ(&q, 0), FAIL);
	EXPECT_EQ(CreateQ(&q, -1), FAIL);
}

TEST(Add_In_Tail, Var_SUCCESS) {
	int arr[1];
	queue_t q;
	q.arr = arr;
	q.size = 1;
	q.head = 0;
	q.tail = 0;

	EXPECT_EQ(AddInTail(&q, 0), SUCCESS);
	EXPECT_EQ(arr[0], 0);
}

TEST(Add_In_Tail, Var1_FAIL) {
	queue_t q;
	q.arr = NULL;
	q.size = 0;
	q.head = 0;
	q.tail = 0;

	EXPECT_EQ(AddInTail(&q, 0), FAIL);
}

TEST(Add_In_Tail, Var2_FAIL) {
	int arr[2] = { 0, 1 };
	queue_t q;
	q.arr = arr;
	q.size = 2;
	q.head = 0;
	q.tail = 2;

	EXPECT_EQ(AddInTail(&q, 2), FAIL);
	EXPECT_EQ(arr[0], 0);
	EXPECT_EQ(arr[1], 1);
	EXPECT_EQ(q.size, 2);
	EXPECT_EQ(q.head, 0);
	EXPECT_EQ(q.tail, 2);
}


TEST(Get_From_Head, Var_SUCCESS) {
	int temp;


	int arr[1] = { 0 };
	queue_t q;
	q.arr = arr;
	q.size = 1;
	q.head = 0;
	q.tail = 1;

	EXPECT_EQ(GetFromHead(&q, &temp), SUCCESS);
	EXPECT_EQ(temp, 0);
}

TEST(Get_From_Head, Var1_FAIL) {
	int temp = 4;
	queue_t q;

	q.arr = NULL;
	q.size = 0;
	q.head = 0;
	q.tail = 0;

	EXPECT_EQ(GetFromHead(&q, &temp), FAIL);
	EXPECT_EQ(temp, 4);

}

TEST(Get_From_Head, Var2_FAIL) {
	int temp = 4;
	int arr[1] = { 0 };
	queue_t q;

	q.arr = arr;
	q.size = 1;
	q.head = 1;
	q.tail = 1;

	EXPECT_EQ(GetFromHead(&q, &temp), FAIL);
	EXPECT_EQ(temp, 4);

}




TEST(Breadth_First_Search, Var_SUCCESS) {
	int arrQ[1];
	int arrT[1];
	queue_t q;
	node_t tops[1];
	adjacency_list_t list;

	q.arr = arrQ;
	q.size = 1;
	q.head = 0;
	q.tail = 0;

	tops[0].numE = 0;
	tops[0].edges = arrT;

	list.numT = 1;
	list.tops = tops;

	EXPECT_EQ(BreadthFirstSearch(&list, &q), SUCCESS);
	EXPECT_EQ(arrQ[0], 0);
	EXPECT_EQ(q.head, 1);
	EXPECT_EQ(q.tail, 1);
}

TEST(Breadth_First_Search, Var1_FAIL) {
	int arrT[1];
	queue_t q;
	node_t tops[1];
	adjacency_list_t list;

	q.arr = NULL;

	tops[0].numE = 0;
	tops[0].edges = arrT;

	list.numT = 1;
	list.tops = tops;

	EXPECT_EQ(BreadthFirstSearch(&list, &q), FAIL);
}

TEST(Breadth_First_Search, Var2_FAIL) {
	int arrQ[1];
	queue_t q;
	adjacency_list_t list;

	q.arr = arrQ;

	list.numT = 0;
	list.tops = NULL;

	EXPECT_EQ(BreadthFirstSearch(&list, &q), FAIL);
}


TEST(Breadth_First_Search, Var3_FAIL) {
	int arrQ[1];
	queue_t q;
	node_t tops[2];
	adjacency_list_t list;

	q.arr = arrQ;
	q.size = 1;
	q.head = 0;
	q.tail = 0;

	list.numT = 2;
	list.tops = tops;

	EXPECT_EQ(BreadthFirstSearch(&list, &q), FAIL);
}

int main(int argc, char* argv[]) {
	return RUN_ALL_TESTS();
}