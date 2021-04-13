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

//TEST_F(InsertTerminate, emptyInsert) {
//    int val = 0;
//    root = insertTerminate(root, val);
//
//    ASSERT_EQ(root->lval, val);
//    ASSERT_EQ(root->rval, EMPTY);
//    ASSERT_EQ(root->max_child, val);
//
//    ASSERT_EQ(root->parent, nullptr);
//    ASSERT_EQ(InsertTerminate::isTerminate(root), true);
//
//    ASSERT_EQ(root->rsib, nullptr);
//    ASSERT_EQ(root->lsib, nullptr);
//}
//
//TEST_F(InsertTerminate, 1ValueBigger) {
//    int first_val = 1, second_val = 3;
//    root = insertTerminate(root, first_val);
//    root = insertTerminate(root, second_val);
//
//    ASSERT_EQ(root->lval, first_val);
//    ASSERT_EQ(root->rval, second_val);
//    ASSERT_EQ(root->max_child, second_val);
//
//    ASSERT_EQ(root->parent, nullptr);
//    ASSERT_EQ(InsertTerminate::isTerminate(root), true);
//
//    ASSERT_EQ(root->rsib, nullptr);
//    ASSERT_EQ(root->lsib, nullptr);
//}
//
//TEST_F(InsertTerminate, 1ValueSmaller) {
//    int first_val = 3, second_val = 1;
//    root = insertTerminate(root, first_val);
//    root = insertTerminate(root, second_val);
//
//    ASSERT_EQ(root->lval, second_val);
//    ASSERT_EQ(root->rval, first_val);
//    ASSERT_EQ(root->max_child, first_val);
//
//    ASSERT_EQ(root->parent, nullptr);
//    ASSERT_EQ(InsertTerminate::isTerminate(root), true);
//
//    ASSERT_EQ(root->rsib, nullptr);
//    ASSERT_EQ(root->lsib, nullptr);
//}
//
//TEST_F(InsertTerminate, 1ValueBiggerSpecialValue) {
//    int first_val = -1, second_val = 0;
//    root = insertTerminate(root, first_val);
//    root = insertTerminate(root, second_val);
//
//    ASSERT_EQ(root->lval, first_val);
//    ASSERT_EQ(root->rval, second_val);
//    ASSERT_EQ(root->max_child, second_val);
//
//    ASSERT_EQ(root->parent, nullptr);
//    ASSERT_EQ(InsertTerminate::isTerminate(root), true);
//
//    ASSERT_EQ(root->rsib, nullptr);
//    ASSERT_EQ(root->lsib, nullptr);
//}
//
//TEST_F(InsertTerminate, 1ValueSmallerSpecialValue) {
//    int first_val = -1, second_val = -2;
//    root = insertTerminate(root, first_val);
//    root = insertTerminate(root, second_val);
//
//    ASSERT_EQ(root->lval, second_val);
//    ASSERT_EQ(root->rval, first_val);
//    ASSERT_EQ(root->max_child, first_val);
//
//    ASSERT_EQ(root->parent, nullptr);
//    ASSERT_EQ(InsertTerminate::isTerminate(root), true);
//
//    ASSERT_EQ(root->rsib, nullptr);
//    ASSERT_EQ(root->lsib, nullptr);
//}
//
//TEST_F(InsertTerminate, Split2NodeSmaller) {
//    int first_val = 2, second_val = 4, insert_val = 1;
//    root = insertTerminate(root, first_val);
//    root = insertTerminate(root, second_val);
//    root = insertTerminate(root, insert_val);
//
//    ASSERT_EQ(root->lval, first_val);
//    ASSERT_EQ(root->rval, EMPTY);
//    ASSERT_EQ(root->max_child, second_val);
//
//    ASSERT_EQ(root->parent, nullptr);
//
//    ASSERT_EQ(root->left->lval, insert_val);
//    Node_t* v = root->left;
//    ASSERT_EQ(v->parent, root);
//    ASSERT_EQ(InsertTerminate::isTerminate(v), true);
//    ASSERT_EQ(v->max_child, v->lval);
//    ASSERT_EQ(v->rval, EMPTY);
//
//    ASSERT_EQ(root->right->lval, second_val);
//    Node_t* Y = root->right;
//    ASSERT_EQ(Y->parent, root);
//    ASSERT_EQ(InsertTerminate::isTerminate(Y), true);
//    ASSERT_EQ(Y->max_child, Y->lval);
//    ASSERT_EQ(Y->rval, EMPTY);
//
//    ASSERT_EQ(v->rsib, Y);
//    ASSERT_EQ(v->lsib, nullptr);
//    ASSERT_EQ(Y->rsib, nullptr);
//    ASSERT_EQ(Y->lsib, v);
//
//    ASSERT_EQ(root->middle, nullptr);
//
//    ASSERT_EQ(root->rsib, nullptr);
//    ASSERT_EQ(root->lsib, nullptr);
//}
//
//TEST_F(InsertTerminate, Split2NodeMiddle) {
//    int first_val = 2, second_val = 4, insert_val = 3;
//    root = insertTerminate(root, first_val);
//    root = insertTerminate(root, second_val);
//    root = insertTerminate(root, insert_val);
//
//    ASSERT_EQ(root->lval, insert_val);
//    ASSERT_EQ(root->rval, EMPTY);
//    ASSERT_EQ(root->max_child, second_val);
//
//    ASSERT_EQ(root->parent, nullptr);
//
//    ASSERT_EQ(root->left->lval, first_val);
//    Node_t* v = root->left;
//    ASSERT_EQ(v->parent, root);
//    ASSERT_EQ(InsertTerminate::isTerminate(v), true);
//    ASSERT_EQ(v->max_child, v->lval);
//    ASSERT_EQ(v->rval, EMPTY);
//
//    ASSERT_EQ(root->right->lval, second_val);
//    Node_t* Y = root->right;
//    ASSERT_EQ(Y->parent, root);
//    ASSERT_EQ(InsertTerminate::isTerminate(Y), true);
//    ASSERT_EQ(Y->max_child, Y->lval);
//    ASSERT_EQ(Y->rval, EMPTY);
//
//    ASSERT_EQ(v->rsib, Y);
//    ASSERT_EQ(v->lsib, nullptr);
//    ASSERT_EQ(Y->rsib, nullptr);
//    ASSERT_EQ(Y->lsib, v);
//
//    ASSERT_EQ(root->middle, nullptr);
//
//    ASSERT_EQ(root->rsib, nullptr);
//    ASSERT_EQ(root->lsib, nullptr);
//}
//
//TEST_F(InsertTerminate, Split2NodeBigger) {
//    int first_val = 2, second_val = 4, insert_val = 5;
//    root = insertTerminate(root, first_val);
//    root = insertTerminate(root, second_val);
//    root = insertTerminate(root, insert_val);
//
//    ASSERT_EQ(root->lval, second_val);
//    ASSERT_EQ(root->rval, EMPTY);
//    ASSERT_EQ(root->max_child, insert_val);
//
//    ASSERT_EQ(root->parent, nullptr);
//
//    ASSERT_EQ(root->left->lval, first_val);
//    Node_t* v = root->left;
//    ASSERT_EQ(v->parent, root);
//    ASSERT_EQ(InsertTerminate::isTerminate(v), true);
//    ASSERT_EQ(v->max_child, v->lval);
//    ASSERT_EQ(v->rval, EMPTY);
//
//    ASSERT_EQ(root->right->lval, insert_val);
//    Node_t* Y = root->right;
//    ASSERT_EQ(Y->parent, root);
//    ASSERT_EQ(InsertTerminate::isTerminate(Y), true);
//    ASSERT_EQ(Y->max_child, Y->lval);
//    ASSERT_EQ(Y->rval, EMPTY);
//
//    ASSERT_EQ(v->rsib, Y);
//    ASSERT_EQ(v->lsib, nullptr);
//    ASSERT_EQ(Y->rsib, nullptr);
//    ASSERT_EQ(Y->lsib, v);
//
//    ASSERT_EQ(root->middle, nullptr);
//
//    ASSERT_EQ(root->rsib, nullptr);
//    ASSERT_EQ(root->lsib, nullptr);
//}

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
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->middle->parent, root);
    ASSERT_EQ(root->right->parent, root);

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
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->middle->parent, root);
    ASSERT_EQ(root->right->parent, root);

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
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->middle->parent, root);
    ASSERT_EQ(root->right->parent, root);

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
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, fo);

    ASSERT_EQ(root->left->lval, f);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, nullptr);
    ASSERT_EQ(root->left->max_child, s);

    Node_t* first = root->left->left, * second = root->left->right,
            * third = root->right->left, * fourth = root->right->right;

    ASSERT_EQ(first->lval, f);
    ASSERT_EQ(first->rval, EMPTY);
    ASSERT_EQ(first->rsib, second);
    ASSERT_EQ(first->lsib, nullptr);
    ASSERT_EQ(first->parent, root->left);

    ASSERT_EQ(second->lval, s);
    ASSERT_EQ(second->rval, EMPTY);
    ASSERT_EQ(second->rsib, third);
    ASSERT_EQ(second->lsib, first);
    ASSERT_EQ(second->parent, root->left);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(third->lval, t);
    ASSERT_EQ(third->rval, EMPTY);
    ASSERT_EQ(third->rsib, fourth);
    ASSERT_EQ(third->lsib, second);
    ASSERT_EQ(third->parent, root->right);

    ASSERT_EQ(fourth->lval, fo);
    ASSERT_EQ(fourth->rval, EMPTY);
    ASSERT_EQ(fourth->rsib, nullptr);
    ASSERT_EQ(fourth->lsib, third);
    ASSERT_EQ(fourth->parent, root->right);

    ASSERT_EQ(root->right->lval, t);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->parent, root);
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
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, fo);

    ASSERT_EQ(root->left->lval, f);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, nullptr);
    ASSERT_EQ(root->left->max_child, s);

    Node_t* first = root->left->left, * second = root->left->right,
            * third = root->right->left, * fourth = root->right->right;

    ASSERT_EQ(first->lval, f);
    ASSERT_EQ(first->rval, EMPTY);
    ASSERT_EQ(first->rsib, second);
    ASSERT_EQ(first->lsib, nullptr);
    ASSERT_EQ(first->parent, root->left);

    ASSERT_EQ(second->lval, s);
    ASSERT_EQ(second->rval, EMPTY);
    ASSERT_EQ(second->rsib, third);
    ASSERT_EQ(second->lsib, first);
    ASSERT_EQ(second->parent, root->left);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(third->lval, t);
    ASSERT_EQ(third->rval, EMPTY);
    ASSERT_EQ(third->rsib, fourth);
    ASSERT_EQ(third->lsib, second);
    ASSERT_EQ(third->parent, root->right);

    ASSERT_EQ(fourth->lval, fo);
    ASSERT_EQ(fourth->rval, EMPTY);
    ASSERT_EQ(fourth->rsib, nullptr);
    ASSERT_EQ(fourth->lsib, third);
    ASSERT_EQ(fourth->parent, root->right);

    ASSERT_EQ(root->right->lval, t);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->parent, root);
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
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, fo);

    ASSERT_EQ(root->left->lval, f);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, nullptr);
    ASSERT_EQ(root->left->max_child, s);

    Node_t* first = root->left->left, * second = root->left->right,
            * third = root->right->left, * fourth = root->right->right;

    ASSERT_EQ(first->lval, f);
    ASSERT_EQ(first->rval, EMPTY);
    ASSERT_EQ(first->rsib, second);
    ASSERT_EQ(first->lsib, nullptr);
    ASSERT_EQ(first->parent, root->left);

    ASSERT_EQ(second->lval, s);
    ASSERT_EQ(second->rval, EMPTY);
    ASSERT_EQ(second->rsib, third);
    ASSERT_EQ(second->lsib, first);
    ASSERT_EQ(second->parent, root->left);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(third->lval, t);
    ASSERT_EQ(third->rval, EMPTY);
    ASSERT_EQ(third->rsib, fourth);
    ASSERT_EQ(third->lsib, second);
    ASSERT_EQ(third->parent, root->right);

    ASSERT_EQ(fourth->lval, fo);
    ASSERT_EQ(fourth->rval, EMPTY);
    ASSERT_EQ(fourth->rsib, nullptr);
    ASSERT_EQ(fourth->lsib, third);
    ASSERT_EQ(fourth->parent, root->right);

    ASSERT_EQ(root->right->lval, t);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->parent, root);
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
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, fo);

    ASSERT_EQ(root->left->lval, f);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, nullptr);
    ASSERT_EQ(root->left->max_child, s);

    Node_t* first = root->left->left, * second = root->left->right,
            * third = root->right->left, * fourth = root->right->right;

    ASSERT_EQ(first->lval, f);
    ASSERT_EQ(first->rval, EMPTY);
    ASSERT_EQ(first->rsib, second);
    ASSERT_EQ(first->lsib, nullptr);
    ASSERT_EQ(first->parent, root->left);

    ASSERT_EQ(second->lval, s);
    ASSERT_EQ(second->rval, EMPTY);
    ASSERT_EQ(second->rsib, third);
    ASSERT_EQ(second->lsib, first);
    ASSERT_EQ(second->parent, root->left);

    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(third->lval, t);
    ASSERT_EQ(third->rval, EMPTY);
    ASSERT_EQ(third->rsib, fourth);
    ASSERT_EQ(third->lsib, second);
    ASSERT_EQ(third->parent, root->right);

    ASSERT_EQ(fourth->lval, fo);
    ASSERT_EQ(fourth->rval, EMPTY);
    ASSERT_EQ(fourth->rsib, nullptr);
    ASSERT_EQ(fourth->lsib, third);
    ASSERT_EQ(fourth->parent, root->right);

    ASSERT_EQ(root->right->lval, t);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->right->lsib, nullptr);
    ASSERT_EQ(root->right->rsib, nullptr);
    ASSERT_EQ(root->right->max_child, fo);
}