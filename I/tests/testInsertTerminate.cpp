#include <gtest/gtest.h>

#include "../23Tree.h"

class InsertTerminate: public testing::Test {
protected:
    Node_t* root = nullptr;

    InsertTerminate() = default;

    ~InsertTerminate() override = default; // TODO replace with actual freeing

    bool isTerminate(Node_t* node) {
        return node != nullptr && node->left == nullptr && node->middle == nullptr && node->right == nullptr;
    }
};

TEST_F(InsertTerminate, 1Value) {
    int val = 1;
    root = insertTerminate(root, val);

    ASSERT_EQ(root->left->lval, val);
    ASSERT_EQ(root->lval, val);
}

TEST_F(InsertTerminate, 2ValuesSmallBig) {
    int fval = 1, sval = 3;
    root = insertTerminate(root, fval);
    root = insertTerminate(root, sval);

    ASSERT_EQ(root->left->lval, fval);
    ASSERT_EQ(root->lval, fval);
    ASSERT_EQ(root->right->lval, sval);
    ASSERT_EQ(root->max_child, sval);
    ASSERT_EQ(root->left->rsib, root->right);
    ASSERT_EQ(root->right->lsib, root->left);
}

TEST_F(InsertTerminate, 2ValuesBigSmall) {
    int fval = 1, sval = 3;
    root = insertTerminate(root, sval);
    root = insertTerminate(root, fval);

    ASSERT_EQ(root->left->lval, fval);
    ASSERT_EQ(root->lval, fval);
    ASSERT_EQ(root->right->lval, sval);
    ASSERT_EQ(root->max_child, sval);
    ASSERT_EQ(root->left->rsib, root->right);
    ASSERT_EQ(root->right->lsib, root->left);
}

TEST_F(InsertTerminate, TurnInto2NodeLeft) {
    int lval = 0, mval = 1, rval = 3;
    root = insertTerminate(root, mval);
    root = insertTerminate(root, rval);
    root = insertTerminate(root, lval);

    ASSERT_EQ(root->lval, lval);
    ASSERT_EQ(root->rval, mval);
    ASSERT_EQ(root->left->lval, lval);
    ASSERT_EQ(root->middle->lval, mval);
    ASSERT_EQ(root->right->lval, rval);

    ASSERT_EQ(root->left->rsib, root->middle);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);
    ASSERT_EQ(root->right->lsib, root->middle);

    ASSERT_EQ(root->max_child, root->right->lval);
}

TEST_F(InsertTerminate, TurnInto2NodeMiddle) {
    int lval = 1, mval = 2, rval = 3;
    root = insertTerminate(root, lval);
    root = insertTerminate(root, rval);
    root = insertTerminate(root, mval);

    ASSERT_EQ(root->lval, lval);
    ASSERT_EQ(root->rval, mval);
    ASSERT_EQ(root->left->lval, lval);
    ASSERT_EQ(root->middle->lval, mval);
    ASSERT_EQ(root->right->lval, rval);

    ASSERT_EQ(root->left->rsib, root->middle);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);
    ASSERT_EQ(root->right->lsib, root->middle);

    ASSERT_EQ(root->max_child, root->right->lval);
}

TEST_F(InsertTerminate, TurnInto2NodeRight) {
    int lval = 1, mval = 3, rval = 4;
    root = insertTerminate(root, lval);
    root = insertTerminate(root, mval);
    root = insertTerminate(root, rval);

    ASSERT_EQ(root->lval, lval);
    ASSERT_EQ(root->rval, mval);
    ASSERT_EQ(root->left->lval, lval);
    ASSERT_EQ(root->middle->lval, mval);
    ASSERT_EQ(root->right->lval, rval);

    ASSERT_EQ(root->left->rsib, root->middle);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);
    ASSERT_EQ(root->right->lsib, root->middle);

    ASSERT_EQ(root->max_child, root->right->lval);
}

TEST_F(InsertTerminate, Split2NodeLeft) {
    int f = 0, s = 1, t = 3, fo = 5;
    root = insertTerminate(root, t);
    root = insertTerminate(root, fo);
    root = insertTerminate(root, s);
    root = insertTerminate(root, f);

    ASSERT_EQ(root->lval, s);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, fo);

    ASSERT_EQ(root->left->lval, f);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, nullptr);
    ASSERT_EQ(root->left->max_child, s);

    Node_t* first = root->left->left, * second = root->left->right,
            * third = root->right->left, * fourth = root->right->right;

    ASSERT_EQ(first->lval, f);
    ASSERT_EQ(first->rval, EMPTY);
    ASSERT_EQ(first->rsib, second);
    ASSERT_EQ(first->lsib, nullptr);

    ASSERT_EQ(second->lval, s);
    ASSERT_EQ(second->rval, EMPTY);
    ASSERT_EQ(second->rsib, third);
    ASSERT_EQ(second->lsib, first);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(third->lval, t);
    ASSERT_EQ(third->rval, EMPTY);
    ASSERT_EQ(third->rsib, fourth);
    ASSERT_EQ(third->lsib, second);

    ASSERT_EQ(fourth->lval, fo);
    ASSERT_EQ(fourth->rval, EMPTY);
    ASSERT_EQ(fourth->rsib, nullptr);
    ASSERT_EQ(fourth->lsib, third);

    ASSERT_EQ(root->right->lval, t);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->lsib, nullptr);
    ASSERT_EQ(root->right->rsib, nullptr);
    ASSERT_EQ(root->right->max_child, fo);
}

