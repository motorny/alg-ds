#include "pch.h"
#include "../../LabC/LabC/labC.c"








TEST(TestCreateGraph, EpmtyNodes) {

    node_t* nodes;
    int err = 0;
    int i, n = 2;

    nodes = CreateGraph(n, &err);

    for (i = 0; i < n; i++) {
        ASSERT_EQ(0, nodes[i].pointS);
        ASSERT_EQ(WHITE, nodes[i].color);
        ASSERT_EQ(NULL, nodes[i].point);
    }

    DestroyGraph(nodes, n);

}

TEST(TestAddPoints, LinkedNodes) {

    node_t* nodes;
    int err = 0;
    int i, n = 2;

    nodes = (node_t*)malloc(sizeof(node_t) * n);
    for (i = 0; i < n; i++) {
        nodes[i].pointS = 0;
        nodes[i].color = WHITE;
        nodes[i].point = NULL;
    }

    AddPoint(&nodes[0], &nodes[1], &err);
    for (i = 0; i < n; i++) {
        ASSERT_EQ(1, nodes[i].pointS);
        ASSERT_EQ(WHITE, nodes[i].color);
        ASSERT_EQ(NULL, nodes[i].point->next);
    }
    ASSERT_EQ(&nodes[1], nodes[0].point->node);
    ASSERT_EQ(&nodes[0], nodes[1].point->node);

    DestroyGraph(nodes, n);

}

TEST(TestAddPoints, LinkedThreeNodes) {

    node_t* nodes;
    int err = 0;
    int i, n = 3;

    nodes = (node_t*)malloc(sizeof(node_t) * n);
    for (i = 0; i < n; i++) {
        nodes[i].pointS = 0;
        nodes[i].color = WHITE;
        nodes[i].point = NULL;
    }

    AddPoint(&nodes[0], &nodes[1], &err);
    AddPoint(&nodes[1], &nodes[2], &err);
    for (i = 0; i < n; i++)
        ASSERT_EQ(WHITE, nodes[i].color);

    ASSERT_EQ(1, nodes[0].pointS);
    ASSERT_EQ(&nodes[1], nodes[0].point->node);
    ASSERT_EQ(NULL, nodes[0].point->next);

    DestroyGraph(nodes, n);

}

TEST(TestRunDFS, Unlinked) {

    node_t* nodes;
    int* ans;
    int err = 0;
    int i, n = 4;

    ans = (int*)malloc(sizeof(int) * n);
    nodes = CreateGraph(n, &err);
    AddPoint(&nodes[0], &nodes[1], &err);
    AddPoint(&nodes[2], &nodes[3], &err);

    RunDFS(ans, nodes, n);

    for (i = 0; i < n; i++)
        ASSERT_EQ(i, ans[i]);

    DestroyGraph(nodes, n);

    free(ans);

}
