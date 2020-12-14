#include "pch.h"
extern "C"{
	#include "LabA.h"
}

TEST(AddToArrayTest, AddToArrayTest_ArrayIsFree_returnValidVal) {
	queue_array_t queue;
	int error, tail;
	CreateArray(&queue);
	tail = queue.tail;

	AddToArray(&queue, 5, &error);

	ASSERT_TRUE(queue.data[queue.head] == 5);
	ASSERT_TRUE(error == NO_ERRORS);
	ASSERT_TRUE(queue.tail - tail == 1);
}

TEST(AddToArrayTest, AddToArrayTest_ArrayIsFull_returnError) {
	queue_array_t queue;
	int error, i, tail;
	CreateArray(&queue);
	tail = queue.tail;

	for (i = 0; i < 4; i++) {
		AddToArray(&queue, i, &error);
	}

	ASSERT_TRUE(queue.data[queue.tail - 1] == 2);
	ASSERT_TRUE(error == ARRAY_IS_FULL);
	ASSERT_TRUE(queue.tail - tail == 3);
}

TEST(CreateArrayTest, CreateArrayTest_NewArray_returnValidVal) {
	queue_array_t queue;
	CreateArray(&queue);

	ASSERT_TRUE(queue.head == 0);
	ASSERT_TRUE(queue.tail == 0);
}

TEST(DeleteAllArrayTest, DeleteAllArrayTest_ArrayIsFilled_returnValidVal) {
	queue_array_t queue;
	CreateArray(&queue);

	queue.data[queue.tail] = 1;
	queue.tail = (queue.tail + 1) % N;

	queue.data[queue.tail] = 2;
	queue.tail = (queue.tail + 1) % N;

	DeleteAllArray(&queue);

	ASSERT_TRUE(queue.head == queue.tail);
}

TEST(DeleteAllArrayTest, DeleteAllArrayTest_ArrayIsFree_returnValidVal) {
	queue_array_t queue;
	CreateArray(&queue);

	DeleteAllArray(&queue);

	ASSERT_TRUE(queue.head == queue.tail);
}

TEST(DeleteFromArrayTest, DeleteFromArrayTest_ArrayIsEmpty_returnError) {
	queue_array_t queue;
	int error, element;
	CreateArray(&queue);

	element = DeleteFromArray(&queue, &error);

	ASSERT_TRUE(error == QUEUE_IS_FREE);
	ASSERT_TRUE(element == 0);
}

TEST(DeleteFromArrayTest, DeleteFromArrayTest_ArrayIsFiiled_returnValidVal) {
	queue_array_t queue;
	int error, element;
	CreateArray(&queue);

	queue.data[queue.tail] = 6;
	queue.tail = (queue.tail + 1) % N;
	element = DeleteFromArray(&queue, &error);

	ASSERT_TRUE(error == NO_ERRORS);
	ASSERT_TRUE(element == 6);
}

TEST(IsFilledArrayTest, IsFilledArrayTest_ArrayIsEmpty_return0) {
	queue_array_t queue;
	int state;
	CreateArray(&queue);

	state = IsFilledArray(&queue);

	ASSERT_TRUE(state == 0);
}

TEST(IsFilledArrayTest, IsFilledArrayTest_ArrayIsFill_return1) {
	queue_array_t queue;
	int state, error;
	CreateArray(&queue);
	AddToArray(&queue, 5, &error);

	state = IsFilledArray(&queue);

	ASSERT_TRUE(state == 1);
}

TEST(SizeOfArrayTest, SizeOfArrayTest_ArrayIsEmpty_return0) {
	queue_array_t queue;
	int size;
	CreateArray(&queue);

	size = SizeOfArray(&queue);

	ASSERT_TRUE(size == 0);
}

