#include "pch.h"
#include <stdio.h>
extern "C" {
#include "..\LAB_C\graph.c"
}

FILE* fp = NULL;

FILE* TestGraphCreate(void) {
    fp = fopen("TestGraph.txt", "w");
    fprintf(fp, "5\n0 4\n1 3\n1 4");
    fclose(fp);
    fp = fopen("TestGraph.txt", "r");
    return fp;
}

TEST(NullTest, ReadGraph_Test) {
    int check;
    graph_t g;
    check = ReadGraph(NULL, stdin);
    EXPECT_EQ(check, -1);
    check = ReadGraph(&g, NULL);
    EXPECT_EQ(check, -1);
}
TEST(BigTest, ReadGraph_Test) {
    graph_t g;
    ReadGraph(&g, TestGraphCreate());
    fclose(fp);
    EXPECT_EQ(g.size, 5);
    EXPECT_EQ(g.head->data, 0);
    EXPECT_EQ(g.head->next->data, 1);
    EXPECT_EQ(g.head->next->next->data, 2);
    EXPECT_EQ(g.head->next->next->next->data, 3);
    EXPECT_EQ(g.head->next->next->next->next->data, 4);

    EXPECT_EQ(g.head->links->ptr->data, 4);
    EXPECT_EQ(g.head->next->links->ptr->data, 3);
    EXPECT_EQ(g.head->next->links->next->ptr->data, 4);
    DestroyGraph(&g);
}
TEST(NullTest, BFS_Test) {
    int check;
    graph_t g;
    check = BFS(NULL, stdin);
    EXPECT_EQ(check, -1);
    check = BFS(&g, NULL);
    EXPECT_EQ(check, -1);
}
TEST(BigTest, BFS_Test) {
    graph_t g;
    FILE* f = fopen("TestAnswer.txt", "w");
    int a, b, c, d;
    ReadGraph(&g, TestGraphCreate());
    fclose(fp);
    BFS(&g, f);
    fclose(f);

    fopen("TestAnswer.txt", "r");
    fscanf(f, "%d %d %d %d", &a, &b, &c, &d);
    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, 4);
    EXPECT_EQ(c, 1);
    EXPECT_EQ(d, 3);
    fclose(f);
    DestroyGraph(&g);
}