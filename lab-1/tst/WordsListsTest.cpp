//
// Created by ikuzin on 10.10.2020.
//
#include "gtest/gtest.h"
#include "WordsList.h"


TEST(getCountOfLettersTest, 1) {
    char *word = "привет";
    ASSERT_EQ(getCountOfLetters(word), 6);
}

TEST(getCountOfLettersTest, 1_empty_string) {
    char *word = "";
    ASSERT_EQ(getCountOfLetters(word), 0);
}

TEST(ruCharTest, 2) {
    char *testWord = "Привет";
    ASSERT_EQ(ruChar(testWord), 191);
}

TEST(toLowerRuTest, 3) {
    char *letter = "П";
    ASSERT_EQ(tolowerRu(tolower("П"[1])), tolowerRu(tolower("п"[1])));
}

TEST(initNodeTest, 4) {
    WordsListNode *tmp = (WordsListNode*) malloc(sizeof(WordsListNode));
    tmp->nextPtr = nullptr;
    tmp->word = "Тестовое";
    tmp->countOfLetters = 8;
    WordsListNode * autoTmp = initWordsListNode("Тестовое", 8);
    ASSERT_EQ(tmp->nextPtr, autoTmp->nextPtr);
    ASSERT_EQ(tmp->word, tmp->word);
    ASSERT_EQ(tmp->countOfLetters, tmp->countOfLetters);
}

TEST(insertInListTest, 5) {
    WordsListNode *tmp2 = (WordsListNode*) malloc(sizeof(WordsListNode));
    WordsListNode *tmp1 = (WordsListNode*) malloc(sizeof(WordsListNode));
    WordsListNode *tmp = (WordsListNode*) malloc(sizeof(WordsListNode));
    //tmp -> tmp1 -> tmp2
    tmp->nextPtr = tmp2;
    insert(tmp, tmp1);
    tmp1->word = "Пока";
    ASSERT_EQ(tmp->nextPtr->word, tmp1->word);
    ASSERT_EQ(tmp1->nextPtr, tmp2);
}

TEST(insertFirstInListTest, 6) {
    WordsListNode *tmp2 = (WordsListNode*) malloc(sizeof(WordsListNode));
    WordsListNode *tmp1 = (WordsListNode*) malloc(sizeof(WordsListNode));
    WordsListNode *tmp = (WordsListNode*) malloc(sizeof(WordsListNode));
    WordsListNode *head = tmp1;
    //tmp -> tmp1 -> tmp2
    tmp1->nextPtr = tmp2;
    ASSERT_EQ(head, tmp1);
    insertFirst(head, tmp);
    tmp->word = "угу";
    ASSERT_EQ(head->word, tmp->word);
    ASSERT_EQ(tmp->nextPtr, tmp1);
}

TEST(add2ListTest, 7_head_empty) {
    WordsListNode * head = nullptr;
    add2List("Привет", head, 6);
    ASSERT_STRCASEEQ(head->word,"Привет");
    ASSERT_EQ(head->countOfLetters, 6);
    ASSERT_NE(&head, nullptr);
}

TEST(add2ListTest, 7_head_more_len) {
    WordsListNode * head = (WordsListNode*) malloc(sizeof(WordsListNode));
    head->word = "Привет";
    head->countOfLetters = 6;
    add2List("Пока", head, 4);
    ASSERT_STRCASEEQ(head->word,"Пока");
    ASSERT_EQ(head->countOfLetters, 4);
}


TEST(add2ListTest, 7_head_a_after_b) {
    WordsListNode * head = (WordsListNode*) malloc(sizeof(WordsListNode));
    head->word = "Привет";
    head->countOfLetters = 6;
    add2List("Аривет", head, 6);
    ASSERT_STRCASEEQ(head->word,"Аривет");
    ASSERT_EQ(head->countOfLetters, 6);
}

TEST(add2ListTest, 7_next_after_head) {
    WordsListNode * head = (WordsListNode*) malloc(sizeof(WordsListNode));
    head->word = "Привет";
    head->countOfLetters = 6;
    add2List("Здравствуйте", head, 12);
    ASSERT_STRCASEEQ(head->nextPtr->word,"Здравствуйте");
    ASSERT_EQ(head->nextPtr->countOfLetters, 12);
    ASSERT_NE(head->nextPtr, nullptr);
}

TEST(add2ListTest, 7_next_after_n_with_EQ_len) {
    WordsListNode * head = (WordsListNode*) malloc(sizeof(WordsListNode));
    head->word = "Привет";
    head->countOfLetters = 6;
    WordsListNode * tmp = (WordsListNode*) malloc(sizeof(WordsListNode));
    tmp->word = "Приветствие";
    tmp->countOfLetters = 11;
    head->nextPtr = tmp;
    add2List("Ариветствие", head, 11);
    ASSERT_STRCASEEQ(head->nextPtr->word,"Ариветствие");
    ASSERT_STRCASEEQ(head->nextPtr->nextPtr->word, "Приветствие");
}

TEST(add2ListTest, 7_next_nullptr) {
    WordsListNode * head = (WordsListNode*) malloc(sizeof(WordsListNode));
    head->word = "Привет";
    head->countOfLetters = 6;
    WordsListNode * tmp = (WordsListNode*) malloc(sizeof(WordsListNode));
    tmp->word = "Приветули";
    tmp->countOfLetters = 9;
    WordsListNode * tmp1 = (WordsListNode*) malloc(sizeof(WordsListNode));
    tmp1->word = "Приветствие";
    tmp1->countOfLetters = 11;
    head->nextPtr = tmp;
    tmp->nextPtr = tmp1;
    add2List("Аффектированный", head, 15);
    ASSERT_NE(head->nextPtr->nextPtr->nextPtr, nullptr);
    ASSERT_STRCASEEQ(head->nextPtr->nextPtr->nextPtr->word, "Аффектированный");
}