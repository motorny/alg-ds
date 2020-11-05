#include "pch.h"

extern "C" {
#include "../Priority queue/queue.h"
#include "../Priority queue/queue.c"
}

//int error = 0;

TEST(Creating_queue, Create_empty_queue) {
	bool_t flag = TRUE;
	queue_t* queue = QueueCreate(NULL, 0, &flag);

	ASSERT_EQ(flag, TRUE);
	ASSERT_EQ(queue, (queue_t*)NULL);
}

TEST(Creating_queue, Create_full_queue) {
	int N = 5, i = 0;
	int mass[5] = { 4, 5, 7, 20, 45 };
	bool_t flag = TRUE;
	queue_t* queue = QueueCreate(mass, N, &flag);

	ASSERT_EQ(flag, TRUE);
	ASSERT_NE(queue, (queue_t*)NULL);
	ASSERT_EQ(queue->head->number, mass[0]);
	ASSERT_EQ(queue->head->next->number, mass[1]);
	ASSERT_EQ(queue->head->next->next->number, mass[2]);
	ASSERT_EQ(queue->head->next->next->next->number, mass[3]);
	ASSERT_EQ(queue->head->next->next->next->next->number, mass[4]);
	ASSERT_EQ(queue->tail->next, (node_t*)NULL);

	QueueDestroy(queue);
}

TEST(Adding_new_element, Add_to_the_end_of_empty_queue) {
	int newdata = 12;
	bool_t flag = TRUE;

	queue_t* queue = QueueCreate(NULL, 0, &flag);
	InsertTail(queue, newdata, &flag);

	ASSERT_EQ(flag, FALSE);
}

TEST(Adding_new_element, Add_to_the_end) {//general case
	int N = 5;
	int mass[5] = { 4, 5, 7, 20, 45 };
	int newdata = 12;
	bool_t flag = TRUE;

	queue_t* queue = QueueCreate(mass, N, &flag);
	node_t* extail = queue->tail;
	int extailpriority = queue->tail->priority;
	InsertTail(queue, newdata, &flag);

	ASSERT_EQ(flag, TRUE);
	ASSERT_EQ(extail->next->priority, extailpriority + 1);
	ASSERT_EQ(extail->next->number, newdata);
	ASSERT_EQ(extail->next->next, (node_t*)NULL);

	QueueDestroy(queue);
}

TEST(Adding_new_element, Add_by_priority_to_empty_queue) {
	int newdata = 12;
	int newpriority = 0;
	bool_t flag = TRUE;

	queue_t* queue = QueueCreate(NULL, 0, &flag);
	EnqueueByPriority(queue, newdata, newpriority, &flag);

	ASSERT_EQ(flag, FALSE);
}

TEST(Adding_new_element, Add_by_zero_priority) {
	int N = 5;
	int mass[5] = { 4, 5, 7, 20, 45 };
	int newdata = 8;
	int newpriority = 0;
	bool_t flag = TRUE;

	queue_t* queue = QueueCreate(mass, N, &flag);
	node_t* exhead = queue->head;
	int exheadpriority = exhead->priority;
	EnqueueByPriority(queue, newdata, newpriority, &flag);
	
	ASSERT_EQ(flag, TRUE);
	ASSERT_EQ(queue->head->priority, 0);
	ASSERT_EQ(queue->head->number, newdata);
	ASSERT_EQ(queue->head->next->number, exhead->number);
	ASSERT_EQ(queue->head->next->priority, exheadpriority + 1);

	QueueDestroy(queue);
}

TEST(Adding_new_element, Add_by_non_zero_priority) {//general case
	int N = 5;
	int mass[5] = { 4, 5, 7, 20, 45 };
	int newdata = 8;
	int newpriority = 3;
	bool_t flag = TRUE;

	queue_t* queue = QueueCreate(mass, N, &flag);
	EnqueueByPriority(queue, newdata, newpriority, &flag);
	node_t* node = GoToNode(queue->head, newpriority);

	ASSERT_EQ(flag, TRUE);
	ASSERT_EQ(node->number, newdata);
	ASSERT_EQ(node->priority, newpriority);
	ASSERT_EQ(node->next->number, mass[newpriority]);
	ASSERT_EQ(node->next->priority, newpriority + 1);

	QueueDestroy(queue);
}

TEST(Deleting_element, Delete_from_empty_queue) {
	bool_t flag = TRUE;
	queue_t* queue = QueueCreate(NULL, 0, &flag);

	DeleteMax(queue, &flag);

	ASSERT_EQ(flag, FALSE);
}

TEST(Deleting_element, Delete_max) {//general case
	int N = 5;
	int mass[5] = { 4, 5, 7, 20, 45 };
	bool_t flag = TRUE;
	queue_t* queue = QueueCreate(mass, N, &flag);

	DeleteMax(queue, &flag);

	ASSERT_EQ(flag, TRUE);
	ASSERT_EQ(queue->head->number, mass[1]);
	ASSERT_EQ(queue->head->priority, 0);

	QueueDestroy(queue);
}

TEST(Extracting_element, Extract_from_empty_queue) {
	bool_t flag = TRUE;
	queue_t* queue = QueueCreate(NULL, 0, &flag);

	int extracted = ExtractMax(queue, &flag);

	ASSERT_EQ(flag, FALSE);	
}

TEST(Extracting_element, Extract_max) {//general case
	int N = 5;
	int mass[5] = { 4, 5, 7, 20, 45 };
	bool_t flag = TRUE;

	queue_t* queue = QueueCreate(mass, N, &flag);
	int extracted = ExtractMax(queue, &flag);

	ASSERT_EQ(flag, TRUE);
	ASSERT_EQ(extracted, mass[0]);
	ASSERT_EQ(queue->head->number, mass[1]);
	ASSERT_EQ(queue->head->priority, 0);

	QueueDestroy(queue);
} 