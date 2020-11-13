#include "pch.h"
extern "C" {
#include"queuePriority.h"
}

TEST(Creating_queue, Create_full_queue) {
	int N = 10, i;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	node_t* el1 = queue->head, * el2 = NULL;
	ASSERT_EQ(error, NONE);
	ASSERT_NE(queue, (queuePrior_t*)NULL);
	for (i = 0; i < N; i++) {
		ASSERT_EQ(el1->data, arr[i]);
		el2 = el1->next;
		if (el2 == NULL)
			break;
		el1 = el2;
	}
	DeleteQueue(queue, N, &error);
}

TEST(Creating_queue, Create_empty_queue) {
	int N = 0;
	int *arr = NULL;
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	ASSERT_EQ(error, NO_DATA);
	ASSERT_EQ(queue, (queuePrior_t*)NULL);
}

TEST(Adding_element, Add_by_priority) {
	int N = 10, el = 2, priority = 5;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	queuePrior_t* queue1 = (queuePrior_t*)malloc(sizeof(queuePrior_t)), * queue2 = (queuePrior_t*)malloc(sizeof(queuePrior_t));
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	node_t* el1 = queue->head, * el2 = NULL;
	InsertEl(queue, queue1, queue2, el, N, priority, &error);
	ASSERT_EQ(error, NONE);
	while (el1->priority != priority) {
		el2 = el1->next;
		el1 = el2;
	}
	ASSERT_EQ(el1->data, el);
	ASSERT_EQ(el1->priority, priority);
	DeleteQueue(queue1, N + 1, &error);
	free(queue2);
	free(queue);
}

TEST(Adding_element, Add_by_priority_to_the_empty_queue) {
	int N = 0, el = 2, priority = 5;
	int* arr = NULL;
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	error = NONE;
	queuePrior_t* queue1 = (queuePrior_t*)malloc(sizeof(queuePrior_t)), * queue2 = (queuePrior_t*)malloc(sizeof(queuePrior_t));
	InsertEl(queue, queue1, queue2, el, N, priority, &error);
	ASSERT_EQ(error, NO_DATA);
	free(queue1);
	free(queue2);
}

TEST(Adding_element, Add_to_the_beginning) {
	int N = 10, el = 2, priority = 0;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	queuePrior_t* queue1 = (queuePrior_t*)malloc(sizeof(queuePrior_t)), * queue2 = (queuePrior_t*)malloc(sizeof(queuePrior_t));
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	InsertEl(queue, queue1, queue2, el, N, priority, &error);
	ASSERT_EQ(error, NONE);
	ASSERT_EQ(queue1->head->data, el);
	DeleteQueue(queue1, N + 1, &error);
	free(queue2);
	free(queue);
}

TEST(Adding_element, Add_to_the_beginning_empty_queue) {
	int N = 0, el = 2, priority = 0;
	int* arr = NULL;
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	error = NONE;
	queuePrior_t* queue1 = (queuePrior_t*)malloc(sizeof(queuePrior_t)), * queue2 = (queuePrior_t*)malloc(sizeof(queuePrior_t));
	InsertEl(queue, queue1, queue2, el, N, priority, &error);
	ASSERT_EQ(error, NO_DATA);
	free(queue1);
	free(queue2);
}

TEST(Adding_element, Add_to_the_end_by_InsertEnd) {
	int N = 10, el = 2;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	InsertEnd(queue, el, &error);
	ASSERT_EQ(error, NONE);
	ASSERT_EQ(queue->tail->data, el);
	DeleteQueue(queue, N, &error);
}

TEST(Adding_element, Add_to_the_end_by_InsertEnd_empty_queue) {
	int N = 0, el = 2, priority = 10;
	int* arr = NULL;
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	error = NONE;
	InsertEnd(queue, el, &error);
	ASSERT_EQ(error, NO_DATA);
}

TEST(Adding_element, Add_to_the_end_by_InsertEl) {
	int N = 10, el = 2, priority = 10;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	queuePrior_t* queue1 = (queuePrior_t*)malloc(sizeof(queuePrior_t)), * queue2 = (queuePrior_t*)malloc(sizeof(queuePrior_t));
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	InsertEl(queue, queue1, queue2, el, N, priority, &error);
	ASSERT_EQ(error, NONE);
	ASSERT_EQ(queue->tail->data, el);
	DeleteQueue(queue, N + 1, &error);
	free(queue1);
	free(queue2);
}

TEST(Adding_element, Add_to_the_end_by_InsertEl_empty_queue) {
	int N = 0, el = 2, priority = 10;
	int* arr = NULL;
	error_t error = NONE;
	queuePrior_t* queue1 = (queuePrior_t*)malloc(sizeof(queuePrior_t)), * queue2 = (queuePrior_t*)malloc(sizeof(queuePrior_t));
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	error = NONE;
	InsertEl(queue, queue1, queue2, el, N, priority, &error);
	ASSERT_EQ(error, NO_DATA);
	free(queue1);
	free(queue2);
}

