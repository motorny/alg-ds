#include <gtest/gtest.h>

#include "../Array.h"

class ArrayInsert : public ::testing::Test {
protected:
    int* array = nullptr;
    int size = 0;

    ArrayInsert() = default;

    ~ArrayInsert() override { freeArray(array); }
};

TEST_F(ArrayInsert, OneElem) {
    ASSERT_EQ(array, nullptr);

    array = append(array, &size, 1);
    ASSERT_EQ(array[0], 1);
}

TEST_F(ArrayInsert, TwoElems) {
    array = append(array, &size, 1);
    array = append(array, &size, 2);

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[1], 2);
    ASSERT_EQ(size, 2);
}

TEST_F(ArrayInsert, Realloc) {
    array = append(array, &size, 1);
    array = append(array, &size, 2);
    array = append(array, &size, 3);
    array = append(array, &size, 4);
    array = append(array, &size, 5);
    array = append(array, &size, 6);
    array = append(array, &size, 7);
    array = append(array, &size, 8);
    array = append(array, &size, 9);

    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[8], 9);
    ASSERT_EQ(size, 9);
}