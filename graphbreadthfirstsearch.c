#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

#define TRUE 1
#define FALSE 0

#define VISITED 1
#define NOT_VISITED 0


typedef struct node_t {
	int nodeNum;
    int visited;
    int numOfNeighbouringNodes;
	int* neighbouringNodes; //array with numbers of neighbouring vertexes
} node_t; //every single vertex of graph

typedef struct adj_list_t {
    int numOfNodes;
    node_t* nodes;
} adj_list_t;  //list of vertexes

typedef struct queue_t {
    int* data;
    int size;
    int start;
    int end;
} queue_t;

 int CreateQueue(queue_t* queue, int size) {
    if (queue == NULL || size <= 0)
        return FALSE;
    queue->size = size;
    queue->data = (int*)malloc(queue->size * sizeof(int));
    if (queue->data == NULL)
        return FALSE;
    queue->start = 0;
    queue->end = 0;
    return TRUE;
}

int Push(int value, queue_t* queue) {
    if (queue == NULL || queue->data == NULL || queue->end >= queue->size)
        return FALSE;
    queue->data[queue->end] = value;
    (queue->end)++;
    return TRUE;
}

int Pop(queue_t* queue, int* value) {
    if (queue == NULL || queue->data == NULL || queue->start >= queue->end || value == NULL)
        return FALSE;
    *value = queue->data[queue->start];
    (queue->start)++;
    return TRUE;
}

int DeleteQueue(queue_t* queue) {
    if (queue == NULL || queue->data == NULL)
        return FALSE;
    free(queue->data);
    queue = NULL;
    return TRUE;
}

int ReadAdjList(adj_list_t* adjList){
    int curNode, curNeigh, lineNum;
    char space;

    if (adjList == NULL)
        return FALSE;

    scanf("%i", &adjList->numOfNodes);
    adjList->nodes = (node_t*)malloc(adjList->numOfNodes * sizeof(node_t));
    if (adjList->nodes == NULL)
        return FALSE;
     
    for (curNode = 0; curNode < adjList->numOfNodes; curNode++) {
        adjList->nodes[curNode].visited = NOT_VISITED;
        adjList->nodes[curNode].numOfNeighbouringNodes = 0;
        adjList->nodes[curNode].neighbouringNodes = (int*)malloc(adjList->numOfNodes * sizeof(int));
        if (adjList->nodes[curNode].neighbouringNodes == NULL) {
            curNode--;
            for (curNode; curNode >= 0; curNode--)
                free(adjList->nodes[curNode].neighbouringNodes);
            free(adjList->nodes);
            adjList->nodes = NULL;
            return FALSE;
        }
    }

    for (lineNum = 0; lineNum < adjList->numOfNodes; lineNum++) {
        scanf("%i%c", &curNode, &space);
        adjList->nodes[curNode].nodeNum = curNode;
        while (space == ' ') {  //filling in arrays of neighbors
            scanf("%i", &curNeigh);
            scanf("%c", &space);
            adjList->nodes[curNode].neighbouringNodes[adjList->nodes[curNode].numOfNeighbouringNodes] = curNeigh;
            adjList->nodes[curNode].numOfNeighbouringNodes++;
            adjList->nodes[curNeigh].neighbouringNodes[adjList->nodes[curNeigh].numOfNeighbouringNodes] = curNode;
            adjList->nodes[curNeigh].numOfNeighbouringNodes++;
        }    
    }

    return TRUE;
}

int FreeAdjList(adj_list_t* adjList) {
    int curNode;

    if (adjList == NULL || adjList->nodes == NULL)
        return FALSE;

    for (curNode = 0; curNode < adjList->numOfNodes; curNode++)
        if(adjList->nodes[curNode].neighbouringNodes != NULL)
            free(adjList->nodes[curNode].neighbouringNodes);
    free(adjList->nodes);
    adjList->nodes = NULL;

    return TRUE;
}

int GraphBreadthFirstSearch(adj_list_t* adjList) {
    queue_t queue;
    int numOfVertex, numOfNeigh;

    if(adjList == NULL || adjList->nodes == NULL || !CreateQueue(&queue, adjList->numOfNodes))
        return FALSE;

    Push(adjList->nodes[0].nodeNum, &queue);
    adjList->nodes[0].visited = VISITED;

    while (queue.end != queue.start) {
        Pop(&queue, &numOfVertex);
        printf("%i ", numOfVertex);
        for (numOfNeigh = 0; numOfNeigh < adjList->nodes[numOfVertex].numOfNeighbouringNodes; numOfNeigh++) {
            if (adjList->nodes[adjList->nodes[numOfVertex].neighbouringNodes[numOfNeigh]].visited == NOT_VISITED) {
                Push(adjList->nodes[numOfVertex].neighbouringNodes[numOfNeigh], &queue);
                adjList->nodes[adjList->nodes[numOfVertex].neighbouringNodes[numOfNeigh]].visited = VISITED;
            }
        }
    }

    DeleteQueue(&queue);

    return TRUE;
}

int main() {
    adj_list_t adjList;

    ReadAdjList(&adjList);
    GraphBreadthFirstSearch(&adjList);
    FreeAdjList(&adjList);

    return 0;
}