TEST(Finding_element, Find_max) {
	int N = 10;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	ASSERT_EQ(queue->head->data, FindMax(queue, &error));
	ASSERT_EQ(error, NONE);
	DeleteQueue(queue, N, &error);
}

TEST(Finding_element, Find_max_empty_queue) {
	int N = 0, el = 2, max = 0;
	int* arr = NULL;
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	error = NONE;
	max = FindMax(queue, &error);
	ASSERT_EQ(error, NO_DATA);
}

TEST(Finding_element, Find_min) {
	int N = 10;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	ASSERT_EQ(queue->tail->data, FindMin(queue, &error));
	ASSERT_EQ(error, NONE);
	DeleteQueue(queue, N, &error);
}

TEST(Finding_element, Find_min_empty_queue) {
	int N = 0, el = 2, min = 0;
	int* arr = NULL;
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	error = NONE;
	min = FindMin(queue, &error);
	ASSERT_EQ(error, NO_DATA);
}

TEST(Finding_element, Find_el) {
	int N = 10, el = 5;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	node_t* el1 = queue->head, * el2 = NULL;
	while (el1->data != el) {
		el2 = el1->next;
		el1 = el2;
	}
	ASSERT_EQ(el1->priority, FindEl(queue, N, el, &error));
	ASSERT_EQ(error, NONE);
	DeleteQueue(queue, N, &error);
}

TEST(Finding_element, Find_in_empty_queue) {
	int N = 0, el = 2, priority = 0;
	int* arr = NULL;
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	error = NONE;
	priority = FindEl(queue, N, el, &error);
	ASSERT_EQ(error, NO_DATA);
}

TEST(Finding_element, Not_existing_element) {
	int N = 10, el = 4, priority = 0;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	priority = FindEl(queue, N, el, &error);
	ASSERT_EQ(error, NO_DATA);
	DeleteQueue(queue, N, &error);
}

TEST(Deleting_element, Delete_max) {
	int N = 10, el = 4, priority = 0;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	DeleteMax(queue, &error);
	ASSERT_EQ(queue->head->data, arr[1]);
	ASSERT_EQ(error, NONE);
	DeleteQueue(queue, N, &error);
}

TEST(Deleting_element, Delete_from_empty_queue) {
	int N = 0, el = 2, priority = 5;
	int* arr = NULL;
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	error = NONE;
	DeleteMax(queue, &error);
	ASSERT_EQ(error, NO_DATA);
}

TEST(Split_and_Merge, Split_queue) {
	int N = 10, priority = 5, i;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	queuePrior_t* queue1 = (queuePrior_t*)malloc(sizeof(queuePrior_t)), * queue2 = (queuePrior_t*)malloc(sizeof(queuePrior_t));
	SplitQueue(queue, queue1, queue2, N, priority, &error);
	ASSERT_EQ(error, NONE);
	node_t* el1 = queue1->head, * el2 = NULL;
	for (i = 0; i < priority - 1; i++) {
		ASSERT_EQ(el1->data, arr[i]);
		el2 = el1->next;
		if (el2 == NULL)
			break;
		el1 = el2;
	}

	el1 = queue2->head,  el2 = NULL;
	for (i = priority; i < N; i++) {
		ASSERT_EQ(el1->data, arr[i]);
		el2 = el1->next;
		if (el2 == NULL)
			break;
		el1 = el2;
	}

	DeleteQueue(queue, N, &error);
	free(queue1);
	free(queue2);
}

TEST(Split_and_Merge, Merge_queue) {
	int N = 10, el = 4, priority = 5, i;
	int arr[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
	error_t error = NONE;
	queuePrior_t* queue = InitQueuePriority(arr, N, &error);
	queuePrior_t* queue1 = (queuePrior_t*)malloc(sizeof(queuePrior_t)), * queue2 = (queuePrior_t*)malloc(sizeof(queuePrior_t));
	SplitQueue(queue, queue1, queue2, N, priority, &error);
	MergeQueue(queue1, queue2, el, priority, &error);
	ASSERT_EQ(error, NONE);
	node_t* el1 = queue1->head, * el2 = NULL;
	for (i = 0; i < priority - 1; i++) {
		ASSERT_EQ(el1->data, arr[i]);
		el2 = el1->next;
		if (el2 == NULL)
			break;
		el1 = el2;
	}
	el2 = el1->next;
	el1 = el2;
	ASSERT_EQ(el1->data, el);
	el2 = el1->next;
	el1 = el2;
	for (i = priority; i < N; i++) {
		ASSERT_EQ(el1->data, arr[i]);
		el2 = el1->next;
		if (el2 == NULL)
			break;
		el1 = el2;
	}
	DeleteQueue(queue1, N + 1, &error);
	free(queue);
	free(queue2);
}