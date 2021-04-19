#include <vector>
#include <numeric>
#include <gtest/gtest.h>
#include <algorithm>
#include <random>
#include <set>
#include <unordered_set>

#include "../23Tree.h"

class FindNode : public testing::Test {
protected:
    Node_t* root = nullptr;

    ~FindNode() override { freeTree(root); }

    Node_t* insertNodes(const std::vector<int> &vals) {
        for (auto it = vals.begin(); it != vals.end(); it++) {
            root = insertNode(root, *it);
            for (auto iit = vals.begin(); iit != it + 1; iit++)
                EXPECT_NE(findNode(root, *iit), nullptr) << " last inserted " << *it << " not found " << *iit;
        }
        return root;
    }

    static void checkNodes(Node_t* root, const std::vector<int> &nodes, const std::unordered_set<int> &set,
                           const std::vector<int> &vec) {
        for (auto node_val : nodes) {
            if (set.count(node_val) > 0) // node_val in set
                EXPECT_NE(findNode(root, node_val), nullptr) << node_val << " Range: " << testing::PrintToString(nodes)
                                                             << " Inserted: " << testing::PrintToString(vec)
                                                             << " Set: " << testing::PrintToString(set);
            else
                EXPECT_EQ(findNode(root, node_val), nullptr) << node_val << " Range: " << testing::PrintToString(nodes)
                                                             << " Inserted: " << testing::PrintToString(vec)
                                                             << " Set: " << testing::PrintToString(set);
        }
    }

    static void checkNodes(Node_t* root, const std::vector<int> &all_vals, const std::unordered_set<int> &inserted_set,
                           const std::vector<int> &inserted_vec, const std::unordered_set<int> &deleted_set,
                           const std::vector<int> &deleted_vec) {
        for (auto node_val : all_vals) {
            if (inserted_set.count(node_val) > 0) // node_val in set
                EXPECT_NE(findNode(root, node_val), nullptr)
                                    << node_val << " Range: " << testing::PrintToString(all_vals)
                                    << " Inserted Set: "
                                    << testing::PrintToString(inserted_set)
                                    << " Inserted Vec: "
                                    << testing::PrintToString(inserted_vec) << std::endl
                                    << " Deleted Set: " << testing::PrintToString(deleted_set)
                                    << " Deleted Vec: " << testing::PrintToString(deleted_vec);
            else
                EXPECT_EQ(findNode(root, node_val), nullptr)
                                    << node_val << " Range: " << testing::PrintToString(all_vals)
                                    << " Inserted Set: "
                                    << testing::PrintToString(inserted_set)
                                    << " Inserted Vec: "
                                    << testing::PrintToString(inserted_vec) << std::endl
                                    << " Deleted Set: " << testing::PrintToString(deleted_set)
                                    << " Deleted Vec: " << testing::PrintToString(deleted_vec);
        }
    }

    void randomFind(int number_of_nodes, int number_of_deletions) {
        std::unordered_set<int> nodes, deleted;
        std::vector<int> all_nodes(number_of_nodes), inserted_nodes, deleted_nodes;
        std::generate(all_nodes.begin(), all_nodes.end(), [n = 0]()mutable { return n++; });
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> insert_val(0, number_of_nodes - 1), delete_val(0, number_of_deletions - 1);
        auto insert = std::bind(insert_val, gen), del = std::bind(delete_val, gen);

        for (int i = 0; i < number_of_nodes; i++) {
            inserted_nodes.push_back(insert());
            nodes.insert(inserted_nodes.back());
            root = insertNode(root, inserted_nodes.back());
            checkNodes(root, all_nodes, nodes, inserted_nodes);
        }
        for (int i = 0; i < number_of_deletions; i++) {
            deleted_nodes.push_back(del());
            deleted.insert(deleted_nodes.back());
            root = deleteNode(root, deleted_nodes.back());
            nodes.erase(deleted_nodes.back());
            checkNodes(root, all_nodes, nodes, inserted_nodes, deleted, deleted_nodes);
        }
    }
};

TEST_F(FindNode, 1Leaf) {
    root = insertNode(root, 1);

    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_EQ(findNode(root, -1), nullptr);
    root = deleteNode(root, 1);
    ASSERT_EQ(findNode(root, 1), nullptr);
    ASSERT_EQ(findNode(root, -1), nullptr);
}

TEST_F(FindNode, 2Leaves) {
    root = insertNode(root, 1);
    root = insertNode(root, 2);

    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);

    root = deleteNode(root, 1);
    ASSERT_NE(findNode(root, 2), nullptr);
    ASSERT_EQ(findNode(root, 1), nullptr);

    root = insertNode(root, 1);
    root = deleteNode(root, 2);
    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_EQ(findNode(root, 2), nullptr);

    root = deleteNode(root, 2);
    root = deleteNode(root, 1);
    ASSERT_EQ(findNode(root, 1), nullptr);
    ASSERT_EQ(findNode(root, 2), nullptr);
}

TEST_F(FindNode, 3Leaves) {
    root = insertNode(root, 1);
    root = insertNode(root, 2);
    root = insertNode(root, 3);

    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);
    ASSERT_NE(findNode(root, 3), nullptr);

    root = deleteNode(root, 1);
    ASSERT_EQ(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);
    ASSERT_NE(findNode(root, 3), nullptr);

    root = insertNode(root, 1);
    root = deleteNode(root, 2);
    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_EQ(findNode(root, 2), nullptr);
    ASSERT_NE(findNode(root, 3), nullptr);

    root = insertNode(root, 2);
    root = deleteNode(root, 3);
    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);
    ASSERT_EQ(findNode(root, 3), nullptr);

    root = insertNode(root, 3);
    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);
    ASSERT_NE(findNode(root, 3), nullptr);
}

TEST_F(FindNode, 4Leaves) {
    root = insertNode(root, 1);
    root = insertNode(root, 2);
    root = insertNode(root, 3);
    root = insertNode(root, 4);

    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);
    ASSERT_NE(findNode(root, 3), nullptr);
    ASSERT_NE(findNode(root, 4), nullptr);

    root = deleteNode(root, 1);
    ASSERT_EQ(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);
    ASSERT_NE(findNode(root, 3), nullptr);
    ASSERT_NE(findNode(root, 4), nullptr);

    root = insertNode(root, 1);
    root = deleteNode(root, 2);
    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_EQ(findNode(root, 2), nullptr);
    ASSERT_NE(findNode(root, 3), nullptr);
    ASSERT_NE(findNode(root, 4), nullptr);

    root = insertNode(root, 2);
    root = deleteNode(root, 3);
    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);
    ASSERT_EQ(findNode(root, 3), nullptr);
    ASSERT_NE(findNode(root, 4), nullptr);

    root = insertNode(root, 3);
    root = deleteNode(root, 4);
    ASSERT_NE(findNode(root, 1), nullptr);
    ASSERT_NE(findNode(root, 2), nullptr);
    ASSERT_NE(findNode(root, 3), nullptr);
    ASSERT_EQ(findNode(root, 4), nullptr);
}

TEST_F(FindNode, RandomFind_35Nodes_70Deletions) {
    for (int number_of_nodes = 0; number_of_nodes < 35; number_of_nodes++)
        for (int i = 0; i < 2000; i++)
            for (int number_of_deletions = 0; number_of_deletions < number_of_nodes * 2; number_of_deletions++) {
                randomFind(number_of_nodes, number_of_deletions);
                freeTree(root);
                root = nullptr;
            }
}
