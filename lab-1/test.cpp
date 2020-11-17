#include "pch.h"
extern "C" {
#include "laba1.h"
}
int main(void) {
	return RUN_ALL_TESTS();
}
TEST(TestClear, Test_Clear_RightClearQueue_returnNull) {
	QUEUE* Q;
	LIST *A, *B, *C;
	int a[4] = { 3, 2, 1 }, b[4] = { 1, 2, 3 }, i;
	A = (LIST*)malloc(sizeof(LIST));
	B = (LIST*)malloc(sizeof(LIST));
	C = (LIST*)malloc(sizeof(LIST));
	Q = (QUEUE*)malloc(sizeof(LIST));
	A->number = b[3];
	A->preoritet = a[3];
	Q->Top = A;
	B->number = b[2];
	B->preoritet = a[2];
	C->number = b[1];
	C->preoritet = a[1];
	A->Next = B;
	B->Next = C;
	C->Next = NULL;
	Q->Tail = C;
	i = Clear(Q);
  EXPECT_TRUE(i == 1);
  EXPECT_TRUE(Q->Top == NULL);
  EXPECT_TRUE(Q->Tail == NULL);
}

TEST(TestPushE, Test_PushE_RightPushFromEndQueue_returnRightElement) {
	QUEUE* Q, * QEnd;
	LIST* A, * B, * C, *Element;
	int a[4] = { 3, 2, 1 }, b[4] = { 1, 2, 3 };
	A = (LIST*)malloc(sizeof(LIST));
	B = (LIST*)malloc(sizeof(LIST));
	C = (LIST*)malloc(sizeof(LIST));
	Element = (LIST*)malloc(sizeof(LIST));
	QEnd = (QUEUE*)malloc(sizeof(LIST));
	Q = (QUEUE*)malloc(sizeof(LIST));
	A->number = b[0];
	A->preoritet = a[0];
	B->number = b[1];
	B->preoritet = a[1];
	C->number = b[2];
	C->preoritet = a[2];
	QEnd->Top = A;
	QEnd->Top->Next = B;
	QEnd->Tail = B;
	Q->Top = A;
	A->Next = B;
	B->Next = C;
	C->Next = NULL;
	Q->Tail = C;
	Element = PushE(Q);
	B->Next = NULL;
	EXPECT_TRUE(QEnd->Top->number == Q->Top->number);
	EXPECT_TRUE(QEnd->Top->preoritet == Q->Top->preoritet);
	EXPECT_TRUE(QEnd->Top->Next->number == Q->Top->Next->number);
	EXPECT_TRUE(QEnd->Top->Next->preoritet == Q->Top->Next->preoritet);
	EXPECT_TRUE(QEnd->Tail->number == Q->Tail->number);
	EXPECT_TRUE(QEnd->Tail->preoritet == Q->Tail->preoritet);
	EXPECT_TRUE(QEnd->Tail->Next == NULL);
	EXPECT_TRUE(Q->Tail->Next == NULL);
//
	EXPECT_EQ(Element, C);
}
TEST(TestPushB, Test_PushB_RightPushFromBeginQueue_returnRightElement) {
	QUEUE* Q, * QEnd;
	LIST* A, * B, * C, * Element;
	int a[4] = { 3, 2, 1 }, b[4] = { 1, 2, 3 };
	A = (LIST*)malloc(sizeof(LIST));
	B = (LIST*)malloc(sizeof(LIST));
	C = (LIST*)malloc(sizeof(LIST));
	Element = (LIST*)malloc(sizeof(LIST));
	QEnd = (QUEUE*)malloc(sizeof(LIST));
	Q = (QUEUE*)malloc(sizeof(LIST));
	A->number = b[2];
	A->preoritet = a[2];
	B->number = b[1];
	B->preoritet = a[1];
	C->number = b[0];
	C->preoritet = a[0];
	QEnd->Top = B;
	QEnd->Top->Next = C;
	QEnd->Tail = C;
	Q->Top = A;
	A->Next = B;
	B->Next = C;
	C->Next = NULL;
	Q->Tail = C;
	Element = PushB(Q);
	EXPECT_TRUE(QEnd->Top->number == Q->Top->number);
	EXPECT_TRUE(QEnd->Top->preoritet == Q->Top->preoritet);
	EXPECT_TRUE(QEnd->Top->Next->number == Q->Top->Next->number);
	EXPECT_TRUE(QEnd->Top->Next->preoritet == Q->Top->Next->preoritet);
	EXPECT_TRUE(Q->Top->Next->number == Q->Tail->number);
	EXPECT_TRUE(Q->Top->Next->preoritet == Q->Tail->preoritet);
	EXPECT_TRUE(QEnd->Tail->number == Q->Tail->number);
	EXPECT_TRUE(QEnd->Tail->preoritet == Q->Tail->preoritet);
	EXPECT_TRUE(QEnd->Tail->Next == NULL);
	EXPECT_TRUE(Q->Tail->Next == NULL);
	EXPECT_EQ(Element, A);
}

