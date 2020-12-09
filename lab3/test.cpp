#include "pch.h"
extern "C"{
#include "dfs.h"
}

TEST(CreateList, EmptyList) {
    int num = 0;
    node_t* list = (node_t*)malloc(num * sizeof(node_t));
    ASSERT_EQ(CreateList(list, num), -1);
}

TEST(CreateList, NotEmptyList) {
    int num = 5;
    node_t* list = (node_t*)malloc(num * sizeof(node_t));
    ASSERT_EQ(CreateList(list, num), 1);
    DestroyList(list, num);
}

TEST(DFS, EmptyListDontCrush) {
    int num = 0;
    node_t* list = (node_t*)malloc(num * sizeof(node_t));
    CreateList(list, num);
    DFS(list, 0, num);
}

TEST(DFS, CorrectDataOneVertex) {
    int num = 1;
    node_t* list = (node_t*)malloc(num * sizeof(node_t));
    CreateList(list, num);
    list[0].vertexes[0] = 0;
    DFS(list, 0, num);
    printf("\n");
    DestroyList(list, num);
}

TEST(DFS, CorrectDataExample) {
    int num = 5, curr, next, i;
    char sym;
    char graph[] = "0 2\n"
        "1\n"
        "2 4\n"
        "3 4\n"
        "4\n";
    int size = strlen(graph);
    node_t* list = (node_t*)malloc(num * sizeof(node_t));
    CreateList(list, num);
    for (i = 0; i < size; i = i + 2) {
        curr = graph[i] - 48;
        sym = graph[i + 1];
        while (sym == ' ') {
            i = i + 2;
            next = graph[i] - 48;
            sym = graph[i + 1];
            list[curr].vertexes[list[curr].index++] = next;
            list[next].vertexes[list[next].index++] = curr;
        }
    }
    DFS(list, 0, num);
    printf("\n");
    DestroyList(list, num);
}