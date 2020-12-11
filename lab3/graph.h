#pragma once


#define VISITED 1
#define NOT_VISITED -1

typedef struct node {
	int data;
	struct node* next;
} node_t;

typedef struct graph {
	int numOfKnot;
	node_t** adjList;
} graph_t;

char* ReadString(int n, int* l);

int InitNode(node_t** head);

node_t* Add(node_t* head, int knotTo);

void BFS(graph_t* graph);

graph_t* StrToGraph(char* str, int n, int len);

void freeGraph(graph_t* graph);

