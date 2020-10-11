#include "gtest/gtest.h"
#include "../Lib List/ListBirthDay.c"
#include <string.h>
#include <stdlib.h>

char *PointString(const char *str) {
    char *start, *point = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    start = point;
    while ( *point++ = *str++ );
    return start;
}

int CompareString(const char *str1, const char *str2) {
    while ( *str1 == *str2 && *str1 && *str2 ) {
        str1++;
        str2++;
    }

    if ( *str1 == (char)0 && *str2 == (char) 0 ) {
        return 1;
    }
    else {
        return 0;
    }
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

// int AddDayToList(ListDays **q, time_t time, char *fio);
TEST(AddDayToListTest, NULLq_returnTrue) {
    ListDays *list = NULL;

    ASSERT_EQ(AddDayToList(&list, (time_t) 989193600, PointString("Ширяев Виктор Андреевич")), SUCCESS);
    ASSERT_EQ(list->time, (time_t) 989193600);
    ASSERT_TRUE(CompareString(list->fio->fio, "Ширяев Виктор Андреевич"));

    DestroyList(&list);
}

TEST(AddDayToListTest, qOf1ElementAddToTheTop_returnTRUE) {
    ListDays *list = NULL;
    AddDayToList(&list, (time_t) 989193600, PointString("Ширяев Виктор Андреевич"));

    ASSERT_EQ(AddDayToList(&list, (time_t) 83635200, PointString("Леонтьев Алексей Александрович")), SUCCESS);
    ASSERT_EQ(list->time, (time_t) 83635200);
    ASSERT_TRUE(CompareString(list->fio->fio, "Леонтьев Алексей Александрович"));
    ASSERT_EQ(list->next->time, (time_t) 989193600);
    ASSERT_TRUE(CompareString(list->next->fio->fio, "Ширяев Виктор Андреевич"));

    DestroyList(&list);
}

TEST(AddDayToListTest, qOf1ElementAddToTheEnd_returnTRUE) {
    ListDays *list = NULL;
    AddDayToList(&list, (time_t) 989193600, PointString("Ширяев Виктор Андреевич"));

    ASSERT_EQ(AddDayToList(&list, (time_t) 1349136000, PointString("Николаева Маргарита Кирилловна")), SUCCESS);
    ASSERT_EQ(list->time, (time_t) 989193600);
    ASSERT_TRUE(CompareString(list->fio->fio, "Ширяев Виктор Андреевич"));
    ASSERT_EQ(list->next->time, (time_t) 1349136000);
    ASSERT_TRUE(CompareString(list->next->fio->fio, "Николаева Маргарита Кирилловна"));

    DestroyList(&list);
}


TEST(AddDayToListTest, qOf2ElementAddToTheTop_returnTRUE) {
    ListDays *list = NULL;
    AddDayToList(&list, (time_t) 989193600, PointString("Ширяев Виктор Андреевич"));
    AddDayToList(&list, (time_t) 1349136000, PointString("Николаева Маргарита Кирилловна"));

    ASSERT_EQ(AddDayToList(&list, (time_t) 83635200, PointString("Леонтьев Алексей Александрович")), SUCCESS);
    ASSERT_EQ(list->time, (time_t) 83635200);
    ASSERT_TRUE(CompareString(list->fio->fio, "Леонтьев Алексей Александрович"));
    ASSERT_EQ(list->next->time, (time_t) 989193600);
    ASSERT_TRUE(CompareString(list->next->fio->fio, "Ширяев Виктор Андреевич"));
    ASSERT_EQ(list->next->next->time, (time_t) 1349136000);
    ASSERT_TRUE(CompareString(list->next->next->fio->fio, "Николаева Маргарита Кирилловна"));

    /*
    ASSERT_EQ(list->time, (time_t));
    ASSERT_TRUE(CompareString(list->fio->fio, ""));
    ASSERT_EQ(list->next->time, (time_t));
    ASSERT_TRUE(CompareString(list->next->fio->fio, ""));
    ASSERT_EQ(list->next->next->time, (time_t));
    ASSERT_TRUE(CompareString(list->next->next->fio->fio, ""));
    */


    DestroyList(&list);
}

TEST(AddDayToListTest, qOf2ElementAddToTheMiddle_returnTRUE) {
    ListDays *list = NULL;
    AddDayToList(&list, (time_t) 1349136000, PointString("Николаева Маргарита Кирилловна"));
    AddDayToList(&list, (time_t) 965088000, PointString("Спиридонов Лев Ярославович"));

    ASSERT_EQ(AddDayToList(&list, (time_t) 989193600, PointString("Ширяев Виктор Андреевич")), SUCCESS);
    ASSERT_EQ(list->time, (time_t) 965088000);
    ASSERT_TRUE(CompareString(list->fio->fio, "Спиридонов Лев Ярославович"));
    ASSERT_EQ(list->next->time, (time_t) 989193600);
    ASSERT_TRUE(CompareString(list->next->fio->fio, "Ширяев Виктор Андреевич"));
    ASSERT_EQ(list->next->next->time, (time_t) 1349136000);
    ASSERT_TRUE(CompareString(list->next->next->fio->fio, "Николаева Маргарита Кирилловна"));

    DestroyList(&list);
}

TEST(AddDayToListTest, qOf2ElementAddToTheEnd_returnTRUE) {
    ListDays *list = NULL;
    AddDayToList(&list, (time_t) 989193600, PointString("Ширяев Виктор Андреевич"));
    AddDayToList(&list, (time_t) 965088000, PointString("Спиридонов Лев Ярославович"));

    ASSERT_EQ(AddDayToList(&list, (time_t) 1349136000, PointString("Николаева Маргарита Кирилловна")), SUCCESS);
    ASSERT_EQ(list->time, (time_t) 965088000);
    ASSERT_TRUE(CompareString(list->fio->fio, "Спиридонов Лев Ярославович"));
    ASSERT_EQ(list->next->time, (time_t) 989193600);
    ASSERT_TRUE(CompareString(list->next->fio->fio, "Ширяев Виктор Андреевич"));
    ASSERT_EQ(list->next->next->time, (time_t) 1349136000);
    ASSERT_TRUE(CompareString(list->next->next->fio->fio, "Николаева Маргарита Кирилловна"));

    DestroyList(&list);
}


TEST(AddDayToListTest, NULLfio_returnERROR) {
    ListDays *list = NULL;

    ASSERT_EQ(AddDayToList(&list, (time_t) 1349136000, NULL), ERROR);

    DestroyList(&list);
}


TEST(AddDayToListTest, ERRORtime_returnERROR) {
    ListDays *list = NULL;

    ASSERT_EQ(AddDayToList(&list, (time_t) (-1), PointString("Николаева Маргарита Кирилловна")), ERROR);

    DestroyList(&list);
}

// ListDays *FindDay(time_t time, ListDays *q);
TEST(FindDayTest, ERRORtime_returnNULL) {
    ListDays *list = NULL;
    AddDayToList(&list, (time_t) 989193600, PointString("Ширяев Виктор Андреевич"));
    AddDayToList(&list, (time_t) 965088000, PointString("Спиридонов Лев Ярославович"));

    ASSERT_TRUE(FindDay((time_t) (-1), list) == NULL);

    DestroyList(&list);
}

TEST(FindDayTest, NULLq_returnNULL) {
    ListDays *list = NULL;

    ASSERT_TRUE(FindDay((time_t) 989234680, NULL) == NULL);

    DestroyList(&list);
}

TEST(FindDayTest, listOf2ElementExistingDate_returnPointer) {
    ListDays *list = NULL, *lday;
    AddDayToList(&list, (time_t) 989193600, PointString("Ширяев Виктор Андреевич"));
    AddDayToList(&list, (time_t) 965088000, PointString("Спиридонов Лев Ярославович"));

    lday = FindDay((time_t) 965088000, list);
    ASSERT_TRUE(lday != NULL);
    ASSERT_EQ(lday->time, (time_t) 965088000);
    ASSERT_TRUE(CompareString(lday->fio->fio, "Спиридонов Лев Ярославович"));

    DestroyList(&list);
}

TEST(FindDayTest, listOf2ElementNonExistingDate_returnNULL) {
    ListDays *list = NULL;
    AddDayToList(&list, (time_t) 989193600, PointString("Ширяев Виктор Андреевич"));
    AddDayToList(&list, (time_t) 965088000, PointString("Спиридонов Лев Ярославович"));

    ASSERT_TRUE(FindDay((time_t) 989234680, list) == NULL);

    DestroyList(&list);
}