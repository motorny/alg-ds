#pragma once


typedef int data_t;

typedef struct node_t {
	data_t data;
	struct node_t* next;
} node_t;

typedef struct {
	node_t* head;
} plenty_t;

enum bool_t {
	FALSE,
	TRUE,
	NaN = -1
};

enum del_t {
	ALL = 1,
	FIRST
};

plenty_t* CreateZeroPlenty(void);
void FillPlenty(plenty_t* A, int size, data_t step);
void DestroyPlenty(plenty_t* A);

void AddInPlenty(plenty_t* A, data_t item);
int DelFromPlenty(plenty_t* A, data_t item, int delType);
int IsIncludeInPlenty(plenty_t* A, data_t item);

plenty_t* PlentyMerge(plenty_t* A, plenty_t* B);
plenty_t* PlentyUnion(plenty_t* A, plenty_t* B);

void PrintPlenty(plenty_t* A);