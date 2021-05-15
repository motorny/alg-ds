#include <vector>

#include <gtest/gtest.h>

#include "../AvlList.h"

class Insertion : public ::testing::Test 
{
protected:
    Node_t* root = nullptr;

    Insertion() = default;

    ~Insertion() override 
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


TEST_F(Insertion, OneNode) 
{
    root = insertNode(root, 1);
    ASSERT_EQ(root->value, 1);
}

TEST_F(Insertion, TwoNodes) 
{
    root = insertNodes({ 1, 2 });

    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->left, nullptr);

    ASSERT_EQ(root->right->value, 2);
    ASSERT_EQ(root->right->right, nullptr);
    ASSERT_EQ(root->right->left, nullptr);
}

TEST_F(Insertion, ThreeNodes) 
{
    root = insertNodes({ 2, 1, 3 });

    ASSERT_EQ(root->value, 2);

    ASSERT_EQ(root->left->value, 1);
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);

    ASSERT_EQ(root->right->value, 3);
    ASSERT_EQ(root->right->right, nullptr);
    ASSERT_EQ(root->right->left, nullptr);
}

TEST_F(Insertion, RightRotation3Nodes)
{
    root = insertNodes({ 3, 2, 1 });

    ASSERT_EQ(root->value, 2);

    ASSERT_EQ(root->left->value, 1);
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);

    ASSERT_EQ(root->right->value, 3);
    ASSERT_EQ(root->right->right, nullptr);
    ASSERT_EQ(root->right->left, nullptr);
}

TEST_F(Insertion, LeftRotation3Nodes) 
{
    root = insertNodes({ 1, 2, 3 });

    ASSERT_EQ(root->value, 2);

    ASSERT_EQ(root->left->value, 1);
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);

    ASSERT_EQ(root->right->value, 3);
    ASSERT_EQ(root->right->right, nullptr);
    ASSERT_EQ(root->right->left, nullptr);
}

TEST_F(Insertion, 2LeftRotation5Nodes) 
{
    root = insertNodes({ 1, 2, 3, 4, 5 });

    ASSERT_EQ(root->value, 2);

    ASSERT_EQ(root->left->value, 1);
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);

    ASSERT_EQ(root->right->value, 4);
    ASSERT_NE(root->right->right, nullptr);
    ASSERT_NE(root->right->left, nullptr);

    ASSERT_EQ(root->right->right->value, 5);
    ASSERT_EQ(root->right->right->left, nullptr);
    ASSERT_EQ(root->right->right->right, nullptr);

    ASSERT_EQ(root->right->left->value, 3);
    ASSERT_EQ(root->right->left->left, nullptr);
    ASSERT_EQ(root->right->left->right, nullptr);
}

TEST_F(Insertion, 2RightRotation5Nodes) 
{
    root = insertNodes({ 5, 4, 3, 2, 1 });

    ASSERT_EQ(root->value, 4);

    ASSERT_EQ(root->right->value, 5);
    ASSERT_EQ(root->right->left, nullptr);
    ASSERT_EQ(root->right->right, nullptr);

    ASSERT_EQ(root->left->value, 2);
    ASSERT_NE(root->left->right, nullptr);
    ASSERT_NE(root->left->left, nullptr);

    ASSERT_EQ(root->left->left->value, 1);
    ASSERT_EQ(root->left->left->left, nullptr);
    ASSERT_EQ(root->left->left->right, nullptr);

    ASSERT_EQ(root->left->right->value, 3);
    ASSERT_EQ(root->left->right->left, nullptr);
    ASSERT_EQ(root->left->right->right, nullptr);
}

TEST_F(Insertion, LeftRightRotation3Nodes)
{
    root = insertNodes({ 3, 2, 1 });

    ASSERT_EQ(root->value, 2);

    ASSERT_EQ(root->left->value, 1);
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);

    ASSERT_EQ(root->right->value, 3);
    ASSERT_EQ(root->right->right, nullptr);
    ASSERT_EQ(root->right->left, nullptr);
}

TEST_F(Insertion, RightLeftRotation3Nodes)
{
    root = insertNodes({ 1, 3, 2 });

    ASSERT_EQ(root->value, 2);

    ASSERT_EQ(root->left->value, 1);
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);

    ASSERT_EQ(root->right->value, 3);
    ASSERT_EQ(root->right->right, nullptr);
    ASSERT_EQ(root->right->left, nullptr);
}

TEST_F(Insertion, SameValue1Node)
{
    root = insertNode(root, 1);
    ASSERT_EQ(root, insertNode(root, 1));
}