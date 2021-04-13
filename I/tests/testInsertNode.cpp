#include <vector>
#include <exception>

#include <gtest/gtest.h>

#include "../23Tree.h"

class InsertNode : public testing::Test {
protected:
    Node_t* root = nullptr;

    InsertNode() = default;

    ~InsertNode() override = default; // TODO replace with actual freeing

    Node_t* prepareTerminal(const std::vector<int> &vals) {
        if (vals.size() <= 4) {
            for (auto i: vals)
                root = insertTerminate(root, i);
            return root;
        } else
            throw std::logic_error("Terminate node cannot have more than 4 leaves");

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
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 7);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 0);
    ASSERT_EQ(left->rval, 1);
    ASSERT_EQ(left->parent, root);
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
    ASSERT_EQ(right->parent, root);
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
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 7);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 2);
    ASSERT_EQ(left->parent, root);
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
    ASSERT_EQ(right->parent, root);
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
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 7);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;


    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->parent, root);
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
    ASSERT_EQ(right->parent, root);
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
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 7);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->parent, root);
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
    ASSERT_EQ(right->parent, root);
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
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 8);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->parent, root);
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
    ASSERT_EQ(right->parent, root);
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

    ASSERT_EQ(root->lval, 2);
    ASSERT_EQ(root->rval, 4);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 6);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->parent, root);
    ASSERT_EQ(left->max_child, 2);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->right->lval, 2);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->left->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->left);
    ASSERT_EQ(left->right->rsib, middle->left);

    ASSERT_EQ(middle->lval, 3);
    ASSERT_EQ(middle->rval, EMPTY);
    ASSERT_EQ(middle->parent, root);
    ASSERT_EQ(middle->max_child, 4);
    ASSERT_EQ(middle->left->lval, 3);
    ASSERT_EQ(middle->right->lval, 4);
    ASSERT_EQ(middle->middle, nullptr);
    ASSERT_EQ(middle->left->lsib, left->right);
    ASSERT_EQ(middle->left->rsib, middle->right);
    ASSERT_EQ(middle->right->lsib, middle->left);
    ASSERT_EQ(middle->right->rsib, right->left);

    ASSERT_EQ(right->lval, 5);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->parent, root);
    ASSERT_EQ(right->max_child, 6);
    ASSERT_EQ(right->left->lval, 5);
    ASSERT_EQ(right->right->lval, 6);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->left->lsib, middle->right);
    ASSERT_EQ(right->left->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->left);
}

TEST_F(InsertNode, 6Nodes_Right1to1) {
    root = prepareTerminal({1, 2, 3, 7});
    root = insertNode(root, 6);
    root = insertNode(root, 5);

    ASSERT_EQ(root->lval, 2);
    ASSERT_EQ(root->rval, 5);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 7);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->parent, root);
    ASSERT_EQ(left->max_child, 2);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->right->lval, 2);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->left->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->left);
    ASSERT_EQ(left->right->rsib, middle->left);

    ASSERT_EQ(middle->lval, 3);
    ASSERT_EQ(middle->rval, EMPTY);
    ASSERT_EQ(middle->parent, root);
    ASSERT_EQ(middle->max_child, 5);
    ASSERT_EQ(middle->left->lval, 3);
    ASSERT_EQ(middle->right->lval, 5);
    ASSERT_EQ(middle->middle, nullptr);
    ASSERT_EQ(middle->left->lsib, left->right);
    ASSERT_EQ(middle->left->rsib, middle->right);
    ASSERT_EQ(middle->right->lsib, middle->left);
    ASSERT_EQ(middle->right->rsib, right->left);

    ASSERT_EQ(right->lval, 6);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->parent, root);
    ASSERT_EQ(right->max_child, 7);
    ASSERT_EQ(right->left->lval, 6);
    ASSERT_EQ(right->right->lval, 7);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->left->lsib, middle->right);
    ASSERT_EQ(right->left->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->left);
}

