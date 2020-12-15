#include "pch.h"
#include "../alg_A10/StackArr.c"
#include "../alg_A10/StackList.c"

stackArr_t* CreateStackArr_Test(void) {
	stackArr_t* stack = (stackArr_t*)malloc(sizeof(stackArr_t));
	if(stack==NULL){
		return NULL;
	}
	stack->last = -1;
	stack->size = 10;
	stack->array = (int*)malloc(stack->size * sizeof(int));
	if (stack->array == NULL) {
		free(stack);
		return NULL;
	}
	return stack;
}

void DestroyStackArr_Test(stackArr_t* stack) {
	if (stack == NULL){
		return;
	}
	if (stack->array != NULL) free(stack->array);
	free(stack);
}

TEST(StackArray, PushArr_Puts2NumbersIntoStack_ReturnesTheLast) {
	stackArr_t* stack=CreateStackArr_Test();
	int data1 = 3, data2 = 10;
	EXPECT_TRUE(stack)<<"Failed to allocate memory";
	PushArr(stack, data1);
	EXPECT_EQ(stack->array[stack->last], data1) << "Failed to put the first element";
	PushArr(stack, data2);
	EXPECT_EQ(stack->array[0], data1) << "Lost the first element";
	EXPECT_EQ(stack->array[stack->last], data2) << "Failed to put the second element";
	DestroyStackArr_Test(stack);
}

TEST(StackArray, LastArr_ReturnsLastElement) {
	stackArr_t* stack = CreateStackArr_Test();
	int data1 = 5, data2 = -2;
	EXPECT_TRUE(stack) << "Failed to allocate memory";
	stack->array[0] = data1;
	stack->last = 0;
	EXPECT_EQ(LastArr(stack), data1) << "The only element was not returned";
	stack->array[1] = data2;
	stack->last = 1;
	EXPECT_EQ(LastArr(stack), data2) << "The second element was not returned";
}

TEST(StackArray, ResizeStackArr_NewSizeIsGreater) {
	stackArr_t* stack = CreateStackArr_Test();
	int size1=stack->size, size2;
	EXPECT_TRUE(stack) << "Failed to allocate memory";
	ResizeStackArr(stack);
	size2 = stack->size;
	EXPECT_GT(size2, size1) << "Size was not changed";
	DestroyStackArr_Test(stack);
}

TEST(StackArray, PopArr_ReturnsSecondNumberThenFirst) {
	stackArr_t* stack = CreateStackArr_Test();
	int data1 = 12, data2 = 23;
	EXPECT_TRUE(stack) << "Failed to allocate memory";
	stack->last = 1;
	stack->array[0] = data1;
	stack->array[1] = data2;
	EXPECT_EQ(PopArr(stack), data2) << "Last element was not returned";
	EXPECT_EQ(PopArr(stack), data1) << "First element was lost";
	DestroyStackArr_Test(stack);
}

TEST(StackArray, PopArr_EmptyArray_Returns0) {
	stackArr_t* stack = CreateStackArr_Test();
	EXPECT_TRUE(stack) << "Failed to allocate memory";
	EXPECT_EQ(PopArr(stack), 0);
	DestroyStackArr_Test(stack);
}

stackList_t* CreateStackList_Test(void) {
	stackList_t* stack = (stackList_t*) malloc(sizeof(stack));
	if (stack == NULL){
		return NULL;
	}
	stack->head = NULL;
	return stack;
}

void DestroyStackList_Test(stackList_t* stack) {
	node_t* tmp;
	if (stack == NULL){
		return;
	}
	while (stack->head != NULL) {
		tmp = stack->head;
		stack->head = tmp->next;
		free(tmp);
	}
	free(stack);
}

TEST(StackList, PushList_Puts2Numbers_Returns2NumbersInRightOrder) {
	stackList_t* stack = CreateStackList_Test();
	int data1 = 14, data2 = -25;
	EXPECT_TRUE(stack) << "Failed to allocate memory";
	PushList(stack, data1);
	EXPECT_EQ(stack->head->data, data1) << "First number was not pushed";
	PushList(stack, data2);
	EXPECT_EQ(stack->head->data, data2) << "Second number was not pushed";
	EXPECT_EQ(stack->head->next->data, data1) << "First number was lost";
	DestroyStackList_Test(stack);
}

TEST(StackList, PopList_2PopsFromStackWith2Nodes_Returns2NumbersInRightOrder) {
	stackList_t* stack = CreateStackList_Test();
	int data1 = 14, data2 = -25;
	ASSERT_TRUE(stack) << "Failed to allocate memory";

	stack->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_TRUE(stack->head) << "Failed to allocate memory";
	stack->head->data = data1;

	stack->head->next = (node_t*)malloc(sizeof(node_t));
	ASSERT_TRUE(stack->head->next) << "Failed to allocate memory";
	stack->head->next->data = data2;
	stack->head->next->next = NULL;

	EXPECT_EQ(PopList(stack), data1) << "First number was not returned";
	EXPECT_EQ(PopList(stack), data2) << "Second number was not returned";
	DestroyStackList_Test(stack);
}

TEST(StackList, PopList_EmptyStack_return0) {
	stackList_t* stack = CreateStackList_Test();
	ASSERT_TRUE(stack) << "Failed to allocate memory";
	EXPECT_EQ(PopList(stack), 0);
	DestroyStackList_Test(stack);
}

TEST(StackList, LastList_LastForStackWith2Nodes_ReturnsFirstNumber) {
	stackList_t* stack = CreateStackList_Test();
	int data1 = 14, data2 = -25;
	ASSERT_TRUE(stack) << "Failed to allocate memory";

	stack->head = (node_t*)malloc(sizeof(node_t));
	ASSERT_TRUE(stack->head) << "Failed to allocate memory";
	stack->head->data = data1;

	stack->head->next = (node_t*)malloc(sizeof(node_t));
	ASSERT_TRUE(stack->head->next) << "Failed to allocate memory";
	stack->head->next->data = data2;
	stack->head->next->next = NULL;

	EXPECT_EQ(LastList(stack), data1);
	DestroyStackList_Test(stack);
}
