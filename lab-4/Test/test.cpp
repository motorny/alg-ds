#include "gtest/gtest.h"
#include "../Tree.c"

TEST(TestAddNode, correct) {
	AddNode(10, "hello");
	AddNode(5, "hello");
	AddNode(15, "hello");
	AddNode(13, "hello");
	AddNode(12, "hello");
	AddNode(14, "hello");
	AddNode(19, "hello");
	AddNode(17, "hello");
	AddNode(16, "hello");
	AddNode(18, "hello");

	EXPECT_EQ(firstNode->key, 10);
	EXPECT_EQ(firstNode->left->key, 5);
	EXPECT_EQ(firstNode->right->key, 15);
	EXPECT_EQ(firstNode->right->left->key, 13);
	EXPECT_EQ(firstNode->right->left->left->key, 12);
	EXPECT_EQ(firstNode->right->left->right->key, 14);
	EXPECT_EQ(firstNode->right->right->key, 19);
	EXPECT_EQ(firstNode->right->right->left->key, 17);
	EXPECT_EQ(firstNode->right->right->left->left->key, 16);
	EXPECT_EQ(firstNode->right->right->left->right->key, 18);
	firstNode = NULL;
}

TEST(TestDeleteNode, correct) {
	AddNode(10, "hello");
	AddNode(5, "hello");
	AddNode(15, "hello");
	AddNode(13, "hello");
	AddNode(12, "hello");
	AddNode(14, "hello");
	AddNode(19, "hello");
	AddNode(17, "hello");
	AddNode(16, "hello");
	AddNode(18, "hello");

	DeleteNode(12);
	DeleteNode(14);
	DeleteNode(19);
	DeleteNode(17);
	DeleteNode(10);
	DeleteNode(5);
	DeleteNode(15);
	DeleteNode(13);
	DeleteNode(16);
	DeleteNode(18);

	EXPECT_TRUE(firstNode == NULL);
}

TEST(TestFindNode, correct) {
	node_t **node;
	AddNode(10, "hello");
	AddNode(5, "hello");
	AddNode(15, "hello");
	AddNode(13, "hello");

	node = FindNode(15);
	EXPECT_EQ((*node)->key, 15);
	node = FindNode(5);
	EXPECT_EQ((*node)->key, 5);
	node = FindNode(10);
	EXPECT_EQ((*node)->key, 10);
	node = FindNode(13);
	EXPECT_EQ((*node)->key, 13);
}

TEST(TestChangeWidth, correct) {
	AddNode(10, "hello");
	AddNode(5, "hello");
	AddNode(15, "hello");
	AddNode(13, "hello");
	EXPECT_EQ(firstNode->width, 15);
	ChangeWidth(*FindNode(13), 3);
	EXPECT_EQ(firstNode->width, 18);
	EXPECT_EQ(firstNode->right->width, 8);
}

TEST(TestFindNodeKLower, correct){
	AddNode(10, "hello");
	AddNode(5, "hello");
	AddNode(15, "hello");
	AddNode(13, "hello");
	AddNode(12, "hello");
	AddNode(14, "hello");
	AddNode(19, "hello");
	AddNode(17, "hello");
	AddNode(16, "hello");
	AddNode(18, "hello");

	EXPECT_EQ(FindNodeKLower(*FindNode(19), 2), 16);
	EXPECT_EQ(FindNodeKLower(*FindNode(15), 2), 12);
}
