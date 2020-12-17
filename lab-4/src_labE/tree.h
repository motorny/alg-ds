//
// Created by ikuzin on 12.12.2020.
//

#ifndef LAB_4_TREE_H
#define LAB_4_TREE_H

typedef struct treeNode {
    struct treeNode *leftPtr;
    struct treeNode *rightPtr;
    char *word;
} treeNode_t;

void getStringParts(char **&, char *);

void addChildren(treeNode_t *&, char *);

void inOrder(const treeNode_t *, int);

void DeleteFromTree(treeNode_t **tree);

void ClearTree(treeNode_t **tree);

#endif //LAB_4_TREE_H
