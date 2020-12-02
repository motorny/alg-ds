#include "graph.h"
#include "malloc.h"
#include "stdlib.h"

int main() {
    G_t *g = (G_t *) malloc(sizeof(G_t));
    if(g==NULL)
        return 1;
    scanf("%u", &g->vMax);
    if (g->vMax == 0)
        return 1;

    g->adjHPtr = createAdj(g->vMax);
    if (g->adjHPtr == NULL)
        return 1;

    int i;
    for (i = 0; i < g->vMax; i++)
        g->adjHPtr[i].queue = readAdj(g);
    bfs(g);

    for (i = 0; i < g->vMax; i++)
        free(g->adjHPtr[i].queue);
    free(g->adjHPtr);
    free(g);
    return 0;
}
