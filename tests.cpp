TEST(CheckFound, NULL)
{
	Node* tree = NULL, * tmp = NULL;
	EXPECT_TRUE(!getNodeByValue(tree, 5));
	insert(&tree, 5);
	tmp = getNodeByValue(tree, 5);
	EXPECT_TRUE(tmp);
	EXPECT_EQ(tmp->data, 5);
	deleteValue(root, 5);
	EXPECT_TRUE(!getNodeByValue(tree, 5));

	destroyTree(tree);
}

#include "Source.cpp"
TEST(ADD_ELEMENT, correct)
{
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
	EXPECT_EQ(firstNode->right->right->right->key, 20);
	EXPECT_EQ(firstNode->right->right->left->key, 17);
	EXPECT_EQ(firstNode->right->right->left->left->key, 16);
	EXPECT_EQ(firstNode->right->right->left->right->key, 18);
	firstNode = NULL;
}

TEST(DELETE_ELEMENT, correct)
{
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

TEST(FIND_NODE)
{
	AddNode(10, "hello");
	AddNode(5, "hello");
	AddNode(15, "hello");
	AddNode(13, "hello");

	EXPECT_TRUE(!!FindNode(15));
	EXPECT_TRUE(!!FindNode(5));
	EXPECT_TRUE(!!FindNode(10));
	EXPECT_TRUE(!!FindNode(13));
}

TEST(CHANGE_WIDTH_PARENT, correct)
{
	AddNode(10, "hello");
	AddNode(5, "hello");
	AddNode(15, "hello");
	AddNode(13, "hello");
	EXPECT_EQ(firstNode->subTreeWidth, 15);
	ChangeWidthParents(*FindNode(13), 3);
	EXPECT_EQ(firstNode->subTreeWidth, 18);
	EXPECT_EQ(firstNode->right->subTreeWidth, 8);
}

TEST(FIND_NODE_K_LOWER, correct)
{
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

	EXPECT_EQ(FindNodeKLower(*FindNode(19), 2),16);
	EXPECT_EQ(FindNodeKLower(*FindNode(15), 2),12);
	EXPECT_EQ(FindNodeKLower(*FindNode(20), 3), 16);
}