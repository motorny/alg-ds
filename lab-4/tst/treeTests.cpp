//
// Created by ikuzin on 16.12.2020.
//
#include "gtest/gtest.h"
#include "tree.h"
#include "labF.h"


char *getTextFromFile(char *path) {
    FILE *file;
    const char *fName = path;
    file = fopen(fName, "r");
    if (file != nullptr) {
        fseek(file, 0, SEEK_END);
        long lSize = ftell(file);
        rewind(file);
        char *buffer = (char *) malloc(sizeof(char) * lSize);
        return buffer;
    }
    return NULL;
}

TEST(getStringParts1, NullStr) {
    char *str, **string;
    string = (char **) calloc(3, sizeof(char *));
    str = getTextFromFile("/home/ikuzin/study/algo_and_struct/alg-ds/lab-4/tst/nullFile.txt");
    getStringParts(string, str);
    EXPECT_EQ(NULL, string[0]);
    EXPECT_EQ(NULL, string[1]);
    EXPECT_EQ(NULL, string[2]);
    free(string);
}

TEST(getStringParts2, OK) {
    char *str, **string;
    string = (char **) calloc(3, sizeof(char *));
    str = getTextFromFile("/home/ikuzin/study/algo_and_struct/alg-ds/lab-4/word'stree.txt");
    getStringParts(string, str);
    EXPECT_EQ("hello", string[0]);
    EXPECT_EQ("how", string[1]);
    EXPECT_EQ("you", string[2]);
    free(string);
}

TEST(addChilderen, OK) {
    char *str, **string;
    string = (char **) calloc(3, sizeof(char *));
    str = getTextFromFile("/home/ikuzin/study/algo_and_struct/alg-ds/lab-4/word'stree.txt");
    treeNode_t *root = (treeNode_t *) malloc(sizeof(treeNode_t));
    addChildren(root, str);
    EXPECT_NE(NULL, root);
    EXPECT_EQ("hello", root->word);
    EXPECT_NE(NULL, root->leftPtr);
    EXPECT_NE(NULL, root->rightPtr);
    EXPECT_EQ("how", root->leftPtr->word);
    EXPECT_EQ("you", root->rightPtr->word);
    free(string);
    ClearTree(&root);
}

TEST(clearTree, OK) {
    char *str, **string;
    string = (char **) calloc(3, sizeof(char *));
    str = getTextFromFile("/home/ikuzin/study/algo_and_struct/alg-ds/lab-4/word'stree.txt");
    treeNode_t *root = (treeNode_t *) malloc(sizeof(treeNode_t));
    addChildren(root, str);
    ClearTree(&root);
    EXPECT_EQ(NULL, root);
    free(string);
    ClearTree(&root);
}
