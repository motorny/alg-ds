#include <gtest/gtest.h>
#include <vector>
#include <string>

#include <hash_table.h>

class DeleteHash : public testing::Test {
protected:
    ht_t* table = nullptr;
    const int capacity = 4;

    inline void _createHash(int _capacity) { table = createHash(table, _capacity); }

    DeleteHash() { _createHash(capacity); }

    ~DeleteHash() override { freeHash(table); }

    void insertHashes(const std::vector<std::string> &vec) {
        for (auto &elem: vec)
            table = insertHash(table, elem.c_str());
    }
};

TEST_F(DeleteHash, 1Elem) {
    insertHashes({"a"});
    table = deleteHash(table, "a");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 0);
    ASSERT_EQ(table->entries[0].key, nullptr);
    ASSERT_EQ(table->entries[0].status, DELETED);

    for (size_t i = 1; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(DeleteHash, 2Elem_DiffHash_1Del) {
    insertHashes({"a", "b"});

    table = deleteHash(table, "a");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 1);
    ASSERT_EQ(table->entries[0].key, nullptr);
    ASSERT_EQ(table->entries[0].status, DELETED);

    ASSERT_STREQ(table->entries[1].key, "b");
    ASSERT_EQ(table->entries[1].status, BUSY);

    for (size_t i = 2; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(DeleteHash, 2Elem_DiffHash_2Del) {
    insertHashes({"a", "b"});

    table = deleteHash(table, "a");
    table = deleteHash(table, "b");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 0);
    ASSERT_EQ(table->entries[0].key, nullptr);
    ASSERT_EQ(table->entries[0].status, DELETED);

    ASSERT_EQ(table->entries[1].key, nullptr);
    ASSERT_EQ(table->entries[1].status, DELETED);

    for (size_t i = 2; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(DeleteHash, 2Elem_EqHash_1Del) {
    insertHashes({"ab", "ba"});

    table = deleteHash(table, "ba");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 1);
    ASSERT_STREQ(table->entries[1].key, "ab");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_EQ(table->entries[2].key, nullptr);
    ASSERT_EQ(table->entries[2].status, DELETED);

    for (size_t i = 0; i < table->capacity; i++) {
        if (i != 1 && i != 2) {
            ASSERT_EQ(table->entries[i].key, nullptr);
            ASSERT_EQ(table->entries[i].status, FREE);
        }
    }
}

TEST_F(DeleteHash, 2Elem_EqHash_1_2Del) {
    insertHashes({"ab", "ba"});

    table = deleteHash(table, "ab");
    table = deleteHash(table, "ba");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 0);
    ASSERT_EQ(table->entries[1].key, nullptr);
    ASSERT_EQ(table->entries[1].status, DELETED);

    ASSERT_EQ(table->entries[2].key, nullptr);
    ASSERT_EQ(table->entries[2].status, DELETED);

    for (size_t i = 0; i < table->capacity; i++) {
        if (i != 1 && i != 2) {
            ASSERT_EQ(table->entries[i].key, nullptr);
            ASSERT_EQ(table->entries[i].status, FREE);
        }
    }
}

TEST_F(DeleteHash, 2Elem_EqHash_2_1Del) {
    insertHashes({"ab", "ba"});

    table = deleteHash(table, "ba");
    table = deleteHash(table, "ab");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 0);
    ASSERT_EQ(table->entries[1].key, nullptr);
    ASSERT_EQ(table->entries[1].status, DELETED);

    ASSERT_EQ(table->entries[2].key, nullptr);
    ASSERT_EQ(table->entries[2].status, DELETED);

    for (size_t i = 0; i < table->capacity; i++) {
        if (i != 1 && i != 2) {
            ASSERT_EQ(table->entries[i].key, nullptr);
            ASSERT_EQ(table->entries[i].status, FREE);
        }
    }
}

