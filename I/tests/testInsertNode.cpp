#include <vector>
#include <exception>

#include <gtest/gtest.h>

#include "../23Tree.h"

class InsertNode : public testing::Test {
protected:
    Node_t* root = nullptr;

    InsertNode() = default;

    ~InsertNode() override { freeTree(root); }

    Node_t* prepareTerminal(const std::vector<int> &vals) {
        if (vals.size() <= 4) {
            for (auto i: vals)
                root = insertTerminate(root, i);
            return root;
        } else
            throw std::logic_error("Terminate node cannot have more than 4 leaves");
    }

    bool isTerminate(Node_t* node) {
        return node != nullptr && node->left == nullptr && node->middle == nullptr && node->right == nullptr;
    }
};

// tests for 2-1 case (kicked-up 2-valued into 1-valued)
TEST_F(InsertNode, 4Values_LeftLeft) {
    root = prepareTerminal({1, 3, 5, 7});
    root = insertNode(root, 0);

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->max_child, 7);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 0);
    ASSERT_EQ(left->rval, 1);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_EQ(left->left->lval, 0);
    ASSERT_EQ(left->middle->lval, 1);
    ASSERT_EQ(left->right->lval, 3);
    ASSERT_EQ(left->left->rsib, left->middle);
    ASSERT_EQ(left->middle->lsib, left->left);
    ASSERT_EQ(left->middle->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->middle);

    ASSERT_EQ(middle, nullptr);

    ASSERT_EQ(right->lval, 5);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 7);
    ASSERT_EQ(right->left->lval, 5);
    ASSERT_EQ(right->right->lval, 7);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->left->lsib, left->right);
    ASSERT_EQ(right->left->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->left);
}

TEST_F(InsertNode, 4Values_LeftLeft_Duplicates) {
    root = prepareTerminal({1, 3, 5, 7});
    root = insertNode(root, 0);
    ASSERT_EQ(root->right->middle, nullptr);
    ASSERT_EQ(root->middle, nullptr);

    root = insertNode(root, 1);
    ASSERT_EQ(root->left->rval, 1);
    ASSERT_EQ(root->right->middle, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    root = insertNode(root, 3);
    ASSERT_EQ(root->left->rval, 1);
    ASSERT_EQ(root->right->middle, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    root = insertNode(root, 5);
    ASSERT_EQ(root->left->rval, 1);
    ASSERT_EQ(root->right->middle, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    root = insertNode(root, 7);
    ASSERT_EQ(root->left->rval, 1);
    ASSERT_EQ(root->right->middle, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    root = insertNode(root, 0);
    ASSERT_EQ(root->left->rval, 1);
    ASSERT_EQ(root->right->middle, nullptr);
    ASSERT_EQ(root->middle, nullptr);

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->max_child, 7);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 0);
    ASSERT_EQ(left->rval, 1);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_EQ(left->left->lval, 0);
    ASSERT_EQ(left->middle->lval, 1);
    ASSERT_EQ(left->right->lval, 3);
    ASSERT_EQ(left->left->rsib, left->middle);
    ASSERT_EQ(left->middle->lsib, left->left);
    ASSERT_EQ(left->middle->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->middle);

    ASSERT_EQ(middle, nullptr);

    ASSERT_EQ(right->lval, 5);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 7);
    ASSERT_EQ(right->left->lval, 5);
    ASSERT_EQ(right->right->lval, 7);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->left->lsib, left->right);
    ASSERT_EQ(right->left->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->left);
}

TEST_F(InsertNode, 4Values_LeftRight) {
    root = prepareTerminal({1, 3, 5, 7});
    root = insertNode(root, 2);

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->max_child, 7);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 2);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->middle->lval, 2);
    ASSERT_EQ(left->right->lval, 3);
    ASSERT_EQ(left->left->rsib, left->middle);
    ASSERT_EQ(left->middle->lsib, left->left);
    ASSERT_EQ(left->middle->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->middle);

    ASSERT_EQ(middle, nullptr);

    ASSERT_EQ(right->lval, 5);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 7);
    ASSERT_EQ(right->left->lval, 5);
    ASSERT_EQ(right->right->lval, 7);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->left->lsib, left->right);
    ASSERT_EQ(right->left->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->left);
}

TEST_F(InsertNode, 4Values_Middle) {
    root = prepareTerminal({1, 3, 5, 7});
    root = insertNode(root, 4);

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->max_child, 7);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;


    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->right->lval, 3);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->left->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->left);
    ASSERT_EQ(left->right->rsib, right->left);

    ASSERT_EQ(middle, nullptr);

    ASSERT_EQ(right->lval, 4);
    ASSERT_EQ(right->rval, 5);
    ASSERT_EQ(right->max_child, 7);
    ASSERT_EQ(right->left->lval, 4);
    ASSERT_EQ(right->middle->lval, 5);
    ASSERT_EQ(right->right->lval, 7);
    ASSERT_EQ(right->left->lsib, left->right);
    ASSERT_EQ(right->left->rsib, right->middle);
    ASSERT_EQ(right->middle->lsib, right->left);
    ASSERT_EQ(right->middle->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->middle);
}

TEST_F(InsertNode, 4Values_RightLeft) {
    root = prepareTerminal({1, 3, 5, 7});
    root = insertNode(root, 6);

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->max_child, 7);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->right->lval, 3);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->left->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->left);
    ASSERT_EQ(left->right->rsib, right->left);

    ASSERT_EQ(middle, nullptr);

    ASSERT_EQ(right->lval, 5);
    ASSERT_EQ(right->rval, 6);
    ASSERT_EQ(right->max_child, 7);
    ASSERT_EQ(right->left->lval, 5);
    ASSERT_EQ(right->middle->lval, 6);
    ASSERT_EQ(right->right->lval, 7);
    ASSERT_EQ(right->left->lsib, left->right);
    ASSERT_EQ(right->left->rsib, right->middle);
    ASSERT_EQ(right->middle->lsib, right->left);
    ASSERT_EQ(right->middle->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->middle);
}

TEST_F(InsertNode, 4Values_RightRight) {
    root = prepareTerminal({1, 3, 5, 7});
    root = insertNode(root, 8);

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->max_child, 8);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->right->lval, 3);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->left->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->left);
    ASSERT_EQ(left->right->rsib, right->left);

    ASSERT_EQ(middle, nullptr);

    ASSERT_EQ(right->lval, 5);
    ASSERT_EQ(right->rval, 7);
    ASSERT_EQ(right->max_child, 8);
    ASSERT_EQ(right->left->lval, 5);
    ASSERT_EQ(right->middle->lval, 7);
    ASSERT_EQ(right->right->lval, 8);
    ASSERT_EQ(right->left->lsib, left->right);
    ASSERT_EQ(right->left->rsib, right->middle);
    ASSERT_EQ(right->middle->lsib, right->left);
    ASSERT_EQ(right->middle->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->middle);
}

