#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <algorithm>

#include "../23Tree.h"

class DeleteNode : public testing::Test {
protected:
    Node_t* root = nullptr;

    DeleteNode() = default;

    ~DeleteNode() override { freeTree(root); }

    Node_t* insertNodes(const std::vector<int> &vals) {
        for (auto i: vals)
            root = insertNode(root, i);
        return root;
    }

    static bool isTerm(Node_t* node) {
        return node->left == nullptr && node->middle == nullptr && node->right == nullptr;
    }

    static void
    checkLeaves(const std::vector<Node_t*> &leaves, const std::vector<int> &vals, Node_t* lsib, Node_t* rsib) {
        ASSERT_EQ(leaves.size(), vals.size()) << "sizes are not equal";
        auto leaf = leaves.begin();
        for (auto val = vals.begin(); val != vals.end(); val++, leaf++) {
            ASSERT_EQ((*leaf)->lval, *val);// << "expected " << *val << " actual " << (*leaf)->lval;
            ASSERT_EQ((*leaf)->rval, EMPTY);// << "expected " << EMPTY << " actual " << (*leaf)->rval;
            ASSERT_EQ((*leaf)->max_child, *val);// << "expected " << *val << " actual " << (*leaf)->max_child;
            ASSERT_EQ(isTerm(*leaf), true);
            ASSERT_EQ((*leaf)->lsib, leaf == leaves.begin() ? lsib : *(leaf - 1));
            ASSERT_EQ((*leaf)->rsib, leaf == leaves.end() - 1 ? rsib : *(leaf + 1));
        }
    }

    static int numberChildren(Node_t* node) {
        if (node == nullptr)
            return 0;
        return (node->left != nullptr) + (node->middle != nullptr) + (node->right != nullptr);
    }

    static std::vector<Node_t*> &getChildren(Node_t* node, std::vector<Node_t*> &children) {
        int childrenNum = numberChildren(node);
        if (childrenNum) {
            children.push_back(node->left);
            if (childrenNum == 3)
                children.push_back(node->middle);
            children.push_back(node->right);
        }
        return children;
    }

    static void check2Terminal(Node_t* root, const std::vector<int> &vals, Node_t* lsib, Node_t* rsib) {
        ASSERT_EQ(vals.size(), 2);
        ASSERT_NE(root, nullptr);
        ASSERT_NE(root->left, nullptr);
        ASSERT_EQ(root->middle, nullptr);
        ASSERT_NE(root->right, nullptr);
        ASSERT_EQ(root->lval, vals.at(0));
        ASSERT_EQ(root->rval, EMPTY);
        ASSERT_EQ(root->max_child, vals.at(1));
        ASSERT_EQ(root->left->lval, vals.at(0));
        ASSERT_EQ(root->right->lval, vals.at(1));

        checkLeaves({root->left, root->right}, vals, lsib, rsib);
    }

    static void check2Terminal(Node_t* root, const std::vector<int> &vals) {
        check2Terminal(root, vals, nullptr, nullptr);
    }

    static void check3Terminal(Node_t* root, const std::vector<int> &vals, Node_t* lsib, Node_t* rsib) {
        ASSERT_EQ(vals.size(), 3);
        ASSERT_NE(root, nullptr);
        ASSERT_NE(root->left, nullptr);
        ASSERT_NE(root->middle, nullptr);
        ASSERT_NE(root->right, nullptr);
        ASSERT_EQ(root->lval, vals.at(0));
        ASSERT_EQ(root->rval, vals.at(1));
        ASSERT_EQ(root->max_child, vals.at(2));
        ASSERT_EQ(root->left->lval, vals.at(0));
        ASSERT_EQ(root->middle->lval, vals.at(1));
        ASSERT_EQ(root->right->lval, vals.at(2));

        checkLeaves({root->left, root->middle, root->right}, vals, lsib, rsib);
    }

    static void check3Terminal(Node_t* root, const std::vector<int> &vals) {
        check3Terminal(root, vals, nullptr, nullptr);
    }