// tests for 2-2 case (kicked-up 2-valued into 2-valued)
TEST_F(InsertNode, 7Nodes_Left2to2) {
    root = prepareTerminal({1, 3, 4, 6});
    root = insertNode(root, 7);
    root = insertNode(root, 9);
    root = insertNode(root, 2); // to the left

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, 6);
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 9);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, 2);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_EQ(left->parent, root);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->middle->lval, 2);
    ASSERT_EQ(left->right->lval, 3);
    ASSERT_EQ(left->left->lsib, nullptr);
    ASSERT_EQ(left->left->rsib, left->middle);
    ASSERT_EQ(left->middle->lsib, left->left);
    ASSERT_EQ(left->middle->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->middle);
    ASSERT_EQ(left->right->rsib, middle->left);

    ASSERT_EQ(middle->lval, 4);
    ASSERT_EQ(middle->rval, EMPTY);
    ASSERT_EQ(middle->max_child, 6);
    ASSERT_EQ(middle->parent, root);
    ASSERT_EQ(middle->left->lval, 4);
    ASSERT_EQ(middle->middle, nullptr);
    ASSERT_EQ(middle->right->lval, 6);
    ASSERT_EQ(middle->left->lsib, left->right);
    ASSERT_EQ(middle->left->rsib, middle->right);
    ASSERT_EQ(middle->right->lsib, middle->left);
    ASSERT_EQ(middle->right->rsib, right->left);

    ASSERT_EQ(right->lval, 7);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 9);
    ASSERT_EQ(right->parent, root);
    ASSERT_EQ(right->left->lval, 7);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->right->lval, 9);
    ASSERT_EQ(right->left->lsib, middle->right);
    ASSERT_EQ(right->left->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->left);
    ASSERT_EQ(right->right->rsib, nullptr);
}

TEST_F(InsertNode, 7Nodes_Middle2to2) {
    root = prepareTerminal({1, 3, 4, 6});
    root = insertNode(root, 7);
    root = insertNode(root, 9);
    root = insertNode(root, 5); // to the middle

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, 6);
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 9);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_EQ(left->parent, root);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->right->lval, 3);
    ASSERT_EQ(left->left->lsib, nullptr);
    ASSERT_EQ(left->left->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->left);
    ASSERT_EQ(left->right->rsib, middle->left);

    ASSERT_EQ(middle->lval, 4);
    ASSERT_EQ(middle->rval, 5);
    ASSERT_EQ(middle->max_child, 6);
    ASSERT_EQ(middle->parent, root);
    ASSERT_EQ(middle->left->lval, 4);
    ASSERT_EQ(middle->middle->lval, 5);
    ASSERT_EQ(middle->right->lval, 6);
    ASSERT_EQ(middle->left->lsib, left->right);
    ASSERT_EQ(middle->left->rsib, middle->middle);
    ASSERT_EQ(middle->middle->lsib, middle->left);
    ASSERT_EQ(middle->middle->rsib, middle->right);
    ASSERT_EQ(middle->right->lsib, middle->middle);
    ASSERT_EQ(middle->right->rsib, right->left);

    ASSERT_EQ(right->lval, 7);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->max_child, 9);
    ASSERT_EQ(right->parent, root);
    ASSERT_EQ(right->left->lval, 7);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->right->lval, 9);
    ASSERT_EQ(right->left->lsib, middle->right);
    ASSERT_EQ(right->left->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->left);
    ASSERT_EQ(right->right->rsib, nullptr);
}

TEST_F(InsertNode, 7Nodes_Right2to2) {
    root = prepareTerminal({1, 3, 4, 6});
    root = insertNode(root, 7);
    root = insertNode(root, 9);
    root = insertNode(root, 8); // to the right

    ASSERT_EQ(root->lval, 3);
    ASSERT_EQ(root->rval, 6);
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 9);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->middle, nullptr);
    ASSERT_NE(root->right, nullptr);

    Node_t* left = root->left, * middle = root->middle, * right = root->right;

    ASSERT_EQ(left->lval, 1);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->max_child, 3);
    ASSERT_EQ(left->parent, root);
    ASSERT_EQ(left->left->lval, 1);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->right->lval, 3);
    ASSERT_EQ(left->left->lsib, nullptr);
    ASSERT_EQ(left->left->rsib, left->right);
    ASSERT_EQ(left->right->lsib, left->left);
    ASSERT_EQ(left->right->rsib, middle->left);

    ASSERT_EQ(middle->lval, 4);
    ASSERT_EQ(middle->rval, EMPTY);
    ASSERT_EQ(middle->max_child, 6);
    ASSERT_EQ(middle->parent, root);
    ASSERT_EQ(middle->left->lval, 4);
    ASSERT_EQ(middle->middle, nullptr);
    ASSERT_EQ(middle->right->lval, 6);
    ASSERT_EQ(middle->left->lsib, left->right);
    ASSERT_EQ(middle->left->rsib, middle->right);
    ASSERT_EQ(middle->right->lsib, middle->left);
    ASSERT_EQ(middle->right->rsib, right->left);

    ASSERT_EQ(right->lval, 7);
    ASSERT_EQ(right->rval, 8);
    ASSERT_EQ(right->max_child, 9);
    ASSERT_EQ(right->parent, root);
    ASSERT_EQ(right->left->lval, 7);
    ASSERT_EQ(right->middle->lval, 8);
    ASSERT_EQ(right->right->lval, 9);
    ASSERT_EQ(right->left->lsib, middle->right);
    ASSERT_EQ(right->left->rsib, right->middle);
    ASSERT_EQ(right->middle->lsib, right->left);
    ASSERT_EQ(right->middle->rsib, right->right);
    ASSERT_EQ(right->right->lsib, right->middle);
    ASSERT_EQ(right->right->rsib, nullptr);
}