// tests for 1-1 case (kicked-up 1-valued into 1-valued)
TEST_F(InsertNode, 6Nodes_Left1to1) {
    root = prepareTerminal({1, 4, 5, 6});
    root = insertNode(root, 3);
    root = insertNode(root, 2);

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->max_child, 6);

    Node_t* left = root->left, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 2);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->middle->lval, 2);
    ASSERT_EQ(left->right->lval, 3);
    ASSERT_EQ(left->left->rsib, left->middle);
    ASSERT_EQ(left->middle->lsib, left->left);
    ASSERT_EQ(left->middle->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->middle);
    ASSERT_EQ(left->right->rsib, right->left);

    ASSERT_EQ(right->lval, 4);
    ASSERT_EQ(right->rval, 5);
    ASSERT_EQ(right->max_child, 6);
    ASSERT_EQ(right->left->lval, 4);
    ASSERT_EQ(right->middle->lval, 5);
    ASSERT_EQ(right->right->lval, 6);
    ASSERT_EQ(right->left->lsib, left->right);
    ASSERT_EQ(right->left->rsib, right->middle);
    ASSERT_EQ(right->middle->lsib, right->left);
    ASSERT_EQ(right->middle->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->middle);
}

TEST_F(InsertNode, 6Nodes_Right1to1) {
    root = prepareTerminal({1, 2, 5, 8});
    root = insertNode(root, 7);
    root = insertNode(root, 6);

    ASSERT_EQ(root->lval, 5);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_NE(root->left, nullptr);
    ASSERT_EQ(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->max_child, 8);

    Node_t* left = root->left, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 2);
    ASSERT_EQ(left->max_child, 5);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->middle->lval, 2);
    ASSERT_EQ(left->right->lval, 5);
    ASSERT_EQ(left->left->rsib, left->middle);
    ASSERT_EQ(left->middle->lsib, left->left);
    ASSERT_EQ(left->middle->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->middle);
    ASSERT_EQ(left->right->rsib, right->left);

    ASSERT_EQ(right->lval, 6);
    ASSERT_EQ(right->rval, 7);
    ASSERT_EQ(right->max_child, 8);
    ASSERT_EQ(right->left->lval, 6);
    ASSERT_EQ(right->middle->lval, 7);
    ASSERT_EQ(right->right->lval, 8);
    ASSERT_EQ(right->left->lsib, left->right);
    ASSERT_EQ(right->left->rsib, right->middle);
    ASSERT_EQ(right->middle->lsib, right->left);
    ASSERT_EQ(right->middle->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->middle);
}

// tests for 2-2 case (kicked-up 2-valued into 2-valued)
TEST_F(InsertNode, 7Nodes_Left2to2) {
    root = prepareTerminal({1, 3, 4, 6});
    root = insertNode(root, 7);
    root = insertNode(root, 9);
    root = insertNode(root, 2); // to the left

    ASSERT_EQ(root->lval, 2);
    ASSERT_EQ(root->rval, 4);
    ASSERT_EQ(root->max_child, 9);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->max_child, 2);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->right->lval, 2);
    ASSERT_EQ(left->left->lsib, nullptr);
    ASSERT_EQ(left->left->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->left);
    ASSERT_EQ(left->right->rsib, middle->left);

    ASSERT_EQ(middle->lval, 3);
    ASSERT_EQ(middle->rval, EMPTY);
    ASSERT_EQ(middle->max_child, 4);
    ASSERT_EQ(middle->left->lval, 3);
    ASSERT_EQ(middle->middle, nullptr);
    ASSERT_EQ(middle->right->lval, 4);
    ASSERT_EQ(middle->left->lsib, left->right);
    ASSERT_EQ(middle->left->rsib, middle->right);
    ASSERT_EQ(middle->right->lsib, middle->left);
    ASSERT_EQ(middle->right->rsib, right->left);

    ASSERT_EQ(right->lval, 6);
    ASSERT_EQ(right->rval, 7);
    ASSERT_EQ(right->max_child, 9);
    ASSERT_EQ(right->left->lval, 6);
    ASSERT_EQ(right->middle->lval, 7);
    ASSERT_EQ(right->right->lval, 9);
    ASSERT_EQ(right->left->lsib, middle->right);
    ASSERT_EQ(right->left->rsib, right->middle);
    ASSERT_EQ(right->middle->lsib, right->left);
    ASSERT_EQ(right->middle->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->middle);
    ASSERT_EQ(right->right->rsib, nullptr);
}

TEST_F(InsertNode, 7Nodes_Right2to2) {
    root = prepareTerminal({1, 3, 4, 6});
    root = insertNode(root, 7);
    root = insertNode(root, 9);
    root = insertNode(root, 8); // to the right

    ASSERT_EQ(root->lval, 4);
    ASSERT_EQ(root->rval, 7);
    ASSERT_EQ(root->max_child, 9);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 3);
    ASSERT_EQ(left->max_child, 4);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->middle->lval, 3);
    ASSERT_EQ(left->right->lval, 4);
    ASSERT_EQ(left->left->lsib, nullptr);
    ASSERT_EQ(left->left->rsib, left->middle);
    ASSERT_EQ(left->middle->lsib, left->left);
    ASSERT_EQ(left->middle->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->middle);
    ASSERT_EQ(left->right->rsib, middle->left);

    ASSERT_EQ(middle->lval, 6);
    ASSERT_EQ(middle->rval, EMPTY);
    ASSERT_EQ(middle->max_child, 7);
    ASSERT_EQ(middle->left->lval, 6);
    ASSERT_EQ(middle->middle, nullptr);
    ASSERT_EQ(middle->right->lval, 7);
    ASSERT_EQ(middle->left->lsib, left->right);
    ASSERT_EQ(middle->left->rsib, middle->right);
    ASSERT_EQ(middle->right->lsib, middle->left);
    ASSERT_EQ(middle->right->rsib, right->left);

    ASSERT_EQ(right->lval, 8);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 9);
    ASSERT_EQ(right->left->lval, 8);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->right->lval, 9);
    ASSERT_EQ(right->left->lsib, middle->right);
    ASSERT_EQ(right->left->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->left);
    ASSERT_EQ(right->right->rsib, nullptr);
}

