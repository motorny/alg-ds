#include "pch.h"
extern "C" {
#include "Header.h"
}

#pragma warning (disable:4996)

TEST(Add_In_List_Test, Add_In_List_Test_ListWithoutElements) {
    list* List = NULL;    char word[] = "Hi\0";
    int number = 1;

    Add_in_list(&List, word, number);
    ASSERT_STREQ((List->word), word);
    ASSERT_EQ(List->number, number);
}
TEST(Add_In_List_Test, Add_In_List_Test_ListWithElement_LessAdded) {
    list* List = NULL;
    char word[] = "Hi\0";
    int number = 2;

    List = (list*)malloc(sizeof(list));
    if (List != NULL) {
        List->number = 1;
        List->word = (char*)malloc(6 * sizeof(char));
        List->word = "Hello\0";
        List->next = NULL;

        Add_in_list(&List, word, number);
        ASSERT_STREQ(List->next->word, word);
        ASSERT_EQ(List->next->number, number);
        ASSERT_GT(List->next->number, List->number);

    }

}


TEST(Add_In_List_Test, Add_In_List_Test_ListWithElement_MoreAdded) {
    list* List = NULL;
    char word[] = "Hi\0";
    int number = 2;

    List = (list*)malloc(sizeof(list));
    if (List != NULL) {
        List->number = 3;
        List->word = (char*)malloc(6 * sizeof(char));
        List->word = "Hello\0";
        List->next = NULL;

        Add_in_list(&List, word, number);
        ASSERT_STREQ(List->word, word);
        ASSERT_EQ(List->number, number);
        ASSERT_GT(List->next->number, List->number);
    }

}

TEST(CreateListTest, CreateListTest_) {
    list* block;
    char word[] = "Hi\0";
    int number = 1;

    Create_list(&block, word, number);
    ASSERT_STREQ((block->word), word);
    ASSERT_EQ(block->number, number);
}

TEST(Get_Nth_List_Test, Get_Nth_List_Test_) {
    list block1;
    list block2;
    list block3;

    list* blockNth = NULL;

    block1.number = 1;
    block1.next = &block2;
    block2.number = 2;
    block2.next = &block3;
    block3.number = 3;
    block3.next = NULL;
    blockNth = get_Nth_list(&block1, 4);
    ASSERT_EQ(&block3, blockNth);

}

TEST(Clear_List_Test, Clear_List_Test) {
    list* List = NULL;

    List = (list*)malloc(sizeof(list));
    if (List != NULL) {
        List->number = 3;
        List->word = (char*)malloc(7 * sizeof(char));
        if (List->word != NULL) {
            strcpy(List->word, "Hello\0");
            List->next = (list*)malloc(sizeof(list));
            if (List->next != NULL) {
                List->next->number = 4;
                List->next->word = (char*)malloc(4 * sizeof(char));
                if (List->next->word != NULL) {
                    strcpy(List->next->word, "Hi\0");
                }
                List->next->next = NULL;
            }
        }

        Clear_list(&List);

    }
    ASSERT_TRUE(List == NULL);
}

int main(void) {
    return RUN_ALL_TESTS();
}