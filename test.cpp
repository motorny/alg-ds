#include "pch.h"

extern "C" {
#include "C:/Users/Lenovo/source/repos/AlgC4/C4.c"
}
TEST(InitGraph, normalWork_returnValidPointer) {
	graph gr;
	InitGraph(&gr);
	ASSERT_TRUE(gr.size == 0);
	ASSERT_TRUE(gr.next == NULL);
}
TEST(PushGraph, nullPtr_returnOne) {
	graph* gr = NULL;
	ASSERT_TRUE(PushGraph(gr, 1) == 1);
}
TEST(PushGraph, normalWorkOneNode_returnZero) {
	graph* gr;
	InitGraph(gr);
	ASSERT_TRUE(PushGraph(gr, 1) == 0);
	ASSERT_TRUE(gr->next[0]== 1);
}
TEST(PushGraph, normalWorkTwoNode_returnZero) {
	graph* gr;
	InitGraph(gr);
	ASSERT_TRUE(PushGraph(gr, 1) == 0);
	ASSERT_TRUE(PushGraph(gr, 2) == 0);
	ASSERT_TRUE(gr->next[0] == 1);
	ASSERT_TRUE(gr->next[1] == 2);
}
TEST(PopGraph, nullPtr_returnMinusOne) {
	graph* gr = NULL;
	ASSERT_TRUE(PopGraph(gr) == -1);
}
TEST(PopGraph, emptyQueue_returnMinusOne) {
	graph* gr;
	InitGraph(gr);
	ASSERT_TRUE(PopGraph(gr) == -1);
}
TEST(PopGraph, normalWork_returnCorrectNumber) {
	graph* gr;
	InitGraph(gr);
	PushGraph(gr, 1);
	int result = PopGraph(gr);
	ASSERT_EQ(result, 1);
}