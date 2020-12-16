#pragma once

#define TRUE 1
#define FALSE 0
#define NULL_DATA 0

typedef enum direction_t {
	FROM_PARENT = 1,
	FROM_LEFT,
	FROM_RIGHT
} direction_t;

typedef struct node_t {
	struct node_t* parent;
	struct node_t* left;
	struct node_t* right;
	int leftBorder;
	int rightBorder;
} node_t;

int AddNode(node_t** tree, int leftBorderValue, int rightBorderValue);
node_t* FindMaxLeftBorderNode(node_t* tree);
node_t* FindNode(node_t* tree, int leftBorderValue, int rightBorderValue);
int RemoveNode(node_t** tree, int leftBorderValue, int rightBorderValue);

void DestroyTree(node_t** tree);
void PrintTree(node_t* tree, int level);
node_t** FindIntersections(node_t* tree, int leftBorder, int rightBorder);
void ManageTreeOfIntervals(node_t** tree);