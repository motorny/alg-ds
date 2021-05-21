#include <vector>
#include <numeric>
#include <gtest/gtest.h>
#include <algorithm>
#include <random>
#include <set>
#include <unordered_set>
#include <string>

#include <hash_table.h>

class FindHash : public testing::Test {
protected:
    ht_t* table = nullptr;
    const int capacity = 4;

    inline void _createHash(int _capacity) { table = createHash(table, _capacity); }

    FindHash() { _createHash(capacity); }

    ~FindHash() override { freeHash(table); }

    void insertHashes(const std::vector<std::string> &vec) {
        for (auto &elem: vec)
            table = insertHash(table, elem.c_str());
    }

    void deleteHashes(const std::vector<std::string> &vec) {
        for (auto &elem: vec)
            table = deleteHash(table, elem.c_str());
    }


    static void
    checkNodes(ht_t* root, const std::vector<std::string> &nodes, const std::unordered_set<std::string> &set,
               const std::vector<std::string> &vec) {
        for (const auto &node_val : nodes) {
            if (set.count(node_val) > 0) // node_val in set
                EXPECT_NE(findHash(root, node_val.c_str()), nullptr)
                                    << node_val << " Range: " << testing::PrintToString(nodes)
                                    << " Inserted: " << testing::PrintToString(vec)
                                    << " Set: " << testing::PrintToString(set);
            else
                EXPECT_EQ(findHash(root, node_val.c_str()), nullptr)
                                    << node_val << " Range: " << testing::PrintToString(nodes)
                                    << " Inserted: " << testing::PrintToString(vec)
                                    << " Set: " << testing::PrintToString(set);
        }
    }

