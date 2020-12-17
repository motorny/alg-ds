#include <stdio.h>

typedef enum {
    WHITE,
    GRAY,
    BLACK,
} color_t;

typedef struct point_t {
    struct node_t* node;
    struct point_t* next;
} point_t;

typedef struct node_t {
    int pointS;
    color_t color;
    point_t* point;
} node_t;

node_t* CreateGraph(int n, int* err);

void AddPoint(node_t* node1, node_t* node2, int* err);

void DestroyGraph(node_t* nodes, int n);

void PrintPoints(node_t* nodes, int n);

void RunDFS(int* ans, node_t* nodes, int n);

void PrintDFS(int* ans, int n);
