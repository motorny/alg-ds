//
// Created by ikuzin on 01.12.2020.
//

#include <graph.h>

#include "gtest/gtest.h"

TEST(createAdj_1, N_0) {
    V_t *t = createAdj(0);
    EXPECT_EQ(t == nullptr, true);
}

TEST(createAdj_2, N_1) {
    V_t *t = createAdj(1);
    EXPECT_EQ(t == nullptr, true);
    EXPECT_EQ(t->i == 0, true);
    EXPECT_EQ(t->queue != nullptr, true);
}

TEST(enqueue_3, retOk) {
    struct Q *q, *ret;
    V_t *x = (V_t *) malloc(sizeof(V_t));
    x->color = V::WHITE;
    x->i = 45;
    x->qSize = 4;
    x->queue = NULL;
    ret = enqueue(q, x);
    EXPECT_EQ(ret != nullptr, true);
    EXPECT_EQ(ret->i == x, true);
    EXPECT_EQ(ret->next == NULL, true);
}

TEST(dequeue_4, N_1) {
    struct Q* q  = (struct Q*)malloc(sizeof(struct Q));
//    q.
//    EXPECT_EQ(t == nullptr, true);
//    EXPECT_EQ(t->i == 0, true);
//    EXPECT_EQ(t->queue != nullptr, true);
}



