#include "pch.h"
extern"C" {
#include"List.h"
}

TEST(CreateStackList_InitializeListPointer, returnPointer) {
	StackList* list = CreateStackList();
	ASSERT_TRUE(list != NULL);
	DestroyStackList(&list);
}

TEST(PushStackList_NULLList, returnFAILED_0) {
	StackList* list = NULL;
	ASSERT_EQ(FAILED, PushStackList(&list, 1));
}

TEST(PushStackList_ValidList, returnSUCCESS_1) {
	StackList* list = CreateStackList(); 
	ASSERT_EQ(SUCCESS, PushStackList(&list, 1));
	DestroyStackList(&list);
}

TEST(PopStackList_NULLList, returnNULL) {
	StackList* list = NULL;
	ASSERT_EQ(NULL, PopStackList(&list));
	DestroyStackList(&list);
}

TEST(PopStackList_ReturnPoppedElement, returnFirstElement) {
	StackList* list = CreateStackList();
	PushStackList(&list, 1);
	PushStackList(&list, 2);
	ASSERT_EQ(2, PopStackList(&list));
	DestroyStackList(&list);
}

TEST(CreateStackArray_InitializeArray, returnPointer) {
	StackArray* array = CreateStackArray();
	ASSERT_TRUE(array != NULL);
	DestroyStackArray(array);
}

TEST(PushStackArray_NULLArray, returnFAILED_0) {
	StackArray* array = NULL;
	ASSERT_EQ(FAILED, PushStackArray(array, 1));
}

TEST(PushStackArray_ValidArray, returnSUCCESS_1) {
	StackArray* array = CreateStackArray();
	ASSERT_EQ(SUCCESS, PushStackArray(array, 1));
	DestroyStackArray(array);
}

TEST(PopStackArray_ArrayUnderflow, returnNULL) {
	StackArray* array = CreateStackArray();
	ASSERT_EQ(NULL, PopStackArray(array));
	DestroyStackArray(array);
}

TEST(PopStackArray_ReturnPoppedElement, returnFirstElement) {
	StackArray* array = CreateStackArray();
	PushStackArray(array, 1);
	PushStackArray(array, 2);
	ASSERT_EQ(2, PopStackArray(array));
	DestroyStackArray(array);
}
