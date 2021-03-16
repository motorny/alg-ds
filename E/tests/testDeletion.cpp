#include <gtest/gtest.h>

#include "../BinTree.h"

class Deletion: public ::testing::Test {
protected:
    Node_t *root = nullptr;

    ~Deletion() override { freeTree(root); }

    Node_t* insertNodes(const std::vector<int>& values) {
        for (int i : values)
            root = insertNode(root, i);
        return root;
    }
};

TEST_F(Deletion, Root) {
    root = insertNodes({0});
    root = deleteNode(root, 0);
    ASSERT_EQ(root, nullptr);
}

TEST_F(Deletion, Root1Left) {
    root = insertNodes({1, 0});
    root = deleteNode(root, 0);
    ASSERT_EQ(root->left, nullptr);
    ASSERT_EQ(root->val, 1);
}

TEST_F(Deletion, Root1Right) {
    root = insertNodes({0, 1});
    root = deleteNode(root, 1);
    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->val, 0);
}

TEST_F(Deletion, Root1Left1Right_DeleteRoot) {
    root = insertNodes({1, 0, 2});
    root = deleteNode(root, 1);
    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->val, 2);
    ASSERT_EQ(root->left->val, 0);
}

TEST_F(Deletion, Root_LR_DeleteL) {
    root = insertNodes({2, 0, 1});
    root = deleteNode(root, 0);
    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->left->val, 1);
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);
}

TEST_F(Deletion, Root_LL_Delete1L) {
    root = insertNodes({2, 1, 0});
    root = deleteNode(root, 1);
    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->left->val, 0);
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);
}