// tests for 1-2 case (kicked-up 1-valued into 2-valued)
TEST_F(InsertNode, 8Nodes_LeftMiddle1to2) { // insert into 2-valued on the left, merge with the middle
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    root = insertNode(root, 11); // splitting 2-node on the right, 2-valued on the left
    root = insertNode(root, 2); // splitting 2-node on the left

    ASSERT_EQ(root->lval, 4);
    ASSERT_EQ(root->rval, 9);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->middle, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 2);
    ASSERT_EQ(left->max_child, 4);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_NE(left->middle, nullptr);

    ASSERT_EQ(middle->lval, 5);
    ASSERT_EQ(middle->rval, 8);
    ASSERT_EQ(middle->max_child, 9);
    ASSERT_NE(middle->left, nullptr);
    ASSERT_NE(middle->right, nullptr);
    ASSERT_NE(middle->middle, nullptr);

    ASSERT_EQ(right->lval, 11);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 12);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_EQ(right->middle, nullptr);

    Node_t* lleft = left->left, * lmiddle = left->middle, * lright = left->right,
            * mleft = middle->left, * mmiddle = middle->middle, * mright = middle->right,
            * rleft = right->left, * rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 1);
    ASSERT_EQ(isTerminate(lleft), true);
    ASSERT_EQ(lleft->lsib, nullptr);
    ASSERT_EQ(lleft->rsib, lmiddle);

    ASSERT_EQ(lmiddle->lval, 2);
    ASSERT_EQ(lmiddle->rval, EMPTY);
    ASSERT_EQ(lmiddle->max_child, 2);
    ASSERT_EQ(lmiddle->lsib, lleft);
    ASSERT_EQ(lmiddle->rsib, lright);
    ASSERT_EQ(isTerminate(lmiddle), true);

    ASSERT_EQ(lright->lval, 4);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 4);
    ASSERT_EQ(lright->lsib, lmiddle);
    ASSERT_EQ(lright->rsib, mleft);
    ASSERT_EQ(isTerminate(lright), true);

    ASSERT_EQ(mleft->lval, 5);
    ASSERT_EQ(mleft->rval, EMPTY);
    ASSERT_EQ(mleft->max_child, 5);
    ASSERT_EQ(mleft->lsib, lright);
    ASSERT_EQ(mleft->rsib, mmiddle);
    ASSERT_EQ(isTerminate(mleft), true);

    ASSERT_EQ(mmiddle->lval, 8);
    ASSERT_EQ(mmiddle->rval, EMPTY);
    ASSERT_EQ(mmiddle->max_child, 8);
    ASSERT_EQ(mmiddle->lsib, mleft);
    ASSERT_EQ(mmiddle->rsib, mright);
    ASSERT_EQ(isTerminate(mmiddle), true);

    ASSERT_EQ(mright->lval, 9);
    ASSERT_EQ(mright->rval, EMPTY);
    ASSERT_EQ(mright->max_child, 9);
    ASSERT_EQ(mright->lsib, mmiddle);
    ASSERT_EQ(mright->rsib, rleft);
    ASSERT_EQ(isTerminate(mright), true);

    ASSERT_EQ(rleft->lval, 11);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 11);
    ASSERT_EQ(rleft->lsib, mright);
    ASSERT_EQ(rleft->rsib, rright);
    ASSERT_EQ(isTerminate(rleft), true);

    ASSERT_EQ(rright->lval, 12);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->lsib, rleft);
    ASSERT_EQ(rright->rsib, nullptr);
    ASSERT_EQ(isTerminate(rright), true);
}

TEST_F(InsertNode, 8Nodes_MiddleLeft1to2) { // insert into 2-valued on the middle, merge with the left
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    root = insertNode(root, 7); // making 2-node on the middle
    root = insertNode(root, 6); // splitting 2-node on the middle

    ASSERT_EQ(root->lval, 5);
    ASSERT_EQ(root->rval, 8);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->middle, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 4);
    ASSERT_EQ(left->max_child, 5);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_NE(left->middle, nullptr);

    ASSERT_EQ(middle->lval, 6);
    ASSERT_EQ(middle->rval, 7);
    ASSERT_EQ(middle->max_child, 8);
    ASSERT_NE(middle->left, nullptr);
    ASSERT_NE(middle->right, nullptr);
    ASSERT_NE(middle->middle, nullptr);

    ASSERT_EQ(right->lval, 9);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 12);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_EQ(right->middle, nullptr);

    Node_t* lleft = left->left, * lmiddle = left->middle, * lright = left->right,
            * mleft = middle->left, * mmiddle = middle->middle, * mright = middle->right,
            * rleft = right->left, * rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 1);
    ASSERT_EQ(isTerminate(lleft), true);
    ASSERT_EQ(lleft->lsib, nullptr);
    ASSERT_EQ(lleft->rsib, lmiddle);

    ASSERT_EQ(lmiddle->lval, 4);
    ASSERT_EQ(lmiddle->rval, EMPTY);
    ASSERT_EQ(lmiddle->max_child, 4);
    ASSERT_EQ(lmiddle->lsib, lleft);
    ASSERT_EQ(lmiddle->rsib, lright);
    ASSERT_EQ(isTerminate(lmiddle), true);

    ASSERT_EQ(lright->lval, 5);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 5);
    ASSERT_EQ(lright->lsib, lmiddle);
    ASSERT_EQ(lright->rsib, mleft);
    ASSERT_EQ(isTerminate(lright), true);

    ASSERT_EQ(mleft->lval, 6);
    ASSERT_EQ(mleft->rval, EMPTY);
    ASSERT_EQ(mleft->max_child, 6);
    ASSERT_EQ(mleft->lsib, lright);
    ASSERT_EQ(mleft->rsib, mmiddle);
    ASSERT_EQ(isTerminate(mleft), true);

    ASSERT_EQ(mmiddle->lval, 7);
    ASSERT_EQ(mmiddle->rval, EMPTY);
    ASSERT_EQ(mmiddle->max_child, 7);
    ASSERT_EQ(mmiddle->lsib, mleft);
    ASSERT_EQ(mmiddle->rsib, mright);
    ASSERT_EQ(isTerminate(mmiddle), true);

    ASSERT_EQ(mright->lval, 8);
    ASSERT_EQ(mright->rval, EMPTY);
    ASSERT_EQ(mright->max_child, 8);
    ASSERT_EQ(mright->lsib, mmiddle);
    ASSERT_EQ(mright->rsib, rleft);
    ASSERT_EQ(isTerminate(mright), true);

    ASSERT_EQ(rleft->lval, 9);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 9);
    ASSERT_EQ(rleft->lsib, mright);
    ASSERT_EQ(rleft->rsib, rright);
    ASSERT_EQ(isTerminate(rleft), true);

    ASSERT_EQ(rright->lval, 12);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->lsib, rleft);
    ASSERT_EQ(rright->rsib, nullptr);
    ASSERT_EQ(isTerminate(rright), true);
}

