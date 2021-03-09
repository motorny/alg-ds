#include <gtest/gtest.h>

#include "../List.h"

class ListInsertion : public ::testing::Test {
protected:
    Node_t* last = nullptr;

    ListInsertion() = default;

    ~ListInsertion() override { freeList(last); }
};

TEST_F(ListInsertion, OneElem) {
    last = insert(last, 1);

    ASSERT_EQ(last->data, 1);
    ASSERT_EQ(last->next, nullptr);
}

TEST_F(ListInsertion, TwoElems) {
    last = insert(last, 1);
    last = insert(last, 2);

    ASSERT_EQ(last->data, 2);
    ASSERT_EQ(last->next->data, 1);
    ASSERT_EQ(last->next->next, nullptr);
}