// tests for 1-2 case (kicked-up 1-valued into 2-valued)
TEST_F(InsertNode, 8Nodes_Left1to2) {
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    root = insertNode(root, 3); // making 2-node on the left
    root = insertNode(root, 2); // splitting 2-node on the left

    ASSERT_EQ(root->lval, 4);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->middle, nullptr);

    Node_t* left = root->left, *right = root->right;

    ASSERT_EQ(left->lval, 2);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->parent, root);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->max_child, 4);

    ASSERT_EQ(right->lval, 8);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->parent, root);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->max_child, 12);

    Node_t* lleft = left->left, *lright = left->right, *rleft = right->left, *rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->parent, left);
    ASSERT_EQ(lleft->max_child, 2);
    ASSERT_EQ(lleft->left->lval, 1);
    ASSERT_EQ(lleft->right->lval, 2);
    ASSERT_EQ(lleft->left->lsib, nullptr);
    ASSERT_EQ(lleft->left->rsib, lleft->right);
    ASSERT_EQ(lleft->right->lsib, lleft->left);
    ASSERT_EQ(lleft->right->rsib, lright->left);

    ASSERT_EQ(lright->lval, 3);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->parent, left);
    ASSERT_EQ(lright->max_child, 4);
    ASSERT_EQ(lright->left->lval, 3);
    ASSERT_EQ(lright->right->lval, 4);
    ASSERT_EQ(lright->left->lsib, lleft->right);
    ASSERT_EQ(lright->left->rsib, lright->right);
    ASSERT_EQ(lright->right->lsib, lright->left);
    ASSERT_EQ(lright->right->rsib, rleft->left);

    ASSERT_EQ(rleft->lval, 5);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->parent, right);
    ASSERT_EQ(rleft->max_child, 8);
    ASSERT_EQ(rleft->left->lval, 5);
    ASSERT_EQ(rleft->right->lval, 8);
    ASSERT_EQ(rleft->left->lsib, lright->right);
    ASSERT_EQ(rleft->left->rsib, rleft->right);
    ASSERT_EQ(rleft->right->lsib, rleft->left);
    ASSERT_EQ(rleft->right->rsib, rright->left);

    ASSERT_EQ(rright->lval, 9);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->parent, right);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->left->lval, 9);
    ASSERT_EQ(rright->right->lval, 12);
    ASSERT_EQ(rright->left->lsib, rleft->right);
    ASSERT_EQ(rright->left->rsib, rright->right);
    ASSERT_EQ(rright->right->lsib, rright->left);
    ASSERT_EQ(rright->right->rsib, nullptr);
}

TEST_F(InsertNode, 8Nodes_Middle1to2) {
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    root = insertNode(root, 7); // making 2-node in the middle
    root = insertNode(root, 6); // splitting 2-node in the middle

    ASSERT_EQ(root->lval, 6);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->middle, nullptr);

    Node_t* left = root->left, *right = root->right;

    ASSERT_EQ(left->lval, 4);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->parent, root);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->max_child, 6);

    ASSERT_EQ(right->lval, 8);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->parent, root);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->max_child, 12);

    Node_t* lleft = left->left, *lright = left->right, *rleft = right->left, *rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->parent, left);
    ASSERT_EQ(lleft->max_child, 4);
    ASSERT_EQ(lleft->left->lval, 1);
    ASSERT_EQ(lleft->right->lval, 4);
    ASSERT_EQ(lleft->left->lsib, nullptr);
    ASSERT_EQ(lleft->left->rsib, lleft->right);
    ASSERT_EQ(lleft->right->lsib, lleft->left);
    ASSERT_EQ(lleft->right->rsib, lright->left);

    ASSERT_EQ(lright->lval, 5);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->parent, left);
    ASSERT_EQ(lright->max_child, 6);
    ASSERT_EQ(lright->left->lval, 5);
    ASSERT_EQ(lright->right->lval, 6);
    ASSERT_EQ(lright->left->lsib, lleft->right);
    ASSERT_EQ(lright->left->rsib, lright->right);
    ASSERT_EQ(lright->right->lsib, lright->left);
    ASSERT_EQ(lright->right->rsib, rleft->left);

    ASSERT_EQ(rleft->lval, 7);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->parent, right);
    ASSERT_EQ(rleft->max_child, 8);
    ASSERT_EQ(rleft->left->lval, 7);
    ASSERT_EQ(rleft->right->lval, 8);
    ASSERT_EQ(rleft->left->lsib, lright->right);
    ASSERT_EQ(rleft->left->rsib, rleft->right);
    ASSERT_EQ(rleft->right->lsib, rleft->left);
    ASSERT_EQ(rleft->right->rsib, rright->left);

    ASSERT_EQ(rright->lval, 9);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->parent, right);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->left->lval, 9);
    ASSERT_EQ(rright->right->lval, 12);
    ASSERT_EQ(rright->left->lsib, rleft->right);
    ASSERT_EQ(rright->left->rsib, rright->right);
    ASSERT_EQ(rright->right->lsib, rright->left);
    ASSERT_EQ(rright->right->rsib, nullptr);
}