TEST(SizeOfArrayTest, SizeOfArray_ArrayIsFill_return1) {
	queue_array_t queue;
	int size;
	CreateArray(&queue);
	queue.data[queue.tail] = 1;
	queue.tail = (queue.tail + 1) % N;

	size = SizeOfArray(&queue);

	ASSERT_TRUE(size == 1);
}

TEST(AddToListTest, AddToListTest_ListIsFree_returnValidVal) {
	queue_list_t queue;
	int error;

	CreateList(&queue, &error);
	AddToList(&queue, 5, &error);

	ASSERT_TRUE(queue.head->data == 5);
	ASSERT_TRUE(error == NO_ERRORS);
}

TEST(CreateListTest, CreateListTest_ListIsFree_returnValidVal) {
	queue_list_t queue;
	int error;

	CreateList(&queue, &error);

	ASSERT_TRUE(queue.size == 0);
	ASSERT_TRUE(queue.head == queue.tail);
	ASSERT_TRUE(error == NO_ERRORS);
}

TEST(DeleteAllListTest, DeleteAllListTest_ListIsFree_returnValidVal) {
	queue_list_t queue;
	int error;

	CreateList(&queue, &error);

	DeleteAllList(&queue);

	ASSERT_TRUE(queue.size == 0);
	ASSERT_TRUE(queue.head == NULL);
}

TEST(DeleteAllListTest, DeleteAllListTest_ListIsFilled_returnValidVal) {
	queue_list_t queue;
	int error;

	CreateList(&queue, &error);

	queue.head->data = 6;
	queue.head->next = NULL;
	queue.tail = queue.head;

	DeleteAllList(&queue);

	ASSERT_TRUE(queue.size == 0);
	ASSERT_TRUE(queue.head == NULL);
}

TEST(DeleteFromListTest, DeleteFromListTest_ListIsFree_returnError) {
	queue_list_t queue;
	int element, error;
	CreateList(&queue, &error);

	element = DeleteFromList(&queue, &error);

	ASSERT_TRUE(element == 0);
	ASSERT_TRUE(error == QUEUE_IS_FREE);
	ASSERT_TRUE(queue.size == 0);
}

TEST(DeleteFromListTest, DeleteFromListTest_ListIsFilled_returnValidVal) {
	queue_list_t queue;
	int element, error;
	element_t* newElement;
	CreateList(&queue, &error);

	queue.head->data = 6;
	queue.head->next = NULL;
	queue.tail = queue.head;
	queue.size++;

	newElement = (element_t*) malloc(sizeof(element_t));

	newElement->data = 4;
	newElement->next = NULL;
	queue.tail->next = newElement;
	queue.tail = newElement;
	queue.size++;

	element = DeleteFromList(&queue, &error);


	ASSERT_TRUE(element == 6);
	ASSERT_TRUE(error == NO_ERRORS);
	ASSERT_TRUE(queue.size == 1);
}

TEST(IsFilledListTest, IsFilledListTest_ListIsFree_return0) {
	queue_list_t queue;
	int state, error;
	CreateList(&queue, &error);

	state = IsFilledList(&queue);

	ASSERT_TRUE(state == 0);
}

TEST(IsFilledListTest, IsFilledListTest_ListIsFilled_return1) {
	queue_list_t queue;
	int state, error;
	CreateList(&queue, &error);

	queue.head->data = 1;
	queue.head->next = NULL;
	queue.tail = queue.head;
	queue.size++;

	state = IsFilledList(&queue);

	ASSERT_TRUE(state == 1);
}

TEST(SizeOfListTest, SizeOfListTest_ListIsFree_return0) {
	queue_list_t queue;
	int size, error;
	CreateList(&queue, &error);

	size = SizeOfList(&queue);

	ASSERT_TRUE(size == 0);
}

TEST(SizeOfListTest, SizeOfListTest_ListIsFilled_return1) {
	queue_list_t queue;
	int size, error;
	CreateList(&queue, &error);

	

	size = SizeOfList(&queue);

	assert(size == 1);
}

int main(int argc,char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}