TEST_F(InsertNode, 8Nodes_RightMiddle1to2) { // insert into 2-valued on the right, merge with the middle
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    root = insertNode(root, 2); // splitting left
    root = insertNode(root, 10); // splitting 2-node on the right

    ASSERT_EQ(root->lval, 2);
    ASSERT_EQ(root->rval, 8);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->middle, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->max_child, 2);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_EQ(left->middle, nullptr);

    ASSERT_EQ(middle->lval, 4);
    ASSERT_EQ(middle->rval, 5);
    ASSERT_EQ(middle->max_child, 8);
    ASSERT_NE(middle->left, nullptr);
    ASSERT_NE(middle->right, nullptr);
    ASSERT_NE(middle->middle, nullptr);

    ASSERT_EQ(right->lval, 9);
    ASSERT_EQ(right->rval, 10);
    ASSERT_EQ(right->max_child, 12);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_NE(right->middle, nullptr);

    Node_t* lleft = left->left, * lright = left->right,
            * mleft = middle->left, * mmiddle = middle->middle, * mright = middle->right,
            * rleft = right->left, * rmiddle = right->middle, * rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 1);
    ASSERT_EQ(isTerminate(lleft), true);
    ASSERT_EQ(lleft->lsib, nullptr);
    ASSERT_EQ(lleft->rsib, lright);

    ASSERT_EQ(lright->lval, 2);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 2);
    ASSERT_EQ(lright->lsib, lleft);
    ASSERT_EQ(lright->rsib, mleft);
    ASSERT_EQ(isTerminate(lright), true);

    ASSERT_EQ(mleft->lval, 4);
    ASSERT_EQ(mleft->rval, EMPTY);
    ASSERT_EQ(mleft->max_child, 4);
    ASSERT_EQ(mleft->lsib, lright);
    ASSERT_EQ(mleft->rsib, mmiddle);
    ASSERT_EQ(isTerminate(mleft), true);

    ASSERT_EQ(mmiddle->lval, 5);
    ASSERT_EQ(mmiddle->rval, EMPTY);
    ASSERT_EQ(mmiddle->max_child, 5);
    ASSERT_EQ(mmiddle->lsib, mleft);
    ASSERT_EQ(mmiddle->rsib, mright);
    ASSERT_EQ(isTerminate(mmiddle), true);

    ASSERT_EQ(mright->lval, 8);
    ASSERT_EQ(mright->rval, EMPTY);
    ASSERT_EQ(mright->max_child, 8);
    ASSERT_EQ(mright->lsib, mmiddle);
    ASSERT_EQ(mright->rsib, rleft);
    ASSERT_EQ(isTerminate(mright), true);

    ASSERT_EQ(rleft->lval, 9);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 9);
    ASSERT_EQ(rleft->lsib, mright);
    ASSERT_EQ(rleft->rsib, rmiddle);
    ASSERT_EQ(isTerminate(rleft), true);

    ASSERT_EQ(rmiddle->lval, 10);
    ASSERT_EQ(rmiddle->rval, EMPTY);
    ASSERT_EQ(rmiddle->max_child, 10);
    ASSERT_EQ(rmiddle->lsib, rleft);
    ASSERT_EQ(rmiddle->rsib, rright);
    ASSERT_EQ(isTerminate(rmiddle), true);

    ASSERT_EQ(rright->lval, 12);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->lsib, rmiddle);
    ASSERT_EQ(rright->rsib, nullptr);
    ASSERT_EQ(isTerminate(rright), true);
}

TEST_F(InsertNode, 9Nodes_LeftRight1to2) { // insert into 2-valued on the left, merge with the right
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9); // right 2-valued node
    root = insertNode(root, 10);
    root = insertNode(root, 12);
    root = insertNode(root, 3); // making 2-node on the left
    root = insertNode(root, 2); // splitting 2-node on the left

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, 8);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->middle, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 2);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_NE(left->middle, nullptr);

    ASSERT_EQ(middle->lval, 4);
    ASSERT_EQ(middle->rval, 5);
    ASSERT_EQ(middle->max_child, 8);
    ASSERT_NE(middle->left, nullptr);
    ASSERT_NE(middle->right, nullptr);
    ASSERT_NE(middle->middle, nullptr);

    ASSERT_EQ(right->lval, 9);
    ASSERT_EQ(right->rval, 10);
    ASSERT_EQ(right->max_child, 12);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_NE(right->middle, nullptr);

    Node_t* lleft = left->left, * lmiddle = left->middle, * lright = left->right,
            * mleft = middle->left, * mmiddle = middle->middle, * mright = middle->right,
            * rleft = right->left, * rmiddle = right->middle, * rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 1);
    ASSERT_EQ(lleft->lsib, nullptr);
    ASSERT_EQ(lleft->rsib, lmiddle);
    ASSERT_EQ(isTerminate(lleft), true);

    ASSERT_EQ(lmiddle->lval, 2);
    ASSERT_EQ(lmiddle->rval, EMPTY);
    ASSERT_EQ(lmiddle->max_child, 2);
    ASSERT_EQ(lmiddle->lsib, lleft);
    ASSERT_EQ(lmiddle->rsib, lright);
    ASSERT_EQ(isTerminate(lmiddle), true);

    ASSERT_EQ(lright->lval, 3);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 3);
    ASSERT_EQ(lright->lsib, lmiddle);
    ASSERT_EQ(lright->rsib, mleft);
    ASSERT_EQ(isTerminate(lright), true);

    ASSERT_EQ(mleft->lval, 4);
    ASSERT_EQ(mleft->rval, EMPTY);
    ASSERT_EQ(mleft->max_child, 4);
    ASSERT_EQ(mleft->lsib, lright);
    ASSERT_EQ(mleft->rsib, mmiddle);
    ASSERT_EQ(isTerminate(mleft), true);

    ASSERT_EQ(mmiddle->lval, 5);
    ASSERT_EQ(mmiddle->rval, EMPTY);
    ASSERT_EQ(mmiddle->max_child, 5);
    ASSERT_EQ(mmiddle->lsib, mleft);
    ASSERT_EQ(mmiddle->rsib, mright);
    ASSERT_EQ(isTerminate(mmiddle), true);

    ASSERT_EQ(mright->lval, 8);
    ASSERT_EQ(mright->rval, EMPTY);
    ASSERT_EQ(mright->max_child, 8);
    ASSERT_EQ(mright->lsib, mmiddle);
    ASSERT_EQ(mright->rsib, rleft);
    ASSERT_EQ(isTerminate(mright), true);

    ASSERT_EQ(rleft->lval, 9);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 9);
    ASSERT_EQ(rleft->lsib, mright);
    ASSERT_EQ(rleft->rsib, rmiddle);
    ASSERT_EQ(isTerminate(rleft), true);

    ASSERT_EQ(rmiddle->lval, 10);
    ASSERT_EQ(rmiddle->rval, EMPTY);
    ASSERT_EQ(rmiddle->max_child, 10);
    ASSERT_EQ(rmiddle->lsib, rleft);
    ASSERT_EQ(rmiddle->rsib, rright);
    ASSERT_EQ(isTerminate(rmiddle), true);

    ASSERT_EQ(rright->lval, 12);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->lsib, rmiddle);
    ASSERT_EQ(rright->rsib, nullptr);
    ASSERT_EQ(isTerminate(rright), true);
}

