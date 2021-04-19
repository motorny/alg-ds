#include <vector>

#include <gtest/gtest.h>

#include "../23Tree.h"

class DeleteTerminal : public testing::Test {
protected:
    Node_t* root = nullptr;

    DeleteTerminal() = default;

    ~DeleteTerminal() override { freeTree(root); }

    Node_t* insertNodes(const std::vector<int> &vals) {
        for (auto i : vals) {
            root = insertNode(root, i);
        }
        return root;
    }
};

TEST_F(DeleteTerminal, 1Leaf) {
    root = insertNodes({1});
    root = deleteTerminal(root, 1);

    ASSERT_EQ(root, nullptr);
}

TEST_F(DeleteTerminal, 1Leaf_None) {
    root = insertNodes({1});
    root = deleteTerminal(root, 0);

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 1);
    ASSERT_EQ(root->left->lval, 1);
}

TEST_F(DeleteTerminal, 2Leaves_Left) {
    root = insertNodes({1, 3});
    root = deleteTerminal(root, 1);

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->left->lval, 3);
    ASSERT_EQ(root->left->max_child, 3);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, nullptr);
}

TEST_F(DeleteTerminal, 2Leaves_Right) {
    root = insertNodes({1, 3});
    root = deleteTerminal(root, 3);

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 1);

    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->left->lval, 1);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, nullptr);
}

TEST_F(DeleteTerminal, 2Leaves_None) {
    root = insertNodes({1, 3});
    root = deleteTerminal(root, 2);

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->left->lval, 1);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->right);
    ASSERT_EQ(root->left->max_child, 1);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->lsib, root->left);
    ASSERT_EQ(root->right->rsib, nullptr);
    ASSERT_EQ(root->right->max_child, 3);
}

TEST_F(DeleteTerminal, 3Leaves_Left) {
    root = insertNodes({0, 1, 3});
    root = deleteTerminal(root, 0);

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(root->left->lval, 1);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->right);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->max_child, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->lsib, root->left);
    ASSERT_EQ(root->right->rsib, nullptr);
}

TEST_F(DeleteTerminal, 3Leaves_Middle) {
    root = insertNodes({1, 2, 3});
    root = deleteTerminal(root, 2);

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(root->left->lval, 1);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->right);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->max_child, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->lsib, root->left);
    ASSERT_EQ(root->right->rsib, nullptr);
}

TEST_F(DeleteTerminal, 3Leaves_Right) {
    root = insertNodes({1, 3, 4});
    root = deleteTerminal(root, 4);

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(root->left->lval, 1);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->right);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->max_child, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->lsib, root->left);
    ASSERT_EQ(root->right->rsib, nullptr);
}

TEST_F(DeleteTerminal, 3Leaves_None) {
    root = insertNodes({1, 2, 3});
    root = deleteTerminal(root, 0);

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, 2);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->left->lval, 1);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->middle);

    ASSERT_EQ(root->middle->lval, 2);
    ASSERT_EQ(root->middle->max_child, 2);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->max_child, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->lsib, root->middle);
    ASSERT_EQ(root->right->rsib, nullptr);
}