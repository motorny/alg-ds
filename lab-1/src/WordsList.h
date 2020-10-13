//
// Created by ikuzin on 05.10.2020.
//
#include "iostream"

#ifndef LAB_1_WORDSLIST_H
#define LAB_1_WORDSLIST_H


typedef struct WordsListNode {
    char *word;
    WordsListNode *nextPtr;
    unsigned int countOfLetters;
} WordsListNode;

WordsListNode *initWordsListNode(char *word, unsigned int);

void add2List(char *, WordsListNode *&, unsigned int);

void printWordsMoreNLen(WordsListNode *&, int n);
void printWordsLenN(WordsListNode *&, int n);


unsigned int getCountOfLetters(const char *);

void insert(WordsListNode*&, WordsListNode*&);

void insertFirst(WordsListNode*&, WordsListNode*&);

int ruChar(char*);

int tolowerRu(int c);


#endif //LAB_1_WORDSLIST_H
