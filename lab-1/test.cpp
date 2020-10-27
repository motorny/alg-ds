#include "pch.h"
extern "C"
{
#include "LabA.h"
}
#pragma warning (disable:4996)

TEST(TestPutWord, Test_PutWord_RightPlaceOfWordBeforeAnother_ReturnPointerToTheLocalBegining) {
    char word1[] = "axc";
    char word2[] = "accp";
    char word3[] = "tye";

    list testlist;
    testlist.previous = NULL;
    strcpy(testlist.string, word1);

    list testlistp;
    testlistp.previous = NULL;
    strcpy(testlistp.string, word2);

    testlist.previous = &testlistp;

    list testnewword;
    testnewword.previous = NULL;
    strcpy(testnewword.string, word3);

    PutWord(&testlist, &testnewword);

    ASSERT_STREQ(testnewword.string, word3);
    ASSERT_STREQ(testnewword.previous->string, word2);
    ASSERT_TRUE(testnewword.previous->previous == NULL);
}

TEST(TestPutWord, Test_PutWord_RightPlaceOfWordAfterAnother_ReturnPointerToTheLocalBegining) {
    char word1[] = "axc";
    char word2[] = "tye";
    char word3[] = "accp";

    list testlist;
    testlist.previous = NULL;
    strcpy(testlist.string, word1);

    list testlistp;
    testlistp.previous = NULL;
    strcpy(testlistp.string, word2);

    testlist.previous = &testlistp;

    list testnewword;
    testnewword.previous = NULL;
    strcpy(testnewword.string, word3);

    PutWord(&testlist, &testnewword);

    ASSERT_STREQ(testlist.string, word1);
    ASSERT_STREQ(testlist.previous->string, word2);
    ASSERT_STREQ(testlist.previous->previous->string, word3);
    ASSERT_TRUE(testlist.previous->previous->previous == NULL);
}

TEST(TestWordToList, Test_WordToList_AddingTheFirstWord_SettingTheFirstWordToTheBegining) {
    char word[] = "accp";

    list testlist;
    testlist.previous = NULL;

    list testnewword;
    testnewword.previous = NULL;
    strcpy(testnewword.string, word);

    WordToList(&testlist, &testnewword);

    ASSERT_STREQ(testlist.previous->string, word);
    ASSERT_TRUE(testlist.previous->previous == NULL);
}

TEST(TestWordToList, Test_WordToList_AddingNotTheFirstWord_SettingTheWordToTheRightPlace) {
    char word1[] = "axc";
    char word2[] = "tye";

    list testlist;
    testlist.previous = NULL;
    strcpy(testlist.string, word1);

    list testnewword;
    testnewword.previous = NULL;
    strcpy(testnewword.string, word2);

    list ad;
    ad.previous = &testlist;

    WordToList(&ad, &testnewword);

    ASSERT_STREQ(ad.previous->string, word1);
    ASSERT_STREQ(ad.previous->previous->string, word2);
    ASSERT_TRUE(ad.previous->previous->previous == NULL);
}


int main(void){
return RUN_ALL_TESTS();
    }