TEST_F(InsertTerminate, Split2NodeLeftMiddle) {
    int f = 1, s = 2, t = 3, fo = 5;
    root = insertTerminate(root, f);
    root = insertTerminate(root, t);
    root = insertTerminate(root, fo);
    root = insertTerminate(root, s);

    ASSERT_EQ(root->lval, s);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, fo);

    ASSERT_EQ(root->left->lval, f);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, nullptr);
    ASSERT_EQ(root->left->max_child, s);

    Node_t* first = root->left->left, * second = root->left->right,
            * third = root->right->left, * fourth = root->right->right;

    ASSERT_EQ(first->lval, f);
    ASSERT_EQ(first->rval, EMPTY);
    ASSERT_EQ(first->rsib, second);
    ASSERT_EQ(first->lsib, nullptr);

    ASSERT_EQ(second->lval, s);
    ASSERT_EQ(second->rval, EMPTY);
    ASSERT_EQ(second->rsib, third);
    ASSERT_EQ(second->lsib, first);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(third->lval, t);
    ASSERT_EQ(third->rval, EMPTY);
    ASSERT_EQ(third->rsib, fourth);
    ASSERT_EQ(third->lsib, second);

    ASSERT_EQ(fourth->lval, fo);
    ASSERT_EQ(fourth->rval, EMPTY);
    ASSERT_EQ(fourth->rsib, nullptr);
    ASSERT_EQ(fourth->lsib, third);

    ASSERT_EQ(root->right->lval, t);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->lsib, nullptr);
    ASSERT_EQ(root->right->rsib, nullptr);
    ASSERT_EQ(root->right->max_child, fo);
}

TEST_F(InsertTerminate, Split2NodeRightMiddle) {
    int f = 1, s = 3, t = 4, fo = 5;
    root = insertTerminate(root, f);
    root = insertTerminate(root, s);
    root = insertTerminate(root, fo);
    root = insertTerminate(root, t);

    ASSERT_EQ(root->lval, s);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, fo);

    ASSERT_EQ(root->left->lval, f);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, nullptr);
    ASSERT_EQ(root->left->max_child, s);

    Node_t* first = root->left->left, * second = root->left->right,
            * third = root->right->left, * fourth = root->right->right;

    ASSERT_EQ(first->lval, f);
    ASSERT_EQ(first->rval, EMPTY);
    ASSERT_EQ(first->rsib, second);
    ASSERT_EQ(first->lsib, nullptr);

    ASSERT_EQ(second->lval, s);
    ASSERT_EQ(second->rval, EMPTY);
    ASSERT_EQ(second->rsib, third);
    ASSERT_EQ(second->lsib, first);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(third->lval, t);
    ASSERT_EQ(third->rval, EMPTY);
    ASSERT_EQ(third->rsib, fourth);
    ASSERT_EQ(third->lsib, second);

    ASSERT_EQ(fourth->lval, fo);
    ASSERT_EQ(fourth->rval, EMPTY);
    ASSERT_EQ(fourth->rsib, nullptr);
    ASSERT_EQ(fourth->lsib, third);

    ASSERT_EQ(root->right->lval, t);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->lsib, nullptr);
    ASSERT_EQ(root->right->rsib, nullptr);
    ASSERT_EQ(root->right->max_child, fo);
}

TEST_F(InsertTerminate, Split2NodeRight) {
    int f = 1, s = 3, t = 5, fo = 6;
    root = insertTerminate(root, f);
    root = insertTerminate(root, s);
    root = insertTerminate(root, t);
    root = insertTerminate(root, fo);

    ASSERT_EQ(root->lval, s);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, fo);

    ASSERT_EQ(root->left->lval, f);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, nullptr);
    ASSERT_EQ(root->left->max_child, s);

    Node_t* first = root->left->left, * second = root->left->right,
            * third = root->right->left, * fourth = root->right->right;

    ASSERT_EQ(first->lval, f);
    ASSERT_EQ(first->rval, EMPTY);
    ASSERT_EQ(first->rsib, second);
    ASSERT_EQ(first->lsib, nullptr);

    ASSERT_EQ(second->lval, s);
    ASSERT_EQ(second->rval, EMPTY);
    ASSERT_EQ(second->rsib, third);
    ASSERT_EQ(second->lsib, first);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(third->lval, t);
    ASSERT_EQ(third->rval, EMPTY);
    ASSERT_EQ(third->rsib, fourth);
    ASSERT_EQ(third->lsib, second);

    ASSERT_EQ(fourth->lval, fo);
    ASSERT_EQ(fourth->rval, EMPTY);
    ASSERT_EQ(fourth->rsib, nullptr);
    ASSERT_EQ(fourth->lsib, third);

    ASSERT_EQ(root->right->lval, t);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->lsib, nullptr);
    ASSERT_EQ(root->right->rsib, nullptr);
    ASSERT_EQ(root->right->max_child, fo);
}