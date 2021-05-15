#include <vector>

#include <gtest/gtest.h>

#include "../AvlList.h"

class Find : public ::testing::Test 
{
protected:
    Node_t* root = nullptr;

    Find() = default;

    ~Find() override 
    {
        freeTree(root);
    }

    Node_t* insertNodes(const std::vector<int>& values) 
    {
        for (auto i : values)
            root = insertNode(root, i);
        return root;
    }


};

TEST_F(Find, EmptyTree)
{
    ASSERT_EQ(findNode(root, 0), nullptr);
}

TEST_F(Find, OneNode) 
{
    root = insertNode(root, 1);
    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_EQ(findNode(root, 1), root);
}

TEST_F(Find, LeftNode2Nodes)
{
    root = insertNodes({ 2, 1 });
    ASSERT_EQ(findNode(root, 1), root->left);
}

TEST_F(Find, RightNode2Nodes)
{
    root = insertNodes({ 1, 2 });
    ASSERT_EQ(findNode(root, 2), root->right);
}

TEST_F(Find, 3NodesDeleteRoot)
{
    root = insertNodes({ 2, 1, 3 });

    ASSERT_EQ(findNode(root, 1), root->left);
    ASSERT_EQ(findNode(root, 3), root->right);
    ASSERT_EQ(findNode(root, 2), root);

    root = deleteNode(root, 2);
    ASSERT_EQ(findNode(root, 2), nullptr);
    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 3), nullptr);
}

TEST_F(Find, 3NodesDeleteLeft)
{
    root = insertNodes({ 2, 1, 3 });

    ASSERT_EQ(findNode(root, 1), root->left);
    ASSERT_EQ(findNode(root, 3), root->right);
    ASSERT_EQ(findNode(root, 2), root);

    root = deleteNode(root, 1);
    ASSERT_EQ(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);
    ASSERT_NE(findNode(root, 3), nullptr);
}

TEST_F(Find, 3NodesDeleteRight) 
{
    root = insertNodes({ 2, 1, 3 });

    ASSERT_EQ(findNode(root, 1), root->left);
    ASSERT_EQ(findNode(root, 3), root->right);
    ASSERT_EQ(findNode(root, 2), root);

    root = deleteNode(root, 3);
    ASSERT_EQ(findNode(root, 3), nullptr);
    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);
}