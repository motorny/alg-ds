#include <stdio.h>
#pragma warning(disable:4996)
#include <stdlib.h>

//ADJACENCY LIST
typedef struct node_t node_t;

typedef struct links_t {
	node_t* ptr;
	struct links_t* next;
}links_t;

typedef struct node_t {
	int data;
	struct links_t* links;
	int isVisited;
	struct node_t* next;
} node_t;

typedef struct {
	node_t* head;
	int size;
} graph_t;


//GENERAL FUNCTIONS
int ReadGraph(graph_t* graph, FILE* fp) {
	if (graph == NULL || fp == NULL)
		return -1;
	int size, from, to;
	int i, check;
	node_t* p = NULL, *t = NULL;
	links_t* l = NULL;

	fscanf(fp, "%d\n", &size);
	if (size < 0)
		return -1;

	//empty adgList
	p = (node_t*)malloc(sizeof(node_t));
	if (p == NULL)
		return -1;
	graph->head = p;
	graph->size = size;
	for (i = 0; i < size; i++) {
		p->data = i;
		p->isVisited = 0;
		p->links = NULL;

		if (i < size - 1) {
			p->next = (node_t*)malloc(sizeof(node_t));
			if (p->next == NULL)
				return -1;
			p = p->next;
		}
		else
			p->next = NULL;
	}

	//links filling 
	check = fscanf(fp, "%d %d\n", &from, &to);
	while (check != -1) {
		t = p = graph->head;

		//finding nodes
		while (p->data != from) {
			p = p->next;
		}
		while (t->data != to) {
			t = t->next;
		}

		//making an undirected graph

		//one hand
		if (p->links == NULL) {
			p->links = (links_t*)malloc(sizeof(links_t));
			if (p->links == NULL)
				return - 1;
			p->links->next = NULL;
			p->links->ptr = t;
		}
		else {
			l = p->links;
			while (l->next != NULL) {
				l = l->next;
			}
			l->next = (links_t*)malloc(sizeof(links_t));
			if (l == NULL)
				return -1;
			l->next->ptr = t;
			l->next->next = NULL;
		}

		//another hand
		if (t->links == NULL) {
			t->links = (links_t*)malloc(sizeof(links_t));
			if (t->links == NULL)
				return -1;
			t->links->next = NULL;
			t->links->ptr = p;
		}
		else {
			l = t->links;
			while (l->next != NULL) {
				l = l->next;
			}
			l->next = (links_t*)malloc(sizeof(links_t));
			if (l == NULL)
				return -1;
			l->next->ptr = p;
			l->next->next = NULL;
		}
		check = fscanf(fp, "%d %d\n", &from, &to);
	}
	return 0;
}
int BFS(graph_t* graph, FILE* fp) {
	if (graph == NULL || fp == NULL)
		return -1;
	node_t* p = graph->head;
	links_t* l;
	int* queue = (int*)malloc((graph->size) * sizeof(int)), *temp;
	if (queue == NULL)
		return -1;
	int qStart = 0, qEnd = 0, qSize = graph->size * sizeof(int);

	//processing the start node
	fprintf(fp, "%d", p->data);
	l = p->links;
	p->isVisited = 1;
	while (l != NULL) {
		queue[qEnd] = l->ptr->data;
		qEnd++;
		l = l->next;
	}
	
	//while queue is not empty
	while (qStart != qEnd) {
		p = graph->head;

		//push from queue
		while (p != NULL && p->data != queue[qStart]) {
			p = p->next;
		}
		if (p != NULL && p->isVisited == 0) {
			fprintf(fp, " %d", p->data);
			p->isVisited = 1;

			//put links into queue
			l = p->links;
			while (l != NULL) {
				if (l->ptr->isVisited == 0) {
					//I think it's impossible to predict the size of the queue, so realloc
					if(qEnd == qSize/sizeof(int) - 1) {
						qSize = 2 * qSize;
						temp = (int*)realloc(queue, qSize);
						if (temp != NULL)
							queue = temp;
						else
							return -1;
					}
					queue[qEnd] = l->ptr->data;
					qEnd++;
				}
				l = l->next;
			}
		}
		else {
			qStart++;
			continue;
		}

	}
	free(queue);
	return 0;
}

void DestroyGraph(graph_t* graph) {
	node_t* p = graph->head, *pTemp;
	links_t* l, *lTemp;
	while (p != NULL) {
		l = p->links;
		while (l != NULL) {
			lTemp = l->next;
			free(l);
			l = lTemp;
		}
		pTemp = p->next;
		free(p);
		p = pTemp;
	}
}

//INTERFACE PART
int main(void) {
	graph_t graph;
	int check = 0;
	check = ReadGraph(&graph, stdin);
	if (check != 0)
		return -1;
	BFS(&graph, stdout);
	DestroyGraph(&graph);
	return 0;
}