TEST_F(InsertNode, 8Nodes_Right1to2) {
    root = prepareTerminal({1, 4, 5, 8});
    root = insertNode(root, 9);
    root = insertNode(root, 12);
    root = insertNode(root, 11); // making 2-node on the right
    root = insertNode(root, 10); // splitting 2-node on the right

    ASSERT_EQ(root->lval, 8);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->parent, nullptr);
    ASSERT_EQ(root->max_child, 12);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_EQ(root->middle, nullptr);

    Node_t* left = root->left, *right = root->right;

    ASSERT_EQ(left->lval, 4);
    ASSERT_EQ(left->rval, EMPTY);
    ASSERT_EQ(left->parent, root);
    ASSERT_NE(left->left, nullptr);
    ASSERT_NE(left->right, nullptr);
    ASSERT_EQ(left->middle, nullptr);
    ASSERT_EQ(left->max_child, 8);

    ASSERT_EQ(right->lval, 10);
    ASSERT_EQ(right->rval, EMPTY);
    ASSERT_EQ(right->parent, root);
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    ASSERT_EQ(right->middle, nullptr);
    ASSERT_EQ(right->max_child, 12);

    Node_t* lleft = left->left, *lright = left->right, *rleft = right->left, *rright = right->right;

    ASSERT_EQ(lleft->lval, 1);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->parent, left);
    ASSERT_EQ(lleft->max_child, 4);
    ASSERT_EQ(lleft->left->lval, 1);
    ASSERT_EQ(lleft->right->lval, 4);
    ASSERT_EQ(lleft->left->lsib, nullptr);
    ASSERT_EQ(lleft->left->rsib, lleft->right);
    ASSERT_EQ(lleft->right->lsib, lleft->left);
    ASSERT_EQ(lleft->right->rsib, lright->left);

    ASSERT_EQ(lright->lval, 5);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->parent, left);
    ASSERT_EQ(lright->max_child, 8);
    ASSERT_EQ(lright->left->lval, 5);
    ASSERT_EQ(lright->right->lval, 8);
    ASSERT_EQ(lright->left->lsib, lleft->right);
    ASSERT_EQ(lright->left->rsib, lright->right);
    ASSERT_EQ(lright->right->lsib, lright->left);
    ASSERT_EQ(lright->right->rsib, rleft->left);

    ASSERT_EQ(rleft->lval, 9);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->parent, right);
    ASSERT_EQ(rleft->max_child, 10);
    ASSERT_EQ(rleft->left->lval, 9);
    ASSERT_EQ(rleft->right->lval, 10);
    ASSERT_EQ(rleft->left->lsib, lright->right);
    ASSERT_EQ(rleft->left->rsib, rleft->right);
    ASSERT_EQ(rleft->right->lsib, rleft->left);
    ASSERT_EQ(rleft->right->rsib, rright->left);

    ASSERT_EQ(rright->lval, 11);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->parent, right);
    ASSERT_EQ(rright->max_child, 12);
    ASSERT_EQ(rright->left->lval, 11);
    ASSERT_EQ(rright->right->lval, 12);
    ASSERT_EQ(rright->left->lsib, rleft->right);
    ASSERT_EQ(rright->left->rsib, rright->right);
    ASSERT_EQ(rright->right->lsib, rright->left);
    ASSERT_EQ(rright->right->rsib, nullptr);
}
