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
    const int capacity = 0;

    inline void _createHash(int _capacity) { table = createHash(table, _capacity); }

    FindHash() { _createHash(capacity); }

    ~FindHash() override { freeHash(table); }

    void insertHashes(const std::set<std::string> &set) {
        for (auto &elem: set)
            table = insertHash(table, elem.c_str());
    }

    void deleteHashes(const std::set<std::string> &set) {
        for (auto &elem: set)
            table = deleteHash(table, elem.c_str());
    }

    void findHashes(const std::set<std::string> &set, bool shouldBe) {
        for (auto &elem: set)
            ASSERT_EQ(findHash(table, elem.c_str()) != nullptr, shouldBe) << elem << " " << shouldBe << std::endl;
    }

    void findHashes(const std::string &hash, bool shouldBe) {
        ASSERT_EQ(findHash(table, hash.c_str()) != nullptr, shouldBe) << hash << " " << shouldBe << std::endl;
    }

    std::string genString(int size) {
        std::string str(
                "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

        std::random_device rd;
        std::mt19937 generator(rd());

        std::shuffle(str.begin(), str.end(), generator);

        return str.substr(0, size);
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
    int v_size = 7000, s_size = 100;
    std::set<std::string> to_insert, to_delete, common, diff, common_copy;
    for (int i = 0; i < v_size; i++) {
        to_insert.insert(genString(s_size));
        to_delete.insert(genString(s_size));
        common.insert(genString(s_size));
    }
    std::set_intersection(to_insert.begin(), to_insert.end(), to_delete.begin(), to_delete.end(),
                          std::inserter(diff, diff.begin()));
    if (!diff.empty())
        for (auto &d : diff)
            to_delete.erase(d);

    insertHashes(to_insert);
    findHashes(to_insert, true);
    deleteHashes(to_delete);
    findHashes(to_insert, true);
    findHashes(to_delete, false);
    insertHashes(common);

    std::copy(common.begin(), common.end(), std::inserter(common_copy, common_copy.begin()));
    for (auto &hash : common_copy) {
        findHashes(common, true);
        common.erase(hash);
        table = deleteHash(table, hash.c_str());
        findHashes(hash, false);
    }
    insertHashes(common);
    findHashes(common, true);
    deleteHashes(common);
    findHashes(common, false);
}