#include "labC.h"

node_t* CreateGraph(int n, int* err) {

    node_t* nodes = (node_t*)malloc(sizeof(node_t) * n);
    int i;

    if (*err != 0) {
        return NULL;
    }

    if (nodes != NULL) {
        for (i = 0; i < n; i++) {
            nodes[i].pointS = 0;
            nodes[i].color = WHITE;
            nodes[i].point = NULL;
        }
    }
    else
        (*err)++;

    return nodes;

}

void AddPoint(node_t* node1, node_t* node2, int* err) {

    point_t* point1 = (point_t*)malloc(sizeof(point_t));
    point_t* point2 = (point_t*)malloc(sizeof(point_t));
    point_t* pCur;

    if (*err != 0)
        return;

    if (point1 != NULL && point2 != NULL) {
        node1->pointS++;
        point1->node = node2;
        point1->next = NULL;
        pCur = node1->point;
        if (pCur == NULL) {
            node1->point = point1;
        }
        else {
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = point1;
        }

        node2->pointS++;
        point2->node = node1;
        point2->next = NULL;
        pCur = node2->point;
        if (pCur == NULL)
            node2->point = point2;
        else {
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = point2;
        }
    }
    else
        (*err)++;

}

void DestroyGraph(node_t* nodes, int n) {

    point_t* pCur, *pNext;
    int i;

    for (i = 0; i < n; i++) {
        pCur = nodes[i].point;
        while (pCur != NULL) {
            pNext = pCur->next;
            free(pCur);
            pCur = pNext;
        }
    }

    free(nodes);

}

void PrintPoints(node_t* nodes, int n) {

    point_t* pCur;
    int i;

    for (i = 0; i < n; i++) {
        pCur = nodes[i].point;
        while (pCur != NULL) {
            printf("%i %i\n", i, pCur->node - nodes);
            pCur = pCur->next;
        }
    }

}

static void DFS(int* i, int* ans, int nodeNum, node_t* nodes, int n) {

    point_t* pCur = nodes[nodeNum].point;

    ans[(*i)++] = nodeNum;
    nodes[nodeNum].color = GRAY;
    while (pCur != NULL) {
        if (pCur->node->color == WHITE) {
            DFS(i, ans, pCur->node - nodes, nodes, n);
        }
        pCur = pCur->next;
    }
    nodes[nodeNum].color = BLACK;

}

void RunDFS(int* ans, node_t* nodes, int n) {

    int i = 0, nodeNum = 0;

    DFS(&i, ans, nodeNum, nodes, n);

    for (nodeNum = 0; nodeNum < n; nodeNum++) {
        if (nodes[nodeNum].color == WHITE) {
            DFS(&i, ans, nodeNum, nodes, n);
        }
    }

}

void PrintDFS(int* ans, int n) {

    int i;

    printf("%i", ans[0]);
    for (i = 1; i < n; i++) {
        printf(" %i", ans[i]);
    }
    printf("\n");

}