    static void
    check2Node(Node_t* root, const std::vector<int> &vals, int order) {
        ASSERT_EQ(numberChildren(root), 2);
        std::array<int, 4> possible_order = {22, 23, 32, 33};
        ASSERT_EQ(std::count(possible_order.begin(), possible_order.end(), order), 1);
        std::div_t dv{std::div(order, 10)};
        int leftNum = dv.quot, rightNum = dv.rem;
        ASSERT_EQ(leftNum + rightNum, vals.size());

        ASSERT_EQ(numberChildren(root->left), leftNum);
        ASSERT_EQ(numberChildren(root->right), rightNum);
        ASSERT_EQ(root->lval, vals.at(leftNum - 1)) << "leftNum - 1 " << leftNum - 1;
        ASSERT_EQ(root->rval, EMPTY);
        ASSERT_EQ(root->max_child, vals.back());

        std::vector<Node_t*> children;
        children = getChildren(root->left, children);
        children = getChildren(root->right, children);
        auto child = children.begin();
        for (auto val = vals.begin(); val != vals.end(); val++, child++)
            ASSERT_EQ((*child)->lval, *val);
    }

    static void
    check3Node(Node_t* root, const std::vector<int> &vals, int order) {
        ASSERT_EQ(numberChildren(root), 3);
        std::array<int, 8> possible_order = {222, 223, 232, 233, 322, 323, 332, 333};
        ASSERT_EQ(std::count(possible_order.begin(), possible_order.end(), order), 1);
        int leftNum = order / 100, middleNum = order % 100 / 10, rightNum = order % 10;
        ASSERT_EQ(leftNum + middleNum + rightNum, vals.size());

        ASSERT_EQ(numberChildren(root->left), leftNum);
        ASSERT_EQ(numberChildren(root->middle), middleNum);
        ASSERT_EQ(numberChildren(root->right), rightNum);
        ASSERT_EQ(root->lval, vals.at(leftNum - 1));
        ASSERT_EQ(root->rval, vals.at(leftNum + middleNum - 1));
        ASSERT_EQ(root->max_child, vals.back());

        std::vector<Node_t*> children;
        children = getChildren(root->left, children);
        children = getChildren(root->middle, children);
        children = getChildren(root->right, children);
        auto child = children.begin();
        for (auto val = vals.begin(); val != vals.end(); val++, child++)
            ASSERT_EQ((*child)->lval, *val);
    }

    static std::vector<std::vector<int>>
    makeChunks(std::vector<int> &vals, const std::vector<int> &deleted, int order) {
        for (int val : deleted)
            vals.erase(std::remove(vals.begin(), vals.end(), val), vals.end());
        std::vector<std::vector<int>> chunks;
        auto curr = vals.cbegin();
        int offset = 0;
        for (auto i : std::to_string(order)) {
            offset = std::stoi(&i);
            chunks.emplace_back(std::vector<int>{curr, curr + offset});
            curr = curr + offset;
        }
        return chunks;
    }
};

// tests for 1-node root
TEST_F(DeleteNode, 4Nodes_2_2) { // 2'2 -> 12 -> 3
    std::vector<int> vals = {0, 1, 2, 3};
    root = insertNodes(vals);
    root = deleteNode(root, 0);

    auto chunks = makeChunks(vals, {0}, 3);
    check3Terminal(root, vals);
}

TEST_F(DeleteNode, 4Nodes_22_) { // 22' -> 21 -> 3
    std::vector<int> vals = {0, 1, 2, 3};
    root = insertNodes(vals);
    root = deleteNode(root, 2);

    auto chunks = makeChunks(vals, {2}, 3);
    check3Terminal(root, vals);
}

TEST_F(DeleteNode, 5Nodes_3_2) { // 3'2 -> 22
    std::vector<int> vals = {1, 2, 3, 4, 0};
    root = insertNodes(vals);
    std::sort(vals.begin(), vals.end());
    root = deleteNode(root, 2);

    auto chunks = makeChunks(vals, {2}, 22);
    check2Node(root, vals, 22);
    check2Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check2Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 5Nodes_32_) { // 32' -> 31 -> 22
    std::vector<int> vals = {1, 2, 3, 4, 0};
    root = insertNodes(vals);
    std::sort(vals.begin(), vals.end());
    root = deleteNode(root, 4);

    auto chunks = makeChunks(vals, {4}, 22);
    check2Node(root, vals, 22);
    check2Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check2Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 5Nodes_23_) { // 23' -> 22
    std::vector<int> vals = {0, 1, 2, 3, 4};
    root = insertNodes(vals);
    std::sort(vals.begin(), vals.end());
    root = deleteNode(root, 4);

    auto chunks = makeChunks(vals, {4}, 22);
    check2Node(root, vals, 22);
    check2Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check2Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 5Nodes_2_3) { // 2'3 -> 13 -> 22
    std::vector<int> vals = {0, 1, 2, 3, 4};
    root = insertNodes(vals);
    std::sort(vals.begin(), vals.end());
    root = deleteNode(root, 0);

    auto chunks = makeChunks(vals, {0}, 22);
    check2Node(root, vals, 22);
    check2Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check2Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 6Nodes_3_3) { // 3'3 -> 23
    std::vector<int> vals = {0, 1, 2, 3, 4, 5};
    root = insertNodes(vals);
    root = deleteNode(root, 1);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {1}, 23);
    check2Node(root, vals, 23);
    check2Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check3Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 6Nodes_33_) { // 33' -> 23
    std::vector<int> vals = {0, 1, 2, 3, 4, 5};
    root = insertNodes(vals);
    root = deleteNode(root, 5);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {5}, 32);
    check2Node(root, vals, 32);
    check3Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check2Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

