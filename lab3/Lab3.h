#ifndef LABC3_H__INCLUDED__
#define LABC3_H__INCLUDED__
#pragma once

#ifdef cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>


#define FAIL 0
#define SUCCESS 1

#define HAVE 1
#define NOT_HAVE 0

	typedef struct {
		int* arr;
		int size;
		int head;
		int tail;
	} queue_t;

	typedef struct {
		int* edges;
		int numE;
	} node_t;

	typedef struct {
		node_t* tops;
		int numT;
	} adjacency_list_t;

	void ReadAdjacencyList(adjacency_list_t* list);
	int CreateQ(queue_t* q, int size);
	int AddInTail(queue_t* q, int nextTop);
	int GetFromHead(queue_t* q, int* oldEl);
	void DeleteQ(queue_t* q);

	int BreadthFirstSearch(adjacency_list_t* list, queue_t* q);

#endif //LABC3_H__INCLUDED__ #pragma once
