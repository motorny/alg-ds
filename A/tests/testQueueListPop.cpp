#include <vector>

#include <gtest/gtest.h>

#include "../List.h"

class ListPop : public ::testing::Test {
protected:
    Node_t* last = nullptr;

    ListPop() = default;

    ~ListPop() override { freeList(last); }

    Node_t* insertList(const std::vector<int> &values) {
        for (int i : values)
            last = insert(last, i);
        return last;
    }
};

TEST_F(ListPop, EmptyList) {
    ASSERT_EQ(last, nullptr);

    last = pop(last);
    ASSERT_EQ(last, nullptr);
}

TEST_F(ListPop, OneElemOnePop) {
    last = insert(last, 1);

    ASSERT_EQ(last->data, 1);
    ASSERT_EQ(last->next, nullptr);

    last = pop(last);
    ASSERT_EQ(last, nullptr);
}

TEST_F(ListPop, TwoElemOnePop) {
    last = insertList({1, 2});

    ASSERT_EQ(last->data, 2);
    ASSERT_EQ(last->next->data, 1);
    ASSERT_EQ(last->next->next, nullptr);

    last = pop(last);
    ASSERT_EQ(last->data, 2);
    ASSERT_EQ(last->next, nullptr);
}

TEST_F(ListPop, ThreeElemOnePop) {
    last = insertList({1, 2, 3});

    ASSERT_EQ(last->data, 3);
    ASSERT_EQ(last->next->data, 2);
    ASSERT_EQ(last->next->next->data, 1);
    ASSERT_EQ(last->next->next->next, nullptr);

    last = pop(last);
    ASSERT_EQ(last->data, 3);
    ASSERT_EQ(last->next->data, 2);
    ASSERT_EQ(last->next->next, nullptr);
}