// tests for 2-node root
TEST_F(DeleteNode, 7Nodes_3_22) { // 3'22 -> 33
    std::vector<int> vals = {0, 1, 2, 3, 4, 5, 6};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 2);
    ASSERT_EQ(numberChildren(root->right), 2);

    root = deleteNode(root, 2);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {2}, 33);
    check2Node(root, vals, 33);
    check3Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check3Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 7Nodes_32_2) { // 32'2 -> 33
    std::vector<int> vals = {0, 1, 2, 3, 4, 5, 6};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 2);
    ASSERT_EQ(numberChildren(root->right), 2);
    root = deleteNode(root, 4);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {4}, 33);
    check2Node(root, vals, 33);
    check3Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check3Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 7Nodes_322_) { // 322' -> 33
    std::vector<int> vals = {0, 1, 2, 3, 4, 5, 6};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 2);
    ASSERT_EQ(numberChildren(root->right), 2);
    root = deleteNode(root, 5);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {5}, 33);
    check2Node(root, vals, 33);
    check3Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check3Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

//TEST_F(DeleteNode, 7Nodes_223_) { // 223' -> 33
//    std::vector<int> vals = {1, 2, 3, 4, 5, 6, 0};
//    root = insertNodes(vals);
//    ASSERT_EQ(numberChildren(root->left), 2);
//    ASSERT_EQ(numberChildren(root->middle), 2);
//    ASSERT_EQ(numberChildren(root->right), 3);
//    root = deleteNode(root, 6);
//
//    std::sort(vals.begin(), vals.end());
//    auto chunks = makeChunks(vals, {6}, 33);
//    check2Node(root, vals, 33);
//    check3Terminal(root->left, chunks.at(0), nullptr, root->right->left);
//    check3Terminal(root->right, chunks.at(1), root->left->right, nullptr);
//}

TEST_F(DeleteNode, 7Nodes_22_3) { // 22'3 -> 33
    std::vector<int> vals = {1, 2, 3, 4, 5, 6, 0};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 2);
    ASSERT_EQ(numberChildren(root->middle), 2);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 3);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {3}, 33);
    check2Node(root, vals, 33);
    check3Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check3Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 7Nodes_2_23) { // 2'23 -> 33
    std::vector<int> vals = {1, 2, 3, 4, 5, 6, 0};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 2);
    ASSERT_EQ(numberChildren(root->middle), 2);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 0);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {0}, 33);
    check2Node(root, vals, 33);
    check3Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check3Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 8Nodes_2_33) { // 2'33 -> 133 -> 223
    std::vector<int> vals = {1, 2, 4, 5, 6, 7, 0, 3};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 2);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 0);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {0}, 223);
    check3Node(root, vals, 223);
    check2Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check2Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check3Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}

TEST_F(DeleteNode, 8Nodes_23_3) { // 23'3 -> 223
    std::vector<int> vals = {1, 2, 4, 5, 6, 7, 0, 3};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 2);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 4);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {4}, 223);
    check3Node(root, vals, 223);
    check2Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check2Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check3Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}

TEST_F(DeleteNode, 8Nodes_233_) { // 233' -> 232
    std::vector<int> vals = {1, 2, 4, 5, 6, 7, 0, 3};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 2);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 6);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {6}, 232);
    check3Node(root, vals, 232);
    check2Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check3Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check2Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}

TEST_F(DeleteNode, 8Nodes_3_23) { // 3'23 -> 223
    std::vector<int> vals = {1, 2, 3, 4, 5, 6, 7, 8};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 2);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 1);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {1}, 223);
    check3Node(root, vals, 223);
    check2Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check2Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check3Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}

TEST_F(DeleteNode, 8Nodes_32_3) { // 32'3 -> 313 -> 223
    std::vector<int> vals = {1, 2, 3, 4, 5, 6, 7, 8};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 2);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 5);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {5}, 223);
    check3Node(root, vals, 223);
    check2Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check2Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check3Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}

