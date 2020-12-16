#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma warning(disable:4996)

#define LAST -1
#define SIZE 30
typedef struct node {
	int data;
	int* next;
	bool Check;
}node;

typedef struct graph{
	int size;
	int* next;
}graph;

void InitGraph(graph* myGraph) {
	myGraph->size = 0;
	myGraph->next = NULL;
}

int PushGraph(graph* myGraph, int pushEl) {
	myGraph->size++;
	myGraph->next = (int*)realloc(myGraph->next, myGraph->size * sizeof(int));
	if (!myGraph->next) {
		return 1;
	}
	for (int i = myGraph->size - 1; i > 0; i--) {
		myGraph->next[i] = myGraph->next[i - 1];
	}
	myGraph->next[0] = pushEl;
	return 0;
}

int PopGraph(graph* myGraph) {
	int popEl = myGraph->next[myGraph->size - 1];
	myGraph->size--;
	if (myGraph->size != 0) {
		myGraph->next = (int*)realloc(myGraph->next, myGraph->size * sizeof(int));
		if (!myGraph->next) {
			return -1;
		}
	}
	else {
		free(myGraph->next);
		myGraph->next = NULL;
	}
	return popEl;
}


void EditNode(node* Nodes, int EditNode, int ResultNode) {
	int FindeNode = LAST;
	int temp = -1;
	Nodes[EditNode].next = (int*)realloc(Nodes[EditNode].next, (Nodes[EditNode].data + 1) * sizeof(int));
	if (!Nodes[EditNode].next) {
		return;
	}
	for (int i = 0; i < Nodes[EditNode].data; i++) {
		if (Nodes[EditNode].next[i] > ResultNode) {
			FindeNode = i;
			break;
		}
	}
	if (FindeNode != LAST) {
		temp = Nodes[EditNode].next[FindeNode];
		Nodes[EditNode].next[FindeNode] = ResultNode;
		Nodes[EditNode].next[Nodes[EditNode].data] = temp;
	}
	else {
		Nodes[EditNode].next[Nodes[EditNode].data] = ResultNode;
	}
	Nodes[EditNode].data++;
}

void GetNodes(node* Nodes) {
	int First = -1, Second = -1, pointer = 0;
	char string[5] = "", sym = '0';
	while (sym != EOF) {
		pointer = 0;
		do {
			sym = fgetc(stdin);
			string[pointer] = sym;
			pointer++;
		} while (sym != EOF && sym != '\r' && sym != '\n' && sym != ' ');
		if (sym == '\r')
			fgetc(stdin);

		First = atoi(string);
		if (sym == ' ') {
			pointer = 0;
			do {
				sym = fgetc(stdin);
				string[pointer] = sym;
				pointer++;
			} while (sym != EOF && sym != '\r' && sym != '\n');
			if (sym == '\r')
				fgetc(stdin);

			Second = atoi(string);
			EditNode(Nodes, First, Second);
			EditNode(Nodes, Second, First);
		}
	}
}

void BFS(node* Nodes, graph* myGraph) {
	int NodesNum = -1;
	PushGraph(myGraph, 0);
	Nodes[0].Check = true;
	while (myGraph->size > 0) {
		NodesNum = PopGraph(myGraph);
		printf("%d ", NodesNum);
		for (int i = 0; i < Nodes[NodesNum].data; i++) {
			if (!Nodes[Nodes[NodesNum].next[i]].Check) {
				PushGraph(myGraph, Nodes[NodesNum].next[i]);
				Nodes[Nodes[NodesNum].next[i]].Check = true;
			}
		}
	}
}


int main(void) {
	int size = 0;
	char sym = '0';
	int pointer = 0;
	node* Nodes = NULL;
	graph myGraph;

	char string[SIZE] = "";
	while (sym != EOF && sym != '\r' && sym != '\n') {
		sym = fgetc(stdin);
		string[pointer] = sym;
		pointer++;
	}
	if (sym == '\r')
		fgetc(stdin);
	size = atoi(string);

	Nodes = (node*)malloc(sizeof(node) * size);
	if (!Nodes)
		return 0;
	for (int i = 0; i < size; i++) {
		Nodes[i].next = NULL;
		Nodes[i].data = 0;
		Nodes[i].Check = false;
	}

	GetNodes(Nodes);
	InitGraph(&myGraph);
	BFS(Nodes, &myGraph);

	for (int i = 0; i < size; i++) {
		free(Nodes[i].next);
	}
	free(Nodes);

	return 0;
}