#include "pch.h"
#include "..//LABC3_2/BFS.c"

TEST(init_queue, not_null_pointer_valid_size) {
    queue_t q;

    EXPECT_EQ(init_queue(&q, 1), true);
    EXPECT_EQ(q.size, 1);

    free(q.data);
}

TEST(init_queue, not_null_pointer_invalid_size_return_false) {
    queue_t q;

    EXPECT_NE(init_queue(&q, -1), true);
}

TEST(push_queue, not_null_pointer) {
    queue_t q;
    int a = 1;

    q.size = 1;
    q.data = (int*)malloc(q.size * sizeof(int));
    q.head = 0;
    q.tail = 0;

    EXPECT_EQ(push_queue(a, &q), true);
    EXPECT_EQ(q.data[0], a);

    free(q.data);
}

TEST(push_queue, push_no_init) {
    queue_t q;
    int a = 1;

    EXPECT_NE(push_queue(a, &q), true);
}
TEST(push_queue, push_to_full_queue) {
    queue_t q;
    int a = 1, b = 2;

    q.size = 1;
    q.data = (int*)malloc(q.size * sizeof(int));
    q.head = 0;
    q.tail = 1;
    q.data[0] = a;

    EXPECT_NE(push_queue(b, &q), true);

    free(q.data);
}

TEST(pop_queue, valid_arguments) {
    queue_t q;
    int a = 1, b;

    q.size = 1;
    q.data = (int*)malloc(q.size * sizeof(int));
    q.head = 0;
    q.tail = 1;
    q.data[0] = a;

    EXPECT_EQ(pop_queue(&q, &b), true);
    EXPECT_EQ(a, b);

    free(q.data);
}
TEST(pop_queue, pop_from_emptyqueue) {
    queue_t q;
    int a;

    q.size = 1;
    q.data = (int*)malloc(q.size * sizeof(int));
    q.head = 0;
    q.tail = 0;

    EXPECT_NE(pop_queue(&q, &a), true);

    free(q.data);
}

TEST(delete_queue, valid_argument) {
    queue_t q;

    q.size = 1;
    q.data = (int*)malloc(q.size * sizeof(int));
    q.head = 0;
    q.tail = 0;

    EXPECT_EQ(delete_queue(&q), true);
}

TEST(bfs, valid_argument) {
    adjacency_list_t  list;
    int counter;

    list.vertices_num = 3;
    list.vertices = (node_t*)malloc(3 * sizeof(node_t));
    for (counter = 0; counter < 3; counter++) {
        list.vertices[counter].was_visited = 0;
        list.vertices[counter].neighborhoods = (int*)malloc(3 * sizeof(int));
    }
    list.vertices[0].num_neighborhoods = 2;
    list.vertices[0].neighborhoods[0] = 1;
    list.vertices[0].neighborhoods[1] = 2;

    list.vertices[1].num_neighborhoods = 1;
    list.vertices[1].neighborhoods[0] = 0;

    list.vertices[2].num_neighborhoods = 1;
    list.vertices[2].neighborhoods[0] = 0;


    EXPECT_EQ(bfs(&list), true);

    for (counter = 0; counter < 3; counter++)
        free(list.vertices[counter].neighborhoods);
    free(list.vertices);
}

TEST(free_adjacency_list, valid_argument) {
    adjacency_list_t  list;
    int counter;

    list.vertices_num = 3;
    list.vertices = (node_t*)malloc(3 * sizeof(node_t));
    for (counter = 0; counter < 3; counter++) {
        list.vertices[counter].was_visited = 0;
        list.vertices[counter].neighborhoods = (int*)malloc(3 * sizeof(int));
    }
    list.vertices[0].num_neighborhoods = 2;
    list.vertices[0].neighborhoods[0] = 1;
    list.vertices[0].neighborhoods[1] = 2;

    list.vertices[1].num_neighborhoods = 1;
    list.vertices[1].neighborhoods[0] = 0;

    list.vertices[2].num_neighborhoods = 1;
    list.vertices[2].neighborhoods[0] = 0;


    EXPECT_EQ(free_adjacency_list(&list), true);
}