TEST_F(DeleteNode, 8Nodes_323_) { // 323' -> 322
    std::vector<int> vals = {1, 2, 3, 4, 5, 6, 7, 8};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 2);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 7);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {7}, 322);
    check3Node(root, vals, 322);
    check3Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check2Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check2Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}

TEST_F(DeleteNode, 8Nodes_3_32) { // 3'32 -> 232
    std::vector<int> vals = {0, 1, 2, 3, 5, 6, 7, 4};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 2);
    root = deleteNode(root, 1);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {1}, 232);
    check3Node(root, vals, 232);
    check2Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check3Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check2Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}

//TEST_F(DeleteNode, 8Nodes_33_2) { // 33'2 -> 322
//    std::vector<int> vals = {0, 1, 2, 3, 5, 6, 7, 4};
//    root = insertNodes(vals);
//    ASSERT_EQ(numberChildren(root->left), 3);
//    ASSERT_EQ(numberChildren(root->middle), 3);
//    ASSERT_EQ(numberChildren(root->right), 2);
//    root = deleteNode(root, 4);
//
//    std::sort(vals.begin(), vals.end());
//    auto chunks = makeChunks(vals, {4}, 322);
//    check3Node(root, vals, 322);
//    check3Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
//    check2Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
//    check2Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
//}

TEST_F(DeleteNode, 8Nodes_332_) { // 332' -> 331 -> 322
    std::vector<int> vals = {0, 1, 2, 3, 5, 6, 7, 4};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 2);
    root = deleteNode(root, 7);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {7}, 322);
    check3Node(root, vals, 322);
    check3Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check2Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check2Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}

// cannot get 232 from 7 nodes because of insertSplitting
// hence achieving by deletion from 8 nodes
TEST_F(DeleteNode, 7Nodes_2_32) { // 2'32 -> 33
    std::vector<int> vals = {0, 1, 2, 3, 5, 6, 7, 4};
    root = insertNodes(vals);
    root = deleteNode(root, 0);
    ASSERT_EQ(numberChildren(root->left), 2);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 2);
    root = deleteNode(root, 1);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {0, 1}, 33);
    check2Node(root, vals, 33);
    check3Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check3Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 7Nodes_23_2) { // 23'2 -> 33
    std::vector<int> vals = {0, 1, 2, 3, 5, 6, 7, 4};
    root = insertNodes(vals);
    root = deleteNode(root, 0);
    ASSERT_EQ(numberChildren(root->left), 2);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 2);
    root = deleteNode(root, 4);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {0, 4}, 33);
    check2Node(root, vals, 33);
    check3Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check3Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 7Nodes_232_) { // 232' -> 33
    std::vector<int> vals = {0, 1, 2, 3, 5, 6, 7, 4};
    root = insertNodes(vals);
    root = deleteNode(root, 0);
    ASSERT_EQ(numberChildren(root->left), 2);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 2);
    root = deleteNode(root, 6);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {0, 6}, 33);
    check2Node(root, vals, 33);
    check3Terminal(root->left, chunks.at(0), nullptr, root->right->left);
    check3Terminal(root->right, chunks.at(1), root->left->right, nullptr);
}

TEST_F(DeleteNode, 9Nodes_3_33) { // 3'33 -> 233
    std::vector<int> vals = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 1);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {1}, 233);
    check3Node(root, vals, 233);
    check2Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check3Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check3Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}

TEST_F(DeleteNode, 9Nodes_33_3) { // 33'3 -> 323
    std::vector<int> vals = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 4);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {4}, 323);
    check3Node(root, vals, 323);
    check3Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check2Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check3Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}

TEST_F(DeleteNode, 9Nodes_333_) { // 333' -> 332
    std::vector<int> vals = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    root = insertNodes(vals);
    ASSERT_EQ(numberChildren(root->left), 3);
    ASSERT_EQ(numberChildren(root->middle), 3);
    ASSERT_EQ(numberChildren(root->right), 3);
    root = deleteNode(root, 7);

    std::sort(vals.begin(), vals.end());
    auto chunks = makeChunks(vals, {7}, 332);
    check3Node(root, vals, 332);
    check3Terminal(root->left, chunks.at(0), nullptr, root->middle->left);
    check3Terminal(root->middle, chunks.at(1), root->left->right, root->right->left);
    check2Terminal(root->right, chunks.at(2), root->middle->right, nullptr);
}
