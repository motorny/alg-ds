#include <vector>

#include <gtest/gtest.h>

#include "../AvlList.h"

class Deletion : public ::testing::Test
{
protected:
    Node_t* root = nullptr;

    Deletion() = default;

    ~Deletion() override
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

TEST_F(Deletion, OneNode)
{
    root = insertNode(root, 1);
    root = deleteNode(root, 1);

    ASSERT_EQ(root, nullptr);
}

TEST_F(Deletion, LeafNode) 
{
    root = insertNodes({ 2, 1 });

    root = deleteNode(root, 2);
    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->left, nullptr);
}

TEST_F(Deletion, OneChild)
{
    root = insertNodes({ 2, 1, 3, 4 });

    ASSERT_EQ(root->right->value, 3);
    ASSERT_EQ(root->right->right->value, 4);
    ASSERT_EQ(root->right->left, nullptr);

    root = deleteNode(root, 3);

    ASSERT_EQ(root->right->value, 4);
    ASSERT_EQ(root->right->left, nullptr);
    ASSERT_EQ(root->right->right, nullptr);

    ASSERT_EQ(root->value, 2);
    ASSERT_EQ(root->left->value, 1);
    ASSERT_EQ(root->left->right, nullptr);
    ASSERT_EQ(root->left->left, nullptr);
}

TEST_F(Deletion, TwoChildren)
{
    root = insertNodes({ 2, 1, 4, 3, 5 });

    ASSERT_EQ(root->right->value, 4);
    ASSERT_EQ(root->right->right->value, 5);
    ASSERT_EQ(root->right->left->value, 3);

    root = deleteNode(root, 4);

    ASSERT_EQ(root->value, 2);

    ASSERT_EQ(root->right->value, 5);
    ASSERT_EQ(root->right->right, nullptr);

    ASSERT_EQ(root->right->left->value, 3);
    ASSERT_EQ(root->right->left->right, nullptr);
    ASSERT_EQ(root->right->left->left, nullptr);
}

TEST_F(Deletion, Empty)
{
    ASSERT_EQ(root, nullptr);

    root = deleteNode(root, 0);
    ASSERT_EQ(root, nullptr);
}