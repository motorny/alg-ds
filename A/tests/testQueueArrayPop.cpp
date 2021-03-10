#include <vector>

#include <gtest/gtest.h>

#include "../Array.h"

class ArrayPop : public ::testing::Test {
protected:
    int* array = nullptr;
    int size = 0;

    ArrayPop() = default;

    ~ArrayPop() override { freeArray(array); }

    int* insertArray(const std::vector<int> &values) {
        for (int i : values)
            array = append(array, &size, i);
        return array;
    }
};

TEST_F(ArrayPop, EmptyArray) {
    ASSERT_EQ(array, nullptr);

    array = popleft(array, &size);
    ASSERT_EQ(array, nullptr);
}

TEST_F(ArrayPop, OneElem) {
    array = insertArray({1});

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(size, 1);

    array = popleft(array, &size);
    ASSERT_EQ(array, nullptr);
    ASSERT_EQ(size, 0);
}

TEST_F(ArrayPop, TwoElemOnePop) {
    array = insertArray({1, 2});

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[1], 2);
    ASSERT_EQ(size, 2);

    array = popleft(array, &size);
    ASSERT_EQ(array[0], 2);
    ASSERT_EQ(size, 1);
}

TEST_F(ArrayPop, TwoElemTwoPop) {
    array = insertArray({1, 2});

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[1], 2);
    ASSERT_EQ(size, 2);

    array = popleft(array, &size);
    array = popleft(array, &size);
    ASSERT_EQ(array, nullptr);
    ASSERT_EQ(size, 0);
}

TEST_F(ArrayPop, ReallocPop) {
    array = insertArray({1, 2, 3, 4, 5, 6, 7, 8, 9});

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[8], 9);
    ASSERT_EQ(size, 9);

    array = popleft(array, &size);
    ASSERT_EQ(array[0], 2);
    ASSERT_EQ(array[7], 9);
    ASSERT_EQ(size, 8);
}
