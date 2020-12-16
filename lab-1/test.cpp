#include "pch.h"
#include "../Queue_for_Lab1/list.h"
#include "../Queue_for_Lab1/queue_array.h"
#include "../Queue_for_Lab1/queue_list.h"


TEST(list_init_test_series, init_mem_test) {
	Node* test = NULL;
	list_init_data(&test, 5);
	EXPECT_NE(test, nullptr);
}
TEST(list_init_test_series, init_data_test) {
	Node* test = NULL;
	list_init_data(&test, 5);
	EXPECT_EQ(test->data, 5);
}

TEST(list_init_test_series, init_next_test) {
	Node* test = NULL;
	list_init_data(&test, 5);
	ASSERT_EQ(test->next, nullptr);
}

TEST(list_push_test_series, push_data_next_test) {
	Node* test = NULL;
	list_init_data(&test, 5);
	list_push(test, 12);
	EXPECT_EQ(test->next->data, 12);
}

TEST(list_push_test_series, push_next_next_null_test) {
	Node* test = NULL;
	list_init_data(&test, 5);
	list_push(test, 12);
	ASSERT_EQ(test->next->next, nullptr);
}

TEST(list_push_test_series, push_extra_next_test) {
	Node* test = NULL;
	list_init_data(&test, 5);
	list_push(test, 12);
	list_push(test->next, 13);
	ASSERT_NE(test->next->next, nullptr);
	EXPECT_EQ(test->next->next->data, 13);
}

TEST(list_pop_test_series, pop_delete_test) {
	Node* test = NULL;
	list_init_data(&test, 5);
	list_pop(&test);
	ASSERT_EQ(test, nullptr);
}

TEST(list_pop_test_series, pop_delete_head_test) {
	Node* test = NULL;
	list_init_data(&test, 5);
	list_push(test, 12);
	list_pop(&test);
	ASSERT_NE(test, nullptr);
	ASSERT_EQ(test->next, nullptr);
}

TEST(list_pop_test_series, pop_save_data_test) {
	Node* test = NULL;
	int data = 0;
	list_init_data(&test, 5);
	data = list_pop(&test);
	EXPECT_EQ(data, 5);
}

TEST(list_pop_test_series, pop_save_next_data_test) {
	Node* test = NULL;
	int data = 0;
	test = (Node*)malloc(sizeof(Node*));
	test->data = 5;
	test->next = (Node*)malloc(sizeof(Node*));
	test->next->data = 12;
	data = list_pop(&test);
	EXPECT_EQ(data, 5);
	data = list_pop(&test);
	EXPECT_EQ(data, 12);
}

TEST(list_get_test_series, get_head_data_test) {
	Node* test = NULL;
	int get_data = 0;
	test = (Node*)malloc(sizeof(Node*));
	test->data = 5;
	get_data = list_get(test, 0);
	EXPECT_EQ(get_data, 5);
}

TEST(list_get_test, series, get_next_data_test) {
	Node* test = NULL;
	int get_data = 0;
	test = (Node*)malloc(sizeof(Node*));
	test->data = 5;
	test->next = (Node*)malloc(sizeof(Node*));
	test->next->data = 12;
	get_data = list_get(test, 1);
    EXPECT_EQ(get_data, 12);
}

TEST(list_get_test_series, get_list_data_test) {
	Node* test = NULL;
	int get_data = 0;
	list_init_data(&test, 0);
	Node* test_head = test;
	for (int i = 1; i < 10; i++) {
		list_init_data(&test->next, i * i);
		test = test->next;
	}
	get_data = list_get(test_head, 7);
	EXPECT_EQ(get_data, 49);
}

TEST(queue_init_test_series, init_queue_test) {
	Queue* test = NULL;
	queue_init(&test, 5);
	for (int i = 0; i < 5; i++) {
		test->data[i] = i * i + i;
	}
	ASSERT_NE(test, nullptr);
	EXPECT_EQ(test->data[0], 0);
	EXPECT_EQ(test->data[1], 2);
	EXPECT_EQ(test->data[2], 6);
	EXPECT_EQ(test->data[3], 12);
	EXPECT_EQ(test->data[4], 20);
	EXPECT_EQ(test->real_size, 0);
}

TEST(queue_init_test_series, init_zero_queue_test) {
	Queue* test = NULL;
	queue_init(&test, 0);
	ASSERT_NE(test, nullptr);
	ASSERT_EQ(sizeof(test->data), sizeof(int));
	EXPECT_EQ(test->real_size, 0);
}

TEST(queue_push_test_series, push_new_queue_test) {
	Queue* test = NULL;
	queue_init(&test, 5);
	for (int i = 0; i < 5; i++) {
		queue_push(test, i * i + i);
	}
	EXPECT_EQ(test->data[0], 0);
	EXPECT_EQ(test->data[1], 2);
	EXPECT_EQ(test->data[2], 6);
	EXPECT_EQ(test->data[3], 12);
	EXPECT_EQ(test->data[4], 20);
	EXPECT_EQ(test->real_size, 5);
}

TEST(queue_push_test_series, push_old_queue_test) {
	Queue* test = NULL;
	queue_init(&test, 5);
	for (int i = 0; i < 5; i++) {
		test->data[i] = i * i + i;
	}
	for (int i = 0; i < 5; i++) {
		queue_push(test, i * i * i);
	}
	EXPECT_NE(test->data[1], 2);
	EXPECT_NE(test->data[2], 6);
	EXPECT_NE(test->data[3], 12);
	EXPECT_NE(test->data[4], 20);
	EXPECT_EQ(test->data[0], 0);
	EXPECT_EQ(test->data[1], 1);
	EXPECT_EQ(test->data[2], 8);
	EXPECT_EQ(test->data[3], 27);
	EXPECT_EQ(test->data[4], 64);
	EXPECT_EQ(test->real_size, 5);

}