#include "pch.h"
#include "../../Lab1/Lab1/lab.c"

TEST(EmptyQueueArr, EmptyQueueArr_NotEmpty) {
	int* data;
	data = InitArray(3);
	quArray_t quAr = { 3,0,2,data };
	ASSERT_EQ(0, IsQuArrayEmpty(quAr));
}

TEST(EmptyQueueArr, EmptyQueueArr_Empty) {
	int* data;
	data = InitArray(3);
	quArray_t quAr = { 3,0,0,data };
	ASSERT_EQ(1, IsQuArrayEmpty(quAr));
}

TEST(PushQueueArr, PushOneQueueArr) {
	int* data;
	data = InitArray(3);
	quArray_t quAr = { 3,0,2,data };
	int newdata = 4;
	PushQuArray(newdata, &quAr);
	ASSERT_EQ(4, quAr.data[3]);
}

TEST(PushQueueArr, PushTwoQueueArr) {
	int* data;
	data = InitArray(3);
	quArray_t quAr = { 3,0,2,data };
	int newdata = 4;
	PushQuArray(newdata, &quAr);
	ASSERT_EQ(4, quAr.data[3]);
	newdata = 5;
	PushQuArray(newdata, &quAr);
	ASSERT_EQ(5, quAr.data[4]);
}

TEST(PopQueueArr, PopOneQueuArr) {
	int* data;
	data = InitArray(3);
	data[0] = 0;
	data[1] = 1;
	data[2] = 2;
	quArray_t quAr = { 3,0,2,data};
	ASSERT_EQ(0, PopQuArray(&quAr));
}

TEST(PopQueueArr, PopTwoQueuArr) {
	int* data;
	data = InitArray(3);
	data[0] = 0;
	data[1] = 1;
	data[2] = 2;
	quArray_t quAr = { 3,0,2,data };
	ASSERT_EQ(0, PopQuArray(&quAr));
	ASSERT_EQ(1, PopQuArray(&quAr));
}

TEST(PushQuList, PushOneNode) {
	quList_t quLi;
	int data[4] = { 0,1,2,3 };
	quLi = InitQuList(4, data);
	PushQuList(4, &quLi);
	ASSERT_EQ(4, quLi.last->data);
}

TEST(PushQuList, PushTwoNode) {
	quList_t quLi;
	int data[4] = { 0,1,2,3 };
	quLi = InitQuList(4, data);
	PushQuList(4, &quLi);
	ASSERT_EQ(4, quLi.last->data);
	PushQuList(5, &quLi);
	ASSERT_EQ(5, quLi.last->data);
}

TEST(PopQuList, PopOneNode) {
	quList_t quLi;
	int data[4] = { 0,1,2,3 };
	quLi = InitQuList(4, data);
	ASSERT_EQ(3, PopQuList(&quLi));
}

TEST(PopQuList, PopTwoNode) {
	quList_t quLi;
	int data[4] = { 0,1,2,3 };
	quLi = InitQuList(4, data);
	ASSERT_EQ(3, PopQuList(&quLi));
	ASSERT_EQ(2, PopQuList(&quLi));
}