TEST_F(InsertNode, 9Nodes_MiddleRight1to2) { // insert into 2-valued on the middle, merge with the right
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9); // right 2-valued node
    root = insertNode(root, 10);
    root = insertNode(root, 12);
    root = insertNode(root, 7); // making 2-node on the middle
    root = insertNode(root, 6); // splitting 2-node on the middle

    ASSERT_EQ(root->lval, 5);
    ASSERT_EQ(root->rval, 8);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->middle, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 4);
    ASSERT_EQ(left->max_child, 5);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_NE(left->middle, nullptr);

    ASSERT_EQ(middle->lval, 6);
    ASSERT_EQ(middle->rval, 7);
    ASSERT_EQ(middle->max_child, 8);
    ASSERT_NE(middle->left, nullptr);
    ASSERT_NE(middle->right, nullptr);
    ASSERT_NE(middle->middle, nullptr);

    ASSERT_EQ(right->lval, 9);
    ASSERT_EQ(right->rval, 10);
    ASSERT_EQ(right->max_child, 12);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_NE(right->middle, nullptr);

    Node_t* lleft = left->left, * lmiddle = left->middle, * lright = left->right,
            * mleft = middle->left, * mmiddle = middle->middle, * mright = middle->right,
            * rleft = right->left, * rmiddle = right->middle, * rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 1);
    ASSERT_EQ(lleft->lsib, nullptr);
    ASSERT_EQ(lleft->rsib, lmiddle);
    ASSERT_EQ(isTerminate(lleft), true);

    ASSERT_EQ(lmiddle->lval, 4);
    ASSERT_EQ(lmiddle->rval, EMPTY);
    ASSERT_EQ(lmiddle->max_child, 4);
    ASSERT_EQ(lmiddle->lsib, lleft);
    ASSERT_EQ(lmiddle->rsib, lright);
    ASSERT_EQ(isTerminate(lmiddle), true);

    ASSERT_EQ(lright->lval, 5);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 5);
    ASSERT_EQ(lright->lsib, lmiddle);
    ASSERT_EQ(lright->rsib, mleft);
    ASSERT_EQ(isTerminate(lright), true);

    ASSERT_EQ(mleft->lval, 6);
    ASSERT_EQ(mleft->rval, EMPTY);
    ASSERT_EQ(mleft->max_child, 6);
    ASSERT_EQ(mleft->lsib, lright);
    ASSERT_EQ(mleft->rsib, mmiddle);
    ASSERT_EQ(isTerminate(mleft), true);

    ASSERT_EQ(mmiddle->lval, 7);
    ASSERT_EQ(mmiddle->rval, EMPTY);
    ASSERT_EQ(mmiddle->max_child, 7);
    ASSERT_EQ(mmiddle->lsib, mleft);
    ASSERT_EQ(mmiddle->rsib, mright);
    ASSERT_EQ(isTerminate(mmiddle), true);

    ASSERT_EQ(mright->lval, 8);
    ASSERT_EQ(mright->rval, EMPTY);
    ASSERT_EQ(mright->max_child, 8);
    ASSERT_EQ(mright->lsib, mmiddle);
    ASSERT_EQ(mright->rsib, rleft);
    ASSERT_EQ(isTerminate(mright), true);

    ASSERT_EQ(rleft->lval, 9);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 9);
    ASSERT_EQ(rleft->lsib, mright);
    ASSERT_EQ(rleft->rsib, rmiddle);
    ASSERT_EQ(isTerminate(rleft), true);

    ASSERT_EQ(rmiddle->lval, 10);
    ASSERT_EQ(rmiddle->rval, EMPTY);
    ASSERT_EQ(rmiddle->max_child, 10);
    ASSERT_EQ(rmiddle->lsib, rleft);
    ASSERT_EQ(rmiddle->rsib, rright);
    ASSERT_EQ(isTerminate(rmiddle), true);

    ASSERT_EQ(rright->lval, 12);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->lsib, rmiddle);
    ASSERT_EQ(rright->rsib, nullptr);
    ASSERT_EQ(isTerminate(rright), true);
}

