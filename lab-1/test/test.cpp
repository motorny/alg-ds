#include "pch.h"
extern "C" {
#include "..//LAB_J/LAB_J.c"
}


TEST(TEST_HASHFUNC, ReturnRigthEq) {
    EXPECT_EQ(Hash((char*)"mfa"), 40);
    EXPECT_EQ(Hash((char*)"...."), 50);
    EXPECT_EQ(Hash((char*)"0"), 48);
    EXPECT_EQ(Hash(NULL), 0);
}


TEST(TEST_DELETEFUNC, Rightexpressions) {
    Addelem((char*)"mfa");
    Addelem((char*)"....");
    Addelem((char*)"0");

    Deleteelem(hash[40]->str);
    Deleteelem(hash[50]->str);
    Deleteelem(hash[48]->str);

    EXPECT_TRUE(hash[40] == NULL);
    EXPECT_TRUE(hash[50] == NULL);
    EXPECT_TRUE(hash[48] == NULL);
}


TEST(TEST_ADDFUNC, SuccessfulAddition) {
    //  the indexes are taken from the first test
    Addelem((char*)"mfa");
    EXPECT_STREQ(hash[40]->str, "mfa");
    Addelem((char*)"....");
    EXPECT_STREQ(hash[50]->str, "....");
    Addelem((char*)"0");
    EXPECT_STREQ(hash[48]->str, "0");
}

TEST(TEST_FINDFUNC, Rightexpressions) {
    Addelem((char*)"a");
    Addelem((char*)"b");
    EXPECT_TRUE(Findelem((char*)"a"));
    EXPECT_TRUE(Findelem((char*)"b"));
    EXPECT_FALSE(Findelem(NULL));
}

