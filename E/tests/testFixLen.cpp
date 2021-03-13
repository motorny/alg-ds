#include <gtest/gtest.h>

#include "../BinTree.h"

class FixLen : public ::testing::Test {
protected:
    Node_t* root = nullptr;

    ~FixLen() override { freeTree(root); }

    Node_t* insertNodes(const std::vector<int> &values) {
        for (int i : values)
            root = insertNode(root, i);
        return root;
    }
};

// fixLen with insertNode only
TEST_F(FixLen, Root_I) {
    root = insertNodes({1});
    ASSERT_EQ(root->len, 0);
}

TEST_F(FixLen, Root1Left_I) {
    root = insertNodes({1, 0});
    ASSERT_EQ(root->left->len, 0);
    ASSERT_EQ(root->len, 1);
}

TEST_F(FixLen, Root1Right_I) {
    root = insertNodes({0, 1});
    ASSERT_EQ(root->right->len, 0);
    ASSERT_EQ(root->len, 1);
}

TEST_F(FixLen, Root1Left1Right_I) {
    root = insertNodes({1, 0, 2});
    ASSERT_EQ(root->right->len, 0);
    ASSERT_EQ(root->left->len, 0);
    ASSERT_EQ(root->len, 2);
}

TEST_F(FixLen, Root1Left2W1Right3W_I) {
    root = insertNodes({11, 10, 100});
    ASSERT_EQ(root->right->len, 0);
    ASSERT_EQ(root->left->len, 0);
    ASSERT_EQ(root->len, 5);
}

TEST_F(FixLen, Root2Left3W2W_I) {
    root = insertNodes({101, 100, 10});
    ASSERT_EQ(root->len, 5);
    ASSERT_EQ(root->left->len, 2);
    ASSERT_EQ(root->left->left->len, 0);
}

TEST_F(FixLen, Root2Right2W3W_I) {
    root = insertNodes({10, 11, 100});
    ASSERT_EQ(root->len, 5);
    ASSERT_EQ(root->right->len, 3);
    ASSERT_EQ(root->right->right->len, 0);
}

// fixLen with deleteNode
TEST_F(FixLen, Root1Left_D_Left) {
    root = insertNodes({1, 0});
    ASSERT_EQ(root->len, 1);
    root = deleteNode(root, 0);
    ASSERT_EQ(root->len, 0);
}

TEST_F(FixLen, Root1Left_D_Root) {
    root = insertNodes({1, 0});
    ASSERT_EQ(root->len, 1);
    root = deleteNode(root, 1);
    ASSERT_EQ(root->len, 0);
}

TEST_F(FixLen, Root1Left_D_Right) {
    root = insertNodes({0, 1});
    ASSERT_EQ(root->len, 1);
    root = deleteNode(root, 1);
    ASSERT_EQ(root->len, 0);
}

TEST_F(FixLen, Root_LR_D_Root) {
    root = insertNodes({1, 0, 2});
    ASSERT_EQ(root->len, 2);
    root = deleteNode(root, 1);
    ASSERT_EQ(root->len, 1);
}

TEST_F(FixLen, Root_LR_D_Left) {
    root = insertNodes({1, 0, 2});
    ASSERT_EQ(root->len, 2);
    root = deleteNode(root, 0);
    ASSERT_EQ(root->len, 1);
}

TEST_F(FixLen, Root_L2wR3w_D_Root) {
    root = insertNodes({11, 10, 100});
    ASSERT_EQ(root->len, 5);
    root = deleteNode(root, 11);
    ASSERT_EQ(root->len, 2);
}

TEST_F(FixLen, Root_L2wR3w_D_Left) {
    root = insertNodes({11, 10, 100});
    ASSERT_EQ(root->len, 5);
    root = deleteNode(root, 10);
    ASSERT_EQ(root->len, 3);
}

TEST_F(FixLen, Root_L2wR3w_D_Right) {
    root = insertNodes({11, 10, 100});
    ASSERT_EQ(root->len, 5);
    root = deleteNode(root, 100);
    ASSERT_EQ(root->len, 2);
}
