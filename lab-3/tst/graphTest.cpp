//
// Created by ikuzin on 01.12.2020.
//

#include <graph.h>

#include "gtest/gtest.h"

TEST(createAdj_1, NegativeN) {
    V_t *t = createAdj(-1);
    EXPECT_EQ(t == NULL, true);
}

TEST(createAdj_2, Ok) {
    V_t *t = createAdj(1);
    EXPECT_EQ(t == nullptr, false);
    EXPECT_EQ(t->i == 0, true);
    EXPECT_EQ(t->queue != nullptr, true);
}

TEST(enqueue_3, retOk) {
    struct Q *q = NULL, *ret;
    V_t *x = (V_t *) malloc(sizeof(V_t));
    x->color = V::WHITE;
    x->i = 45;
    x->qSize = 4;
    x->queue = NULL;
    ret = enqueue(q, x);
    EXPECT_EQ(ret != NULL, true);
    EXPECT_EQ(ret->i == x, true);
    std::cout<<ret->next;
    EXPECT_EQ(ret->next == NULL, true);
}

TEST(enqueue_4, retOk2) {
    struct Q *q, *ret;
    q = (struct Q*)malloc(sizeof(struct Q));
    q->i = (V_t *) malloc(sizeof(V_t));
    q->i->i = 45;
    q->i->qSize = 45;
    q->i->queue = NULL;
    q->i->color = V::BLACK;
    V_t *x = (V_t *) malloc(sizeof(V_t));
    x->color = V::WHITE;
    x->i = 45;
    x->qSize = 4;
    x->queue = NULL;
    ret = enqueue(q, x);
    EXPECT_EQ(ret != NULL, true);
    EXPECT_EQ(ret->i == x, true);
    EXPECT_EQ(ret->next->i->color == q->i->color, true);
    EXPECT_EQ(ret->next->i->i == q->i->i, true);
    EXPECT_EQ(ret->next->i->queue == q->i->queue, true);
}

TEST(dequeue_5, nullArg) {
    struct Q *q, *ret;
    q = NULL;
    ret = dequeue(&q);
    EXPECT_EQ(ret == NULL, true);
}

TEST(dequeue_6, retHead) {
    struct Q *q, *tail, *u;
    V_t *x = (V_t *) malloc(sizeof(V_t));
    x->color = V::WHITE;
    x->i = 45;
    x->qSize = 4;
    x->queue = NULL;
    tail = enqueue(NULL, x);
    u = dequeue(&tail);
    EXPECT_EQ(tail == NULL, true);
    EXPECT_EQ(u->i == x, true);
    EXPECT_EQ(u->i->color == x->color, true);
    EXPECT_EQ(u->i->queue == x->queue, true);
}

TEST(dequeue_7, retNode) {
    struct Q *q, *tail, *u;
    q = (struct Q*)malloc(sizeof(struct Q));
    q->i = (V_t *) malloc(sizeof(V_t));
    q->i->i = 45;
    V_t a,b,c,*x = (V_t *) malloc(sizeof(V_t));
    x->i = 1;
    a = *x;
    b = *x;
    tail = enqueue(q, x);
    a.i = 2;
    tail = enqueue(tail, &a);
    b.i = 3;
    tail = enqueue(tail, &b);
    u = dequeue(&tail);
    EXPECT_EQ(tail != NULL, true);
    EXPECT_EQ(u->i->i == 45, true);
    u = dequeue(&tail);
    EXPECT_EQ(tail != NULL, true);
    EXPECT_EQ(u->i->i == 1, true);
    u = dequeue(&tail);
    EXPECT_EQ(tail != NULL, true);
    EXPECT_EQ(u->i->i == 2, true);
    u = dequeue(&tail);
    EXPECT_EQ(tail == NULL, true);
    EXPECT_EQ(u->i->i == 3, true);
}

TEST(bfs_8, nullArg) {
   G_t *g = NULL;
   int i = bfs(g);
   EXPECT_EQ( i == 1, true);
}



