#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef enum
{
    FALSE,
    TRUE
} Bool;

#define SUCCESS 1
#define FAIL 0

typedef struct node {
    int data;
    struct node* next;
    Bool visited;
} adjList_t;

adjList_t* InitGraph(int size) {
    adjList_t* adjList = NULL;
    if (size < 0) {
        return NULL;
    }
    adjList = (adjList_t*)malloc((size) * sizeof(adjList_t));
    if (adjList == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        adjList[i].data = i;
        adjList[i].next = NULL;
        adjList[i].visited = FALSE;
    }
    return adjList;
}

int FillGraph(adjList_t* arr, int a, int b) {
    adjList_t* newB, * tmp;
    newB = (adjList_t*)malloc(sizeof(adjList_t));
    if (newB == NULL) {
        return FAIL;
    }
    tmp = &arr[a];
    if (tmp->next != NULL) {
        while (tmp) {
            if (tmp->next == NULL) {
                break;
            }
            if (tmp->next->data < b) {
                tmp = tmp->next;
            }
            else
                break;
        }
    }
    newB->next = tmp->next;
    tmp->next = newB;
    newB->data = b;

    newB = (adjList_t*)malloc(sizeof(adjList_t));
    if (newB == NULL) {
        return FAIL;
    }
    tmp = &arr[b];
    if (tmp->next != NULL) {
        while (tmp->next != NULL) {
            if (tmp->next->data < a) {
                tmp = tmp->next;
            }
            else
                break;
        }
    }
    newB->next = tmp->next;
    tmp->next = newB;
    newB->data = a;

    return SUCCESS;
}

void FreeGraph(adjList_t* arr, int size) {
    adjList_t* freeP;
    adjList_t* tmp = arr;
    for (int i = 0; i < size; i++) {
        tmp = arr[i].next;
        while (tmp) {
            freeP = tmp;
            tmp = tmp->next;
            free(freeP);
        }
    }
    free(arr);
}

int BFS(adjList_t* graph, int startVertex, int* visited, int* queue) {
    int countVertex = 0, countV = 0, endQ = 0;
    int cur;
    adjList_t* tmp;

    queue[endQ++] = graph[startVertex].data;

    while (endQ != 0) {
        cur = queue[0];
        visited[countV] = queue[0];
        graph[queue[0]].visited = TRUE;
        countV++;
        for (int i = 0; i < endQ - 1; i++) {
            queue[i] = queue[i + 1];
        }
        endQ--;
        tmp = graph[cur].next;
        while (tmp) {
            if (graph[tmp->data].visited == FALSE) {
                queue[endQ] = tmp->data;
                graph[tmp->data].visited = TRUE;
                endQ++;
            }
            tmp = tmp->next;
        }
    }
    return countV;
}