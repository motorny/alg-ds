#include "pch.h"

extern "C" {
#include "../Graph BFS/queue.h"
#include "../Graph BFS/queue.c"
#include "../Graph BFS/BreadthFirstSearch.c"
}

TEST(CreateQueue, Create_queue_by_null_ptr_returnFAILED) {
    EXPECT_EQ(CreateQueue((queue_t*)NULL, 10), FAILED);
}

TEST(CreateQueue, Create_queue_negative_size_returnFAILED) {
    queue_t queue;
    EXPECT_EQ(CreateQueue(&queue, -10), FAILED);
}

TEST(CreateQueue, Create_queue_valid_input_returnFINISHED) {
    queue_t queue;
    EXPECT_EQ(CreateQueue(&queue, 5), FINISHED);
    EXPECT_EQ(queue.size, 5);
    EXPECT_NE(queue.arr, (int*)NULL);
    
    DestroyQueue(&queue);
}

TEST(Push, Push_in_empty_queue_returnFAILED) {
    queue_t queue;
    CreateQueue(&queue, 5);
    queue.tail = 5;

    EXPECT_EQ(Push(&queue, 10), FAILED);

    DestroyQueue(&queue);
}

TEST(Push, Push_in_queue_returnFINISHED) {
    queue_t queue;
    CreateQueue(&queue, 5);

    EXPECT_EQ(Push(&queue, 7), FINISHED);
    EXPECT_EQ(queue.arr[0], 7);
    EXPECT_EQ(queue.tail, 1);
    
    DestroyQueue(&queue);
}

TEST(Pop, Pop_elem_from_empty_queue_returnFAILED) {
    queue_t queue;
    CreateQueue(&queue, 5);
    int num = 0;
    
    EXPECT_EQ(Pop(&queue, &num), FAILED);

    DestroyQueue(&queue);
}

TEST(Pop, Pop_elem_from_queue_returnFINISHED) {
    queue_t queue;
    CreateQueue(&queue, 5);
    int num = 9;
    Push(&queue, num);

    EXPECT_EQ(Pop(&queue, &num), FINISHED);
    EXPECT_EQ(num, 9);
    EXPECT_EQ(queue.head, 1);

    DestroyQueue(&queue);
}

TEST(BFS, Breadth_First_Search_returnFINISHED) {
    adjacencyList_t list;
    list.vertexQuantity = 3;
    list.vertexes = (vertex_t*)malloc(list.vertexQuantity * sizeof(vertex_t));
    for (int i = 0; i < list.vertexQuantity; i++) {
        list.vertexes[i].flag = NOT_VISITED;
        list.vertexes[i].number = i;
        list.vertexes[i].neighbors = (int*)malloc(list.vertexQuantity * sizeof(int));
    }
    list.vertexes[0].neighborsQuantity = 2;
    list.vertexes[0].neighbors[0] = 1;
    list.vertexes[0].neighbors[1] = 2;

    list.vertexes[1].neighborsQuantity = 1;
    list.vertexes[1].neighbors[0] = 0;

    list.vertexes[2].neighborsQuantity = 1;
    list.vertexes[2].neighbors[0] = 0;

    EXPECT_EQ(BFS(&list), FINISHED);

    FreeAdjacencyList(&list);
}

TEST(FreeAdjacencyList, Free_valid_list_ptr_returnFINISHED) {
    adjacencyList_t list;
    list.vertexQuantity = 3;
    list.vertexes = (vertex_t*)malloc(list.vertexQuantity * sizeof(vertex_t));
    for (int i = 0; i < list.vertexQuantity; i++) {
        list.vertexes[i].flag = NOT_VISITED;
        list.vertexes[i].number = i;
        list.vertexes[i].neighbors = (int*)malloc(list.vertexQuantity * sizeof(int));
    }
    list.vertexes[0].neighborsQuantity = 2;
    list.vertexes[0].neighbors[0] = 1;
    list.vertexes[0].neighbors[1] = 2;

    list.vertexes[1].neighborsQuantity = 1;
    list.vertexes[1].neighbors[0] = 0;

    list.vertexes[2].neighborsQuantity = 1;
    list.vertexes[2].neighbors[0] = 0;

    EXPECT_EQ(FreeAdjacencyList(&list), FINISHED);
    EXPECT_EQ(list.vertexQuantity, 0);
}