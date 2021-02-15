#include "pch.h"
#include "Graph.h"


TEST(AddNode, NullNode) {
	node_list_t* list = InitList(1);
	node_t* node = NewNode(-1);
	node_t* node1 = AddNode(list, node);
	EXPECT_EQ(node1, (node_t*)NULL);
	EXPECT_EQ(list->head, (node_t*)NULL);
}

TEST(AddNode, EqualNodes) {
	node_list_t* list = InitList(1);
	node_t* node1 = NewNode(0);
	node_t* node2 = NewNode(0);

	node_t* res1 = AddNode(list, node1);
	node_t* res2 = AddNode(list, node2);

	EXPECT_EQ(res1, node1);
	EXPECT_EQ(list->head, node1);
	EXPECT_EQ(res2, node1);
}

TEST(AddNode, DifferentNodes) {
	node_list_t* list = InitList(2);
	node_t* node1 = NewNode(0);
	node_t* node2 = NewNode(1);

	node_t* res1 = AddNode(list, node1);
	node_t* res2 = AddNode(list, node2);

	EXPECT_EQ(res1, node1);
	EXPECT_EQ(res2, node2);
	EXPECT_EQ(list->head, node1);
	EXPECT_EQ(node1->next, node2);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}