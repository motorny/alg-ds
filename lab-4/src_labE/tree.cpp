//
// Created by ikuzin on 12.12.2020.
//
#include "tree.h"
#include "cstring"
#include "malloc.h"


void DeleteFromTree(treeNode_t **tree) {
    treeNode_t *elemToDel, **tmp;

    elemToDel = *tree;

    if ((*tree)->leftPtr == NULL && (*tree)->rightPtr == NULL)
        (*tree) = NULL;
    else if ((*tree)->leftPtr == NULL)
        (*tree) = (*tree)->rightPtr;
    else if ((*tree)->rightPtr == NULL)
        (*tree) = (*tree)->leftPtr;
    else {
        tmp = &(*tree)->leftPtr;
        while ((*tmp)->rightPtr != NULL)
            tmp = &(*tmp)->rightPtr;
        strcpy((*tree)->word, (*tmp)->word);
        elemToDel = *tmp;
        (*tmp) = (*tmp)->leftPtr;
    }

    free(elemToDel);
}

void ClearTree(treeNode_t **tree) {
    while ((*tree) != NULL)
        DeleteFromTree(tree);
}

void inOrder(const treeNode_t *x, int depth) {
    if (x == NULL)
        return;
    inOrder(x->leftPtr, depth + 1);
    for (int i = 0; i < depth; ++i)
        printf("       ");
    printf("%s<\n", x->word);
    inOrder(x->rightPtr, depth + 1);
}

void getStringParts(char **&string, char *buffer) {
    if (strlen(buffer) == 0)
        return;
    char *tmp = (char *) malloc(sizeof(char) * strlen(buffer));
    tmp = strtok(buffer, " ");
    if (tmp != NULL) {
        string[0] = (char *) malloc(sizeof(char) * strlen(tmp));
        string[0] = tmp;
    }
    tmp = strtok(NULL, "\0");
    if (tmp == NULL)
        return;
    int j, k, i[] = {0, 0};
    k = 0;
    for (j = 0; j < strlen(tmp); j++) {
        if (tmp[j] == '(')
            k += 1;
        if (tmp[j] == ')')
            k -= 1;
        if (k == 0) {
            i[i[0] == 0 ? 0 : 1] = j;
            continue;
        }
    }
    j = i[0];
    while (tmp[j] == ')') {
        j++;
    }
    if (i[0] != strlen(tmp)) {
        string[1] = (char *) malloc(sizeof(char) * i[0]);
        strncpy(string[1], &tmp[1], i[0] - (j - i[0]));
    }
    strncpy(tmp, &tmp[i[0] + j - i[0]], strlen(tmp));
    if (i[1] != strlen(tmp)) {
        string[2] = (char *) malloc(sizeof(char) * (i[1] - i[0]));
        strncpy(string[2], &tmp[1], i[1] - i[0] - 2);
    }
}

void addChildren(treeNode_t *&p, char *string) {
    char **strs = (char **) calloc(3, sizeof(char *));
    getStringParts(strs, string);
    treeNode_t *c = (treeNode *) malloc(sizeof(treeNode));
    if (c == NULL)
        return;
    if (strs[0]) {
        c->word = strs[0];
    }
    p = c;
    if (strs[1] != NULL)
        addChildren(c->leftPtr, strs[1]);
    if (strs[2] != NULL)
        addChildren(c->rightPtr, strs[2]);
    free(strs);
}


