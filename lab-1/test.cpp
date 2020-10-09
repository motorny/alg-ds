#include "pch.h"

extern "C" {
#include "..\LAB_A\lab_A.h"
#include "..\LAB_A\lab_A_30.c"
}

int NumberOfElements(plenty_t* A) {
	node_t* p = A->head;
	int n = 0;
	while (p != NULL) {
		n++;
		p = p->next;
	}
	return n;
}
int CompareValues(plenty_t* A, int a[], int size) {
	int i = 0;
	node_t* p = A->head;
	while (i < size && p != NULL) {
		if (a[i] != p->data)
			return FALSE;
		i++;
		p = p->next;
	}
	return TRUE;
}
int IsSorted(plenty_t* A) {
	node_t* p = A->head;
	data_t a, b;
	while (p != NULL) {
		a = p->data;
		p = p->next;
		if (p != NULL)
			b = p->data;
		else 
			break;
		if (a > b)
			return FALSE;
	}
	return TRUE;
}

TEST(Filling, Fill_OneElement_ReturnsValid) {
	plenty_t* A = CreateZeroPlenty();

	FillPlenty(A, 1, 1);

	ASSERT_EQ(1, A->head->data);

	DestroyPlenty(A);
}
TEST(Filling, Fill_TenElements_ReturnsValid) {
	plenty_t* A = CreateZeroPlenty();
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int check;
	FillPlenty(A, 10, 1);

	check = CompareValues(A, a, 10);
	ASSERT_EQ(TRUE, check);

	DestroyPlenty(A);
}

TEST(CreatingPlenty, Create_NormalCase_ReturnsValid) {
	plenty_t* A = CreateZeroPlenty();
	ASSERT_TRUE(A->head == NULL);
	DestroyPlenty(A);
}
TEST(DestructionPlenty, Del_NormalCase_ReturnsNULL) {
	plenty_t* A = CreateZeroPlenty();
	FillPlenty(A, 10, 1);
	DestroyPlenty(A);
	ASSERT_NO_THROW(A->head->data);
}

TEST(AddingElement, Add_NormalValues_ReturnsValid) {
	plenty_t* A = CreateZeroPlenty();
	int check;
	int n = 10;
	FillPlenty(A, n, 1);

	AddInPlenty(A, 2);

	check = NumberOfElements(A);
	ASSERT_EQ(n+1, check);
	check = IsSorted(A);
	ASSERT_EQ(TRUE, check);
	DestroyPlenty(A);
}
TEST(AddingElement, Add_InEmptyPlenty_ReturnsValid) {
	plenty_t* A = CreateZeroPlenty();
	
	AddInPlenty(A, 1);

	ASSERT_EQ(1, A->head->data);

	DestroyPlenty(A);
}