    static void checkNodes(ht_t* root, const std::vector<std::string> &all_vals,
                           const std::unordered_set<std::string> &inserted_set,
                           const std::vector<std::string> &inserted_vec,
                           const std::unordered_set<std::string> &deleted_set,
                           const std::vector<std::string> &deleted_vec) {
        for (const auto &node_val : all_vals) {
            if (inserted_set.count(node_val) > 0) // node_val in set
                EXPECT_NE(findHash(root, node_val.c_str()), nullptr)
                                    << node_val << " Range: " << testing::PrintToString(all_vals)
                                    << " Inserted Set: "
                                    << testing::PrintToString(inserted_set)
                                    << " Inserted Vec: "
                                    << testing::PrintToString(inserted_vec) << std::endl
                                    << " Deleted Set: " << testing::PrintToString(deleted_set)
                                    << " Deleted Vec: " << testing::PrintToString(deleted_vec);
            else
                EXPECT_EQ(findHash(root, node_val.c_str()), nullptr)
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
        std::unordered_set<std::string> nodes, deleted;
        std::vector<std::string> all_nodes(number_of_nodes), inserted_nodes, deleted_nodes;
        std::generate(all_nodes.begin(), all_nodes.end(), [n = 0]()mutable { return n++; });
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> insert_val(0, number_of_nodes - 1), delete_val(0, number_of_deletions - 1);
        auto insert = std::bind(insert_val, gen), del = std::bind(delete_val, gen);

        for (int i = 0; i < number_of_nodes; i++) {
            inserted_nodes.push_back(std::to_string(insert()));
            nodes.insert(inserted_nodes.back());
            table = insertHash(table, inserted_nodes.back().c_str());
            checkNodes(table, all_nodes, nodes, inserted_nodes);
        }
        for (int i = 0; i < number_of_deletions; i++) {
            deleted_nodes.push_back(std::to_string(del()));
            deleted.insert(deleted_nodes.back());
            table = deleteHash(table, deleted_nodes.back().c_str());
            nodes.erase(deleted_nodes.back());
            checkNodes(table, all_nodes, nodes, inserted_nodes, deleted, deleted_nodes);
        }
    }
};

TEST_F(FindHash, 1Elem) {
    insertHashes({"a"});
    ASSERT_NE(findHash(table, "a"), nullptr);
    deleteHashes({"a"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
}

TEST_F(FindHash, 1Elem_Duplicate) {
    insertHashes({"a"});
    ASSERT_NE(findHash(table, "a"), nullptr);
    insertHashes({"a"});
    ASSERT_NE(findHash(table, "a"), nullptr);
    deleteHashes({"a"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
    deleteHashes({"a"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
}

TEST_F(FindHash, 2Elem_DiffHash) {
    insertHashes({"a", "b"});
    ASSERT_NE(findHash(table, "a"), nullptr);
    ASSERT_NE(findHash(table, "b"), nullptr);
    deleteHashes({"a"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
    ASSERT_NE(findHash(table, "b"), nullptr);
    deleteHashes({"b"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
    ASSERT_EQ(findHash(table, "b"), nullptr);
}

TEST_F(FindHash, 2Elem_EqHash_1_2Del) {
    insertHashes({"ab", "ba"});
    ASSERT_NE(findHash(table, "ab"), nullptr);
    ASSERT_NE(findHash(table, "ba"), nullptr);
    deleteHashes({"ab"});
    ASSERT_EQ(findHash(table, "ab"), nullptr);
    ASSERT_NE(findHash(table, "ba"), nullptr);
    deleteHashes({"ba"});
    ASSERT_EQ(findHash(table, "ab"), nullptr);
    ASSERT_EQ(findHash(table, "ba"), nullptr);
}

TEST_F(FindHash, 2Elem_EqHash_2_1Del) {
    insertHashes({"ab", "ba"});
    ASSERT_NE(findHash(table, "ab"), nullptr);
    ASSERT_NE(findHash(table, "ba"), nullptr);
    deleteHashes({"ba"});
    ASSERT_EQ(findHash(table, "ba"), nullptr);
    ASSERT_NE(findHash(table, "ab"), nullptr);
    deleteHashes({"ab"});
    ASSERT_EQ(findHash(table, "ab"), nullptr);
    ASSERT_EQ(findHash(table, "ba"), nullptr);
}

TEST_F(FindHash, 3Elem_DiffHash_1lDel) {
    insertHashes({"a", "b", "c"});
    ASSERT_NE(findHash(table, "a"), nullptr);
    ASSERT_NE(findHash(table, "b"), nullptr);
    ASSERT_NE(findHash(table, "c"), nullptr);
    deleteHashes({"a"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
    ASSERT_NE(findHash(table, "b"), nullptr);
    ASSERT_NE(findHash(table, "c"), nullptr);
    deleteHashes({"b"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
    ASSERT_EQ(findHash(table, "b"), nullptr);
    ASSERT_NE(findHash(table, "c"), nullptr);
    deleteHashes({"c"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
    ASSERT_EQ(findHash(table, "b"), nullptr);
    ASSERT_EQ(findHash(table, "c"), nullptr);
}

TEST_F(FindHash, 3Elem_DiffHash_1mDel) {
    insertHashes({"a", "b", "c"});
    ASSERT_NE(findHash(table, "a"), nullptr);
    ASSERT_NE(findHash(table, "b"), nullptr);
    ASSERT_NE(findHash(table, "c"), nullptr);
    deleteHashes({"b"});
    ASSERT_NE(findHash(table, "a"), nullptr);
    ASSERT_EQ(findHash(table, "b"), nullptr);
    ASSERT_NE(findHash(table, "c"), nullptr);
    deleteHashes({"a"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
    ASSERT_EQ(findHash(table, "b"), nullptr);
    ASSERT_NE(findHash(table, "c"), nullptr);
    deleteHashes({"c"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
    ASSERT_EQ(findHash(table, "b"), nullptr);
    ASSERT_EQ(findHash(table, "c"), nullptr);
}

TEST_F(FindHash, 3Elem_DiffHash_1rDel) {
    insertHashes({"a", "b", "c"});
    ASSERT_NE(findHash(table, "a"), nullptr);
    ASSERT_NE(findHash(table, "b"), nullptr);
    ASSERT_NE(findHash(table, "c"), nullptr);
    deleteHashes({"c"});
    ASSERT_EQ(findHash(table, "c"), nullptr);
    ASSERT_NE(findHash(table, "a"), nullptr);
    ASSERT_NE(findHash(table, "b"), nullptr);
    deleteHashes({"a"});
    ASSERT_EQ(findHash(table, "c"), nullptr);
    ASSERT_EQ(findHash(table, "a"), nullptr);
    ASSERT_NE(findHash(table, "b"), nullptr);
    deleteHashes({"b"});
    ASSERT_EQ(findHash(table, "a"), nullptr);
    ASSERT_EQ(findHash(table, "b"), nullptr);
    ASSERT_EQ(findHash(table, "c"), nullptr);
}

TEST_F(FindHash, 3Elem_EqHash_1lDel) {
    insertHashes({"aab", "aba", "baa"});
    ASSERT_NE(findHash(table, "aab"), nullptr);
    ASSERT_NE(findHash(table, "aba"), nullptr);
    ASSERT_NE(findHash(table, "baa"), nullptr);
    deleteHashes({"aab"});
    ASSERT_EQ(findHash(table, "aab"), nullptr);
    ASSERT_NE(findHash(table, "aba"), nullptr);
    ASSERT_NE(findHash(table, "baa"), nullptr);
    deleteHashes({"aba"});
    ASSERT_EQ(findHash(table, "aab"), nullptr);
    ASSERT_EQ(findHash(table, "aba"), nullptr);
    ASSERT_NE(findHash(table, "baa"), nullptr);
    deleteHashes({"baa"});
    ASSERT_EQ(findHash(table, "aab"), nullptr);
    ASSERT_EQ(findHash(table, "aba"), nullptr);
    ASSERT_EQ(findHash(table, "baa"), nullptr);
}

TEST_F(FindHash, 3Elem_EqHash_1mDel) {
    insertHashes({"aab", "aba", "baa"});
    ASSERT_NE(findHash(table, "aab"), nullptr);
    ASSERT_NE(findHash(table, "aba"), nullptr);
    ASSERT_NE(findHash(table, "baa"), nullptr);
    deleteHashes({"aba"});
    ASSERT_EQ(findHash(table, "aba"), nullptr);
    ASSERT_NE(findHash(table, "aab"), nullptr);
    ASSERT_NE(findHash(table, "baa"), nullptr);
    deleteHashes({"baa"});
    ASSERT_EQ(findHash(table, "baa"), nullptr);
    ASSERT_EQ(findHash(table, "aba"), nullptr);
    ASSERT_NE(findHash(table, "aab"), nullptr);
    deleteHashes({"aab"});
    ASSERT_EQ(findHash(table, "aab"), nullptr);
    ASSERT_EQ(findHash(table, "aba"), nullptr);
    ASSERT_EQ(findHash(table, "baa"), nullptr);
}

TEST_F(FindHash, 3Elem_EqHash_1rDel) {
    insertHashes({"aab", "aba", "baa"});
    ASSERT_NE(findHash(table, "aab"), nullptr);
    ASSERT_NE(findHash(table, "aba"), nullptr);
    ASSERT_NE(findHash(table, "baa"), nullptr);
    deleteHashes({"baa"});
    ASSERT_EQ(findHash(table, "baa"), nullptr);
    ASSERT_NE(findHash(table, "aba"), nullptr);
    ASSERT_NE(findHash(table, "aab"), nullptr);
    deleteHashes({"aab"});
    ASSERT_EQ(findHash(table, "aab"), nullptr);
    ASSERT_EQ(findHash(table, "baa"), nullptr);
    ASSERT_NE(findHash(table, "aba"), nullptr);
    deleteHashes({"aba"});
    ASSERT_EQ(findHash(table, "aab"), nullptr);
    ASSERT_EQ(findHash(table, "aba"), nullptr);
    ASSERT_EQ(findHash(table, "baa"), nullptr);
}

TEST_F(FindHash, Exhaustive) {
    for (int number_of_nodes = 0; number_of_nodes < 35; number_of_nodes++)
        for (int i = 0; i < 2000; i++)
            for (int number_of_deletions = 0; number_of_deletions < number_of_nodes * 2; number_of_deletions++) {
                randomFind(number_of_nodes, number_of_deletions);
                freeHash(table);
                table = nullptr;
            }
}