TEST_F(InsertNode, 9Nodes_RightLeft1to2) { // insert into 2-valued on the right, merge with the leftt
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    root = insertNode(root, 3); // left 2-valued node
    root = insertNode(root, 11); // making 2-node on the right
    root = insertNode(root, 10); // splitting 2-node on the right

    ASSERT_EQ(root->lval, 4);
    ASSERT_EQ(root->rval, 9);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->middle, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 3);
    ASSERT_EQ(left->max_child, 4);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_NE(left->middle, nullptr);

    ASSERT_EQ(middle->lval, 5);
    ASSERT_EQ(middle->rval, 8);
    ASSERT_EQ(middle->max_child, 9);
    ASSERT_NE(middle->left, nullptr);
    ASSERT_NE(middle->right, nullptr);
    ASSERT_NE(middle->middle, nullptr);

    ASSERT_EQ(right->lval, 10);
    ASSERT_EQ(right->rval, 11);
    ASSERT_EQ(right->max_child, 12);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_NE(right->middle, nullptr);

    Node_t* lleft = left->left, * lmiddle = left->middle, * lright = left->right,
            * mleft = middle->left, * mmiddle = middle->middle, * mright = middle->right,
            * rleft = right->left, * rmiddle = right->middle, * rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 1);
    ASSERT_EQ(lleft->lsib, nullptr);
    ASSERT_EQ(lleft->rsib, lmiddle);
    ASSERT_EQ(isTerminate(lleft), true);

    ASSERT_EQ(lmiddle->lval, 3);
    ASSERT_EQ(lmiddle->rval, EMPTY);
    ASSERT_EQ(lmiddle->max_child, 3);
    ASSERT_EQ(lmiddle->lsib, lleft);
    ASSERT_EQ(lmiddle->rsib, lright);
    ASSERT_EQ(isTerminate(lmiddle), true);

    ASSERT_EQ(lright->lval, 4);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 4);
    ASSERT_EQ(lright->lsib, lmiddle);
    ASSERT_EQ(lright->rsib, mleft);
    ASSERT_EQ(isTerminate(lright), true);

    ASSERT_EQ(mleft->lval, 5);
    ASSERT_EQ(mleft->rval, EMPTY);
    ASSERT_EQ(mleft->max_child, 5);
    ASSERT_EQ(mleft->lsib, lright);
    ASSERT_EQ(mleft->rsib, mmiddle);
    ASSERT_EQ(isTerminate(mleft), true);

    ASSERT_EQ(mmiddle->lval, 8);
    ASSERT_EQ(mmiddle->rval, EMPTY);
    ASSERT_EQ(mmiddle->max_child, 8);
    ASSERT_EQ(mmiddle->lsib, mleft);
    ASSERT_EQ(mmiddle->rsib, mright);
    ASSERT_EQ(isTerminate(mmiddle), true);

    ASSERT_EQ(mright->lval, 9);
    ASSERT_EQ(mright->rval, EMPTY);
    ASSERT_EQ(mright->max_child, 9);
    ASSERT_EQ(mright->lsib, mmiddle);
    ASSERT_EQ(mright->rsib, rleft);
    ASSERT_EQ(isTerminate(mright), true);

    ASSERT_EQ(rleft->lval, 10);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 10);
    ASSERT_EQ(rleft->lsib, mright);
    ASSERT_EQ(rleft->rsib, rmiddle);
    ASSERT_EQ(isTerminate(rleft), true);

    ASSERT_EQ(rmiddle->lval, 11);
    ASSERT_EQ(rmiddle->rval, EMPTY);
    ASSERT_EQ(rmiddle->max_child, 11);
    ASSERT_EQ(rmiddle->lsib, rleft);
    ASSERT_EQ(rmiddle->rsib, rright);
    ASSERT_EQ(isTerminate(rmiddle), true);

    ASSERT_EQ(rright->lval, 12);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->lsib, rmiddle);
    ASSERT_EQ(rright->rsib, nullptr);
    ASSERT_EQ(isTerminate(rright), true);
}

TEST_F(InsertNode, 10Nodes_Left1to2) { // insert into full 2-valued tree on the left
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    root = insertNode(root, 3); // 2-valued on the left
    root = insertNode(root, 7); // 2-valued on the middle
    root = insertNode(root, 11); // 2-valued on the right
    root = insertNode(root, 2); // split 2-valued left

    ASSERT_EQ(root->lval, 4);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->middle, nullptr);

    Node_t* left = root->left, * right = root->right;

    ASSERT_EQ(left->lval, 2);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->max_child, 4);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_EQ(left->middle, nullptr);

    ASSERT_EQ(right->lval, 8);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 12);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_EQ(right->middle, nullptr);

    Node_t* lleft = left->left, * lright = left->right,
            * rleft = right->left, * rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 2);
    ASSERT_EQ(lleft->left->lval, 1);
    ASSERT_EQ(lleft->right->lval, 2);
    ASSERT_EQ(lleft->middle, nullptr);

    ASSERT_EQ(lright->lval, 3);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 4);
    ASSERT_EQ(lright->left->lval, 3);
    ASSERT_EQ(lright->right->lval, 4);
    ASSERT_EQ(lright->middle, nullptr);

    ASSERT_EQ(rleft->lval, 5);
    ASSERT_EQ(rleft->rval, 7);
    ASSERT_EQ(rleft->max_child, 8);
    ASSERT_EQ(rleft->left->lval, 5);
    ASSERT_EQ(rleft->middle->lval, 7);
    ASSERT_EQ(rleft->right->lval, 8);

    ASSERT_EQ(rright->lval, 9);
    ASSERT_EQ(rright->rval, 11);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->left->lval, 9);
    ASSERT_EQ(rright->middle->lval, 11);
    ASSERT_EQ(rright->right->lval, 12);

    Node_t* llleft = lleft->left, * llright = lleft->right,
            * lrleft = lright->left, * lrright = lright->right,
            * rlleft = rleft->left, * rlmiddle = rleft->middle, * rlright = rleft->right,
            * rrleft = rright->left, * rrmiddle = rright->middle, * rrright = rright->right;

    ASSERT_EQ(llleft->lval, 1);
    ASSERT_EQ(llleft->rval, EMPTY);
    ASSERT_EQ(llleft->max_child, 1);
    ASSERT_EQ(llleft->lsib, nullptr);
    ASSERT_EQ(llleft->rsib, llright);
    ASSERT_EQ(isTerminate(llleft), true);

    ASSERT_EQ(llright->lval, 2);
    ASSERT_EQ(llright->rval, EMPTY);
    ASSERT_EQ(llright->max_child, 2);
    ASSERT_EQ(llright->lsib, llleft);
    ASSERT_EQ(llright->rsib, lrleft);
    ASSERT_EQ(isTerminate(llright), true);

    ASSERT_EQ(lrleft->lval, 3);
    ASSERT_EQ(lrleft->rval, EMPTY);
    ASSERT_EQ(lrleft->max_child, 3);
    ASSERT_EQ(lrleft->lsib, llright);
    ASSERT_EQ(lrleft->rsib, lrright);
    ASSERT_EQ(isTerminate(lrleft), true);

    ASSERT_EQ(lrright->lval, 4);
    ASSERT_EQ(lrright->rval, EMPTY);
    ASSERT_EQ(lrright->max_child, 4);
    ASSERT_EQ(lrright->lsib, lrleft);
    ASSERT_EQ(lrright->rsib, rlleft);
    ASSERT_EQ(isTerminate(lrright), true);

    ASSERT_EQ(rlleft->lval, 5);
    ASSERT_EQ(rlleft->rval, EMPTY);
    ASSERT_EQ(rlleft->max_child, 5);
    ASSERT_EQ(rlleft->lsib, lrright);
    ASSERT_EQ(rlleft->rsib, rlmiddle);
    ASSERT_EQ(isTerminate(rlleft), true);

    ASSERT_EQ(rlmiddle->lval, 7);
    ASSERT_EQ(rlmiddle->rval, EMPTY);
    ASSERT_EQ(rlmiddle->max_child, 7);
    ASSERT_EQ(rlmiddle->lsib, rlleft);
    ASSERT_EQ(rlmiddle->rsib, rlright);
    ASSERT_EQ(isTerminate(rlmiddle), true);

    ASSERT_EQ(rlright->lval, 8);
    ASSERT_EQ(rlright->rval, EMPTY);
    ASSERT_EQ(rlright->max_child, 8);
    ASSERT_EQ(rlright->lsib, rlmiddle);
    ASSERT_EQ(rlright->rsib, rrleft);
    ASSERT_EQ(isTerminate(rlright), true);

    ASSERT_EQ(rrleft->lval, 9);
    ASSERT_EQ(rrleft->rval, EMPTY);
    ASSERT_EQ(rrleft->max_child, 9);
    ASSERT_EQ(rrleft->lsib, rlright);
    ASSERT_EQ(rrleft->rsib, rrmiddle);
    ASSERT_EQ(isTerminate(rrleft), true);

    ASSERT_EQ(rrmiddle->lval, 11);
    ASSERT_EQ(rrmiddle->rval, EMPTY);
    ASSERT_EQ(rrmiddle->max_child, 11);
    ASSERT_EQ(rrmiddle->lsib, rrleft);
    ASSERT_EQ(rrmiddle->rsib, rrright);
    ASSERT_EQ(isTerminate(rrmiddle), true);

    ASSERT_EQ(rrright->lval, 12);
    ASSERT_EQ(rrright->rval, EMPTY);
    ASSERT_EQ(rrright->max_child, 12);
    ASSERT_EQ(rrright->lsib, rrmiddle);
    ASSERT_EQ(rrright->rsib, nullptr);
    ASSERT_EQ(isTerminate(rrright), true);
}

