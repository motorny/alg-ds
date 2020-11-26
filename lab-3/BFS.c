#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"
#pragma warning (disable:4996)


typedef struct {
    int vertex, visited;
    int *neighbor;
    int countOfNeigh;
}node_t;

int BFS(node_t* nodes, int n) {
    queue_t q;
    int j, curVertex;
    if (!InitQ(&q, n) || nodes == NULL || n <= 0)
        return FALSE;

    nodes[0].visited = TRUE;
    push(&q, nodes[0].vertex);
    while (q.head < q.last) {
        pop(&q, &curVertex);
        j = 0;
        while (j < nodes[curVertex].countOfNeigh) {
            if (nodes[nodes[curVertex].neighbor[j]].visited == FALSE) {
                push(&q, nodes[curVertex].neighbor[j]);
                nodes[nodes[curVertex].neighbor[j]].visited = TRUE;
            }
            j++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%i ", q.arr[i]);
    }
    RemoveQ(&q);
    return TRUE;
}


int main(void) {
    int countOfVertex = 0;
    node_t* nodes;
    scanf("%i", &countOfVertex);

    nodes = (node_t*)malloc(countOfVertex * sizeof(node_t));
    if (nodes == NULL)
        return ERROR;

    for (int i = 0; i < countOfVertex; i++)
    {
        nodes[i].neighbor = (int*)malloc(countOfVertex * sizeof(int));
        if (nodes[i].neighbor == NULL) {
            for (int j = 0; j < i; j++)
            {
                free(nodes[j].neighbor);
            }
            free(nodes);
            return ERROR;
        }
        nodes[i].visited = FALSE;
        nodes[i].countOfNeigh = 0;
    }

    for (int i = 0; i < countOfVertex; i++)
    {
        char buffer;
        int vert, neigh;
        scanf("%i%c", &vert, &buffer);
        nodes[i].vertex = vert;

        while (buffer == ' ') {
            scanf("%i", &neigh);
            nodes[i].neighbor[ nodes[i].countOfNeigh++ ] = neigh;
            nodes[neigh].neighbor[ nodes[neigh].countOfNeigh++ ] = vert;
            scanf("%c", &buffer);
        }
    }

    BFS(nodes, countOfVertex);

    for (int i = 0; i < countOfVertex; i++)
    {
        free(nodes[i].neighbor);
    }
    free(nodes);

	return 0;
}