TEST(TestPopB, Test_PopB_RightPopToBeginQueue_returnRightQueue) {
	QUEUE* Q, * QEnd;
	LIST* A, * B, * C, * Element, *D, *E;
	int a[4] = { 3, 2, 1 }, b[4] = { 1, 2, 3 }, i;
	A = (LIST*)malloc(sizeof(LIST));
	B = (LIST*)malloc(sizeof(LIST));
	C = (LIST*)malloc(sizeof(LIST));
	D = (LIST*)malloc(sizeof(LIST));
	E = (LIST*)malloc(sizeof(LIST));
	Element = (LIST*)malloc(sizeof(LIST));
	QEnd = (QUEUE*)malloc(sizeof(QUEUE));
	Q = (QUEUE*)malloc(sizeof(QUEUE));
	A->number = b[2];
	A->preoritet = a[2];
	B->number = b[1];
	B->preoritet = a[1];
	C->number = b[0];
	C->preoritet = a[0];
	if (Q->Top == NULL)
		EXPECT_TRUE(1 == 0);
	Q->Top = E;
	Q->Tail = D;
	Q->Top->number = B->number;
	Q->Top->preoritet = B->preoritet;
	Q->Top->Next = C;
	Q->Tail = Q->Top->Next;
	QEnd->Top = A;
	A->Next = B;
	B->Next = C;
	C->Next = NULL;
	QEnd->Tail = C;
	Element = A;
	i = PopB(Element, Q);
	EXPECT_TRUE(QEnd->Top->number == Q->Top->number);
	EXPECT_TRUE(QEnd->Top->preoritet == Q->Top->preoritet);
	EXPECT_TRUE(QEnd->Top->Next->number == Q->Top->Next->number);
	EXPECT_TRUE(QEnd->Top->Next->preoritet == Q->Top->Next->preoritet);
	EXPECT_TRUE(QEnd->Top->Next->Next->number == Q->Top->Next->Next->number);
	EXPECT_TRUE(QEnd->Top->Next->Next->preoritet == Q->Top->Next->Next->preoritet);
	EXPECT_TRUE(Q->Top->Next->Next->number == Q->Tail->number);
	EXPECT_TRUE(Q->Top->Next->Next->preoritet == Q->Tail->preoritet);
	EXPECT_TRUE(QEnd->Tail->number == Q->Tail->number);
	EXPECT_TRUE(QEnd->Tail->preoritet == Q->Tail->preoritet);
	EXPECT_TRUE(QEnd->Tail->Next == NULL);
	EXPECT_TRUE(Q->Tail->Next == NULL);
	EXPECT_TRUE(QEnd->Top == Element);
	EXPECT_TRUE(i == 1);
}