TEST_F(InsertNode, 10Nodes_Middle1to2) { // insert into full 2-valued tree on the middle
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    root = insertNode(root, 3); // 2-valued on the left
    root = insertNode(root, 7); // 2-valued on the middle
    root = insertNode(root, 11); // 2-valued on the right
    root = insertNode(root, 6); // split 2-valued middle

    ASSERT_EQ(root->lval, 6);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->middle, nullptr);

    Node_t* left = root->left, * right = root->right;

    ASSERT_EQ(left->lval, 4);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->max_child, 6);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_EQ(left->middle, nullptr);

    ASSERT_EQ(right->lval, 8);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 12);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_EQ(right->middle, nullptr);

    Node_t* lleft = left->left, * lright = left->right,
            * rleft = right->left, * rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, 3);
    ASSERT_EQ(lleft->max_child, 4);
    ASSERT_EQ(lleft->left->lval, 1);
    ASSERT_EQ(lleft->middle->lval, 3);
    ASSERT_EQ(lleft->right->lval, 4);

    ASSERT_EQ(lright->lval, 5);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 6);
    ASSERT_EQ(lright->left->lval, 5);
    ASSERT_EQ(lright->right->lval, 6);
    ASSERT_EQ(lright->middle, nullptr);

    ASSERT_EQ(rleft->lval, 7);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 8);
    ASSERT_EQ(rleft->left->lval, 7);
    ASSERT_EQ(rleft->middle, nullptr);
    ASSERT_EQ(rleft->right->lval, 8);

    ASSERT_EQ(rright->lval, 9);
    ASSERT_EQ(rright->rval, 11);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->left->lval, 9);
    ASSERT_EQ(rright->middle->lval, 11);
    ASSERT_EQ(rright->right->lval, 12);

    Node_t* llleft = lleft->left, * llmiddle = lleft->middle, * llright = lleft->right,
            * lrleft = lright->left, * lrright = lright->right,
            * rlleft = rleft->left, * rlright = rleft->right,
            * rrleft = rright->left, * rrmiddle = rright->middle, * rrright = rright->right;

    ASSERT_EQ(llleft->lval, 1);
    ASSERT_EQ(llleft->rval, EMPTY);
    ASSERT_EQ(llleft->max_child, 1);
    ASSERT_EQ(llleft->lsib, nullptr);
    ASSERT_EQ(llleft->rsib, llmiddle);
    ASSERT_EQ(isTerminate(llleft), true);

    ASSERT_EQ(llmiddle->lval, 3);
    ASSERT_EQ(llmiddle->rval, EMPTY);
    ASSERT_EQ(llmiddle->max_child, 3);
    ASSERT_EQ(llmiddle->lsib, llleft);
    ASSERT_EQ(llmiddle->rsib, llright);
    ASSERT_EQ(isTerminate(llmiddle), true);

    ASSERT_EQ(llright->lval, 4);
    ASSERT_EQ(llright->rval, EMPTY);
    ASSERT_EQ(llright->max_child, 4);
    ASSERT_EQ(llright->lsib, llmiddle);
    ASSERT_EQ(llright->rsib, lrleft);
    ASSERT_EQ(isTerminate(llright), true);

    ASSERT_EQ(lrleft->lval, 5);
    ASSERT_EQ(lrleft->rval, EMPTY);
    ASSERT_EQ(lrleft->max_child, 5);
    ASSERT_EQ(lrleft->lsib, llright);
    ASSERT_EQ(lrleft->rsib, lrright);
    ASSERT_EQ(isTerminate(lrleft), true);

    ASSERT_EQ(lrright->lval, 6);
    ASSERT_EQ(lrright->rval, EMPTY);
    ASSERT_EQ(lrright->max_child, 6);
    ASSERT_EQ(lrright->lsib, lrleft);
    ASSERT_EQ(lrright->rsib, rlleft);
    ASSERT_EQ(isTerminate(lrright), true);

    ASSERT_EQ(rlleft->lval, 7);
    ASSERT_EQ(rlleft->rval, EMPTY);
    ASSERT_EQ(rlleft->max_child, 7);
    ASSERT_EQ(rlleft->lsib, lrright);
    ASSERT_EQ(rlleft->rsib, rlright);
    ASSERT_EQ(isTerminate(rlleft), true);

    ASSERT_EQ(rlright->lval, 8);
    ASSERT_EQ(rlright->rval, EMPTY);
    ASSERT_EQ(rlright->max_child, 8);
    ASSERT_EQ(rlright->lsib, rlleft);
    ASSERT_EQ(rlright->rsib, rrleft);
    ASSERT_EQ(isTerminate(rlright), true);

    ASSERT_EQ(rrleft->lval, 9);
    ASSERT_EQ(rrleft->rval, EMPTY);
    ASSERT_EQ(rrleft->max_child, 9);
    ASSERT_EQ(rrleft->lsib, rlright);
    ASSERT_EQ(rrleft->rsib, rrmiddle);
    ASSERT_EQ(isTerminate(rrleft), true);

    ASSERT_EQ(rrmiddle->lval, 11);
    ASSERT_EQ(rrmiddle->rval, EMPTY);
    ASSERT_EQ(rrmiddle->max_child, 11);
    ASSERT_EQ(rrmiddle->lsib, rrleft);
    ASSERT_EQ(rrmiddle->rsib, rrright);
    ASSERT_EQ(isTerminate(rrmiddle), true);

    ASSERT_EQ(rrright->lval, 12);
    ASSERT_EQ(rrright->rval, EMPTY);
    ASSERT_EQ(rrright->max_child, 12);
    ASSERT_EQ(rrright->lsib, rrmiddle);
    ASSERT_EQ(rrright->rsib, nullptr);
    ASSERT_EQ(isTerminate(rrright), true);
}

