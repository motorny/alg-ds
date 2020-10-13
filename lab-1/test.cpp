#include "pch.h"
extern "C"
{
#include "LabA.h"
}
#pragma warning (disable:4996)

TEST(TestSortSubstitution, Test_SortSubstitution_RightPlaceOfWord_ReturnPointerToTheLocalBegining) {
    list testlist = { NULL,"accp" };
    list testlistp = { NULL, "axc" };
    list testlistpp = { NULL,"tye" };
    testlistp.previous = &testlistpp;
    testlist.previous = &testlistp;

    list* ad = &testlist;
    SortSubstitution(ad);

    ASSERT_STREQ(ad->string, "accp");
    ASSERT_TRUE(ad->previous == NULL);
}
TEST(TestSortSubstitution, Test_SortSubstitution_MovingWords_ReturnPointerToTheLocalBegining) {
    list testlist = {NULL,"accp"};
    list testlistp = { NULL, "axc" };
    list testlistpp = { NULL,"tye" };
    testlistp.previous = &testlistpp;
    testlist.previous = &testlistp;

    list* ad = &testlist;
    list* proverka = SortSubstitution(ad);

    ASSERT_STREQ(proverka->string,"axc");
    ASSERT_STREQ(proverka->previous->string, "tye");
    ASSERT_STREQ(proverka->previous->previous->string, "accp");
    ASSERT_TRUE(proverka->previous->previous->previous == NULL);
}

TEST(TestSortList, Test_SortList_SortingByLengthAndAlphabet_LiningUpInTheRightOrder) {
    list testlist = { NULL,"accp" };
    list testlistp = { NULL, "axc" };
    list testlistpp = { NULL,"tye" };
    testlistp.previous = &testlistpp;
    testlist.previous = &testlistp;

    list ad;
    ad.previous = &testlist;
    SortList(&ad);

    ASSERT_STREQ(ad.previous->string, "axc");
    ASSERT_STREQ(ad.previous->previous->string, "tye");
    ASSERT_STREQ(ad.previous->previous->previous->string, "accp");
    ASSERT_TRUE(ad.previous->previous->previous->previous == NULL);
}

TEST(TestSortList, Test_SortList_TheEndOfSorting_ReturnEmptyCheckBox) {
    list testlist = { NULL,"accp" };
    list testlistp = { NULL, "axc" };
    list testlistpp = { NULL,"tye" };
    testlistp.previous = &testlistpp;
    testlist.previous = &testlistp;

    list ad;
    ad.previous = &testlist;
    SortList(&ad);

    ASSERT_TRUE(flagSort == 0);
}


int main(void){
return RUN_ALL_TESTS();
    }
