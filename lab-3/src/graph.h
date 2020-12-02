//
// Created by ikuzin on 01.12.2020.
//

#ifndef LAB_3_GRAPH_H
#define LAB_3_GRAPH_H


typedef struct V {
    enum color {
        WHITE = 1,
        GRAY = 2,
        BLACK = 3
    } color;
    int qSize;
    unsigned int i;
    struct Q *queue;
} V_t;


struct Q {
    V_t *i;
    struct Q *next;
};

typedef struct Graph {
    V_t *adjHPtr;
    unsigned int vMax;
} G_t;


V_t *createAdj(int n);
struct Q *readAdj(G_t *g);
struct Q *enqueue(struct Q *q, V_t *x);
struct Q *dequeue(struct Q **q);
int bfs(G_t *g);
#endif //LAB_3_GRAPH_H

