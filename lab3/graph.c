#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"graph.h"
#include"queue.h"
#include <ctype.h>







char* ReadString(int n, int* l) {
	char* str = NULL, * ptr = NULL;
	int j = -1;
	int i = 0;
	str = (char*)malloc(2 * sizeof(char));
	if (!str)
		return NULL;

	while (((str[i] = fgetc(stdin)) != EOF)) {

		if (str[i] == '\n')
			j++;
		if (str[0] == '\n')
			i--;
		i++;
		ptr = realloc(str, (i + 1) * sizeof(char));
		if (ptr)
			str = ptr;
		else
			return NULL;
	}
	str[i] = 0;
	*l = j;
	return str;
}

int InitNode(node_t** head) {
	*head = (node_t*)malloc(sizeof(node_t));
	if (*head == NULL)
		return -1;
	return 1;
}

node_t* Add(node_t* head, int knotTo) {
	node_t* cur = head;
	if (!head) {
		if (InitNode(&head) == -1)
			return NULL;
		head->data = knotTo;
		head->next = NULL;
	}
	else {
		while (cur->next)
			cur = cur->next;
		cur->next = (node_t*)malloc(sizeof(node_t));
		if (!cur->next)
			return NULL;
		cur->next->data = knotTo;
		cur->next->next = NULL;
	}
	return head;
}

graph_t* StrToGraph(char* str, int n, int len) {
	graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
	if (n <= 0) {
		graph->numOfKnot = -1;
		return graph;
	}
	char* newStr, * tmpStr;
	int numOfKnot = n;
	int knotFrom, knotTo;

	int i = 0;
	int k = 0;
	graph->numOfKnot = numOfKnot;
	if (numOfKnot == 1)
		return graph;
	graph->adjList = malloc(numOfKnot * sizeof(node_t));
	for (int i = 0; i < numOfKnot; i++)
		graph->adjList[i] = NULL;
	len = len * 2;
	while (i < len) {

		i++;
		newStr = str;
		while (isspace(*newStr)) {

			newStr++;
		}
		knotFrom = (int)strtod(newStr + k, &tmpStr);
		k = strlen(newStr) - strlen(tmpStr);
		while (isspace(*newStr)) {
			newStr++;

		}
		knotTo = (int)strtod(newStr + k, &tmpStr);
		k = strlen(newStr) - strlen(tmpStr);
		graph->adjList[knotTo] = Add(graph->adjList[knotTo], knotFrom);
		graph->adjList[knotFrom] = Add(graph->adjList[knotFrom], knotTo);

		if (graph->adjList[knotTo] == NULL || graph->adjList[knotFrom] == NULL) {
			graph->numOfKnot = -1;
			return graph;
		}
		while (isspace(*newStr)) {

			newStr++;
		}
	}
	return graph;
}

void BFS(graph_t* graph) {
	int* wasVisited = (int*)malloc(graph->numOfKnot * sizeof(int));
	int i, curKnot, nextKnot;
	queue_t* queue = QueueCreate();

	if (graph->numOfKnot <= 0) {
		return;
	}
	if (graph->numOfKnot == 1) {
		printf("0 ");
		return;
	}
	for (i = 0; i < graph->numOfKnot; i++)
		wasVisited[i] = NOT_VISITED;
	if (Push(queue, 0) == -1)
		return;
	wasVisited[0] = VISITED;
	while (queue->head) {
		curKnot = Pop(queue);
		if (curKnot < 0)
			return;
		printf("%i ", curKnot);
		node_t* tmp = graph->adjList[curKnot];
		while (tmp) {
			nextKnot = tmp->data;
			if (wasVisited[nextKnot] == NOT_VISITED) {
				wasVisited[nextKnot] = VISITED;
				if (Push(queue, nextKnot) == -1)
					return;
			}
			tmp = tmp->next;
		}
		if (!queue->head) {
			for (i = 0; i < graph->numOfKnot; i++)
				if (graph->adjList[i] != NULL && wasVisited[i] != VISITED) {
					if (Push(queue, i) == -1)
						return;
					wasVisited[i] = VISITED;
					break;
				}
		}
	}
	free(wasVisited);
	QueueDelete(queue);
}


void freeGraph(graph_t* graph) {
	if (graph->numOfKnot > 1) {
		for (int i = 0; i < graph->numOfKnot; i++) {
			if (graph->adjList[i])
				if (graph->adjList[i]->next) {
					while (graph->adjList[i]) {
						node_t* tmp = graph->adjList[i];
						graph->adjList[i] = graph->adjList[i]->next;
						free(tmp);
					}
				}
			free(graph->adjList[i]);
		}
		free(graph->adjList);
	}
	free(graph);
}
