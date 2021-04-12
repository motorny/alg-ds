#include <gtest/gtest.h>

#include "../23Tree.h"

class InsertTerminate: public testing::Test {
protected:
    Node_t* root = nullptr;

    InsertTerminate() = default;

    ~InsertTerminate() override = default;

    bool isTerminate(Node_t* node) {
        return node != nullptr && node->left == nullptr && node->middle == nullptr && node->right == nullptr;
    }
};

TEST_F(InsertTerminate, emptyInsert) {
    int val = 0;
    root = insertTerminate(root, val);

    ASSERT_EQ(root->lval, val);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, val);

    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(InsertTerminate::isTerminate(root), true);

    ASSERT_EQ(root->rsib, nullptr);
    ASSERT_EQ(root->lsib, nullptr);
}

TEST_F(InsertTerminate, 1ValueBigger) {
    int first_val = 1, second_val = 3;
    root = insertTerminate(root, first_val);
    root = insertTerminate(root, second_val);

    ASSERT_EQ(root->lval, first_val);
    ASSERT_EQ(root->rval, second_val);
    ASSERT_EQ(root->max_child, second_val);

    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(InsertTerminate::isTerminate(root), true);

    ASSERT_EQ(root->rsib, nullptr);
    ASSERT_EQ(root->lsib, nullptr);
}

TEST_F(InsertTerminate, 1ValueSmaller) {
    int first_val = 3, second_val = 1;
    root = insertTerminate(root, first_val);
    root = insertTerminate(root, second_val);

    ASSERT_EQ(root->lval, second_val);
    ASSERT_EQ(root->rval, first_val);
    ASSERT_EQ(root->max_child, first_val);

    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(InsertTerminate::isTerminate(root), true);

    ASSERT_EQ(root->rsib, nullptr);
    ASSERT_EQ(root->lsib, nullptr);
}

TEST_F(InsertTerminate, 1ValueBiggerSpecialValue) {
    int first_val = -1, second_val = 0;
    root = insertTerminate(root, first_val);
    root = insertTerminate(root, second_val);

    ASSERT_EQ(root->lval, first_val);
    ASSERT_EQ(root->rval, second_val);
    ASSERT_EQ(root->max_child, second_val);

    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(InsertTerminate::isTerminate(root), true);

    ASSERT_EQ(root->rsib, nullptr);
    ASSERT_EQ(root->lsib, nullptr);
}

TEST_F(InsertTerminate, 1ValueSmallerSpecialValue) {
    int first_val = -1, second_val = -2;
    root = insertTerminate(root, first_val);
    root = insertTerminate(root, second_val);

    ASSERT_EQ(root->lval, second_val);
    ASSERT_EQ(root->rval, first_val);
    ASSERT_EQ(root->max_child, first_val);

    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(InsertTerminate::isTerminate(root), true);

    ASSERT_EQ(root->rsib, nullptr);
    ASSERT_EQ(root->lsib, nullptr);
}

TEST_F(InsertTerminate, Split2NodeSmaller) {
    int first_val = 2, second_val = 4, insert_val = 1;
    root = insertTerminate(root, first_val);
    root = insertTerminate(root, second_val);
    root = insertTerminate(root, insert_val);

    ASSERT_EQ(root->lval, first_val);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, second_val);

    ASSERT_EQ(root->parent, nullptr);

    ASSERT_EQ(root->left->lval, insert_val);
    Node_t* v = root->left;
    ASSERT_EQ(v->parent, root);
    ASSERT_EQ(InsertTerminate::isTerminate(v), true);
    ASSERT_EQ(v->max_child, v->lval);
    ASSERT_EQ(v->rval, EMPTY);

    ASSERT_EQ(root->right->lval, second_val);
    Node_t* Y = root->right;
    ASSERT_EQ(Y->parent, root);
    ASSERT_EQ(InsertTerminate::isTerminate(Y), true);
    ASSERT_EQ(Y->max_child, Y->lval);
    ASSERT_EQ(Y->rval, EMPTY);

    ASSERT_EQ(v->rsib, Y);
    ASSERT_EQ(v->lsib, nullptr);
    ASSERT_EQ(Y->rsib, nullptr);
    ASSERT_EQ(Y->lsib, v);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(root->rsib, nullptr);
    ASSERT_EQ(root->lsib, nullptr);
}

TEST_F(InsertTerminate, Split2NodeMiddle) {
    int first_val = 2, second_val = 4, insert_val = 3;
    root = insertTerminate(root, first_val);
    root = insertTerminate(root, second_val);
    root = insertTerminate(root, insert_val);

    ASSERT_EQ(root->lval, insert_val);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, second_val);

    ASSERT_EQ(root->parent, nullptr);

    ASSERT_EQ(root->left->lval, first_val);
    Node_t* v = root->left;
    ASSERT_EQ(v->parent, root);
    ASSERT_EQ(InsertTerminate::isTerminate(v), true);
    ASSERT_EQ(v->max_child, v->lval);
    ASSERT_EQ(v->rval, EMPTY);

    ASSERT_EQ(root->right->lval, second_val);
    Node_t* Y = root->right;
    ASSERT_EQ(Y->parent, root);
    ASSERT_EQ(InsertTerminate::isTerminate(Y), true);
    ASSERT_EQ(Y->max_child, Y->lval);
    ASSERT_EQ(Y->rval, EMPTY);

    ASSERT_EQ(v->rsib, Y);
    ASSERT_EQ(v->lsib, nullptr);
    ASSERT_EQ(Y->rsib, nullptr);
    ASSERT_EQ(Y->lsib, v);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(root->rsib, nullptr);
    ASSERT_EQ(root->lsib, nullptr);
}

TEST_F(InsertTerminate, Split2NodeBigger) {
    int first_val = 2, second_val = 4, insert_val = 5;
    root = insertTerminate(root, first_val);
    root = insertTerminate(root, second_val);
    root = insertTerminate(root, insert_val);

    ASSERT_EQ(root->lval, second_val);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, insert_val);

    ASSERT_EQ(root->parent, nullptr);

    ASSERT_EQ(root->left->lval, first_val);
    Node_t* v = root->left;
    ASSERT_EQ(v->parent, root);
    ASSERT_EQ(InsertTerminate::isTerminate(v), true);
    ASSERT_EQ(v->max_child, v->lval);
    ASSERT_EQ(v->rval, EMPTY);

    ASSERT_EQ(root->right->lval, insert_val);
    Node_t* Y = root->right;
    ASSERT_EQ(Y->parent, root);
    ASSERT_EQ(InsertTerminate::isTerminate(Y), true);
    ASSERT_EQ(Y->max_child, Y->lval);
    ASSERT_EQ(Y->rval, EMPTY);

    ASSERT_EQ(v->rsib, Y);
    ASSERT_EQ(v->lsib, nullptr);
    ASSERT_EQ(Y->rsib, nullptr);
    ASSERT_EQ(Y->lsib, v);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(root->rsib, nullptr);
    ASSERT_EQ(root->lsib, nullptr);
}
