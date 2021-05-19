#include pch.h
#include stdio.h
#include malloc.h
const int firstCapacity = 10;
#define ERROR -1
typedef struct arLine {

    int data;
    int count;
    int startFree;
    int capacity;
}arLine_t;

arLine_t arLineBuild() {
    arLine_t start = (arLine_t)malloc(sizeof(arLine_t));
    start->count = 0;
    start->capacity = firstCapacity;
    start->data = (int)malloc(start->capacity  sizeof(int));

    start->startFree = 0;
    if(start->data)
    return start;
    else return ERROR;
}

void push(int number, arLine_t line) {
    line->data[line->count] = number;
    line->count++;
    if (line->startFree) {
        for (int i = line->startFree; i != line->count + line->startFree; ++i) {
              line->data[i -> line->startFree] = line->data[i];
        }
    }
if (!(line->capacity -> line->count)) {
    int newData = (int)malloc(sizeof(int)  (line->capacity + firstCapacity));
    for (int i = 0; i != line->capacity; ++i) {
        newData[i] = line->data[i];
    }
    line->capacity += firstCapacity;
    free(line->data);
    line->data = newData;
}
}

int pop(arLine_t line) {
    line->count--;
    return line->data[line->startFree++];
}

void arLineDestroy(arLine_t line) {
    free(line->data);
    free(line);
}

typedef struct Node {
    struct Node first;
    struct Node last;
    int data;
}Node_t;

Node_t nodeBuild() {
    Node_t left = (Node_t)malloc(sizeof(Node_t));
    if (!left)
        return ERROR;


    Node_t right = (Node_t)malloc(sizeof(Node_t));
    if (!right)
        return ERROR;

    left->first = NULL;
    right->last = NULL;
    left->last = right;
    right->first = left;
    right->data = 0;
    left->data = 0;

    return left;
}

void push(int item, struct Node theFirst) {
    Node_t next = (Node_t)malloc(sizeof(Node_t));
    if (!next) return ERROR;

    next->data = item;
    next->first = theFirst;
    theFirst->last->first = next;
    next->last = theFirst->last;
    theFirst->last = next;
}

int pop(Node_t index) {
    int popped = index->data;
    index->last->first = index->first;
    index->first->last = index->last;
    free(index);
    return popped;
}


void nodeDestroy(Node_t theLast) {
    while (theLast->first->first) {
        pop(theLast->first);
    }
    free(theLast->first);
    free(theLast);
}

TEST(Array, buildingArrayLine) {
    arLine_t t = arLineBuild();
    EXPECT_TRUE(t->count == 0);
    EXPECT_TRUE(t->capacity == 10);
    EXPECT_TRUE(t->startFree == 0);
    free(t->data);
    free(t);
}

TEST(Array, pushOneArrayLine) {
    arLine_t t = arLineBuild();
    push(1,t);
    EXPECT_EQ(t->data[0], 1);
    EXPECT_EQ(t->count, 1);
    free(t->data);
    free(t);
}

TEST(Array, pushManyArrayLine) {
    arLine_t t = arLineBuild();
    push(1, t);
    push(1, t);
    push(1, t);
    push(1, t);
    push(1, t);
    push(1, t);
    push(1, t);
    push(1, t);
    push(1, t);
    push(1, t);
    push(1, t);
    push(1, t);
    EXPECT_EQ(t->data[0], 1);
    EXPECT_EQ(t->count, 12);
    EXPECT_EQ(t->capacity, 20);
    arLineDestroy(t);
}


TEST(Array, poppingFromArrayLine) {
    arLine_t t = arLineBuild();
    t->data[t->count] = 1;
    t->count++;
    EXPECT_EQ(pop(t), 1);
    free(t->data);
    free(t);
}


TEST(List, buildingListLine) {
    Node_t t = nodeBuild();
    EXPECT_TRUE(t->first == NULL);
    EXPECT_TRUE(t->data == 0);
    free(t->first);
    free(t);
}


TEST(List, pushingIntoListLine) {
    Node_t t = nodeBuild();
    push(1, t);
    EXPECT_TRUE(t->last->data == 1);
    EXPECT_TRUE(t->last->last->last == NULL);
    free(t->first);
    free(t);
}

TEST(List, poppingoutOfListLine) {
    Node_t t = nodeBuild();
    push(1, t);
    pop(t->last);
    EXPECT_TRUE(t->last->last == NULL);
    free(t->first);
    free(t->last);
    free(t);
}





int main(int argc,char argv) {
    testingInitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}