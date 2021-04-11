#ifndef TREE23_H
#define TREE23_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAIL 0

typedef struct TreeNode TreeNode;
struct TreeNode {
    bool isLeaf;

    int data;
    int maxSubtreeData;
    int childsCount;
    int leftNum, rightNum;
    TreeNode* left;
    TreeNode* middle;
    TreeNode* right;
    TreeNode* parent;
};

typedef struct treeStackNode treeStackNode;
struct treeStackNode{
    TreeNode* currentTree;
    treeStackNode *nextTree;
};

//int UnTwoNodes(TreeNode** tree, TreeNode* nodeInTree, TreeNode* newNode);

int Insert(TreeNode** tree, int newElement);
int Find(TreeNode* tree, int element);
int Delete(TreeNode** tree, int deleteElement);

int Merge(TreeNode** tree, TreeNode* tree1, TreeNode* tree2);
int Split(TreeNode* tree, TreeNode** tree1, TreeNode** tree2, int elementToSplit);

#endif // TREE23_H
