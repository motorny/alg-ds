#include<stdbool.h>

#pragma once
typedef struct NODE {
	int leftBorder;
	int rightBorder;
	struct NODE* parent;
	struct NODE* left;
	struct NODE* right;
}NODE;

void InsertInTree(NODE** root, int leftBorder, int rightBorder);
static NODE* GetMinLeftBorderNode(NODE* root);
static NODE* GetMaxLeftBorderNode(NODE* root);
static void RemoveNodeByPtr(NODE* target, NODE* root);
static NODE* SearchNodeByData(NODE* root, int leftBorder, int rightBorder);
static void RemoveNodeByData(NODE* root, int leftBorder, int rightBorder);
void DestroyTree(NODE** root);
void ConsoleTree(NODE** root);
void printTreePreOrder(NODE* root, const char* dir, int level);
void printTreePostOrder(NODE* root);
void PrintSectMass(NODE** mass);
NODE** FindInterSegm(NODE* root, int leftBorder, int rightBorder);
bool CheckForCrossing(int leftFinding, int rightFinding, int leftWith, int rightWith);
