#include <gtest/gtest.h>
#include <hash_table.h>

class InsertHash : public testing::Test {
protected:
    ht_t* table = nullptr;
    const int capacity = 4;

    inline void _createHash(int _capacity) { table = createHash(table, _capacity); }
    InsertHash() { _createHash(capacity ); }
    ~InsertHash() override { freeHash(table); }
};

TEST_F(InsertHash, 1Elem) {
    table = insertHash(table, "a");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 1);
    ASSERT_STREQ(table->entries[0].key, "a");
    ASSERT_EQ(table->entries[0].status, BUSY);

    for (size_t i = 1; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(InsertHash, 2Elem_DiffHash) {
    table = insertHash(table, "a");
    table = insertHash(table, "b");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_STREQ(table->entries[0].key, "a");
    ASSERT_EQ(table->entries[0].status, BUSY);

    ASSERT_STREQ(table->entries[1].key, "b");
    ASSERT_EQ(table->entries[1].status, BUSY);

    for (size_t i = 2; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(InsertHash, 2Elem_EqHash) {
    table = insertHash(table, "ab");
    table = insertHash(table, "ba");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_STREQ(table->entries[1].key, "ab");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_STREQ(table->entries[2].key, "ba");
    ASSERT_EQ(table->entries[2].status, BUSY);

    for (size_t i = 0; i < table->capacity; i++) {
        if (i != 1 && i != 2) {
            ASSERT_EQ(table->entries[i].key, nullptr);
            ASSERT_EQ(table->entries[i].status, FREE);
        }
    }
}

TEST_F(InsertHash, 3Elem_DiffHash) {
    table = insertHash(table, "a");
    table = insertHash(table, "b");
    table = insertHash(table, "c");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 3);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_STREQ(table->entries[0].key, "a");
    ASSERT_EQ(table->entries[0].status, BUSY);

    ASSERT_STREQ(table->entries[1].key, "b");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_STREQ(table->entries[2].key, "c");
    ASSERT_EQ(table->entries[2].status, BUSY);

    for (size_t i = 3; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(InsertHash, 3Elem_EqHash) {
    table = insertHash(table, "aab");
    table = insertHash(table, "aba");
    table = insertHash(table, "baa");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 3);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_STREQ(table->entries[1].key, "aab");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_STREQ(table->entries[2].key, "aba");
    ASSERT_EQ(table->entries[2].status, BUSY);

    ASSERT_STREQ(table->entries[6].key, "baa");
    ASSERT_EQ(table->entries[6].status, BUSY);

    for (size_t i = 0; i < table->capacity; i++) {
        if (i != 1 && i != 2 && i != 6) {
            ASSERT_EQ(table->entries[i].key, nullptr);
            ASSERT_EQ(table->entries[i].status, FREE);
        }
    }
}

TEST_F(InsertHash, 2Elem_EqHash_1ElemDiffHash) {
    table = insertHash(table, "aab"); // 1
    table = insertHash(table, "aba"); // 1
    table = insertHash(table, "aac"); // 2
                                          // * aab aba aac * * * *
    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 3);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_STREQ(table->entries[1].key, "aab");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_STREQ(table->entries[2].key, "aba");
    ASSERT_EQ(table->entries[2].status, BUSY);

    ASSERT_STREQ(table->entries[3].key, "aac");
    ASSERT_EQ(table->entries[3].status, BUSY);

    for (size_t i = 0; i < table->capacity; i++) {
        if (i != 1 && i != 2 && i != 3) {
            ASSERT_EQ(table->entries[i].key, nullptr);
            ASSERT_EQ(table->entries[i].status, FREE);
        }
    }
}