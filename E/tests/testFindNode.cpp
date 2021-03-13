#include <gtest/gtest.h>

#include "../BinTree.h"

class FindNode: public ::testing::Test {
protected:
    Node_t *root = nullptr;

    ~FindNode() override { freeTree(root); }

    Node_t* insertNodes(const std::vector<int>& values) {
        for (int i : values)
            root = insertNode(root, i);
        return root;
    }
};

TEST_F(FindNode, Root) {
    root = insertNodes({1});
    ASSERT_EQ(findNode(root, 1), root);
}

TEST_F(FindNode, Root1Left) {
    root = insertNodes({1, 0});
    ASSERT_EQ(findNode(root, 0), root->left);
}

TEST_F(FindNode, Root1Right) {
    root = insertNodes({0, 1});
    ASSERT_EQ(findNode(root, 1), root->right);
}

TEST_F(FindNode, Root1Left1Right) {
    root = insertNodes({1, 0, 2});
    ASSERT_EQ(findNode(root, 1), root);
    ASSERT_EQ(findNode(root, 0), root->left);
    ASSERT_EQ(findNode(root, 2), root->right);
}

TEST_F(FindNode, Root6Nodes) {
    root = insertNodes({3, 1, 0, 5, 4, 6});
    ASSERT_EQ(findNode(root, 3), root);
    ASSERT_EQ(findNode(root, 1), root->left);
    ASSERT_EQ(findNode(root, 0), root->left->left);
    ASSERT_EQ(findNode(root, 2), root->left->right);
    ASSERT_EQ(findNode(root, 5), root->right);
    ASSERT_EQ(findNode(root, 4), root->right->left);
    ASSERT_EQ(findNode(root, 6), root->right->right);
}