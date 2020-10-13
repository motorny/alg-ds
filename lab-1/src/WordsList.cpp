#include "WordsList.h"
#include "iostream"

int ruChar(char *word) {
    return tolowerRu(tolower(word[1])) <= 143 ?
           tolowerRu(tolower(word[1])) + 64 : tolowerRu(tolower(word[1]));
}

int tolowerRu(int c) {
    if (c >= 144 && c <= 175) {
        if (c >= 160) {
            return c - 32;
        } else {
            return c + 32;
        }
    }
    return c;
}

WordsListNode *initWordsListNode(char *word, unsigned int len) {
    auto *newNode = (WordsListNode *) malloc(sizeof(WordsListNode));
    newNode->nextPtr = nullptr;
    newNode->word = word;
    newNode->countOfLetters = len;
    return newNode;
}

unsigned int getCountOfLetters(const char word[]) {
    unsigned int counter = 0;
    while (word[counter] != '\0') {
        counter++;
    }
    return counter / 2;
}

void insert(WordsListNode *&currentNode, WordsListNode *&newNode) {
    newNode->nextPtr = currentNode->nextPtr;
    currentNode->nextPtr = newNode;
}


void insertFirst(WordsListNode *&currentFstNode, WordsListNode *&newNode) {
    newNode->nextPtr = currentFstNode;
    currentFstNode = newNode;
}

void add2List(char *word, WordsListNode *&listHead, unsigned int len) {
    WordsListNode *newWord = initWordsListNode(word, len);
    if (listHead == nullptr || listHead->countOfLetters > len ||
        (ruChar(listHead->word) > ruChar(word) && listHead->countOfLetters == len)) {
        insertFirst(listHead, newWord);
        return;
    }
    WordsListNode *prevWord, *currWord = listHead;
    while (currWord->countOfLetters < len && currWord->nextPtr != nullptr) {
        prevWord = currWord;
        currWord = currWord->nextPtr;
    }
    if (currWord->countOfLetters > len) {
        insert(prevWord, newWord);
        return;
    }
    if (currWord->countOfLetters == len) {
        while (ruChar(currWord->word) < ruChar(word) &&
               (currWord->nextPtr != nullptr && currWord->nextPtr->countOfLetters == len)) {
            prevWord = currWord;
            currWord = currWord->nextPtr;
        }
        if (ruChar(currWord->word) > ruChar(word)) {
            insert(prevWord, newWord);
            return;
        }
        insert(currWord, newWord);
    }
    if (currWord->nextPtr == nullptr) {
        insert(currWord, newWord);
        return;
    }
}

void cout(WordsListNode *&currNode, bool all) {
    unsigned int len = currNode->countOfLetters;
    std::cout << std::endl;
    while (currNode != nullptr && (len == currNode->countOfLetters || all)) {
        std::cout << currNode->word << std::endl;
        currNode=currNode->nextPtr;
    }
}

void printWordsLenN(WordsListNode *&listHead, int n){
    std::cout << "\nСлова длинной " << n;
    WordsListNode *currNode = listHead;
    while (currNode != nullptr && currNode->countOfLetters < n) {
        currNode = currNode->nextPtr;
    }
    if (currNode != nullptr) {
        cout(currNode, false);
        return;
    }
    std::cout << "\nНет слов длинной " << n;
}

void printWordsMoreNLen(WordsListNode *&listHead, int n) {
    std::cout << "\nСлова длинной большей " << n;
    WordsListNode *currNode = listHead;
    while (currNode != nullptr && currNode->countOfLetters < n) {
        currNode = currNode->nextPtr;
    }
    if (currNode != nullptr) {
        cout(currNode, true);
        return;
    }
    std::cout << "\nНет слова длинной большей чем " << n;
}
