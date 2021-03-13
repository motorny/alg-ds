#include <gtest/gtest.h>

#include "../BinTree.h"

class TestInsertion : public ::testing::Test {
protected:
    Node_t* root = nullptr;

    ~TestInsertion() override { delete root; }
};

TEST_F(TestInsertion, 1Node) {
    root = insertNode(root, 0);

    ASSERT_EQ(root->left, nullptr);
    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->val, 0);
//    ASSERT_EQ(root->len, 0);
}

TEST_F(TestInsertion, Root1Left1Len) {
    root = insertNode(root, 1);
    root = insertNode(root, 0);

    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->left->val, 0);
//    ASSERT_EQ(root->left->len, 1);
    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);
    ASSERT_EQ(root->right, nullptr);
    ASSERT_EQ(root->val, 1);
//    ASSERT_EQ(root->len, 1);

    delete root->left;
}

//TEST_F(TestInsertion, Root1Left2Len) {
//    root = insertNode(root, 11);
//    root = insertNode(root, 10);
//
//    ASSERT_NE(root->left, nullptr);
//    ASSERT_EQ(root->left->val, 10);
////    ASSERT_EQ(root->left->len, 2);
//    ASSERT_EQ(root->left->left, nullptr);
//    ASSERT_EQ(root->left->right, nullptr);
//    ASSERT_EQ(root->right, nullptr);
//    ASSERT_EQ(root->val, 11);
////    ASSERT_EQ(root->len, 2);
//
//    delete root->left;
//}

TEST_F(TestInsertion, Root1Right) {
    root = insertNode(root, 0);
    root = insertNode(root, 1);

    ASSERT_EQ(root->left, nullptr);
    ASSERT_EQ(root->right->val, 1);
//    ASSERT_EQ(root->left->len, 2);
    ASSERT_EQ(root->right->left, nullptr);
    ASSERT_EQ(root->right->right, nullptr);
    ASSERT_EQ(root->left, nullptr);
    ASSERT_EQ(root->val, 0);
//    ASSERT_EQ(root->len, 2);

    delete root->right;
}

TEST_F(TestInsertion, Root1Left1Right) {
    root = insertNode(root, 1);
    root = insertNode(root, 0);
    root = insertNode(root, 2);

    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);

    ASSERT_EQ(root->left->val, 0);
    ASSERT_EQ(root->right->val, 2);
    ASSERT_EQ(root->val, 1);

    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);
    ASSERT_EQ(root->right->left, nullptr);
    ASSERT_EQ(root->right->right, nullptr);

    delete root->left;
    delete root->right;
}

TEST_F(TestInsertion, 4NodeLeftRightInsertion) {
    root = insertNode(root, 2);
    root = insertNode(root, 0);
    root = insertNode(root, 3);
    root = insertNode(root, 1);

    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->left->right, nullptr);

    ASSERT_EQ(root->left->val, 0);
    ASSERT_EQ(root->right->val, 3);
    ASSERT_EQ(root->val, 2);
    ASSERT_EQ(root->left->right->val, 1);

    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right->left, nullptr);
    ASSERT_EQ(root->left->right->right, nullptr);
    ASSERT_EQ(root->right->left, nullptr);
    ASSERT_EQ(root->right->right, nullptr);

    delete root->left->right;
    delete root->left;
    delete root->right;
}

TEST_F(TestInsertion, 4NodeRightLeftInsertion) {
    root = insertNode(root, 1);
    root = insertNode(root, 3);
    root = insertNode(root, 0);
    root = insertNode(root, 2);

    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->right->left, nullptr);

    ASSERT_EQ(root->left->val, 0);
    ASSERT_EQ(root->right->val, 3);
    ASSERT_EQ(root->val, 1);
    ASSERT_EQ(root->right->left->val, 2);

    ASSERT_EQ(root->left->left, nullptr);
    ASSERT_EQ(root->left->right, nullptr);
    ASSERT_EQ(root->right->left->left, nullptr);
    ASSERT_EQ(root->right->left->right, nullptr);
    ASSERT_EQ(root->right->right, nullptr);

    delete root->right->left;
    delete root->left;
    delete root->right;
}