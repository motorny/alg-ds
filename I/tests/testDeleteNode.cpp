#include <gtest/gtest.h>
#include <vector>

#include "../23Tree.h"

class DeleteNode : public testing::Test {
protected:
    Node_t* root = nullptr;

    DeleteNode() = default;

    ~DeleteNode() override = default; //{freeTree(root);}

    Node_t* insertNodes(const std::vector<int> &vals) {
        for (auto i: vals)
            root = insertNode(root, i);
        return root;
    }
};

// tests for 1-1 case
TEST_F(DeleteNode, 4Nodes_LeftLeft) {
    root = insertNodes({0, 1, 2, 3});
    root = deleteNode(root, 0);

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, 2);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->left->lval, 1);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 1);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->middle);

    ASSERT_EQ(root->middle->lval, 2);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 2);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 3);
    ASSERT_EQ(root->right->lsib, root->middle);
    ASSERT_EQ(root->right->rsib, nullptr);
}

TEST_F(DeleteNode, 4Nodes_LeftRight) {
    root = insertNodes({0, 1, 2, 3});
    root = deleteNode(root, 1);

    ASSERT_EQ(root->lval, 0);
    ASSERT_EQ(root->rval, 2);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 0);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->middle);

    ASSERT_EQ(root->middle->lval, 2);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 2);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 3);
    ASSERT_EQ(root->right->lsib, root->middle);
    ASSERT_EQ(root->right->rsib, nullptr);
}

TEST_F(DeleteNode, 4Nodes_RightLeft) {
    root = insertNodes({0, 1, 2, 3});
    root = deleteNode(root, 2);

    ASSERT_EQ(root->lval, 0);
    ASSERT_EQ(root->rval, 1);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 0);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->middle);

    ASSERT_EQ(root->middle->lval, 1);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 1);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 3);
    ASSERT_EQ(root->right->lsib, root->middle);
    ASSERT_EQ(root->right->rsib, nullptr);
}

TEST_F(DeleteNode, 4Nodes_RightRight) {
    root = insertNodes({0, 1, 2, 3});
    root = deleteNode(root, 3);

    ASSERT_EQ(root->lval, 0);
    ASSERT_EQ(root->rval, 1);
    ASSERT_EQ(root->max_child, 2);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 0);
    ASSERT_EQ(root->left->lsib, nullptr);
    ASSERT_EQ(root->left->rsib, root->middle);

    ASSERT_EQ(root->middle->lval, 1);
    ASSERT_EQ(root->middle->rval, EMPTY);
    ASSERT_EQ(root->middle->max_child, 1);
    ASSERT_EQ(root->middle->lsib, root->left);
    ASSERT_EQ(root->middle->rsib, root->right);

    ASSERT_EQ(root->right->lval, 2);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 2);
    ASSERT_EQ(root->right->lsib, root->middle);
    ASSERT_EQ(root->right->rsib, nullptr);
}

// tests for 2-1 case
TEST_F(DeleteNode, 5Nodes_Left2to1) {
    root = insertNodes({1, 2, 3, 4, 0}); // 2-valued node on the left
    root = deleteNode(root, 2); // root->lval should updated

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 4);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 1);

    ASSERT_EQ(root->right->lval, 3);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 4);

    Node_t* lleft = root->left->left, * lright = root->left->right,
          * rleft = root->right->left, * rright = root->right->right;

    ASSERT_EQ(lleft->lval, 0);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 0);
    ASSERT_EQ(lleft->lsib, nullptr);
    ASSERT_EQ(lleft->rsib, lright);

    ASSERT_EQ(lright->lval, 1);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 1);
    ASSERT_EQ(lright->lsib, lleft);
    ASSERT_EQ(lright->rsib, rleft);

    ASSERT_EQ(rleft->lval, 3);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 3);
    ASSERT_EQ(rleft->lsib, lright);
    ASSERT_EQ(rleft->rsib, rright);

    ASSERT_EQ(rright->lval, 4);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 4);
    ASSERT_EQ(rright->lsib, rleft);
    ASSERT_EQ(rright->rsib, nullptr);
}

TEST_F(DeleteNode, 5Nodes_Right2to1) {
    root = insertNodes({0, 1, 2, 3, 4}); // 2-valued node on the right
    root = deleteNode(root, 4); // root->max_child should updated

    ASSERT_EQ(root->lval, 1);
    ASSERT_EQ(root->rval, EMPTY);
    ASSERT_EQ(root->max_child, 3);

    ASSERT_EQ(root->left->lval, 0);
    ASSERT_EQ(root->left->rval, EMPTY);
    ASSERT_EQ(root->left->max_child, 1);

    ASSERT_EQ(root->right->lval, 2);
    ASSERT_EQ(root->right->rval, EMPTY);
    ASSERT_EQ(root->right->max_child, 3);

    Node_t* lleft = root->left->left, * lright = root->left->right,
            * rleft = root->right->left, * rright = root->right->right;

    ASSERT_EQ(lleft->lval, 0);
    ASSERT_EQ(lleft->rval, EMPTY);
    ASSERT_EQ(lleft->max_child, 0);
    ASSERT_EQ(lleft->lsib, nullptr);
    ASSERT_EQ(lleft->rsib, lright);

    ASSERT_EQ(lright->lval, 1);
    ASSERT_EQ(lright->rval, EMPTY);
    ASSERT_EQ(lright->max_child, 1);
    ASSERT_EQ(lright->lsib, lleft);
    ASSERT_EQ(lright->rsib, rleft);

    ASSERT_EQ(rleft->lval, 2);
    ASSERT_EQ(rleft->rval, EMPTY);
    ASSERT_EQ(rleft->max_child, 2);
    ASSERT_EQ(rleft->lsib, lright);
    ASSERT_EQ(rleft->rsib, rright);

    ASSERT_EQ(rright->lval, 3);
    ASSERT_EQ(rright->rval, EMPTY);
    ASSERT_EQ(rright->max_child, 3);
    ASSERT_EQ(rright->lsib, rleft);
    ASSERT_EQ(rright->rsib, nullptr);
}
