#include "pch.h"




TEST(queue, push_addInQueue_return0) {


	int* q,e;
	int n = 5;
	q = mem(n,&e);

    EXPECT_EQ(push(q,0,0), 0);



}

TEST(queue, pop_removeFromQueue_return3) {


	int* q, e;
	int n = 5;
	q = mem(n, &e);
	q[0] = 3;

	EXPECT_EQ(pop(q, 1), 3);
}




	TEST(BFS, BFS_check_return0) {

		int e;
		A = memA(3,&e);
		
		A[0][1] = 1;
		A[1][2] = 1;
		A[1][3] = 1;
		

		EXPECT_EQ(BFS(A,3), 0);



	}