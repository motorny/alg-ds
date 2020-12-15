#include "pch.h"
extern "C" {
    #include "labC.h"
}

TEST(CreateQueueTest, CreateQueueTest_WrongSize_ReturnFailing) {
    queue_t q;
    int error;

    error = CreateQueue(&q, -1);
    
    EXPECT_EQ(error, FAILING);
  //EXPECT_TRUE(true);
}

TEST(CreateQueueTest, CreateQueueTest_RightSize_ReturnSuccess) {
    queue_t q;
    int error;

    error = CreateQueue(&q, 1);

    EXPECT_EQ(error, SUCCESS);
    //EXPECT_TRUE(true);
}

TEST(PutToQueueTest, PutToQueueTest_NotCreatedQueue_ReturnFailing) {
    queue_t q;
    int error;

    error = PutToQueue(&q, 1);

    EXPECT_EQ(error, FAILING);
}

TEST(PutToQueueTest, PutToQueueTest_CreatedQueue_ReturnSuccess) {
    queue_t q;
    int error;

    CreateQueue(&q, 1);
    error = PutToQueue(&q, 1);

    EXPECT_EQ(error, SUCCESS);
}

TEST(GetFromQueueTest, GetFromQueueTest_EmptyQueue_ReturnFaling) {
    queue_t q;
    int error, element;

    CreateQueue(&q, 1);
    error = GetFromQueue(&q, &element);

    EXPECT_EQ(error, FAILING);
}

TEST(GetFromQueueTest, GetFromQueueTest_FilledQueue_ReturnSuccess) {
    queue_t q;
    int error, element;

    CreateQueue(&q, 1);
    PutToQueue(&q, 1);
    error = GetFromQueue(&q, &element);

    EXPECT_EQ(error, SUCCESS);
    EXPECT_EQ(element, 1);
}

TEST(IsNotSortedTest, IsNotSortedTest_NotSortedArray_ReturnFaling) {
    int error, array[2] = {2, 1};

    error = IsNotSorted(array, 2);

    EXPECT_EQ(error, FAILING);
}

TEST(IsNotSortedTest, IsNotSortedTest_SortedArray_ReturnSuccess) {
    int error, array[2] = { 1, 1 };

    error = IsNotSorted(array, 2);

    EXPECT_EQ(error, SUCCESS);
}

TEST(QuickSortTest, QuickSortTest_Array_ReturnSuccess) {
    int array[3] = { 3, 1, 2 };
    int error;

    QuickSort(array, 3);
    error = IsNotSorted(array, 3);

    EXPECT_EQ(error, SUCCESS);
}

TEST(BFSTest, BFSTest_NoneVertix_ReturnFailing) {
    tree_t graph;
    queue_t q;
    int error;

    CreateQueue(&q, 1);
    error = BFS(&graph, 0, &q);

    EXPECT_EQ(error, FAILING);
}

TEST(BFSTest, BFSTest_TwoVertix_ReturnSuccess) {
    tree_t graph;
    queue_t q;
    int error;

    graph.nodes = (node_t*)malloc( 2 * sizeof(node_t));
    graph.nodes[0].edges = (int *)malloc(2 * sizeof(int));
    graph.nodes[0].number = 0;
    graph.nodes[1].edges = (int*)malloc(2 * sizeof(int));
    graph.nodes[1].number = 0;
    graph.nodes[0].edges[graph.nodes[0].number++] = 1;
    graph.nodes[1].edges[graph.nodes[1].number++] = 0;


    CreateQueue(&q, 1);
    error = BFS(&graph, 2, &q);

    EXPECT_EQ(error, SUCCESS);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}