#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef enum BOOL {
	FALSE,
	TRUE
}BOOL;

typedef struct edge_t edge_t;
typedef struct node_t node_t;
typedef struct node_list_t node_list_t;

struct edge_t {
	struct node_t* node;
	struct edge_t* next;
};
	
struct node_t {
	int num;
	struct edge_t* edge_head;
	struct node_t* next;
};

struct node_list_t {
	node_t* head;
	int nodeNum;
};

node_list_t* InitList(int nodeNum);
void FreeNodeList(node_list_t* list);

node_t* NewNode(int num);
//return node if its num is unique in list
//else return ptr to node that already exists
node_t* AddNode(node_list_t* list, node_t* node);
void FreeNode(node_t* node);


edge_t* NewEdge(node_t* node);
void AddEdge(node_t* destination, edge_t* edge);
void FreeEdge(edge_t* edge);
void FreeEdgeList(node_t* node);

void DepthFirstSearch(node_list_t* list);
void PrintNode(node_t* node);
void AttendNode(node_t* node, int* attendanceArray);
BOOL IsAttended(node_t* node, int* attendanceArray);
void SearchConnectedGraph(node_t* node, int* attendanceArray);