TEST(Deleting, Del_NormalCase_ReturnsTrue) {
	plenty_t* A = CreateZeroPlenty();
	int a1[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int a2[9] = { 1,2,3,5,6,7,8,9,10 };
	int check;
	FillPlenty(A, 10, 1);
	check = CompareValues(A, a1, 10);
	ASSERT_EQ(TRUE, check);

	DelFromPlenty(A, 4, FIRST);
	check = CompareValues(A, a2, 9);
	ASSERT_EQ(TRUE, check);

	DestroyPlenty(A);
}
TEST(Deleting, Del_NormalCase_ReturnsFalse) {
	plenty_t* A = CreateZeroPlenty();
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int check, returns;
	FillPlenty(A, 10, 1);

	returns = DelFromPlenty(A, 15, FIRST);
	check = CompareValues(A, a, 10);
	ASSERT_EQ(TRUE, check);
	ASSERT_FALSE(returns);

	DestroyPlenty(A);
}
TEST(Deleting, Del_NullCase_ReturnsNaN) {
	int returns;
	returns = DelFromPlenty(NULL, 1, FIRST);

	ASSERT_EQ(NaN, returns);
}

TEST(Searcing, Include_NormalCase_ReturnsTrue) {
	plenty_t* A = CreateZeroPlenty();
	int check;
	FillPlenty(A, 10, 1);
	check = IsIncludeInPlenty(A, 4);
	ASSERT_EQ(TRUE, check);
	DestroyPlenty(A);
}
TEST(Searcing, Include_NormalCase_ReturnsFalse) {
	plenty_t* A = CreateZeroPlenty();
	int check;
	FillPlenty(A, 10, 1);
	check = IsIncludeInPlenty(A, 14);
	ASSERT_EQ(FALSE, check);
	DestroyPlenty(A);
}
TEST(Searcing, Include_EmptyCase_ReturnsNaN) {
	plenty_t* A = CreateZeroPlenty();
	int check;
	check = IsIncludeInPlenty(A, 14);
	ASSERT_EQ(NaN, check);
	DestroyPlenty(A);
}
TEST(Searcing, Include_NULLCase_ReturnsNaN) {
	int check;
	check = IsIncludeInPlenty(NULL, 14);
	ASSERT_EQ(NaN, check);
}

TEST(Merging, Merge_NormalCase_ReturnsTrue) {
	plenty_t* A = CreateZeroPlenty();
	plenty_t* B = CreateZeroPlenty();
	plenty_t* C;
	int check;
	int a[15] = { 1,2,3,4,5,6,7,8,9,10,12,14,16,18,20 };
	FillPlenty(A, 10, 1); //1 2 3 4 5 6 7 8 9 10
	FillPlenty(B, 10, 2); //2 4 6 8 10 12 14 16 18 20
	
	C = PlentyMerge(A, B);
	check = CompareValues(C, a, 15);
	ASSERT_EQ(TRUE, check);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}
TEST(Merging, Merge_OneIsEmpty_ReturnsTrue) {
	plenty_t* A = CreateZeroPlenty();
	plenty_t* B = CreateZeroPlenty();
	plenty_t* C;
	int check;
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	FillPlenty(A, 10, 1); //1 2 3 4 5 6 7 8 9 10

	C = PlentyMerge(A, B);
	check = CompareValues(C, a, 10);
	ASSERT_EQ(TRUE, check);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}
TEST(Merging, Merge_BothIsEmpty_ReturnsTrue) {
	plenty_t* A = CreateZeroPlenty();
	plenty_t* B = CreateZeroPlenty();
	plenty_t* C;

	C = PlentyMerge(A, B);
	ASSERT_TRUE(C->head == NULL);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}

TEST(Union, Union_NormalCase_ReturnsTrue) {
	plenty_t* A = CreateZeroPlenty();
	plenty_t* B = CreateZeroPlenty();
	plenty_t* C;
	int check;
	int a[5] = { 2,4,6,8,10 };
	FillPlenty(A, 10, 1); //1 2 3 4 5 6 7 8 9 10
	FillPlenty(B, 10, 2); //2 4 6 8 10 12 14 16 18 20

	C = PlentyUnion(A, B);
	check = CompareValues(C, a, 5);
	ASSERT_EQ(TRUE, check);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}
TEST(Union, Union_OneIsEmpty_ReturnsTrue) {
	plenty_t* A = CreateZeroPlenty();
	plenty_t* B = CreateZeroPlenty();
	plenty_t* C;
	int check;

	FillPlenty(A, 10, 1); //1 2 3 4 5 6 7 8 9 10

	C = PlentyUnion(A, B);
	ASSERT_TRUE(C->head == NULL);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}
TEST(Union, Union_BothIsEmpty_ReturnsTrue) {
	plenty_t* A = CreateZeroPlenty();
	plenty_t* B = CreateZeroPlenty();
	plenty_t* C;

	C = PlentyUnion(A, B);
	ASSERT_TRUE(C->head == NULL);
	DestroyPlenty(A);
	DestroyPlenty(B);
	DestroyPlenty(C);
}