TEST(TestPopE, Test_PopE_RightPopToEndQueue_returnRightQueue) {
	QUEUE* Q, * QEnd;
	LIST* A, * B, * C, * Element, * D, * E;
	int a[4] = { 3, 2, 1 }, b[4] = { 1, 2, 3 }, i;
	A = (LIST*)malloc(sizeof(LIST));
	Element = (LIST*)malloc(sizeof(LIST));
	B = (LIST*)malloc(sizeof(LIST));
	C = (LIST*)malloc(sizeof(LIST));
	QEnd = (QUEUE*)malloc(sizeof(QUEUE));
	Q = (QUEUE*)malloc(sizeof(QUEUE));
	D = (LIST*)malloc(sizeof(LIST));
	E = (LIST*)malloc(sizeof(LIST));
	A->number = a[0];
	A->preoritet = b[0];
	B->number = a[1];
	B->preoritet = b[1];
	C->number = a[2];
	C->preoritet = b[2];
	D->number = a[0];
	D->preoritet = b[0]; 
	E->number = a[1];
	E ->preoritet = b[1]; 
	Q->Top = D;
	Q->Top->Next = E;
	Q->Top->number = D->number;
	Q->Top->preoritet = D->preoritet;
	E->Next = NULL;
	Q->Tail = Q->Top->Next;
	QEnd->Top = A;
	QEnd->Top->Next = B;
	B->Next = C;
	C->Next = NULL;
	QEnd->Tail = C;
	Element = C;
	i = PopE(Element, Q);
	EXPECT_TRUE(QEnd->Top->number == Q->Top->number);
	EXPECT_TRUE(QEnd->Top->preoritet == Q->Top->preoritet);
	EXPECT_TRUE(QEnd->Top->Next->number == Q->Top->Next->number);
	EXPECT_TRUE(QEnd->Top->Next->preoritet == Q->Top->Next->preoritet);
	EXPECT_TRUE(QEnd->Top->Next->Next->number == Q->Top->Next->Next->number);
	EXPECT_TRUE(QEnd->Top->Next->Next->preoritet == Q->Top->Next->Next->preoritet);
	EXPECT_TRUE(Q->Top->Next->Next->number == Q->Tail->number);
	EXPECT_TRUE(Q->Top->Next->Next->preoritet == Q->Tail->preoritet);
	EXPECT_TRUE(QEnd->Tail->number == Q->Tail->number);
	EXPECT_TRUE(QEnd->Tail->preoritet == Q->Tail->preoritet);
	EXPECT_TRUE(QEnd->Tail->Next == NULL);
	EXPECT_TRUE(Q->Tail->Next == NULL);
	EXPECT_TRUE(QEnd->Tail == Element); 
	EXPECT_TRUE(i == 1);
}
TEST(TestPopE2, Test_PopE_RightPopToEndToEmptyQueue_returnRightQueue) {
	QUEUE *Q;
	LIST* A, *Element;
	int i, j = 0;
	A = (LIST*)malloc(sizeof(LIST));
	Element = (LIST*)malloc(sizeof(LIST));
	Q = (QUEUE*)malloc(sizeof(QUEUE));
	Q->Top = NULL;
	A->number = 1;
	A->preoritet = 1;
	A->Next = NULL;
	Element = A;
	i = PopE(Element, Q);
		EXPECT_TRUE(i == j);
}
TEST(TestPopB2, Test_PopB_RightPopToEndToEmptyQueue_returnRightQueue) {
	QUEUE* Q;
	LIST* A, * Element;
	int i;
	A = (LIST*)malloc(sizeof(LIST));
	Element = (LIST*)malloc(sizeof(LIST));
	Q = (QUEUE*)malloc(sizeof(QUEUE));
	Q->Top = NULL;
	A->number = 1;
	A->preoritet = 1;
	A->Next = NULL;
	Element = A;
	i = PopB(Element, Q);
	EXPECT_TRUE(i == 0);
}