TEST_F(InsertNode, 10Nodes_Right1to2) { // insert into full 2-valued tree on the right
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    root = insertNode(root, 3); // 2-valued on the left
    root = insertNode(root, 7); // 2-valued on the middle
    root = insertNode(root, 11); // 2-valued on the right
    root = insertNode(root, 10); // split 2-valued left

    ASSERT_EQ(root->lval, 8);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->middle, nullptr);

    Node_t* left = root->left, * right = root->right;

    ASSERT_EQ(left->lval, 4);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->max_child, 8);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_EQ(left->middle, nullptr);

    ASSERT_EQ(right->lval, 10);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 12);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_EQ(right->middle, nullptr);

    Node_t* lleft = left->left, * lright = left->right,
            * rleft = right->left, * rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, 3);
    ASSERT_EQ(lleft->max_child, 4);
    ASSERT_EQ(lleft->left->lval, 1);
    ASSERT_EQ(lleft->middle->lval, 3);
    ASSERT_EQ(lleft->right->lval, 4);

    ASSERT_EQ(lright->lval, 5);
    ASSERT_EQ(lright->rval, 7);
    ASSERT_EQ(lright->max_child, 8);
    ASSERT_EQ(lright->left->lval, 5);
    ASSERT_EQ(lright->middle->lval, 7);
    ASSERT_EQ(lright->right->lval, 8);

    ASSERT_EQ(rleft->lval, 9);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 10);
    ASSERT_EQ(rleft->left->lval, 9);
    ASSERT_EQ(rleft->middle, nullptr);
    ASSERT_EQ(rleft->right->lval, 10);

    ASSERT_EQ(rright->lval, 11);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->left->lval, 11);
    ASSERT_EQ(rright->middle, nullptr);
    ASSERT_EQ(rright->right->lval, 12);

    Node_t* llleft = lleft->left, * llmiddle = lleft->middle, * llright = lleft->right,
            * lrleft = lright->left, * lrmiddle = lright->middle, * lrright = lright->right,
            * rlleft = rleft->left, * rlright = rleft->right,
            * rrleft = rright->left, * rrright = rright->right;

    ASSERT_EQ(llleft->lval, 1);
    ASSERT_EQ(llleft->rval, EMPTY);
    ASSERT_EQ(llleft->max_child, 1);
    ASSERT_EQ(llleft->lsib, nullptr);
    ASSERT_EQ(llleft->rsib, llmiddle);
    ASSERT_EQ(isTerminate(llleft), true);

    ASSERT_EQ(llmiddle->lval, 3);
    ASSERT_EQ(llmiddle->rval, EMPTY);
    ASSERT_EQ(llmiddle->max_child, 3);
    ASSERT_EQ(llmiddle->lsib, llleft);
    ASSERT_EQ(llmiddle->rsib, llright);
    ASSERT_EQ(isTerminate(llmiddle), true);

    ASSERT_EQ(llright->lval, 4);
    ASSERT_EQ(llright->rval, EMPTY);
    ASSERT_EQ(llright->max_child, 4);
    ASSERT_EQ(llright->lsib, llmiddle);
    ASSERT_EQ(llright->rsib, lrleft);
    ASSERT_EQ(isTerminate(llright), true);

    ASSERT_EQ(lrleft->lval, 5);
    ASSERT_EQ(lrleft->rval, EMPTY);
    ASSERT_EQ(lrleft->max_child, 5);
    ASSERT_EQ(lrleft->lsib, llright);
    ASSERT_EQ(lrleft->rsib, lrmiddle);
    ASSERT_EQ(isTerminate(lrleft), true);

    ASSERT_EQ(lrmiddle->lval, 7);
    ASSERT_EQ(lrmiddle->rval, EMPTY);
    ASSERT_EQ(lrmiddle->max_child, 7);
    ASSERT_EQ(lrmiddle->lsib, lrleft);
    ASSERT_EQ(lrmiddle->rsib, lrright);
    ASSERT_EQ(isTerminate(lrmiddle), true);

    ASSERT_EQ(lrright->lval, 8);
    ASSERT_EQ(lrright->rval, EMPTY);
    ASSERT_EQ(lrright->max_child, 8);
    ASSERT_EQ(lrright->lsib, lrmiddle);
    ASSERT_EQ(lrright->rsib, rlleft);
    ASSERT_EQ(isTerminate(lrright), true);

    ASSERT_EQ(rlleft->lval, 9);
    ASSERT_EQ(rlleft->rval, EMPTY);
    ASSERT_EQ(rlleft->max_child, 9);
    ASSERT_EQ(rlleft->lsib, lrright);
    ASSERT_EQ(rlleft->rsib, rlright);
    ASSERT_EQ(isTerminate(rlleft), true);

    ASSERT_EQ(rlright->lval, 10);
    ASSERT_EQ(rlright->rval, EMPTY);
    ASSERT_EQ(rlright->max_child, 10);
    ASSERT_EQ(rlright->lsib, rlleft);
    ASSERT_EQ(rlright->rsib, rrleft);
    ASSERT_EQ(isTerminate(rlright), true);

    ASSERT_EQ(rrleft->lval, 11);
    ASSERT_EQ(rrleft->rval, EMPTY);
    ASSERT_EQ(rrleft->max_child, 11);
    ASSERT_EQ(rrleft->lsib, rlright);
    ASSERT_EQ(rrleft->rsib, rrright);
    ASSERT_EQ(isTerminate(rrleft), true);

    ASSERT_EQ(rrright->lval, 12);
    ASSERT_EQ(rrright->rval, EMPTY);
    ASSERT_EQ(rrright->max_child, 12);
    ASSERT_EQ(rrright->lsib, rrleft);
    ASSERT_EQ(rrright->rsib, nullptr);
    ASSERT_EQ(isTerminate(rrright), true);
}
