#include "pch.h"
extern "C" {
#include"graph.h"
#include"queue.h"
}

TEST(TestPush, PushToNullQueue) {
	EXPECT_EQ(Push(NULL, 1), -1);
}

TEST(TestPush, PushToEmptyQueue) {
	queue_t* queue = QueueCreate();
	EXPECT_EQ(Push(queue, 1), 1);
	QueueDelete(queue);
}

TEST(TestPop, NULLPtr) {
	ASSERT_EQ(Pop(NULL), -1);
}

TEST(TestPop, EmptyQueue) {
	queue_t* queue = QueueCreate();
	ASSERT_EQ(Pop(queue), -1);
	QueueDelete(queue);
}