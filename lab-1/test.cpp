#include "pch.h"
extern "C"
{
#include "LabA.h"
}
#pragma warning (disable:4996)

TEST(TestSortSubstitution, Test_SortSubstitution_RightPlaceOfWord_ReturnPointerToTheLocalBegining) {
    char word1[] = "accp";
    char word2[] = "axc";
    char word3[] = "tye";

    list testlist;
    testlist.previous = NULL;
    strcpy(testlist.string, word1);

    list testlistp;
    testlistp.previous = NULL;
    strcpy(testlistp.string, word2);

    list testlistpp;
    testlistpp.previous = NULL;
    strcpy(testlistpp.string, word3);

    testlistp.previous = &testlistpp;
    testlist.previous = &testlistp;

    list* ad = &testlist;
    SortSubstitution(ad);

    ASSERT_STREQ(ad->string, word1);
    ASSERT_TRUE(ad->previous == NULL);
}
TEST(TestSortSubstitution, Test_SortSubstitution_MovingWords_ReturnPointerToTheLocalBegining) {
    char word1[] = "accp";
    char word2[] = "axc";
    char word3[] = "tye";

    list testlist;
    testlist.previous = NULL;
    strcpy(testlist.string, word1);

    list testlistp;
    testlistp.previous = NULL;
    strcpy(testlistp.string, word2);

    list testlistpp;
    testlistpp.previous = NULL;
    strcpy(testlistpp.string, word3);

    testlistp.previous = &testlistpp;
    testlist.previous = &testlistp;

    list* ad = &testlist;
    list* proverka = SortSubstitution(ad);

    ASSERT_STREQ(proverka->string, word2);
    ASSERT_STREQ(proverka->previous->string, word3);
    ASSERT_STREQ(proverka->previous->previous->string, word1);
    ASSERT_TRUE(proverka->previous->previous->previous == NULL);
}

TEST(TestSortList, Test_SortList_SortingByLengthAndAlphabet_LiningUpInTheRightOrder) {
    char word1[] = "accp";
    char word2[] = "axc";
    char word3[] = "tye";

    list testlist;
    testlist.previous = NULL;
    strcpy(testlist.string, word1);

    list testlistp;
    testlistp.previous = NULL;
    strcpy(testlistp.string, word2);

    list testlistpp;
    testlistpp.previous = NULL;
    strcpy(testlistpp.string, word3);

    testlistp.previous = &testlistpp;
    testlist.previous = &testlistp;

    list ad;
    ad.previous = &testlist;
    SortList(&ad);

    ASSERT_STREQ(ad.previous->string, word2);
    ASSERT_STREQ(ad.previous->previous->string, word3);
    ASSERT_STREQ(ad.previous->previous->previous->string, word1);
    ASSERT_TRUE(ad.previous->previous->previous->previous == NULL);
}

TEST(TestSortList, Test_SortList_TheEndOfSorting_ReturnEmptyCheckBox) {
    char word1[] = "accp";
    char word2[] = "axc";
    char word3[] = "tye";

    list testlist;
    testlist.previous = NULL;
    strcpy(testlist.string, word1);

    list testlistp;
    testlistp.previous = NULL;
    strcpy(testlistp.string, word2);

    list testlistpp;
    testlistpp.previous = NULL;
    strcpy(testlistpp.string, word3);

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