TEST_F(DeleteHash, 3Elem_DiffHash_1lDel) {
    insertHashes({"a", "b", "c"});

    table = deleteHash(table, "a");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_EQ(table->entries[0].key, nullptr);
    ASSERT_EQ(table->entries[0].status, DELETED);

    ASSERT_STREQ(table->entries[1].key, "b");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_STREQ(table->entries[2].key, "c");
    ASSERT_EQ(table->entries[2].status, BUSY);

    for (size_t i = 3; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(DeleteHash, 3Elem_DiffHash_1mDel) {
    insertHashes({"a", "b", "c"});

    table = deleteHash(table, "b");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_STREQ(table->entries[0].key, "a");
    ASSERT_EQ(table->entries[0].status, BUSY);

    ASSERT_EQ(table->entries[1].key, nullptr);
    ASSERT_EQ(table->entries[1].status, DELETED);

    ASSERT_STREQ(table->entries[2].key, "c");
    ASSERT_EQ(table->entries[2].status, BUSY);

    for (size_t i = 3; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(DeleteHash, 3Elem_DiffHash_1rDel) {
    insertHashes({"a", "b", "c"});

    table = deleteHash(table, "c");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_STREQ(table->entries[0].key, "a");
    ASSERT_EQ(table->entries[0].status, BUSY);

    ASSERT_STREQ(table->entries[1].key, "b");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_EQ(table->entries[2].key, nullptr);
    ASSERT_EQ(table->entries[2].status, DELETED);

    for (size_t i = 3; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(DeleteHash, 3Elem_DiffHash_2mrDel) {
    insertHashes({"a", "b", "c"});

    table = deleteHash(table, "b");
    table = deleteHash(table, "c");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 1);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_STREQ(table->entries[0].key, "a");
    ASSERT_EQ(table->entries[0].status, BUSY);

    ASSERT_EQ(table->entries[1].key, nullptr);
    ASSERT_EQ(table->entries[1].status, DELETED);

    ASSERT_EQ(table->entries[2].key, nullptr);
    ASSERT_EQ(table->entries[2].status, DELETED);

    for (size_t i = 3; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(DeleteHash, 3Elem_DiffHash_2lmDel) {
    insertHashes({"a", "b", "c"});

    table = deleteHash(table, "a");
    table = deleteHash(table, "b");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 1);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_EQ(table->entries[0].key, nullptr);
    ASSERT_EQ(table->entries[0].status, DELETED);

    ASSERT_EQ(table->entries[1].key, nullptr);
    ASSERT_EQ(table->entries[1].status, DELETED);

    ASSERT_STREQ(table->entries[2].key, "c");
    ASSERT_EQ(table->entries[2].status, BUSY);

    for (size_t i = 3; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(DeleteHash, 3Elem_DiffHash_2lrDel) {
    insertHashes({"a", "b", "c"});

    table = deleteHash(table, "a");
    table = deleteHash(table, "c");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 1);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_EQ(table->entries[0].key, nullptr);
    ASSERT_EQ(table->entries[0].status, DELETED);

    ASSERT_STREQ(table->entries[1].key, "b");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_EQ(table->entries[2].key, nullptr);
    ASSERT_EQ(table->entries[2].status, DELETED);

    for (size_t i = 3; i < table->capacity; i++) {
        ASSERT_EQ(table->entries[i].key, nullptr);
        ASSERT_EQ(table->entries[i].status, FREE);
    }
}

TEST_F(DeleteHash, 3Elem_EqHash_1lDel) {
    insertHashes({"aab", "aba", "baa"});

    table = deleteHash(table, "aab");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_EQ(table->entries[1].key, nullptr);
    ASSERT_EQ(table->entries[1].status, DELETED);

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

TEST_F(DeleteHash, 3Elem_EqHash_1mDel) {
    insertHashes({"aab", "aba", "baa"});

    table = deleteHash(table, "aba");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_STREQ(table->entries[1].key, "aab");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_EQ(table->entries[2].key, nullptr);
    ASSERT_EQ(table->entries[2].status, DELETED);

    ASSERT_STREQ(table->entries[6].key, "baa");
    ASSERT_EQ(table->entries[6].status, BUSY);

    for (size_t i = 0; i < table->capacity; i++) {
        if (i != 1 && i != 2 && i != 6) {
            ASSERT_EQ(table->entries[i].key, nullptr);
            ASSERT_EQ(table->entries[i].status, FREE);
        }
    }
}

TEST_F(DeleteHash, 3Elem_EqHash_1rDel) {
    insertHashes({"aab", "aba", "baa"});

    table = deleteHash(table, "baa");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_EQ(table->capacity, capacity * 2);
    ASSERT_STREQ(table->entries[1].key, "aab");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_STREQ(table->entries[2].key, "aba");
    ASSERT_EQ(table->entries[2].status, BUSY);

    ASSERT_EQ(table->entries[6].key, nullptr);
    ASSERT_EQ(table->entries[6].status, DELETED);

    for (size_t i = 0; i < table->capacity; i++) {
        if (i != 1 && i != 2 && i != 6) {
            ASSERT_EQ(table->entries[i].key, nullptr);
            ASSERT_EQ(table->entries[i].status, FREE);
        }
    }
}

TEST_F(DeleteHash, 2Elem_EqHash_1ElemDiffHash_1lDel) {
    insertHashes({"aab", "aba", "aac"});
    // * aab aba aac * * * *
    table = deleteHash(table, "aab");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_EQ(table->capacity, capacity * 2);

    ASSERT_EQ(table->entries[1].key, nullptr);
    ASSERT_EQ(table->entries[1].status, DELETED);

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

TEST_F(DeleteHash, 2Elem_EqHash_1ElemDiffHash_1mDel) {
    insertHashes({"aab", "aba", "aac"});
    // * aab aba aac * * * *
    table = deleteHash(table, "aba");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_EQ(table->capacity, capacity * 2);

    ASSERT_STREQ(table->entries[1].key, "aab");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_EQ(table->entries[2].key, nullptr);
    ASSERT_EQ(table->entries[2].status, DELETED);

    ASSERT_STREQ(table->entries[3].key, "aac");
    ASSERT_EQ(table->entries[3].status, BUSY);

    for (size_t i = 0; i < table->capacity; i++) {
        if (i != 1 && i != 2 && i != 3) {
            ASSERT_EQ(table->entries[i].key, nullptr);
            ASSERT_EQ(table->entries[i].status, FREE);
        }
    }
}

TEST_F(DeleteHash, 2Elem_EqHash_1ElemDiffHash_1rDel) {
    insertHashes({"aab", "aba", "aac"});
    // * aab aba aac * * * *
    table = deleteHash(table, "aac");

    ASSERT_NE(table, nullptr);
    ASSERT_EQ(table->size, 2);
    ASSERT_EQ(table->capacity, capacity * 2);

    ASSERT_STREQ(table->entries[1].key, "aab");
    ASSERT_EQ(table->entries[1].status, BUSY);

    ASSERT_STREQ(table->entries[2].key, "aba");
    ASSERT_EQ(table->entries[2].status, BUSY);

    ASSERT_EQ(table->entries[3].key, nullptr);
    ASSERT_EQ(table->entries[3].status, DELETED);

    for (size_t i = 0; i < table->capacity; i++) {
        if (i != 1 && i != 2 && i != 3) {
            ASSERT_EQ(table->entries[i].key, nullptr);
            ASSERT_EQ(table->entries[i].status, FREE);
        }
    }
}