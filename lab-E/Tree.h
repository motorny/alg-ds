#pragma once
typedef struct NODE{
	struct NODE* parent;
	struct NODE* left;
	struct NODE* right;
	int data;
} NODE;

NODE* CreateNode(int data, NODE* parent);
void InsertInTree(NODE** root, int data);
NODE* GetMinNode(NODE* root);
NODE* GetMaxNode(NODE* root);
NODE* SearchNodeByData(NODE* root, int data);
void RemoveNodeByPtr(NODE* target);
void RemoveNodeByData(NODE* root, int data);
void printTreePreOrder(NODE* root, const char* dir, int level);
void printTreePostOrder(NODE* root);
void ConsoleTree(NODE** root);
void WriteInDataMinLeavesHeight(NODE* root);