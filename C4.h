#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct knot_t {
	int con_c;
	int* con_knots;
	bool visited;
}knot_t;

typedef struct queue_t {
	int elem_c;
	int* elems;
}queue_t;


void queue_init(queue_t* que);
void queue_push(queue_t* que, int pushEl);
int queue_pop(queue_t* que);

void insert_con(knot_t* all_knots, int knot_change, int knot_ins);
void get_con(knot_t* all_knots);

void bfs(knot_t* all_knots, queue_t* que);