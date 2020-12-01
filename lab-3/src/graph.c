//
// Created by ikuzin on 01.12.2020.
//

#include <stdio.h>
#include "malloc.h"
#include "graph.h"


V_t *createAdj(unsigned int n) {
    V_t *adj = calloc(n, sizeof(V_t));
    if(adj == NULL)
        return NULL;
    int i;
    for (i = 0; i < n; i++) {
        adj[i].i = i;
        adj[i].queue = calloc(n, sizeof(struct Q));
        if(adj[i].queue == NULL)
            return NULL;
    }
    return adj;
}

struct Q *readAdj(G_t *g) {
    int curVert, tmpVert;
    char ch;
    scanf("%i%c", &curVert, &ch);
    struct Q *tmp = g->adjHPtr[curVert].queue;
    while (ch == ' ') {
        scanf("%u%c", &tmpVert, &ch);
        tmp[g->adjHPtr[curVert].qSize++].i = &g->adjHPtr[tmpVert];
        g->adjHPtr[tmpVert].queue[g->adjHPtr[tmpVert].qSize++].i = &g->adjHPtr[curVert];
    }
    if (g->adjHPtr[curVert].qSize == 0) {
        free(tmp);
        return NULL;
    }
    return tmp;
}

struct Q *enqueue(struct Q *q, V_t *x) {
    struct Q *newTail = (struct Q *) malloc(sizeof(struct Q));
    if(newTail == NULL)
        return NULL;
    newTail->i = x;
    newTail->next = q;
    return newTail;
}

struct Q *dequeue(struct Q **q) {
    struct Q *curr = *q, *prev = *q;
    if ((*q)->next == NULL) {
        (*q) = NULL;
        return curr;
    }
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = NULL;
    return curr;
}

void bfs(G_t *g) {
    if(g->adjHPtr == NULL)
        return;
    g->adjHPtr->color = GRAY;
    int i;
    for (i = 1; i < g->vMax; i++) {
        g->adjHPtr[i].color = WHITE;
    }
    struct Q *u, *tail = NULL;
    tail = enqueue(NULL, g->adjHPtr);
    while (tail != NULL) {
        u = dequeue(&tail);
        V_t *tmp = &g->adjHPtr[u->i->i];
        for (i = 0; i < tmp->qSize; i++) {
            if (tmp->queue[i].i->color == WHITE) {
                tmp->queue[i].i->color = GRAY;
                tail = enqueue(tail, g->adjHPtr[u->i->i].queue[i].i);
            }
        }
        printf("%u ", g->adjHPtr[u->i->i].i);
        g->adjHPtr[u->i->i].color = BLACK;
    }
}
