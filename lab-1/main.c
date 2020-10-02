#include "pch.h"
#include <stdlib.h>
//#include "vld.h"
#include <stdio.h>
typedef struct ArrayStack {
	int* data;
	int capacity;
	int size;
}ArrayStack_t;

ArrayStack_t* createArrayStack() {
	ArrayStack_t* t = (ArrayStack_t*)malloc(sizeof(ArrayStack_t));
	t->capacity = 10;
	t->size = 0;
	t->data = (int*)malloc(sizeof(int) * 10);
	return t;
}
void pushArray(int d, ArrayStack_t* stack) {
	stack->data[stack->size++] = d;
	if (stack->capacity == stack->size)
	{
		int* newData = (int*)malloc(sizeof(int) * (stack->capacity + 10));
		for (int i = 0; i != stack->size; ++i)
			newData[i] = stack->data[i];
		stack->capacity += 10;
		free(stack->data);
		stack->data = newData;
	}
}
int popArray(ArrayStack_t* stack)
{
	return stack->data[(stack->size--) - 1];
}
void destroyArray(ArrayStack_t* stack)
{
	free(stack->data);
	free(stack);
}
typedef struct LinkedListStack
{
	struct LinkedListStack* next;
	int data;
}LinkedListStack_t;
struct LinkedListStack* createLinkedListStack()
{
	LinkedListStack_t* t = (LinkedListStack_t*)malloc(sizeof(LinkedListStack_t));
	if (t) {
		t->data = 0;
		t->next = 0;
	}
	return t;

}
void push(int newData, LinkedListStack_t** stack)
{
	LinkedListStack_t* t = createLinkedListStack();
	t->data = newData;
	t->next = *stack;
	*stack = t;
}
int pop(LinkedListStack_t** stack)
{
	if (stack) {
		int t = (*stack)->data;
		LinkedListStack_t* prev = (*stack)->next;
		free(*stack);
		*stack = prev;
		return t;
	}
	else return -1;
}
void destroy(LinkedListStack_t** stack) {
	LinkedListStack_t* prev = NULL;
	while ((*stack)->next) {
		prev = (*stack)->next;
		free(*stack);
		*stack = prev;
	}
	free(*stack);
}
TEST(testArrayStack, createAndDestroyEmptyArrayStack) {
	ArrayStack_t* t = createArrayStack();
	EXPECT_TRUE(t->capacity == 10);
	EXPECT_TRUE(t->size == 0);
	EXPECT_TRUE(t->data != NULL);
	destroyArray(t);
}
TEST(testArrayStack, pushOnetoArrayStack) {
	ArrayStack_t* t = createArrayStack();
	pushArray(1, t);
	EXPECT_TRUE(t->capacity == 10);
	EXPECT_TRUE(t->size == 1);
	EXPECT_TRUE(t->data[0] == 1);
	destroyArray(t);
}
TEST(testArrayStack, pushMoreThenTenIntstoArrayStack) {
	ArrayStack_t* t = createArrayStack();
	for (int i = 0; i != 11; ++i)
		pushArray(i, t);
	EXPECT_TRUE(t->capacity == 20);
	EXPECT_TRUE(t->size == 11);
	for (int i = 0; i != 11; ++i)
		EXPECT_TRUE(t->data[i] == i);
	destroyArray(t);
}
TEST(testArrayStack, popOnetoArrayStack) {
	ArrayStack_t* t = createArrayStack();
	pushArray(1, t);
	EXPECT_TRUE(popArray(t) == 1);
	EXPECT_TRUE(t->capacity == 10);
	EXPECT_TRUE(t->size == 0);
	destroyArray(t);
}
TEST(testArrayStack, pushAndPopMoreThenTentoArrayStack) {
	ArrayStack_t* t = createArrayStack();
	for (int i = 0; i != 11; ++i)
		pushArray(i, t);
	for (int i = 0; i != 11; ++i)
		EXPECT_TRUE(popArray(t) == 10 - i);
	EXPECT_TRUE(t->capacity == 20);
	EXPECT_TRUE(t->size == 0);
	destroyArray(t);
}


TEST(testLinkedListStack, createAndDestroyEmptyLinkedListStack) {
	LinkedListStack_t* t = createLinkedListStack();
	EXPECT_TRUE(t->next == NULL);
	EXPECT_TRUE(t->data == 0);
	destroy(&t);
}
TEST(testLinkedListStack, pushOneToLinkedListStack) {
	LinkedListStack_t* t = createLinkedListStack();
	push(1, &t);
	EXPECT_TRUE(t->next->next == NULL);
	EXPECT_TRUE(t->data == 1);
	destroy(&t);
}
TEST(testLinkedListStack, popOneToLinkedListStack) {
	LinkedListStack_t* t = createLinkedListStack();
	push(1, &t);
	EXPECT_TRUE(pop(&t) == 1);
	EXPECT_TRUE(t->next == NULL);
	destroy(&t);
}
TEST(testLinkedListStack, pushAndPopSomeIntsToLinkedListStack) {
	LinkedListStack_t* t = createLinkedListStack();
	push(1, &t);
	push(2, &t);
	push(3, &t);
	EXPECT_TRUE(pop(&t) == 3);
	EXPECT_TRUE(pop(&t) == 2);
	EXPECT_TRUE(t->next->next == NULL);
	destroy(&t);
}
int main(int argc, char** argv) {
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
// К минусам реализации стека через связный список можно отнести большую, по сравнении с реализации через
//массив, вероятность фрагментации памяти(так как на каждый элемент память выделяеться отдельно), необходимость
//хранить дополнительные данные, количество которых зависит от количества элементов в стеке. Однако, при
// реализации через массив при превышении некоторого количества элементов приходится создавать новый массив 
// большего объема и копировать все элементы, уже находящиеся в стеке, что является потенциально длительной 
// операцией, и соответсвенно большим минусом. 


